#include "mylib.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 获取版本
 * 
 * @return 当前版本
 */
char* get_ver(void) {
	return MYLIB_VER;
}

//--------------------------------------------------
/** 调试版本区域 **/

#include <stdarg.h>
/**
 * @brief 输出调试信息
 * 
 * @param ...    地址
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

//--------------------------------------------------



//--------------------------------------------------
/** 函数域 **/

#include <string.h>
#include <ctype.h> 
/**
 * @brief 判断指定字符串是否为纯数字
 * 
 * @param str 欲检测字符串
 * 
 * @return 是否为纯数字
 */
bool is_digit(const char *str) {
	bool result = true;
	
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		// 判断指定字符是否为数字
		if (!isdigit(str[i])) {
			result = false;
			break;
		}
	}
	
	return result;
}

#include <unistd.h>
#include <io.h>
/**
 * @brief 判断指定路径文件是否存在
 * 
 * @param path 欲测试的文件
 * 
 * @return 返回文件是否存在
 */
bool is_exist(const char *path) {
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
		return false;
	}
	
	return true;
}

#include <string.h>
/**
 * @brief 查找指定字符第一次出现在字符串里的位置
 * 
 * @param c       指定字符
 * @param str     目标字符串
 * @param reverse 是否为正序，true 为正序查找，false 为倒序查找
 * 
 * @return 指定字符第一次出现在字符串里的索引
 */
int get_idx_by_char(const char *str, const char c, bool reverse) {
	int i, len;
	len = strlen(str);
	
	// 正序查找
	if (reverse) {
		for (i = 0; i < len; i++) {
			if (str[i] == c) {
				return i;
			}
		}
		
		return IDX_NOT_FIND;
	}
	
	// 倒序查找
	for (i = len - 1; i >= 0; i--) {
		if (str[i] == c) {
			return i;
		}
	}
	
	return IDX_NOT_FIND;
}

//--------------------------------------------------
