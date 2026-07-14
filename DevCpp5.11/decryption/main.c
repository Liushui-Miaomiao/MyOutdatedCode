#define VERSION "0.12"

/**
 * 程序设计构思：
 * usage 能够显示自身名称
 * 附带可选参数 --frontsize --endsize 以应对官方修改加密大小
 * 以后可能支持对于 key 和 iv 的修改支持，但有点困难
 * 首先 as3 的 aes 算法有个漏洞，对于长度判断有误，
 * 接着就是 key 和 iv 都有问题，强制把字符串（里面带有十六进制外其他字母和特殊符号）
 * 转换成十六进制数组，结果解析毫无疑问是有问题的，得到的数组根本不是字符串的字节数组，
 * 结果就导致了个很尴尬的问题，为了在 C 中还原这个漏洞，不得不魔改了原版 aes 数据访问方式，
 * 我猜目前这个 aes 算法已经不能正常使用了，所以导致如果后期官方更换了 key iv 的长度和内容，
 * 假如恰好又格式正确了，比如 key iv 都变成正常的 16 倍数而不是现在的 20，
 * 那么这个解密工具就废了
 * 以上就是对这个工具的一些简单总结
 */

#include "stdafx.h"
#include "utils.h"
#include "dec.h"
#include <getopt.h>

#define DEFAULT_FRONT_SIZE 1024				// 定义默认头大小
#define DEFAULT_END_SIZE   1024				// 定义默认尾大小

// 全局变量，加密头尾大小
struct SIZE_En g_size;

/**
 * @brief 用法
 * 
 * @param path 路径 
 * 
 * @param void 
 */
void usage(void) {
	char name[_MAX_PATH];
	if (!get_current_name(name)) {
		printf("获取自身名称失败！\n");
		goto EXIT;
	}
	
	printf(
		"用法：\n"
		"%s\n"
		"      [-h 显示本帮助] \n"
		"      [-f 加密头长度，默认 %d] \n"
		"      [-e 加密尾长度，默认 %d] \n"
		"       -i 要解密的文件路径\n", 
		name, DEFAULT_FRONT_SIZE, DEFAULT_END_SIZE
	);
	
EXIT:
	exit(1);
}

/**
 * @brief 主函数，程序入口
 * 
 * @param argc 
 * @param argv 
 * 
 * @return 
 */
int main(int argc, char *argv[]) {
	DEBUG_MSG("当前处于调试模式下\n");
	printf("BVN 3.6+ 版本资源解密器 V%s\n", VERSION);
	
	if (argc < 2) {
		usage();
	}
	
	// 初始化加密结构体头尾大小
	g_size.front = DEFAULT_FRONT_SIZE;
	g_size.end   = DEFAULT_END_SIZE;
	
	/**
	 * 命令行参数解析参考：
	 * https://blog.csdn.net/loophome/article/details/50700267
	 * https://www.jianshu.com/p/a86315d20ba4
	 */
	const char *options = "hf:e:i:";
	
	// 关闭 getopt 打印出错信息
	opterr = 0;
	int ret;
	while((ret = getopt(argc, argv, options)) != -1) {
		switch (ret) {
		case 'f':
		case 'e':
			// 检测是否是纯数字
			if (!is_digit(optarg)) {
				printf("参数 -%c 不是纯数字！\n", ret);
				break;
			}
			int size = atoi(optarg);
			
			// 设置头尾大小
			int *p_size = (int *)(ret == 'f' ? &g_size.front : &g_size.end);
			*(p_size) = size;
			break;
		case 'i':
			DEBUG_MSG("要处理的文件路径：%s\n", optarg);
			
			// 开始解密
			return init(optarg);
			break;
		case 'h':
		default:
			usage();
			break;
		}
	}
	DEBUG_MSG("g_size.front = %d, g_size.end = %d\n", g_size.front, g_size.end);
	
	/**
	 * optind 指向整理后参数列表中未识别的第一个参数，执行完上面那些后，
	 * 所有参数都会被重新排列，未识别的靠后排列
	 * 参考：https://blog.csdn.net/chaoyue1216/article/details/7329788
	 */
	DEBUG_MSG("argc = %d, optind = %d\n",argc, optind);
	
	// 输出所有未被识别的参数
	if (optind != argc) {
		printf("未识别的参数：");
		for (int i = optind; i < argc; i++) {
			printf("%s, ", argv[i]);
		}
		printf("\n");
		
		return 1;
	}
	
	return 0;
}
