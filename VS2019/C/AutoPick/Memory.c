/************************************************************************/
/*                       Memory.c - 内存操作实现文件                    */
/*                                                                      */
/* 包含对于 Windows 进程内存的部分操作                                  */
/*                                                                      */
/************************************************************************/

// -----------------------------------------------------------------------
// INCLUDE
#include "Memory.h"
#include <STDARG.H>

// -----------------------------------------------------------------------
// 宏定义

// -----------------------------------------------------------------------
// 全局变量声明

// -----------------------------------------------------------------------
// 函数声明

/******************************************
 * @brief 计算最终内存
 * 
 * @param [in] hProcess		进程句柄
 * @param [in] dwBaseAddr	进程内存基址
 * @param [in] dwSize		数据类型大小
 * @param [in] nLen			可变参数长度
 * @param [in] args			可变参数
 * @return 返回经计算的最终的内存
 ******************************************/
static DWORD 
GetMemory
(HANDLE hProcess, DWORD dwBaseAddr, DWORD dwSize, int nLen, va_list args); 

// -----------------------------------------------------------------------
// 函数定义

/******************************************
 * @brief 计算最终内存
 * 
 * @param [in] hProcess		进程句柄
 * @param [in] dwBaseAddr	进程内存基址
 * @param [in] dwSize		数据类型大小
 * @param [in] nLen			可变参数长度
 * @param [in] args			可变参数
 * @return 返回经计算的最终的内存
 ******************************************/
static DWORD 
GetMemory
(HANDLE hProcess, DWORD dwBaseAddr, DWORD dwSize, int nLen, va_list args) 
{
	// --------------------------------------------------------------------
	// 函数局部变量处理

	// 局部变量声明
	int		i			;									/* 计次变量 */
	DWORD	dwTempAddr	;									/* 临时地址 */

	// 局部变量初始化
	dwTempAddr = dwBaseAddr;

	// --------------------------------------------------------------------
	// 函数体

	// 如果读取长度为 0，直接返回基址
	if (!nLen) {
		goto CLOSE;
	}

	// 读取字节大小最多为 4 字节
	if (dwSize > 4) {
		dwSize = 4;
	}

	// 根据所需的读取级别，循环读取内存内容
	for (i = 0; i < nLen; i++) {
		ReadProcessMemory(
			hProcess, (LPCVOID)dwTempAddr, &dwTempAddr, dwSize, NULL
		);

		dwTempAddr += va_arg(args, DWORD);
	}

	// --------------------------------------------------------------------
	// 函数返回前需要处理的过程
CLOSE:
	va_end(args);
	// --------------------------------------------------------------------
	// 函数返回值
//RET:
	return dwTempAddr;
}

/******************************************
 * @brief 读取指定内存数据
 * 
 * @param [in] hProcess		进程句柄
 * @param [in] dwBaseAddr	进程内存基址
 * @param [in] dwSize		数据类型大小
 * @param [in] nLen			可变参数长度
 * @param [in] args			可变参数
 * @return 返回指定内存数据
 ******************************************/
DWORD 
ReadMemory
(HANDLE hProcess, DWORD dwBaseAddr, DWORD dwSize, int nLen, ...) 
{
	// --------------------------------------------------------------------
	// 函数局部变量处理

	// 局部变量声明
	va_list args	;										/* 可变参数 */
	DWORD 	dwValue	;										/* 读取数值 */

	// 局部变量初始化
	va_start(args, nLen);
	
	// --------------------------------------------------------------------
	// 函数体

	// 根据基址和偏移得到目标地址
	dwBaseAddr = GetMemory(hProcess, dwBaseAddr, dwSize, nLen, args);
	va_end(args);

	// 读取内存
	ReadProcessMemory(
		hProcess, (LPCVOID)dwBaseAddr, &dwValue, dwSize, NULL
	);

	// --------------------------------------------------------------------
	// 函数返回前需要处理的过程
//CLOSE:

	// --------------------------------------------------------------------
	// 函数返回值
//RET:
	return dwValue;
}

/******************************************
 * @brief 写入指定内存数据
 * 
 * @param [in] hProcess		进程句柄
 * @param [in] dwBaseAddr	进程内存基址
 * @param [in] dwValue		数据值
 * @param [in] dwSize		数据类型大小
 * @param [in] nLen			可变参数长度
 * @param [in] args			可变参数
 * @return 返回写入内存数据是否成功
 ******************************************/
BOOL 
WriteMemory
(HANDLE hProcess, DWORD dwBaseAddr, DWORD dwValue, DWORD dwSize, int nLen, ...) 
{
	// --------------------------------------------------------------------
	// 函数局部变量处理

	// 局部变量声明
	BOOL 	bRet;											/* 函数结果 */
	va_list args;											/* 可变参数 */

	// 局部变量初始化
	va_start(args, nLen);

	// --------------------------------------------------------------------
	// 函数体

	// 根据基址和偏移得到目标地址
	dwBaseAddr = GetMemory(hProcess, dwBaseAddr, dwSize, nLen, args);
	va_end(args);

	// 写入内存
	bRet = WriteProcessMemory(
		hProcess, (LPVOID)dwBaseAddr, &dwValue, dwSize, NULL
	);

	// --------------------------------------------------------------------
	// 函数返回前需要处理的过程
//CLOSE:

	// --------------------------------------------------------------------
	// 函数返回值
//RET:
	return bRet;
}
