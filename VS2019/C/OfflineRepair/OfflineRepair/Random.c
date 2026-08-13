#include <time.h>

#include "Random.h"

static CHAR GetRandomChar(void);

// 取指定长度的随机字符串
LPSTR GetRandomString(int nSize) {
	if (nSize <= 0 || nSize > MAX_PATH) {										// 长度不能小于 0 或大于 MAX_PATH(260)
		return NULL;
	}

	LPSTR lpBuffer = MALLOC(CHAR, nSize + 1);
	CHECK_POINTER(lpBuffer);

	srand((unsigned int)time(NULL));											// 置随机数种子
	for (int i = 0; i < nSize; i++) {
		lpBuffer[i] = GetRandomChar();
	}
	lpBuffer[nSize] = '\0';

	return lpBuffer;
}

// 取随机大写字母或数字
static CHAR GetRandomChar(void) {
	if (rand() % 2) {
		return 'A' + rand() % 26;
	}
	return '0' + rand() % 10;
}