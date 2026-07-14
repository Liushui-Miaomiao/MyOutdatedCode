/**
 * 工具类
 * 包含了一些实用方法
 */

#include "utils.h"
#include "dec.h"
#include <ctype.h>
#include <unistd.h>
#include <windows.h>

extern char *g_exts[EXTS_LEN][2];
extern char *g_txt_exts[TXT_EXTS_LEN];

static const char g_dot   = '.';			// 点
static const char g_slash = '\\';			// 反斜杠

static int get_idx_by_char(const char *str, const char c, int reverse);

// 调试版本区域
////////////////////////////////////////////////////////////
#if defined(DEBUG) && DEBUG == 1

/**
 * @brief 输出调试信息
 * 
 * @param ... 地址
 * @param format 格式控制串 
 */
void debug_msg(const char *format, ...) {
	va_list parameters;
	va_start(parameters, format);
	
	char msg[_MAX_PATH];
	vsnprintf(msg, _MAX_PATH, format, parameters);
	va_end(parameters);
	
	printf("%s", msg);
}

#endif
////////////////////////////////////////////////////////////

/**
 * @brief 判断指定字符串是否为纯数字
 * 
 * @param str 欲检测字符串
 * 
 * @return 是否为纯数字
 */
int is_digit(const char *str) {
	int result = 1;
	int len = strlen(str);
	
	for (int i = 0; i < len; i++) {
		// 判断指定字符是否为数字
		if (!isdigit(str[i])) {
			result = 0;
			break;
		}
	}
	
	return result;
}

/**
 * @brief 获取程序当前名称
 * 
 * @param name 存放名称的地址
 * 
 * @return 返回当前程序名称
 */
int get_current_name(char *name) {
	char temp[_MAX_PATH];
	DWORD dwRet = GetModuleFileNameA(NULL, (CHAR *)temp, _MAX_PATH);
	
	// dwRet 为 0 代表获取失败
	if (dwRet == 0) {
		return 0;
	}
	
	DEBUG_MSG("当前路径：%s\n", temp);
	
	int dot_pos, slash_pos;
	dot_pos = get_idx_by_char(temp, g_dot, 0);
	slash_pos = get_idx_by_char(temp, g_slash, 0);
	
	DEBUG_MSG("点的位置：%d，斜杠的位置：%d\n", get_idx_by_char(temp, g_dot, 0), get_idx_by_char(temp, g_slash, 0));
	// 如果找不到点或斜杠位置，或者点的位置比斜杠靠前，
	// 代表文件无扩展名，则返回。
	if (dot_pos == -1 || slash_pos == -1 || dot_pos < slash_pos) {
		return 0;
	}
	
	int name_len = dot_pos - slash_pos - 1;
	memcpy(name, temp + slash_pos + 1, name_len);
	name[name_len] = '\0';
	
	DEBUG_MSG("获取到的名字：%s\n", name);
	
	return 1;
}

/**
 * @brief 判断指定路径文件是否存在
 * 
 * @param path 欲测试的文件
 * 
 * @return 返回文件是否存在
 */
int is_exist(const char *path) {
	/**
	 * 函数参考：https://blog.csdn.net/qq_37858386/article/details/102976154
	 * 
	 * int access(const char *pathname, int mode)
	 * mode 取值：
	 * R_OK 是否具有读权限
	 * W_OK 是否具有写权限
	 * X_OK 是否具有可执行权限
	 * F_OK 文件是否存在
	 * 
	 * 返回 0 代表成功执行，-1 代表失败。
	 */
	if (access(path, F_OK) == -1) {
		return 0;
	}
	
	return 1;
}

/**
 * @brief 判断是否是 BVN 的加密文件
 * 
 * @param info 文件信息结构体
 * 
 * @return 是否是 BVN 的加密文件
 */
int is_enc_file(struct FILE_info *info) {
	if (!get_file_ext(info)) {
		return 0;
	}
	
	DEBUG_MSG("开始检测扩展名\n");
	
	for (int i = 0; i < EXTS_LEN; i++) {
		if (!strcmp(g_exts[i][0], info->enc_ext)) {
			DEBUG_MSG("是加密文件\n");
			return 1;
		}
	}
	
	return 0;
}

/**
 * @brief 获取文件扩展名
 * 
 * @param info 文件信息结构体
 * 
 * @return 是否成功获取扩展名
 */
