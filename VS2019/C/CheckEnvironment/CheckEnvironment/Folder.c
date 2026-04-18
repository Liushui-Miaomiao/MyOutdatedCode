#include "Folder.h"

// 取指定目录的子目录数量并返回子目录数组
UINT GetSubdirectoryNumber(LPCSTR lpPath, LPSTR* lpSubdirectoryArray) {
	UINT nSubdirectoryNumber = 0;														// 子目录计数器
	
	CHAR lpFilter[MAX_PATH];
	SPRINTF_S(lpFilter, "%s\\*.*", lpPath);

	WIN32_FIND_DATA lpFindFileData;
	HANDLE hFindFile = FindFirstFileA(lpFilter, (LPWIN32_FIND_DATAA)&lpFindFileData);
	do {																				// 开始遍历目录
		if (strcmp((char*)lpFindFileData.cFileName, ".") &&
			strcmp((char*)lpFindFileData.cFileName, "..")) {							// 排除自身目录和父级目录
			LPSTR lpTempPath = MALLOC(CHAR, MAX_PATH);
			CHECK_POINTER(lpTempPath);
			SPRINTF_S(lpTempPath, "%s\\%s", lpPath, (char*)lpFindFileData.cFileName);

			if (lpFindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {			// 检查是否为子目录，是则加入数组并增加计数
				lpSubdirectoryArray[nSubdirectoryNumber] = lpTempPath;
				nSubdirectoryNumber++;
			}
		}
	} while (FindNextFileA(hFindFile, (LPWIN32_FIND_DATAA)&lpFindFileData));

	return nSubdirectoryNumber;
}