/**
 * 公用标准头文件
 * 需要被多个文件调用的公共信息集合
 * 例如公用头文件，公用结构体，以及特殊设置等
 */

#ifndef _STDAFX_H_
#define _STDAFX_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// 设置是否为调试模式
#ifndef DEBUG
	// 0 为正式版，1 为调试版 
	#define DEBUG 0
#endif
// 申请内存简写宏
#define MALLOC(type, size)						\
	(type *)malloc(sizeof(type) * (size))
// 释放内存简写宏
#define FREE(pointer)							\
	if (pointer != NULL) {						\
		free(pointer);							\
		pointer = NULL;							\
	}

// 加密信息结构体
struct SIZE_En {
	int front;									// 头字节数
	int end;									// 尾字节数
};

// 文件信息结构体
struct FILE_info {
	char enc_path[_MAX_PATH];					// 加密文件路径
	char enc_ext[_MAX_EXT];						// 加密文件后缀
	char org_ext[_MAX_EXT];						// 原本文件后缀
	char org_path[_MAX_PATH];					// 原本文件路径
	int is_txt;									// 是否文本文件
};

#endif
