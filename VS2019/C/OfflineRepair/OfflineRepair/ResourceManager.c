#include "ResourceManager.h"

// 将指定 ID 的资源释放到指定目录
BOOL ReleaseResource(LPCSTR lpName, LPCSTR lpType, LPCSTR lpFileName) {
	BOOL bResult = TRUE;
	HRSRC hResource = FindResourceA(GetModuleHandle(NULL), lpName, lpType);
	if (hResource) {
		HGLOBAL hResourceData = LoadResource(GetModuleHandle(NULL), hResource);
		if (!hResourceData) {
			return FALSE;
		}

		LPVOID	pData	= LockResource(hResourceData);
		DWORD	dwSize	= SizeofResource(GetModuleHandle(NULL), hResource);
		HANDLE	hFile	= CreateFileA(lpFileName, 
			GENERIC_WRITE, 
			FILE_SHARE_WRITE, 
			NULL, 
			CREATE_ALWAYS, 
			FILE_ATTRIBUTE_NORMAL, 
			NULL
		);
		DWORD dwBytesWritten = 0;

		if (!WriteFile(hFile, (LPVOID)pData, dwSize, &dwBytesWritten, NULL)) {
			bResult = FALSE;
		}
		CloseHandle(hFile);
	}
	
	return bResult;
}