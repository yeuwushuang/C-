
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <locale.h>
void Str_cat(wchar_t *str) {
	//文件地址输入
	wchar_t get_char;
	int i = 0;
	while (get_char = getwchar()) {	//存储getwcahr获取的字符
		if (get_char == '\n') {
			str[i] = '\0';
			break;
		};
		str[i] = get_char;
		i++;
	}

}
void create(wchar_t* str)
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

void FFile_fine(wchar_t* str, wchar_t* backups)
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
	// 需要自动保存的文件夹L"C:\Users\333\Desktop\MITE R196\.minecraft\MITE\saves\1.6.4\极其困难的世界-"
	wchar_t str[400] ;
	//C:\Users\\333\Desktop
	//保存的路径源 L"C:\Users\333\Desktop\233\极其困难的世界"
	wchar_t backups[400];
	// 保存的路径源+时间形成的文件夹
	wchar_t str_backups[400];
	//备份时间
	 	int time;
	//提示用户输入备份地址
	printf("请输入要备份的文件夹");
	Str_cat(str);
	printf("\n请输入文件夹存储的位置");
	Str_cat(backups);
	printf("请输入备份时间，以分钟为单位");
		scanf("%d", &time);

	Sleep(time * 60000); // 防止启动程序就备份
	if (GetFileAttributesW(str) != INVALID_FILE_ATTRIBUTES&&time!=0)
	{ // 判断源文件是否存在

		while (1)
		{
			SYSTEMTIME Fine_File;
			GetLocalTime(&Fine_File); // 时间结构体初始化
			swprintf(str_backups, 400, L"%ls%d年-%d月-%d日-%d时-%d分-%d秒", backups, Fine_File.wYear, Fine_File.wMonth, Fine_File.wDay, Fine_File.wHour, Fine_File.wMinute, Fine_File.wSecond);
			create(str_backups);	  // 创建存档文件夹
			FFile_fine(str, str_backups); // 复制文件
			wprintf(L"保存成功 %ls\n", str_backups);
			str_backups[0] = '\0';
			Sleep(time * 60000); // 指定存档时间
		}
	}
	else
	{
		printf("备份源不存在");
	}
	return 0;
}
