#include "InternationalMajong.h"


InternationalMajong::InternationalMajong()
{
	m_byKeziNum = 0;
	m_byGangNum = 0;
	m_byJiangNum = 0;
	m_pGameAlgorithm = new CGameAlgorithm();
}


InternationalMajong::~InternationalMajong()
{
	CC_SAFE_DELETE(m_pGameAlgorithm);
}

//统计每张牌中出现的次数
int InternationalMajong::CountEachPaiNum(BYTE arrHandCardData[], int len, BYTE paiValue)
{
	int count = 0;
	for (size_t i = 0; i < len; i++)
	{
		if (arrHandCardData[i] == paiValue)
			count++;
	}
	return count;
}

bool InternationalMajong::GetHuPaiMaxCombination(BYTE arrHandCardData[], int len)
{
	if (CheckDASIXI(arrHandCardData, len))
		byDaSiXi = 88;
	if (CheckDASANYUAN(arrHandCardData, len))
		byDaSanYuan = 88;
	if (CheckLVYISE(arrHandCardData, len))
		byLvYiSe = 88;
	if (CheckJIULIANBAODENG(arrHandCardData, len))
		byJiuLianBaoDeng = 88;
	if (CheckSIGANG(arrHandCardData, len))
		bySiGang = 88;

	return false;
}

//大四喜：由4副风刻（杠）组成的和牌。不计圈风刻、门风刻、三风刻、碰碰和
bool InternationalMajong::CheckDASIXI(BYTE arrHandCardData[], int len)
{
	m_byKeziNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, KEZI_FLAG);
	m_byGangNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, GANG_FLAG);
	m_byJiangNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, JIANG_FLAG);
	if (m_byKeziNum + m_byGangNum < 4)
		return false;
	if (m_byJiangNum < 1)
		return false;
	BYTE iPaiValue = 0x31;
	
	if (CountEachPaiNum(arrHandCardData, len, iPaiValue) >= 3 &&
		CountEachPaiNum(arrHandCardData, len, iPaiValue + 1) >= 3 &&
		CountEachPaiNum(arrHandCardData, len, iPaiValue + 2) >= 3 &&
		CountEachPaiNum(arrHandCardData, len, iPaiValue + 3) >= 3
		)
		return true;
	return false;
}

//大三元：和牌中，有中发白3副刻子。不计箭刻
bool InternationalMajong::CheckDASANYUAN(BYTE arrHandCardData[], int len)
{
	m_byKeziNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, KEZI_FLAG);
	m_byGangNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, GANG_FLAG);
	m_byJiangNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, JIANG_FLAG);
	if (m_byKeziNum + m_byGangNum < 4)
		return false;
	if (m_byJiangNum < 1)
		return false;
	BYTE iPaiValue = 0x35;

	if (CountEachPaiNum(arrHandCardData, len, iPaiValue) >= 3 &&
		CountEachPaiNum(arrHandCardData, len, iPaiValue + 1) >= 3 &&
		CountEachPaiNum(arrHandCardData, len, iPaiValue + 2) >= 3 
		)
		return true;
	return false;
}

//绿一色：由23468条及发字中的任何牌组成的顺子、刻子、将的和牌。不计混一色。如无“发”字组成的各牌，可计清一色
bool InternationalMajong::CheckLVYISE(BYTE arrHandCardData[], int len)
{
	if (m_pGameAlgorithm->IsPingHu(arrHandCardData, len) || m_pGameAlgorithm->IsQiDuiHu(arrHandCardData, len))
	{
		BYTE iPaiValue = 0x12;
		for (size_t i = 0; i < len; i++)
		{
			if (arrHandCardData[i] != iPaiValue && 
				arrHandCardData[i] != iPaiValue + 1 && 
				arrHandCardData[i] != iPaiValue + 2 && 
				arrHandCardData[i] != iPaiValue + 4 && 
				arrHandCardData[i] != iPaiValue + 6 &&
				arrHandCardData[i] != 0x36)
				return false;
		}
		
	}
	return false;

}

//九莲宝灯：由一种花色序数牌子按一一一二三四五六七八九九九组成的特定牌型，见同花色任何1张序数牌即成和牌。不计清一色
bool InternationalMajong::CheckJIULIANBAODENG(BYTE arrHandCardData[], int len)
{
	m_pGameAlgorithm->SortCardAsc(arrHandCardData, len);//排序，似乎没必要
	for (size_t i = 0; i < len; i++)
	{
		if ((arrHandCardData[0] & MASK_COLOR) >> 4 != (arrHandCardData[i] & MASK_COLOR) >> 4 || ((arrHandCardData[i] & MASK_COLOR) >> 4 == 3))
		{
			return false;
		}
	}
	for (size_t i = 0; i < len; i++)
	{
		if (arrHandCardData[i] & MASK_VALUE == 1 || arrHandCardData[i] & MASK_VALUE == 9)
		{
			if (CountEachPaiNum(arrHandCardData, len, arrHandCardData[i]) < 3)
			{
				return false;
			}
		}
		else
		{
			if (CountEachPaiNum(arrHandCardData, len, arrHandCardData[i]) < 1)
			{
				return false;
			}
		}
	}
	return true;
}

//四杠
bool InternationalMajong::CheckSIGANG(BYTE arrHandCardData[], int len)
{
	m_byGangNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, GANG_FLAG);
	if (m_byGangNum == 4)
		return true;
	return false;
}
