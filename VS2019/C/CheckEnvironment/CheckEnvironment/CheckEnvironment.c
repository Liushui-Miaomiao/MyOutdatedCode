#include "CheckEnvironment.h"
#include "Check.h"

// 主函数，函数入口
int main(void) {
	printf_s("编译时间：%s %s\n", __DATE__, __TIME__);

	BOOL bHasNetFrame, bHasAssetCache, bHasSoundCard;
	bHasNetFrame = CheckNetFrame();
	bHasAssetCache = CheckAssetCache();
	bHasSoundCard = CheckSoundCard();

	if (bHasNetFrame && bHasAssetCache && bHasSoundCard) {						// 都没问题则输出成功
		MessageBoxA(NULL, "未发现任何问题。", "信息", MB_ICONINFORMATION);
		exit(EXIT_SUCCESS);
	}

	EXIT_MESSAGE(bHasNetFrame, "[.NET Framework] 未在此计算机上安装！\n");
	EXIT_MESSAGE(bHasAssetCache, "未检测到[Adobe AIR] 缓存文件！\n");
	EXIT_MESSAGE(bHasSoundCard, "未检测到声卡设备或声音服务未启动！\n");

	return EXIT_SUCCESS;
}