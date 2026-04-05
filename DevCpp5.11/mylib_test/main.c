#define MY_DEBUG 1

#include "../mylib/mylib.h"

#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	printf("mylib版本：%s\n", get_ver());
	
	for (int i = 0; i < 3; i++) {
		DEBUG_MSG("当前是调试版：%d\n", i);
	} 
	
	char *str = "123a4";
	printf("测试字符串是否纯数字：%d\n", is_digit(str));
	
	char *path = "C:\\Windows\\explorer.exe";
	printf("文件 %s 是否存在：%d\n", path, is_exist(path));
	
	char c = 'a';
	printf("字符串 %s 中正序字符 %c 的位置为：%d\n", str, c, get_idx_by_char(str, c, true));
	printf("查找失败返回：%d\n", IDX_NOT_FIND);
	
	printf("\n");
	system("pause >nul");
	
	return 0;
}
