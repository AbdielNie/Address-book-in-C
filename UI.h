#pragma once
#include "Management.h"
//主菜单
void Mencu();
//添加菜单
void Add();
//删除菜单
void Delete();
//修改菜单
void Revisr();
//查找菜单
void Find();
//显示所有字符串
void ShowAll();
//统计菜单
void Census();
//碎片整理
void UIDefragment();
//显示内存分别情况
void ShowRAM();

void ShowOneDate(tagLinkMan Date);


tagLinkMan Buf();

//数据结构
struct tagDatebuf
{
	char m_szName[30];
	char m_szLocation[30];
	char m_szPhone[13];
	char m_szbirthday[13];
	char m_szremark[30];
};

extern int nDeleteCounts;
