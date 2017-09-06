#include "GameAlgorithm.h"
#include "GameLogic.h"
#include "GameDataEx.h"
#include <map>
using namespace std;

CGameAlgorithm::CGameAlgorithm()
{
	memset(m_HandCardData, 0, sizeof(m_HandCardData));
	m_pGameLogic = new CGameLogic();
}


CGameAlgorithm::~CGameAlgorithm()
{
	CC_SAFE_DELETE(m_pGameLogic);
}
UINT CGameAlgorithm::CountPai(BYTE arrHandCardData[], int len, PAI_REPRESS_FLAG iFlag)
{
	int count = 0;
	map<BYTE, int> mapCount;
	for (int i = 0; i < len; i++)
	{
		if (mapCount.end() != mapCount.find(arrHandCardData[i]))
			mapCount[arrHandCardData[i]]++;
		else
			mapCount.insert(pair<BYTE, int>(arrHandCardData[i], 1));
	}

	for (auto it : mapCount)
	{
		//cout << it.first << endl << it.second << endl;
		if (iFlag == it.second)
			count++;
	}
	return count;
}

int* CGameAlgorithm::CountElemCount(BYTE arrHandCardData[], int len, int countArray[])
{
	int count;

	memset(countArray, -1, sizeof(countArray));
	for (int i = 0; i < len; i++)
	{
		count = 1;
		for (int j = i + 1; j < len; j++)
		{
			if (arrHandCardData[i] == arrHandCardData[j])
			{
				countArray[j] = 0;
				count++;
			}
		}
		if (countArray[i] != 0)
		{
			countArray[i] = count;
		}
	}
	return countArray;
}

bool CGameAlgorithm::IsPengPengHu(BYTE arrHandCardData[], int len)
{
	int kezi = CountPai(arrHandCardData, len, KEZI_FLAG);
	int gang = CountPai(arrHandCardData, len, GANG_FLAG);
	int jiang = CountPai(arrHandCardData, len, JIANG_FLAG);
	if (1 == jiang)
	{
		if (4 == kezi || 4 == gang)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool CGameAlgorithm::IsQiDuiHu(BYTE arrHandCardData[], int len)
{
	int jiang = CountPai(arrHandCardData, len, JIANG_FLAG);
	int gang = CountPai(arrHandCardData, len, GANG_FLAG);
	return (7 == jiang) || (1 == jiang && 3 == gang);
}

bool CGameAlgorithm::IsPingHu(BYTE arr[], int len)
{
	SortCardAsc(arr, len);
	BYTE *set = new BYTE[len];
	int k = 0;
	for (int i = 0; i < len; i++)
	{
		if (arr[i] == arr[i + 1])
		{
			for (int j = 0; j < len; j++)
			{
				if (j != i&&j != i + 1)
				{
					set[k] = arr[j];
					k++;
				}
				
			}
			if (Check_3n(set, len - 2) || len - 2 == 0)
				return true;
		}
	}
	//delete []set;
	return false;
}

bool CGameAlgorithm::IsPengPengHuWithLaizi(BYTE arrHandCardData[], int len, CGameDataEx *pGameDataEx)
{
	int iDanzhangNum = CountPai(arrHandCardData, len, DANZHANG_FALG);
	int iKeziNum = CountPai(arrHandCardData, len, KEZI_FLAG);
	int iGangNum = CountPai(arrHandCardData, len, GANG_FLAG);
	int iJiangNum = CountPai(arrHandCardData, len, JIANG_FLAG);
	int iLaiziNum = 0;
	for (size_t i = 0; i < len; i++)
	{
		if (arrHandCardData[i] == pGameDataEx->byLaiZiCard)
			iLaiziNum++;
	}
	//if (len % 3 != 2)
	//	return false;

	return false;
}

bool CGameAlgorithm::Check_3n(BYTE arr[], int len)
{
	if (len == 0) return true;
	BYTE set_t[HAND_CARD_MAX_REPERTORY + 6] = { 0 };
	for (int i = 0; i < len; i++)
		set_t[i] = arr[i];

	if (RemoveABC(arr, len))
	{
		if (Check_3n(arr, len - 3))
			return true;
	}

	for (size_t i = 0; i < len; i++)
		arr[i] = set_t[i];
	if (RemoveAAA(arr, len))
	{
		if (Check_3n(arr, len - 3))
			return true;
	}
	return false;
}

bool CGameAlgorithm::RemoveABC(BYTE arr[], int len)
{
	size_t second = 0, third = 0;
	for (size_t i = 0; i < len; i++)
	{
		if (arr[i] == arr[0] + 1)
			second = i;
		if (arr[i] == arr[0] + 2)
			third = i;
		if (arr[i]>arr[0]+2)
			break;
		if (second !=0 && third!=0)
			break;
	}
	if (second != 0 && third != 0)
	{
		int j = 0;
		for (size_t i = 1; i < len; i++)
		{
			if (i != second&&i != third)
			{
				arr[j] = arr[i];
				j++;
			}
		}
		return true;
	}
	return false;
}

bool CGameAlgorithm::RemoveAAA(BYTE arr[], int len)
{

	if (arr[0] == arr[1] && arr[0] == arr[2])
	{
		for (size_t i = 0; i < len-3; i++)
		{
			arr[i] = arr[i + 3];
		}
		return true;
	}
	return false;
}

void CGameAlgorithm::SortCardAsc(BYTE arr[], int len)
{
	for (int i = 0; i<len; i++)
	{
		BYTE max = arr[i];
		BYTE position = i;
		for (int j = len - 1; j >= i; j--)
		{
			if (MaxValue(max, arr[j]))
			{
				max = arr[j];
				position = j;
			}
		}
		//
		BYTE tmp = arr[i];
		arr[i] = max;
		arr[position] = tmp;
	}
}

bool CGameAlgorithm::MaxValue(BYTE a, BYTE b)
{
	if ((a & MASK_COLOR) > (b&MASK_COLOR))
		return true;
	else if ((a&MASK_COLOR) == (b&MASK_COLOR))
	{
		return (a&MASK_VALUE) > (b&MASK_VALUE);
	}
	return false;
}
