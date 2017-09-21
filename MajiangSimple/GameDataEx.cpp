#define  _CRT_SECURE_NO_WARNINGS
#include "GameDataEx.h"
#include "CMD_Sparrow.h"
#include <atlstr.h>

CGameDataEx::CGameDataEx()
{
}


CGameDataEx::~CGameDataEx()
{
}

BYTE CGameDataEx::ConvertHexChar(BYTE ch)
{
	if ((ch >= '0') && (ch <= '9'))
		return ch - 0x30;
	else if ((ch >= 'A') && (ch <= 'F'))
		return ch - 'A' + 10;
	else if ((ch >= 'a') && (ch <= 'f'))
		return ch - 'a' + 10;
	else
		return -1;
}

//void CGameDataEx::TcharToChar(const TCHAR * tchar, char * _char)
//{
//	int iLength;
//	//获取字节长度   
//	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
//	//将tchar值赋给_char    
//	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
//}
//
//void CGameDataEx::CharToTchar(const char * _char, TCHAR * tchar)
//{
//	int iLength;
//
//	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
//	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
//}

char* CGameDataEx::find(char a[], char b[])
{
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; a[i] != '\0'; i++)
	{

		if (a[i] == b[0])
		{
			k = i + 1;
			for (j = 1; a[k] == b[j] && a[k] != '\0'&&b[j] != '\0'; k++, j++);
			if (b[j] == '\0')
				return a + i;
		}

	}
	return 0;
}

void CGameDataEx::del(char a[], char b[])
{
	char* p;
	while (p = find(a, b))
		strcpy(p, p + strlen(b));
}

void CGameDataEx::ZuoPai()
{
	ZuoPaiRoll(m_szPai0, MAX_COUNT, 0);
	//ZuoPaiRoll(m_szPai1, MAX_COUNT - 1, 1);
	//ZuoPaiRoll(m_szPai2, MAX_COUNT - 1, 2);
	//ZuoPaiRoll(m_szPai3, MAX_COUNT - 1, 3);
	ZuoPaiLaizi(m_szPaiLaiziPi,LAIZIPI_CARD);
	ZuoPaiLaizi(m_szPaiLaizi,LAIZI_CARD);

}

void CGameDataEx::ZuoPaiRoll(TCHAR *m_szPai, size_t len, int index)
{
	//char tmpPai[MAX_PATH];
	//memset(tmpPai, 0, sizeof(tmpPai));
	//TcharToChar(m_szPai, tmpPai);
	//del(tmpPai, "0x");
	//CharToTchar(tmpPai, m_szPai);
	del(m_szPai, "0x");
	CString cstr0;
	cstr0.Format(m_szPai);
	cstr0.Replace(',', ' ');

	BYTE tmpByte = 0x00;
	BYTE tmpCardData[MAX_COUNT];
	memset(tmpCardData, 0, sizeof(tmpCardData));
	for (int i = 0, j = 0; i < MAX_COUNT, j < cstr0.GetLength(); i++, j++)
	{
		if (cstr0[j] == ' ')
			++j;
		tmpByte = cstr0[j];
		tmpCardData[i] = ConvertHexChar(tmpByte) << 4;
		if (cstr0[++j] == ' ')
			++j;
		tmpByte = cstr0[j];
		tmpCardData[i] = tmpCardData[i] + (ConvertHexChar(tmpByte) & 0xF);//取低4位然后相加。
	}

	for (size_t i = 0; i < len; i++)
	{
		m_tMatchMJ.byArHandPai[index][i] = tmpCardData[i] / BASE_DECIMAL * 10 + tmpCardData[i] % BASE_DECIMAL;
	}
}

void CGameDataEx::ZuoPaiLaizi(TCHAR *m_szPai, LaiziKind lzkind)
{
	del(m_szPai, "0x");
	CString cstr0;
	cstr0.Format(m_szPai);
	//cstr0.Replace(',', ' ');

	BYTE tmpByte = 0x00;
	BYTE tmpCardData[1];
	memset(tmpCardData, 0, sizeof(tmpCardData));
	for (int i = 0, j = 0; i < 1, j < cstr0.GetLength(); i++, j++)
	{
		if (cstr0[j] == ' ')
			++j;
		tmpByte = cstr0[j];
		tmpCardData[i] = ConvertHexChar(tmpByte) << 4;
		if (cstr0[++j] == ' ')
			++j;
		tmpByte = cstr0[j];
		tmpCardData[i] = tmpCardData[i] + (ConvertHexChar(tmpByte) & 0xF);//取低4位然后相加。
	}

	for (int i = 0; i < 1; i++)
	{
		if (lzkind==LAIZIPI_CARD)
			byLaiZiPiCard = tmpCardData[i] / BASE_DECIMAL * 10 + tmpCardData[i] % BASE_DECIMAL;
		else if (lzkind == LAIZI_CARD)
			byLaiZiCard = tmpCardData[i] / BASE_DECIMAL * 10 + tmpCardData[i] % BASE_DECIMAL;
	}
}

void CGameDataEx::ReadConfigZuoPai()
{
	TCHAR szPath[MAX_PATH] = TEXT("");
	GetCurrentDirectory(CountArray(szPath), szPath);
	TCHAR szFileName[MAX_PATH] = TEXT("");
	_sntprintf(szFileName, CountArray(szFileName), TEXT("%s\\MajiangConfig.ini"), szPath);
	m_isOpenZuoPaiFlag = GetPrivateProfileInt(GAME_NAME, TEXT("isOpenZuoPai"), 0, szFileName);
	m_isHasLaiZiFlag   = GetPrivateProfileInt(GAME_NAME, TEXT("isHasLaiZi"), 0, szFileName);
	GetPrivateProfileString(GAME_NAME, TEXT("UserCard0"), _T(""), m_szPai0, sizeof(m_szPai0), szFileName);
	GetPrivateProfileString(GAME_NAME, TEXT("UserCard1"), _T(""), m_szPai1, sizeof(m_szPai1), szFileName);
	GetPrivateProfileString(GAME_NAME, TEXT("UserCard2"), _T(""), m_szPai2, sizeof(m_szPai2), szFileName);
	GetPrivateProfileString(GAME_NAME, TEXT("UserCard3"), _T(""), m_szPai3, sizeof(m_szPai3), szFileName);
	GetPrivateProfileString(GAME_NAME, TEXT("LaiZiPiCard"), _T(""), m_szPaiLaiziPi, sizeof(m_szPaiLaiziPi), szFileName);
	GetPrivateProfileString(GAME_NAME, TEXT("LaiZiCard"), _T(""), m_szPaiLaizi, sizeof(m_szPaiLaizi), szFileName);

	//m_LaiZiPiCard = GetPrivateProfileInt(GAME_NAME, TEXT("LaiZiPiCard"), 1, szFileName);
	//m_LaiZiCard = GetPrivateProfileInt(GAME_NAME, TEXT("LaiZiCard"), 2, szFileName);
}
