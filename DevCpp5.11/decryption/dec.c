/**
 * 解密类
 * 包含了解密文件所需要的核心代码以及调用三方库代码
 */

#include "dec.h"
#include "utils.h"
#include "aes.h"

#define _ERROR_ 1
#define _SUCCESS_ 0

extern struct SIZE_En g_size;

// KEY -> kan%ni%zen%me%po!*wo*ye*hen*wu*nai*a*
// 这是 AS3 中，KEY 转换为字节数组的内容
static const uint8_t g_KEY[20] = {
	0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 
	0x00, 0x00, 0x0a, 0x00
};
// IV -> buyao(zenzhala(gaotaiguishouba####(x_x) 20
// 这是 AS3 中，IV 转换为字节数组的内容
static const uint8_t g_IV[16] = {
	0x0b, 0x00, 0x0a, 0x00, 0x0e, 0x00, 0x0a, 0x0a, 
	0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x0a
};
// 加密扩展名对应原版扩展名的对照表
const char *g_exts[EXTS_LEN][2] = {
	{"j" , "json"},
	{"x" , "xml" },
	{"f" , "swf" },
	{"m3", "mp3" },
	{"pi", "png" },
	{"ji", "jpg" }
};
// 文本文件的加密扩展名
const char *g_txt_exts[TXT_EXTS_LEN] = {
	"j", "x"
};
// AES 解密所需的上下文
static struct AES_ctx g_cxt;

static int  package_info(struct FILE_info *info, const char *enc_path);
static int  do_dec(struct FILE_info *info);
static void dec(uint8_t *bytes, uint32_t size);

// 调试版本区域
////////////////////////////////////////////////////////////
#if defined(DEBUG) && DEBUG == 1

/**
 * @brief 打印结构体信息
 * 
 * @param info 
 */
void print_f_info(struct FILE_info *info) {
	DEBUG_MSG("info结构体信息：\n");
	DEBUG_MSG("info->enc_path = %s\n", info->enc_path);
	DEBUG_MSG("info->enc_ext  = %s\n", info->enc_ext);
	DEBUG_MSG("info->org_ext  = %s\n", info->org_ext);
	DEBUG_MSG("info->org_path = %s\n", info->org_path);
	DEBUG_MSG("info->is_txt   = %d\n", info->is_txt);
}

#define P_F_INFO(info)										\
	print_f_info(info);

#else

#define P_F_INFO(info)

#endif
////////////////////////////////////////////////////////////

/**
 * @brief 进行解密前初始化操作
 * 
 * @param path 要解密的文件路径
 * 
 * @return 返回初始化结果
 */
int init(const char *path) {
	// 先判断路径是否合法
	if (!is_exist(path)) {
		printf("无效的路径！%s\n", path);
		return _ERROR_;
	}
	
	// 开始处理文件路径信息，把所有信息封装起来
	struct FILE_info info;
	if (!package_info(&info, path)) {
		printf("打包信息失败！\n");
		return _ERROR_;
	}
	
	// 开始解密文件
	if (!do_dec(&info)) {
		printf("解密失败！\n");
		return _ERROR_;
	}
	
	return _SUCCESS_;
}

////////////////////////////////////////////////////////////
// 静态函数区域
/**
 * @brief 打包文件信息结构体
 * 
 * @param enc_path 加密路径
 * @param info 文件信息结构体
 * 
 * @return 是否打包成功
 */
static int package_info(struct FILE_info *info, const char *enc_path) {
	memcpy(info->enc_path, enc_path, _MAX_PATH);
	
	// 判断是否是BVN的加密文件，如果是，顺便把扩展名也获取出来
	if (!is_enc_file(info)) {
		printf("不是BVN的加密文件！%s\n", info->enc_path);
		return 0;
	}
	
	DEBUG_MSG("复核是否复制出文件扩展名：%s\n", info->enc_ext);
	
	// 根据加密的扩展名查找原始扩展名
	if (!get_org_ext(info)) {
		printf("查找失败！目标扩展名不在可解密列表中！扩展名：%s\n", info->enc_ext);
		return 0;
	}
	
	DEBUG_MSG("复核是否复制出原始的扩展名：%s\n", info->org_ext);
	
	// 写入是否是文本类型
	info->is_txt = is_txt_file(info);
	if (!change_ext(info)) {
		printf("修改扩展名失败！\n");
		return 0;
	}
	
	DEBUG_MSG("打包信息成功！\n");
	P_F_INFO(info);
	
	return 1;
}

