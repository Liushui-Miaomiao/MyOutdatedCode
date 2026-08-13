#include <stdio.h>
#include <string.h>
#include <direct.h>
#include <io.h>

#include "File.h"

static BOOL RemoveFile(LPCSTR lpPath);

// 创建目录
BOOL CreateFolder(LPCSTR lpPath) {
	BOOL bResult = FALSE;
	const CHAR SLASH = '\\';

	CHAR lpTemp[MAX_PATH];
	strcpy_s((char *)lpTemp, MAX_PATH, lpPath);

	int nLength = strlen(lpTemp);
	BOOL bIsFristSlash = FALSE;															// 是否第一次遇到 '\'
	for (int i = 0; i <= nLength; i++) {												// 遍历路径
		if (lpTemp[i] == SLASH) {														// 如果不是路径结尾
			if (!bIsFristSlash) {														// 判断是否是第一次出现 '\'
				bIsFristSlash = TRUE;													// 如果是代表应该为磁盘根目录，应该跳过
				continue;
			}
			lpTemp[i] = '\0';															// 如果不是磁盘根目录，那么把 '\' 修改为 '\0' 表示临时目录
			if (!_access(lpTemp, 0)) {													// 如果目录存在，把 '\0' 修改回 '\'，继续下一轮判断
				lpTemp[i] = SLASH;
				continue;
			}
			if (!CreateDirectoryA(lpTemp, NULL)) {										// 如果目录不存在，执行创建目录操作
				break;																	// 创建失败则结束循环
			}
			lpTemp[i] = SLASH;
			continue;																	// 不是路径结尾跳到下一轮判断
		}

		if (lpTemp[i] == '\0') {														// 如果处于路径结尾，说明到了最后一级目录，创建目录
			if (!_access(lpTemp, 0) || !CreateDirectoryA(lpTemp, NULL)) {				// 如果最后一级目录存在,跳出循环，不存在，执行创建目录操作
				break;																	// 创建失败则结束循环
			}
			bResult = TRUE;																// 以上条件都满足了，则证明创建成功，返回 TRUE
			break;
		}
	}

	return bResult;																		// 否则任何一个环节出问题都会返回 FALSE
}

// 删除指定目录，包括该目录下的所有子目录和文件
BOOL RemoveFolder(LPCSTR lpPath) {
	CHAR lpFilter[MAX_PATH];
	SPRINTF_S(lpFilter, "%s\\*.*", lpPath);

	CHAR lpTempPath[MAX_PATH];
	WIN32_FIND_DATA lpFindFileData;
	HANDLE hFindFile = FindFirstFileA(lpFilter, (LPWIN32_FIND_DATAA)&lpFindFileData);
	do {																				// 开始遍历目录
		if (strcmp((char *)lpFindFileData.cFileName, ".") && 
			strcmp((char *)lpFindFileData.cFileName, "..")) {							// 排除自身目录和父级目录
			SPRINTF_S(lpTempPath, "%s\\%s", lpPath, (char *)lpFindFileData.cFileName);

			if (lpFindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {			// 检查是否为子目录，是则递归继续检查
				EXIT_MESSAGE(RemoveFolder(lpTempPath), "移除文件夹 [%s] 失败！", lpTempPath);
			}
			else {																		// 否则是文件，执行删除文件操作
				EXIT_MESSAGE(RemoveFile(lpTempPath), "移除文件 [%s] 失败！", lpTempPath);
			}
		}
	} while (FindNextFileA(hFindFile, (LPWIN32_FIND_DATAA)&lpFindFileData));

	FindClose(hFindFile);																// 关闭句柄
	return !(BOOL)_rmdir(lpPath);														// 删除空目录
}

// 删除指定文件
static BOOL RemoveFile(LPCSTR lpPath) {
	return DeleteFileA(lpPath);
}