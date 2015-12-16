#define _CRT_SECURE_NO_WARNINGS
#include "UI.h"
#include "Management.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


tagLinkMan Buf()
{
	tagDatebuf buf;
	tagLinkMan people;
	printf("输入联系人姓名:\r\n");
	fflush(stdin);
	fgets(buf.m_szName, 30, stdin);
	printf("输入联系人地址:\r\n");
	fflush(stdin);
	fgets(buf.m_szLocation, 30, stdin);
	printf("输入联系人电话:\r\n");
	fflush(stdin);
	fgets(buf.m_szPhone, 13, stdin);
	printf("输入联系人生日:\r\n");
	fflush(stdin);
	fgets(buf.m_szbirthday, 13, stdin);
	printf("输入联系人备注:\r\n");
	fflush(stdin);
	fgets(buf.m_szremark, 30, stdin);

	buf.m_szbirthday[strlen(buf.m_szbirthday) - 1] = '\0';
	buf.m_szLocation[strlen(buf.m_szLocation) - 1] = '\0';
	buf.m_szName[strlen(buf.m_szName) - 1] = '\0';
	buf.m_szPhone[strlen(buf.m_szPhone) - 1] = '\0';
	buf.m_szremark[strlen(buf.m_szremark) - 1] = '\0';

	people.m_pbirthday = (char *)malloc(strlen(buf.m_szbirthday));
	people.m_pLocation = (char *)malloc(strlen(buf.m_szLocation));
	people.m_pName = (char *)malloc(strlen(buf.m_szName));
	people.m_pPhone = (char *)malloc(strlen(buf.m_szPhone));
	people.m_premark = (char *)malloc(strlen(buf.m_szremark));

	strcpy(people.m_pbirthday, buf.m_szbirthday);
	strcpy(people.m_pLocation, buf.m_szLocation);
	strcpy(people.m_pName, buf.m_szName);
	strcpy(people.m_pPhone, buf.m_szPhone);
	strcpy(people.m_premark, buf.m_szremark);
	return people;
}




//主菜单
void Mencu()
{
	system("cls");
	printf("C语言通讯录：\r\n");
	printf("------------------------------\n");
	printf("1.添加联系人\n");
	printf("2.删除联系人\n");
	printf("3.修改联系人\n");
	printf("4.查找联系人\n");
	printf("5.统计联系人个数和百分比\r\n");
	printf("6.资源管理\r\n");
	printf("0.退出\r\n");
	printf("------------------------------\n");
	printf("请选择:");
}
//添加菜单
void Add()
{
	tagLinkMan buf = Buf();
	AddDate(buf);
	printf("添加成功\n");
	
	system("pause");
	FreeSpase(buf);
}



//删除菜单
void Delete()
{
	int number = 0;
	ShowAll();
	printf("请输入需要删除的编号\n");
	scanf("%d", &number);
	DeleteDate(number);
	printf("删除成功\n");
	ShowAll();
	system("pause");
}


//修改菜单
void Revisr()
{
	int number = 0;
	ShowAll();
	printf("请输入需要修改的编号\n");
	scanf("%d", &number);
	fflush(stdin);
	Revise(number, Buf());
	printf("修改成功\n");
	system("pause");
}


//查找菜单
void Find()
{
	int nChoise = 0;
	printf("1: 下标查找;\n2: 模糊查找;\n3: 显示所有字符!\n");
	scanf("%d", &nChoise);
	if (nChoise == 1)
	{
		system("cls");
		int nUnderMark = 0;
		printf("请输入下标：");
		fflush(stdin);
		scanf("%d", &nUnderMark);
		tagLinkMan Date = FindMan(nUnderMark);
		if (Date.m_pName != NULL)
		{
			ShowOneDate(Date);
		}
		printf("该数据不存在\n");
		FreeSpase(Date);
	}
	else if (nChoise == 2)
	{
		system("cls");
		char szbuff[10] = { 0 };
		printf("请输入查询的字符：");
		fflush(stdin);
		fgets(szbuff, 10, stdin);
		int n = 0;
		szbuff[strlen(szbuff) - 1] = '\0';
		tagReadMenagementListReturn RMLReturnValue = ReadMenagementList();
		for (unsigned int i = 0; i < RMLReturnValue.nCounts; i++)
		{
			tagLinkMan Date = FindMan(i);
			if (strstr(Date.m_pName, szbuff))
			{
				ShowOneDate(Date);
			}
			if (strstr(Date.m_pLocation, szbuff))
			{
				ShowOneDate(Date);
			}
			if (strstr(Date.m_pPhone, szbuff))
			{
				ShowOneDate(Date);
			}
		}
		if (n == 0)
		{
			printf("没有\n");
		}
		free(RMLReturnValue.ptrMenagementList);
		RMLReturnValue.ptrMenagementList = NULL;
	}
	else
	{
		system("cls");
		ShowAll();
	}
	system("pause");
}



