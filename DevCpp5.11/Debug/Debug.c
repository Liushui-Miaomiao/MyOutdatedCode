#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <io.h>

#define MALLOC(type, n)																\
	(type *)malloc(sizeof(type) * (n))
#define FREE_POINTER(pointer) 														\
	if (pointer != NULL) {															\
		free(pointer);																\
		pointer = NULL;																\
	}
#define CHECK_POINTER(pointer) 														\
	if (pointer == NULL) {															\
		printf("Line:%d\tFailed to create pointer ["#pointer"]!\n", __LINE__);		\
		system("pause>nul");														\
		free(pointer);																\
		return -1;																	\
	}
#define EXIT()																		\
	system("pause>nul");															\
	FREE_POINTER(lpFile)															\
	FREE_POINTER(lpCurrentPath);													\
	return -1;

int main(void) {
	const LPSTR lpFiles[] = {"debug\\debug.bat", "debug\\adl.exe", "META-INF\\AIR\\application.xml"};
	
	// Gets the directory where the program is currently running.
	LPSTR lpCurrentPath = MALLOC(CHAR, MAX_PATH);
	CHECK_POINTER(lpCurrentPath);
	GetCurrentDirectory(MAX_PATH, lpCurrentPath);
	
	// Gets the length of the array "lpFiles".
	int nFileLength = sizeof(lpFiles) / sizeof(lpFiles[0]);
	LPSTR lpFile = MALLOC(CHAR, MAX_PATH);
	CHECK_POINTER(lpFile);
	LPSTR lpFilePath[nFileLength];
	for (int i = 0; i < nFileLength; i++) {
		sprintf(lpFile, "%s\\%s", lpCurrentPath, lpFiles[i]);
		
		// Check whether the file exists. 
		if (access(lpFile, 0)) {
			printf("Unable to find file:%s\n", lpFile);
			
			EXIT();
		}
		
		lpFilePath[i] = MALLOC(CHAR, MAX_PATH);
		CHECK_POINTER(lpFilePath[i])
		strcpy(lpFilePath[i], lpFile);
		
		// Check whether the file path contains Spaces.
		if (strstr(lpFilePath[i], " ")) {
			puts("The file path contains Spaces!");
			
			EXIT();
		}
	}
	FREE_POINTER(lpFile);
	
	// Generation command.
	LPSTR lpCommand = MALLOC(CHAR, MAX_PATH * 2);
	CHECK_POINTER(lpCommand);
	sprintf(lpCommand, "%s %s %s %s %s", lpFilePath[0], lpFilePath[1], lpCurrentPath, lpFilePath[2], lpCurrentPath);
	
	FREE_POINTER(lpCurrentPath);
	for (int i = 0; i < nFileLength; i++) {
		FREE_POINTER(lpFilePath[i]);
	}
	
	system(lpCommand);
	FREE_POINTER(lpCommand);
	
	return 0;
}
