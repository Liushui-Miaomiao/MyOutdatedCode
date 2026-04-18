#pragma once

#ifndef _CHECK_ENVIRONMENT_H_
#define _CHECK_ENVIRONMENT_H_

#include <stdio.h>
#include <Windows.h>

#ifndef NDEBUG
#define DEBUG
#endif  // !NDEBUG

// 定义宏函数 PAUSE，用于暂停屏幕查看回显结果
#define PAUSE()																						\
	system("pause>nul");
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


#endif // !_CHECK_ENVIRONMENT_H_
