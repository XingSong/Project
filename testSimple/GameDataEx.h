#pragma once
#include "UpgradeMessage.h"
enum LaiziKind
{
	LAIZIPI_CARD,
	LAIZI_CARD
};
class CGameDataEx
{
public:
	CGameDataEx();
	~CGameDataEx();
public:
	//做牌
	int			m_isOpenZuoPaiFlag;						//做牌开关
	TCHAR		m_szPai0[MAX_PATH];						//做牌牌值保存的数组
	TCHAR		m_szPai1[MAX_PATH];						//做牌牌值保存的数组
	TCHAR		m_szPai2[MAX_PATH];						//做牌牌值保存的数组
	TCHAR		m_szPai3[MAX_PATH];						//做牌牌值保存的数组
	TCHAR		m_szPaiLaizi[MAX_PATH];					//做牌赖子
	TCHAR		m_szPaiLaiziPi[MAX_PATH];				//做牌赖子皮
	tagMatchMJ  m_tMatchMJ;

	BYTE		byLaiZiPiCard;							//赖子皮
	BYTE		byLaiZiCard;							//赖子牌

public:
	//做牌
	//将ASCII码转化为16进制数
	BYTE ConvertHexChar(BYTE ch);
	//将TCHAR转为char 
	void TcharToChar(const TCHAR * tchar, char * _char);
	//把char转为TCHAR
	void CharToTchar(const char * _char, TCHAR * tchar);
	char* find(char a[], char b[]);
	void del(char a[], char b[]);
	void ZuoPai();
	void ZuoPaiRoll(TCHAR *m_szPai, int len, int index);
	void ZuoPaiLaizi(TCHAR *m_szPai, LaiziKind lzkind);
	void ReadConfigZuoPai();
};

