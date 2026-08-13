#pragma once

#ifndef _OFFLINE_REPAIR_H_
#define _OFFLINE_REPAIR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#ifndef NDEBUG
	#define DEBUG
#endif  // !NDEBUG

#define FILE_NAME_LEN 8

#define INNER_TRUE 1
#define INNER_FALSE 0
// IS_INDEPENDENT_TOOLS	为 INNER_TRUE 代表编译后该工具作为独立运行的存在	（回显用户提示信息）
//						为 INNER_FALSE 代表被其他工具调用的存在			（不回显用户提示信息）
#define IS_INDEPENDENT_TOOLS INNER_TRUE

// 定义宏函数 PAUSE，用于暂停屏幕查看回显结果
#if IS_INDEPENDENT_TOOLS == INNER_FALSE
	#define PAUSE()																					\
		system("pause>nul");
#else
	#define PAUSE()
#endif
// 定义宏函数 EXIT_ERROR，用于处理遇到各种错误后执行退出的代码
#define EXIT_ERROR()																				\
	PAUSE();																						\
	exit(EXIT_FAILURE);
// 定义宏函数 EXIT_MESSAGE，用于处理失败后提示信息并退出
#define EXIT_MESSAGE(bIsSuccess, _Format, ...)														\
	if (bIsSuccess == FALSE) {																		\
		printf_s(_Format, ##__VA_ARGS__);															\
		EXIT_ERROR();																				\
	}
// 定义宏函数 SPRINTF_S，用于简化 sprintf_s 函数
#define SPRINTF_S(_Buffer, _Format, ...)															\
	sprintf_s(_Buffer, MAX_PATH, _Format, ##__VA_ARGS__)
// 定义宏函数 MALLOC，用于分配内存
#define MALLOC(type, nSize)																			\
	(type *)malloc(sizeof(type) * (nSize))
// 定义宏 FREE_POINTER，用于释放不必要的指针
#define FREE_POINTER(pointer)																		\
	if (pointer != NULL) {																			\
		free(pointer);																				\
		pointer = NULL;																				\
	}
// 定义宏 CHECK_POINTER，用于检查指定指针是否被成功创建
#ifdef DEBUG
	#define CHECK_POINTER(pointer)																	\
		if (pointer == NULL) {																		\
			printf_s("文件：%s，函数：%s，行数：%d\t", __FILE__, __FUNCTION__, __LINE__);			\
			printf_s("创建指针 ["#pointer"] 失败！\n");												\
			EXIT_ERROR();																			\
		}
#else
	#define CHECK_POINTER(pointer)																	\
		if (pointer == NULL) {																		\
			printf_s("创建指针 ["#pointer"] 失败！\n");												\
			EXIT_ERROR();																			\
		}
#endif // DEBUG

#endif // !_OFFLINE_REPAIR_H_
