#include "GameAlgorithm.h"
#include "GameLogic.h"
#include "GameDataEx.h"
#include <map>
using namespace std;

CGameAlgorithm::CGameAlgorithm()
{
	memset(m_HandCardData, 0, sizeof(m_HandCardData));
	m_pGameLogic = new CGameLogic();
	m_tMJKindNum.iDanzhangNum = 0;
	m_tMJKindNum.iJiangNum = 0;
	m_tMJKindNum.iKeziNum = 0;
	m_tMJKindNum.iGangNum = 0;
	m_tMJKindNum.iKeziNum = 0;
}


CGameAlgorithm::~CGameAlgorithm()
{
	CC_SAFE_DELETE(m_pGameLogic);
}

int CGameAlgorithm::CountPai(BYTE arrHandCardData[], int len, PAI_REPRESS_FLAG iFlag)
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

//计算A、AA、AAA、AAAA的数量
UINT CGameAlgorithm::CountPaiWithLaizi(BYTE arrHandCardData[], int len, PAI_REPRESS_FLAG iFlag, CGameDataEx *m_pGameDataEx)
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
		if (m_pGameDataEx->byLaiZiCard == it.first)//赖子不参与计算
			continue;
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
//判断碰碰和
bool CGameAlgorithm::IsPengPengHu(BYTE arrHandCardData[], int len)
{
	int kezi = CountPai(arrHandCardData, len, KEZI_FLAG);
	int gang = CountPai(arrHandCardData, len, GANG_FLAG);
	int jiang = CountPai(arrHandCardData, len, JIANG_FLAG);
	if (1 == jiang && 4 == kezi + gang)
	{
		return true;
	}
	else
		return false;
}
//判断7对
bool CGameAlgorithm::IsQiDuiHu(BYTE arrHandCardData[], int len)
{
	int jiang = CountPai(arrHandCardData, len, JIANG_FLAG);
	int gang = CountPai(arrHandCardData, len, GANG_FLAG);
	return (2 * jiang + 4 * gang == 14);
}
//判断平和
bool CGameAlgorithm::IsPingHu(BYTE arr[], int len)
{
	SortCardAsc(arr, len);
	BYTE set[HAND_CARD_MAX_REPERTORY] = { 0 };
	
	for (int i = 0; i < len; i++)
	{
		if (arr[i] == arr[i + 1])
		{
			int k = 0;
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
	
	return false;
}

//判断清一色
bool CGameAlgorithm::IsQingYiSe(BYTE arrHandCardData[], int len)
{
	bool result = true;
	for (size_t i = 1; i < len; i++)
	{
		if (m_pGameLogic->getColor(arrHandCardData[0]) != m_pGameLogic->getColor(arrHandCardData[i]))
		{
			result = false;
			break;
		}
	}
	return result;
}

bool CGameAlgorithm::IsZiYiSe(BYTE arrHandCardData[], int len)
{
	bool result = true;
	for (size_t i = 0; i < len; i++)
	{
		if (m_pGameLogic->getColor(arrHandCardData[i]) != 3)
		{
			result = false;
			break;
		}
	
	}
	return result;
}

//计算A、AA、AAA、AAAA、赖子的数量汇总，方便调用
void CGameAlgorithm::CalKindMJKindNum(BYTE arrHandCardData[], int len, CGameDataEx *m_pGameDataEx /*= nullptr*/)
{
	m_tMJKindNum.iDanzhangNum = CountPaiWithLaizi(arrHandCardData, len, DANZHANG_FALG, m_pGameDataEx);
	m_tMJKindNum.iKeziNum = CountPaiWithLaizi(arrHandCardData, len, KEZI_FLAG, m_pGameDataEx);
	m_tMJKindNum.iGangNum = CountPaiWithLaizi(arrHandCardData, len, GANG_FLAG, m_pGameDataEx);
	m_tMJKindNum.iJiangNum = CountPaiWithLaizi(arrHandCardData, len, JIANG_FLAG, m_pGameDataEx);
	m_tMJKindNum.iLaiziNum = 0;

	for (size_t i = 0; i < len; i++)
	{
		if (arrHandCardData[i] == m_pGameDataEx->byLaiZiCard)
			m_tMJKindNum.iLaiziNum++;
	}
}
//判断碰碰和
bool CGameAlgorithm::IsPengPengHuWithLaizi(BYTE arrHandCardData[], int len, CGameDataEx *m_pGameDataEx)
{
	int iDanzhangNum = CountPaiWithLaizi(arrHandCardData, len, DANZHANG_FALG, m_pGameDataEx);
	int iKeziNum = CountPaiWithLaizi(arrHandCardData, len, KEZI_FLAG, m_pGameDataEx);
	int iGangNum = CountPaiWithLaizi(arrHandCardData, len, GANG_FLAG, m_pGameDataEx);
	int iJiangNum = CountPaiWithLaizi(arrHandCardData, len, JIANG_FLAG, m_pGameDataEx);
	int iLaiziNum = 0;

	for (size_t i = 0; i < len; i++)
	{
		if (arrHandCardData[i] == m_pGameDataEx->byLaiZiCard)
			iLaiziNum++;
	}
	
	if(iJiangNum > 1)
	{
		if (iDanzhangNum<1)
		{
			iLaiziNum -= iJiangNum - 1;
			iKeziNum += iJiangNum-1;
		}
		else if (iDanzhangNum == 1)
		{
			iLaiziNum -= iJiangNum+1;
			iKeziNum += iJiangNum;
			iDanzhangNum--;
		}
		iJiangNum = 1;
	}
	else if (iJiangNum==0)
	{
		if (iDanzhangNum < 1)
		{
			iKeziNum = 4 - iGangNum;
		}
		else
		{
			if (iLaiziNum == 1 && iDanzhangNum == 1)
			{
				iKeziNum = 4 - iGangNum;
			}
			else
			{
				iKeziNum++;
			}
		}
		iDanzhangNum = 0;
		iLaiziNum = 0;
		iJiangNum++;
	}
	else if (iJiangNum == 1)
	{
		if (iDanzhangNum < 1)
		{
			iKeziNum++;
		}
		else
		{
			//if (iDanzhangNum == 1)
			//{
			//	iKeziNum++;
			//}
			//if (iDanzhangNum == 2)
			//{
			//	iKeziNum += 2;
			//}
			iKeziNum += iDanzhangNum;
		}
		iDanzhangNum = 0;
		iLaiziNum = 0;
	}
	if (iGangNum == 4 && iGangNum * 4 + iDanzhangNum + iLaiziNum + iJiangNum == 18)
		return true;
	if (iJiangNum * 2 + iKeziNum * 3 + iDanzhangNum + iLaiziNum == HAND_CARD_MAX_REPERTORY)
		return true;
	return false;
}

//判断7对
bool CGameAlgorithm::IsQiDuiHuWithLaizi(BYTE arrHandCardData[], int len, CGameDataEx *m_pGameDataEx)
{
	CalKindMJKindNum(arrHandCardData, len, m_pGameDataEx);
	return (4 * m_tMJKindNum.iGangNum + 3 * m_tMJKindNum.iKeziNum + 2 * m_tMJKindNum.iJiangNum + m_tMJKindNum.iDanzhangNum + m_tMJKindNum.iLaiziNum == HAND_CARD_MAX_REPERTORY);
}

//这个比较复杂
bool CGameAlgorithm::IsPingHuWithLaizi(BYTE arrHandCardData[], int len, CGameDataEx *m_pGameDataEx)
{

	return false;
}
//检测是否满足N * ABC + M *DDD
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
//删除顺子
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
//删除刻子
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
//按花色、牌值升序排序
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
//数值掩码大小比较，先比较花色
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