int get_file_ext(struct FILE_info *info) {
	int dot_pos, slash_pos;
	dot_pos   = get_idx_by_char(info->enc_path, g_dot,   0);
	slash_pos = get_idx_by_char(info->enc_path, g_slash, 0);
	
	// 如果找不到点或斜杠位置，或者点的位置比斜杠靠前，
	// 代表文件无扩展名，则返回。
	if (dot_pos == -1 || slash_pos == -1 || dot_pos < slash_pos) {
		return 0;
	}
	
	int ext_len = strlen(info->enc_path) - dot_pos - 1;
	memcpy(info->enc_ext, info->enc_path + dot_pos + 1, ext_len);
	info->enc_ext[ext_len] = '\0';
	
	DEBUG_MSG("获取到的扩展名：%s\n", info->enc_ext);
	
	return 1;
}

/**
 * @brief 获得文件大小（字节为单位）
 * 
 * @param file 文件指针
 * 
 * @return 获取到的大小
 */
#define METHOD 1						// 实现方式
uint32_t get_file_size(FILE *file) {
	if (file == NULL) {
		return 0;
	}
	
	uint32_t size = 0;
#if defined(METHOD) && METHOD == 0
	DEBUG_MSG("获取方式1\n");
	
	while (1) {
		fgetc(file);
		if (feof(file)) {
			break;
		}
		
		size++;
	}
	
#else
	DEBUG_MSG("获取方式2\n");
	
	if (fseek(file, 0, SEEK_END)) {
		return 0;
	}
	
	size = ftell(file);
	
#endif
	// 将文件指针复位到开始区域
	rewind(file);
	
	return size;
}

/**
 * @brief 根据旧的扩展名查询新扩展名
 * 
 * @param info 文件信息结构体
 * 
 * @return 是否成功获取原版扩展名
 */
int get_org_ext(struct FILE_info *info) {
	for (int i = 0; i < EXTS_LEN; i++) {
		if (!strcmp(g_exts[i][0], info->enc_ext)) {
			int len = strlen(g_exts[i][1]);
			memcpy(info->org_ext, g_exts[i][1], len);
			info->org_ext[len] = '\0';
			DEBUG_MSG("加密的扩展名：%s，原始的扩展名：%s\n", info->enc_ext, info->org_ext);
			return 1;
		}
	}
	
	return 0;
}

/**
 * @brief 根据传入的加密扩展名，查找表内是否是文本类型的加密文件
 * 
 * @param info 文件信息结构体
 * 
 * @return 是否是文本型文件
 */
int is_txt_file(const struct FILE_info *info) {
	for (int i = 0; i < TXT_EXTS_LEN; i++) {
		if (!strcmp(g_txt_exts[i], info->enc_ext)) {
			DEBUG_MSG("是加密的文本类型文件\n");
			return 1;
		}
	}
	
	return 0;
}

/**
 * @brief 修改文件路径的扩展名
 * 
 * @param info 文件信息结构体
 * 
 * @return 是否成功修改
 */
int change_ext(struct FILE_info *info) {
	int dot_pos = get_idx_by_char(info->enc_path, g_dot, 0);
	if (dot_pos == -1) {									// 其实此处没必要再做判断，前置函数足够了，
		return 0;											// 但为了保持工具类的标准，需要设计一个返回值
	}
	
	int dot_next_pos = dot_pos + 1;							// +1 为了把点也直接复制上
	memcpy(info->org_path, info->enc_path, dot_next_pos);
	info->org_path[dot_next_pos] = '\0';
	
	int path_len, ext_len;
	path_len = strlen(info->enc_path);
	ext_len = strlen(info->org_ext);
	DEBUG_MSG("path_len = %d, ext_len = %d\n", path_len, ext_len);
	if (path_len + ext_len > _MAX_PATH) {					// 判断长度是否溢出
		return 0;
	}
	
	char *temp = MALLOC(char, ext_len + 1);
	if (temp == NULL) {
		return 0;
	}
	memcpy(temp, info->org_ext, ext_len);
	temp[ext_len] = '\0';
	strcat(info->org_path, temp);							// 连接文件名与扩展名
	
	DEBUG_MSG("info->org_path = %s\n", info->org_path);
	
	FREE(temp);
	
	return 1;
}


////////////////////////////////////////////////////////////
// 静态函数区域
/**
 * @brief 查找指定字符第一次出现在字符串里的位置
 * 
 * @param c 指定字符
 * @param reverse 是否为正序，1 为正序查找，0 为倒序查找
 * @param str 目标字符串
 * 
 * @return 指定字符第一次出现在字符串里的索引
 */
static int get_idx_by_char(const char *str, const char c, int reverse) {
	int i, len;
	len = strlen(str);
	
	// 正序查找
	if (reverse) {
		for (i = 0; i < len; i++) {
			if (str[i] == c) {
				return i;
			}
		}
		
		return -1;
	}
	
	// 倒序查找
	for (i = len - 1; i >= 0; i--) {
		if (str[i] == c) {
			return i;
		}
	}
	
	return -1;
}
////////////////////////////////////////////////////////////