//显示所有字符串
void ShowAll()
{
	system("cls");
	tagReadMenagementListReturn RMLReturnValue = ReadMenagementList();
	if (RMLReturnValue.ptrMenagementList == NULL)
	{
		printf("没有数据，请添加数据");
		return;
	}
	for (unsigned int i = 0; i < RMLReturnValue.nCounts ; i++)
	{
		if (!IsRightSign(RMLReturnValue.ptrMenagementList[i].m_chSign))
		{
			printf("[编号]: %d\n", i);
			tagLinkMan Date = FindMan(i);
			ShowOneDate(Date);
			printf("\n*******************************************************\n");
		}
	}
	free(RMLReturnValue.ptrMenagementList);
	RMLReturnValue.ptrMenagementList = NULL;
}

void ShowOneDate(tagLinkMan Date)
{
	printf("联系人姓名:");
	puts(Date.m_pName);
	printf("地址:");
	puts(Date.m_pLocation);
	printf("电话:");
	puts(Date.m_pPhone);
	printf("生日:");
	puts(Date.m_pbirthday);
	printf("备注:");
 	puts(Date.m_premark);
}

//统计菜单
void Census()
{
	tagReadMenagementListReturn RMLReturnValue = ReadMenagementList();
	int nAry[1000] = { 0 };
	for (unsigned int i = 0; i < RMLReturnValue.nCounts; i++)
	{
		tagLinkMan Date = FindMan(i);
		for (unsigned int i = 0; i < RMLReturnValue.nCounts; i++)
		{
			tagLinkMan Date2 = FindMan(i);
			if (strcmp(Date.m_pName, Date2.m_pName) == 0)
			{
				nAry[i] += 1;
			}
		}
	}
	for (unsigned int i = 0; i < RMLReturnValue.nCounts; i++)
	{
		tagLinkMan Date = FindMan(i);
		puts(Date.m_pName);
		printf("所占比例:%f", nAry[i] / RMLReturnValue.nCounts);
	}
	printf("总联系人数量：%d", RMLReturnValue.nCounts);

	free(RMLReturnValue.ptrMenagementList);
	RMLReturnValue.ptrMenagementList = NULL;
}
//碎片整理
void UIDefragment()
{
	ShowRAM();
	printf("\n任意键进行碎片整理\n");
	char chChoies = 0;
	fflush(stdin);
	scanf("%c", &chChoies);
	if (chChoies != 0)
	{
		tagReadMenagementListReturn RMLReturnValue = ReadMenagementList();
		int nLength = RMLReturnValue.nCounts ;
		int nstart = 0;
		tagMenagementDate *ptrListAry = (tagMenagementDate *)malloc(sizeof(tagMenagementDate) * nLength);
		for (unsigned int i = 0; i < RMLReturnValue.nCounts; i++)
		{
			if (!IsRightSign(RMLReturnValue.ptrMenagementList[i].m_chSign))
			{
				ptrListAry[nLength - 1] = RMLReturnValue.ptrMenagementList[i];
				nLength--;
			}
			else
			{
				ptrListAry[nstart] = RMLReturnValue.ptrMenagementList[i];
				nstart++;
			}
		}

		for (unsigned int i = 0; i < RMLReturnValue.nCounts; i++)
		{
			SaveMenagementFile(ptrListAry[i], RMLReturnValue.nCounts, i * 29 + sizeof(int));
		}
		
		free(ptrListAry);
		ptrListAry = NULL;
		free(RMLReturnValue.ptrMenagementList);
		RMLReturnValue.ptrMenagementList = NULL;
	}
	printf("整理成功\n");
	ShowRAM();
}

//显示内存分别情况
void ShowRAM()
{
	tagReadMenagementListReturn RMLReturnValue = ReadMenagementList();
	for (unsigned int i = 0; i < RMLReturnValue.nCounts ; i++)
	{
		if (IsRightSign(RMLReturnValue.ptrMenagementList[i].m_chSign))
		{
			printf("U");
		}
		else
		{
			printf("F");
		}
	}
	system("pause");
	free(RMLReturnValue.ptrMenagementList);
	RMLReturnValue.ptrMenagementList = NULL;
}
