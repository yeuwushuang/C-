
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <locale.h>
void create(wchar_t *str)
{
	// 创建文件夹模块
	if (CreateDirectoryW(str, NULL)) // 创建文件夹
	{
		//	printf("文件夹创建成功\n");
	}
	else
	{
		//		printf("文件夹创建失败代码:%lu\n", GetLastError());
	}
}

void FFile_fine(wchar_t *str, wchar_t *backups)
{
	// 复制复制文件模块
	WIN32_FIND_DATAW Fine_Structure;							   // 存储文件或文件夹信息
	wchar_t Fine_Buffer[300], Fine_Backups[300];				   // 合成地址缓存
	swprintf_s(Fine_Buffer, 300, L"%s\\*", str);				   // 进行字符串合成
	HANDLE Find_ID = FindFirstFileW(Fine_Buffer, &Fine_Structure); // 初始化Fine结构体
	do
	{
		if (!wcsncmp(Fine_Structure.cFileName, L".", 1))
		{ // 消除初始的. ..
			continue;
		}
		/*//控制台显示文件类型
		if (Fine_Structure.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {//输出文件类型
			printf("该文件是文件夹：：：：");
		}
		else {
			printf("文件：：：：");
		}//*/
		//	wprintf(L"%s\n", Fine_Structure.cFileName); //输出获取到的文件信息
		// 文件复制CopyFileEx
		swprintf_s(Fine_Buffer, 300, L"%s\\%s", str, Fine_Structure.cFileName);		 // 复制的源路径地址合成
		swprintf_s(Fine_Backups, 300, L"%s\\%s", backups, Fine_Structure.cFileName); // 复制的新地址合成

		if (CopyFileW(Fine_Buffer, Fine_Backups, FALSE))
		{ // 复制
		  // printf("\n%d\n", GetLastError());//测试，判断错误
		}

		if (Fine_Structure.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{																		 // 当dwFileAttributes等于FILE_ATTRIBUTE_DIRECTORY时说明当前枚举的是文件夹
			wchar_t plus[400], MITE[400];										 // 缓存400字节
			swprintf_s(MITE, 400, L"%s\\%s", backups, Fine_Structure.cFileName); // 嵌套文件夹名称
			swprintf_s(plus, 400, L"%s\\%s", str, Fine_Structure.cFileName);	 // 多重文件地址合成
			create(MITE);														 // 创建嵌套文件夹
			if (GetLastError() != ERROR_FILE_NOT_FOUND)
				FFile_fine(plus, MITE); // 递归函数获取嵌套文件
		}
	} while (FindNextFileW(Find_ID, &Fine_Structure));
}

int main()
{
	setlocale(LC_ALL, "chs"); // 防止乱码
	// 需要自动保存的文件夹
	wchar_t *str = L"C:\\Users\\333\\Desktop\\MITER196\\.minecraft\\MITE\\saves\\1.6.4\\极其困难的世界";
	// 保存的个路径
	wchar_t backups[400] = L"C:\\Users\\333\\Desktop\\233\\极其困难的世界";
	while (1)
	{
		SYSTEMTIME Fine_File;
		GetLocalTime(&Fine_File); // 时间结构体初始化
		swprintf(backups, 400, L"%ls%d年-%d月-%d日-%d时-%d分-%d秒", backups, Fine_File.wYear, Fine_File.wMonth, Fine_File.wDay, Fine_File.wHour, Fine_File.wMinute, Fine_File.wSecond);
		create(backups);		  // 创建存档文件夹
		FFile_fine(str, backups); // 复制文件
		wprintf(L"保存成功 %ls\n", backups);
		Sleep(30000); // 指定存档时间
	}
	return 0;
}
