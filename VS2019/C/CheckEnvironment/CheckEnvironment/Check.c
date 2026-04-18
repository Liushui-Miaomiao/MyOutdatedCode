#include <io.h>
#include "Check.h"
#include "Folder.h"

#pragma comment(lib, "WinMM.lib")

// 检查 .NET FRAME 组件
BOOL CheckNetFrame(void) {
	BOOL bResult = FALSE;

	LPSTR lpSystemPath = MALLOC(CHAR, MAX_PATH);								// 取 Windows\System32 目录
	CHAR  lpMscoreeDll[MAX_PATH];												// mscoree.dll 完整路径
	EXIT_MESSAGE(GetSystemDirectoryA(lpSystemPath, MAX_PATH), "获取用户 [System] 目录失败！");
	CHECK_POINTER(lpSystemPath);
	SPRINTF_S(lpMscoreeDll, "%s\\mscoree.dll", lpSystemPath);

	if (!_access(lpMscoreeDll, 0)) {
		bResult = TRUE;
	}

	return bResult;
}

// 检查 AssetCache 缓存
BOOL CheckAssetCache(void) {
	LPSTR lpAppDataPath = NULL;													// 取用户 %AppData% 目录
	EXIT_MESSAGE(!_dupenv_s(&lpAppDataPath, (size_t*)0, "AppData"), "获取用户 [APPTATA] 目录失败！");
	CHECK_POINTER(lpAppDataPath);

	CHAR lpAdobeCachePath[MAX_PATH];											// 取 %AppData%\Adobe\Flash Player\AssetCache 目录
	SPRINTF_S(lpAdobeCachePath, "%s\\Adobe\\Flash Player\\AssetCache", lpAppDataPath);
	FREE_POINTER(lpAppDataPath);

	LPSTR lpSubdirectoryArray[MAX_PATH];										// 定义子目录数组和子目录数量
	UINT nSubdirectoryNumber = GetSubdirectoryNumber(lpAdobeCachePath, lpSubdirectoryArray);
	if (nSubdirectoryNumber == 0) {
		return FALSE;
	}

	CHAR lpHeuPath[MAX_PATH], lpSwzPath[MAX_PATH], lpTxtPath[MAX_PATH];			// 定义 HEU、SWZ 和 TXT 文件路径
	for (UINT i = 0; i < nSubdirectoryNumber; i++) {
		SPRINTF_S(lpHeuPath, "%s\\8F903698240FE799F61EEDA8595181137B996156.heu", lpSubdirectoryArray[i]);
		SPRINTF_S(lpSwzPath, "%s\\8F903698240FE799F61EEDA8595181137B996156.swz", lpSubdirectoryArray[i]);
		SPRINTF_S(lpTxtPath, "%s\\cacheSize.txt", lpSubdirectoryArray[i]);

		if (!_access(lpHeuPath, 0) && !_access(lpSwzPath, 0) && !_access(lpTxtPath, 0)) {
			return TRUE;														// 三个关键文件都存在，返回真
		}
	}

	return FALSE;
}

// 检查声卡设备
BOOL CheckSoundCard(void) {
	/* 
	 * UINT waveOutGetNumDevs function (mmeapi.h)（需包含 WinMM.lib 库）
	 * https://docs.microsoft.com/zh-cn/windows/win32/api/mmeapi/nf-mmeapi-waveoutgetnumdevs?redirectedfrom=MSDN
	 * waveOutGetNumDevs 函数检索系统中存在的波形音频输出设备的数量。
	 * 
	 * 返回值 返回设备数。返回值为零表示不存在任何设备或发生错误。
	 * 
	 */
	return (BOOL)waveOutGetNumDevs() > 0;
}