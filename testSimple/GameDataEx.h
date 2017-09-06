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
	//����
	int			m_isOpenZuoPaiFlag;						//���ƿ���
	TCHAR		m_szPai0[MAX_PATH];						//������ֵ���������
	TCHAR		m_szPai1[MAX_PATH];						//������ֵ���������
	TCHAR		m_szPai2[MAX_PATH];						//������ֵ���������
	TCHAR		m_szPai3[MAX_PATH];						//������ֵ���������
	TCHAR		m_szPaiLaizi[MAX_PATH];					//��������
	TCHAR		m_szPaiLaiziPi[MAX_PATH];				//��������Ƥ
	tagMatchMJ  m_tMatchMJ;

	BYTE		byLaiZiPiCard;							//����Ƥ
	BYTE		byLaiZiCard;							//������

public:
	//����
	//��ASCII��ת��Ϊ16������
	BYTE ConvertHexChar(BYTE ch);
	//��TCHARתΪchar 
	void TcharToChar(const TCHAR * tchar, char * _char);
	//��charתΪTCHAR
	void CharToTchar(const char * _char, TCHAR * tchar);
	char* find(char a[], char b[]);
	void del(char a[], char b[]);
	void ZuoPai();
	void ZuoPaiRoll(TCHAR *m_szPai, int len, int index);
	void ZuoPaiLaizi(TCHAR *m_szPai, LaiziKind lzkind);
	void ReadConfigZuoPai();
};