/**
 * @brief 开始解密文件
 * 
 * @param info 
 * 
 * @return 
 */
static int do_dec(struct FILE_info *info) {
	int is_success = 1;								// 返回值
	int is_txt     = info->is_txt;					// 是否为文本类型
	
	char *path_in  = info->enc_path;				// 输入（加密）文件路径 
	char *path_out = info->org_path;				// 输出（解密）文件路径 
	
	FILE *file_in, *file_out;						// 加密文件和输出文件的文件流
	
	file_in  = fopen(path_in , "rb");
	file_out = fopen(path_out, "wb");
	if (file_in == NULL || file_out == NULL) {
		printf("打开文件失败！\n");
		return 0;
	}
	
	DEBUG_MSG("打开输入输出文件成功！\n");
	
	// 总大小，头大小，中间大小，尾大小，头和尾总大小
	uint32_t total_size, front_size, center_size, end_size, front_end_size;
	total_size     = get_file_size(file_in);
	front_size     = (uint32_t)g_size.front;
	end_size       = (uint32_t)g_size.end;
	front_end_size = front_size + end_size;
	center_size    = total_size - front_end_size;
	
	DEBUG_MSG("total_size  = %u\n", total_size);
	DEBUG_MSG("front_size  = %u\n", front_size);
	DEBUG_MSG("center_size = %u\n", center_size);
	DEBUG_MSG("end_size    = %u\n", end_size);
	
	int uint8_size = sizeof(uint8_t);
	uint8_t *front_byte, *center_byte, *end_byte, *total_byte;
	
	total_byte = front_byte = center_byte = end_byte = NULL;
	
	int exp;										// 表达式的值
	int is_split = 									// 是否需要拆分解密
		!is_txt && 
		total_size > front_end_size
	;
	
	if (is_split) {
		front_byte  = MALLOC(uint8_t, front_size);
		end_byte    = MALLOC(uint8_t, end_size);
		center_byte = MALLOC(uint8_t, center_size);
	}
	else {
		total_byte  = MALLOC(uint8_t, total_size);
	}
	
	
	exp = 
		(
			is_split && 
			(
				front_byte  == NULL || 
				center_byte == NULL || 
				end_byte    == NULL
			)
		) || 
		(
			!is_split && total_byte == NULL
		); 
	if (exp) 
	{
		printf("申请内存失败！\n");
		goto ERR;
	}
	
	printf("正在读取文件中...\n");
	exp = 
		is_split ? 
		(
			fread(front_byte,  uint8_size, front_size,  file_in) < front_size  || 
			fread(center_byte, uint8_size, center_size, file_in) < center_size ||
			fread(end_byte,    uint8_size, end_size,    file_in) < end_size
		) : 
		(
			fread(total_byte,  uint8_size, total_size,  file_in) < total_size
		);
	if (exp){
		printf("读取文件内容失败！\n");
		goto ERR;
	}
	
	printf("开始解密文件...\n");
	if (is_split) {
		dec(front_byte, front_size);
		dec(end_byte,   end_size);
	}
	else {
		dec(total_byte, total_size);
	}
	printf("解密完成！\n");
	
	printf("开始写出文件...\n");
	exp = 
		is_split ? 
		(
			fwrite(front_byte,  uint8_size, front_size,  file_out) < front_size  || 
			fwrite(center_byte, uint8_size, center_size, file_out) < center_size ||
			fwrite(end_byte,    uint8_size, end_size,    file_out) < end_size
		) : 
		(
			fwrite(total_byte,  uint8_size, total_size,  file_out) < total_size
		);
	if (exp) {
		printf("写出文件内容失败！\n");
		goto ERR;
	}
	
	printf("写出文件内容成功！\n");
	goto EXIT;
	
ERR:
	is_success = 0;
EXIT:
	FREE(front_byte);
	FREE(end_byte);
	FREE(center_byte);
	FREE(total_byte);
	
	fclose(file_in);
	fclose(file_out);
	
	return is_success;
}

/**
 * @brief 开始解密文件
 * 
 * @param bytes 要解密的字节
 * @param size 大小
 * 
 * @return 
 */
static void dec(uint8_t *bytes, uint32_t size) {
	if (bytes == NULL) {
		return;
	}
	
	// 解密核心，调用相关函数
	AES_init_ctx_iv(&g_cxt, g_KEY, g_IV);
	AES_CBC_decrypt_buffer(&g_cxt, bytes, size);
}

////////////////////////////////////////////////////////////
