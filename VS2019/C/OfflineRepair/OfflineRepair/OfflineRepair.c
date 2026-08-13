#include <io.h>

#include "Random.h"
#include "resource.h"
#include "ResourceManager.h"
#include "File.h"
#include "OfflineRepair.h"

// 定义宏函数 CREATE_FOLDER，用于简化创建目录
#define CREATE_FOLDER(lpPath)																		\
	if (!_access(lpPath, 0)) {												/* 先清空目录 */		\
		EXIT_MESSAGE(RemoveFolder(lpPath), "移除文件夹 [%s] 失败！", lpPath);						\
	}																								\
	EXIT_MESSAGE(CreateFolder(lpPath), "创建文件夹 [%s] ！", lpPath);

// 主函数，函数入口
int main(void) {
	printf_s("编译时间：%s %s\n", __DATE__, __TIME__);

	LPSTR lpAppDataPath = NULL;													// 取用户 %AppData% 目录
	EXIT_MESSAGE(!_dupenv_s(&lpAppDataPath, (size_t *)0, "AppData"), "获取用户 [APPTATA] 目录失败！");
	CHECK_POINTER(lpAppDataPath);

	CHAR lpAdobeCachePath[MAX_PATH];											// 取 %AppData%\Adobe\Flash Player\AssetCache 目录
	SPRINTF_S(lpAdobeCachePath, "%s\\Adobe\\Flash Player\\AssetCache", lpAppDataPath);
	FREE_POINTER(lpAppDataPath);
	CREATE_FOLDER(lpAdobeCachePath);

	LPSTR lpRandomFolderName = GetRandomString(FILE_NAME_LEN);					// 取 随机八位字符 目录
	CHAR lpTempFolder[MAX_PATH];												// 取 %AppData%\Adobe\Flash Player\AssetCache\随机八位字符 目录
	CHECK_POINTER(lpRandomFolderName);
	SPRINTF_S(lpTempFolder, "%s\\%s", lpAdobeCachePath, lpRandomFolderName);
	FREE_POINTER(lpRandomFolderName);
	CREATE_FOLDER(lpTempFolder);

	CHAR lpHeuPath[MAX_PATH], lpSwzPath[MAX_PATH], lpTxtPath[MAX_PATH];			// 定义 HEU、SWZ 和 TXT 文件路径
	SPRINTF_S(lpHeuPath, "%s\\8F903698240FE799F61EEDA8595181137B996156.heu", lpTempFolder);
	SPRINTF_S(lpSwzPath, "%s\\8F903698240FE799F61EEDA8595181137B996156.swz", lpTempFolder);
	SPRINTF_S(lpTxtPath, "%s\\cacheSize.txt", lpTempFolder);

	BOOL bIsSuccess = ReleaseResource((LPCSTR)IDR_RES_HEU1, "RES_HEU", lpHeuPath) &&
		ReleaseResource((LPCSTR)IDR_RES_SWZ1, "RES_SWZ", lpSwzPath) &&
		ReleaseResource((LPCSTR)IDR_RES_TXT1, "RES_TXT", lpTxtPath);			// 释放资源
	EXIT_MESSAGE(bIsSuccess, "修复失败！\n");

	#if IS_INDEPENDENT_TOOLS == INNER_FALSE
		puts("修复成功！");
		PAUSE();
	#else
		MessageBoxA(NULL, "修复成功！", "信息", MB_ICONINFORMATION);
	#endif

	return EXIT_SUCCESS;
}