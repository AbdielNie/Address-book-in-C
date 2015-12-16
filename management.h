#pragma once

//数据结构
struct tagLinkMan
{
	char *m_pName;
	char *m_pLocation;
	char *m_pPhone;
	char *m_pbirthday;
	char *m_premark;
};


//管理数据表结构
struct tagMenagementDate
{
	unsigned int m_unStorageOffset;
	char m_chSign;
	unsigned int m_nLength;
	unsigned int m_nNameLength;
	unsigned int m_nLocationLength;
	unsigned int m_nPhoneLength;
	unsigned int m_nbirthdayLength;
	unsigned int m_nremarkLength;
};

struct tagReadMenagementListReturn
{
	tagMenagementDate *ptrMenagementList;
	unsigned int nCounts;
};




tagReadMenagementListReturn  ReadMenagementList();
void SaveMenagementFile(tagMenagementDate Menagement, int nCounts, int nOffset);
void SaveDateFile(struct tagLinkMan pDate, int nOffset);
bool IsRightSign(char chSign);
int FindSpase(struct tagMenagementDate Menagement, tagReadMenagementListReturn RMLReturnValue);
void NewSpace(tagReadMenagementListReturn RMLReturnValue, struct tagMenagementDate Menagement, int nSubscript);
tagMenagementDate SetMenagement(struct tagLinkMan bufDate);
tagMenagementDate ReadMenagementONE(int nNitem);

int FreeSpase(struct tagLinkMan bufDate);

void AddDate(struct tagLinkMan bufDate);


void DeleteDate(int nNitem);


int Revise(int nNitem, struct tagLinkMan bufDate);


tagLinkMan FindMan(int nNitem);

