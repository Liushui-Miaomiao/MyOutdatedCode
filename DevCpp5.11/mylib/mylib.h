/**
 * MyLib 头文件
 * 使用前请检查目标编译方式不是是 32bit Release 
 */

#ifndef _MY_LIB_H_
#define _MY_LIB_H_

// 库版本
#define MYLIB_VER "0.1.1"

//--------------------------------------------------
/** 库引用 **/

#include <stdbool.h>

//--------------------------------------------------

/**
 * @brief 获取版本
 * 
 * @return 当前版本
 */
char* get_ver(void);

//--------------------------------------------------
/** 调试宏 **/

// 设置是否为调试模式
#ifndef MY_DEBUG
	// 0 为正式版，1 为调试版
	#define MY_DEBUG 0
#endif

#if defined(MY_DEBUG) && MY_DEBUG == 1
	/**
	 * @brief 输出调试信息
	 * 
	 * @param ...    地址
	 * @param format 格式控制串
	 */
	void debug_msg(const char *format, ...);
	#define DEBUG_MSG(_Format, ...)			\
		debug_msg(_Format, ##__VA_ARGS__);
#else
	#define DEBUG_MSG(_Format, ...)
#endif

//--------------------------------------------------



//--------------------------------------------------
/** 常用宏 **/

// 申请内存简写宏
#define MALLOC(type, size)						\
	(type *)malloc(sizeof(type) * (size))
// 释放内存简写宏
#define FREE(pointer)							\
	if (pointer != NULL) {						\
		free(pointer);							\
		pointer = NULL;							\
	}

//--------------------------------------------------



//--------------------------------------------------
/** 函数原型 **/

/**
 * @brief 判断指定字符串是否为纯数字
 * 
 * @param str 欲检测字符串
 * 
 * @return 是否为纯数字
 */
bool is_digit(const char *str);

/**
 * @brief 判断指定路径文件是否存在
 * 
 * @param path 欲测试的文件
 * 
 * @return 返回文件是否存在
 */
bool is_exist(const char *path); 

// 找不到字符的默认索引 
#define IDX_NOT_FIND -1
/**
 * @brief 查找指定字符第一次出现在字符串里的位置
 * 
 * @param c       指定字符
 * @param str     目标字符串
 * @param reverse 是否为正序，true 为正序查找，false 为倒序查找
 * 
 * @return 指定字符第一次出现在字符串里的索引
 */
int get_idx_by_char(const char *str, const char c, bool reverse);

#endif
