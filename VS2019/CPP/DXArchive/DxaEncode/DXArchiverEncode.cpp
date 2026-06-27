// ============================================================================
//
//			ＤＸＡファイル作成ソフト
//
//	Creator			: 山田　巧
//	Creation Date	: 2003/09/13
//	Version			: 1.08
//
// ============================================================================

// include ----------------------------
#include "DXArchive.h"
#include "FileLib.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <direct.h>

// define -----------------------------
#define VERSION			"1.09"				// バージョン
#define FILETYPE		"dxa"				// 拡張子

// code -------------------------------

// メイン関数
int main( int argc, char *argv[] )
{
	char SrcPath[256], DestPath[256], *KeyString, *SrcDirectoryPath, *DestFilePath ;
	bool Press ;
	bool MaxPress ;
	bool NoOutput ;
	bool NoKey ;
	bool AlwaysHuffman ;
	int HuffmanSize ;
	int i ;

	printf( "DXA 文件简易创建软件  Ver%s\n", VERSION ) ;

	// 引数が一個だったらヘルプを出す
	if( argc == 1 ) goto ERR ;

	Press = true ;
	MaxPress = false ;
	NoOutput = false ;
	NoKey = false ;
	HuffmanSize = 10 ;
	AlwaysHuffman = false ;
	SrcDirectoryPath = NULL ;
	DestFilePath = NULL ;
	KeyString = NULL ;
	for( i = 1 ; i < argc ; i ++ )
	{
		if( argv[i][0] == '-' && argv[i][1] == 'K' && argv[i][2] == ':' )
		{
			KeyString = argv[i] + 3 ;
		}
		else
		if( argv[i][0] == '-' && argv[i][1] == 'N' && argv[i][2] == 'P' && argv[i][3] == '\0' )
		{
			Press = false ;
		}
		else
		if( argv[i][0] == '-' && argv[i][1] == 'N' && argv[i][2] == 'S' && argv[i][3] == '\0' )
		{
			NoOutput = true ;
		}
		else
		if( argv[i][0] == '-' && argv[i][1] == 'N' && argv[i][2] == 'K' && argv[i][3] == '\0' )
		{
			NoKey = true ;
		}
		else
		if( argv[i][0] == '-' && argv[i][1] == 'H' && argv[i][2] == ':' )
		{
			HuffmanSize = atoi( argv[i] + 3 ) ;
			if( HuffmanSize < 0 )
			{
				HuffmanSize = 0 ;
			}
			else
			if( HuffmanSize > 255 )
			{
				HuffmanSize = 255 ;
			}
		}
		else
		if( argv[i][0] == '-' && argv[i][1] == 'A' && argv[i][2] == 'H' && argv[i][3] == '\0' )
		{
			AlwaysHuffman = true ;
		}
		else
		if( argv[i][0] == '-' && argv[i][1] == 'M' && argv[i][2] == 'P' && argv[i][3] == '\0' )
		{
			MaxPress = true ;
		}
		else
		if( SrcDirectoryPath == NULL )
		{
			SrcDirectoryPath = argv[i] ;
		}
		else
		{
			DestFilePath = argv[i] ;
		}
	}

	if( SrcDirectoryPath == NULL )
		goto ERR ;

	// ソースパスのフルパスを作成する
	ConvertFullPath__( SrcDirectoryPath, SrcPath ) ;

	// 出力ファイルパスの作成
	{
		if( DestFilePath != NULL )
		{
			char temp[256] ;

			strcpy( temp, DestFilePath ) ;
			ConvertFullPath__( temp, DestPath ) ;
		}
		else
		{
			// ソースパスから出力ファイル名を作成する
			sprintf( DestPath, "%s.%s", SrcPath, FILETYPE ) ;
		}
	}

	// アーカイブファイルを作成する
	DXArchive::EncodeArchiveOneDirectory( DestPath, SrcPath, Press, AlwaysHuffman, ( u8 )HuffmanSize, KeyString, NoKey, NoOutput ? false : true, MaxPress ) ;

	// 終了
	return 0 ;

ERR:

	printf( "DxaEncode.exe [Option] SrcDirectoryPath  [DestFilePath]\n\n" ) ;
	printf( "您可以通过简单地拖放要创建的文件夹来创建 DXA 文件。\n" ) ; 
	printf( "·-K  您可以将 key 设置为选项（最多 63 个半角字符） 　例  -K:KeyCode \n" ) ; 
	printf( "·-NP 归档时不进行压缩\n" ) ;
	printf( "·-NS 不显示进度\n" ) ;
	printf( "·-NK 不进行加密\n" ) ;
	printf( "·-H  文件开头和结尾的哈夫曼压缩大小（单位：千字节）（0 到 255）\n" ) ;
	printf( "      默认值为 10 示例 -H:20 （此外，-H:255 哈夫曼 压缩整个文件）\n" ) ;
	printf( "·-AH 使所有文件格式都符合哈夫曼压缩条件\n" ) ;
	printf( "      默认仅适用于png、wav等主要文件格式\n" ) ;
	printf( "·-MP 最大化自身压缩的压缩比\n" ) ;
	return -1; 
}


