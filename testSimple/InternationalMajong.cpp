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

//统计每张牌值出现的次数
int InternationalMajong::CountEachPaiCardValue(BYTE arrHandCardData[], int len, BYTE paiValue)
{
	int count = 0;
	for (size_t i = 0; i < len; i++)
	{
		if (GetCardValue(arrHandCardData[i]) == paiValue)
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
	if (CheckLIANQIDUI(arrHandCardData, len))
		byLianQIDUI = 88;
	if (CheckSHISANYAO(arrHandCardData, len))
		byShiSanYao = 88;
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
	
	if (CountEachPaiNum(arrHandCardData, len, CMJEnum::MJ_TYPE_FD) >= 3 &&
		CountEachPaiNum(arrHandCardData, len, CMJEnum::MJ_TYPE_FX) >= 3 &&
		CountEachPaiNum(arrHandCardData, len, CMJEnum::MJ_TYPE_FB) >= 3 &&
		CountEachPaiNum(arrHandCardData, len, CMJEnum::MJ_TYPE_FN) >= 3
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

	if (CountEachPaiNum(arrHandCardData, len, CMJEnum::MJ_TYPE_ZHONG) >= 3 &&
		CountEachPaiNum(arrHandCardData, len, CMJEnum::MJ_TYPE_FA) >= 3 &&
		CountEachPaiNum(arrHandCardData, len, CMJEnum::MJ_TYPE_BAI) >= 3
		)
		return true;
	return false;
}

//绿一色：由23468条及发字中的任何牌组成的顺子、刻子、将的和牌。不计混一色。如无“发”字组成的各牌，可计清一色
bool InternationalMajong::CheckLVYISE(BYTE arrHandCardData[], int len)
{
	if (m_pGameAlgorithm->IsPingHu(arrHandCardData, len) || m_pGameAlgorithm->IsQiDuiHu(arrHandCardData, len))
	{
		for (size_t i = 0; i < len; i++)
		{
			if (arrHandCardData[i] != CMJEnum::MJ_TYPE_T2 && 
				arrHandCardData[i] != CMJEnum::MJ_TYPE_T3 &&
				arrHandCardData[i] != CMJEnum::MJ_TYPE_T4 &&
				arrHandCardData[i] != CMJEnum::MJ_TYPE_T6 &&
				arrHandCardData[i] != CMJEnum::MJ_TYPE_T8 &&
				arrHandCardData[i] != CMJEnum::MJ_TYPE_FA)
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
		if (GetColor(arrHandCardData[0]) != GetColor(arrHandCardData[i]) || GetColor(arrHandCardData[i]) == 3)
		{
			return false;
		}
	}
	for (size_t i = 0; i < len; i++)
	{
		if (GetCardValue(arrHandCardData[i]) == 1 || GetCardValue(arrHandCardData[i]) == 9)
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

//连七对：由一种花色序数牌组成序数相连的7个对子的和牌。不计清一色、不求人、单钓
bool InternationalMajong::CheckLIANQIDUI(BYTE arrHandCardData[], int len)
{
	m_pGameAlgorithm->SortCardAsc(arrHandCardData, len);
	for (size_t i = 1; i < len; i++)
	{
		if (GetColor(arrHandCardData[i - 1]) != GetColor(arrHandCardData[i]) || GetColor(arrHandCardData[i]) == 3 || GetColor(arrHandCardData[0]) == 3)
			return false;
	}
	for (size_t i = 0; i < len-2; i++)
	{
		if (arrHandCardData[i + 2] - arrHandCardData[i] != 1 || CountEachPaiNum(arrHandCardData,len,arrHandCardData[i]) != 2)
			return false;
	}
	return true;
}

//十三幺：3种序数牌的一、九牌，7种字牌共13张中的12个单张及另外一对作将组成的和牌。不计五门齐、不求人、单钓
bool InternationalMajong::CheckSHISANYAO(BYTE arrHandCardData[], int len)
{
	for (size_t i = 0; i < len; i++)
	{
		if (GetColor(arrHandCardData[i]) != 3 && GetCardValue(arrHandCardData[i]) != 1 && GetCardValue(arrHandCardData[i]) != 9)
			return false;
	}
	m_byJiangNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, JIANG_FLAG);
	if (m_byJiangNum != 1)
		return false;
	return true;
}

//清幺九：由序数牌一、九刻子（杠）、将牌组成的和牌。不计碰碰和、同刻、无字。
bool InternationalMajong::CheckQINGYAOJIU(BYTE arrHandCardData[], int len)
{
	for (size_t i = 0; i < len; i++)
	{
		if (GetColor(arrHandCardData[i]) == 3 || (GetCardValue(arrHandCardData[i]) != 1 && GetCardValue(arrHandCardData[i]) != 9))
			return false;
	}
	m_byJiangNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, JIANG_FLAG);

	if (m_byJiangNum < 1)
		return false;
	return true;
}

//小四喜：和牌时有风牌的3副刻子（杠），第四种风牌作将。不计三风刻
bool InternationalMajong::CheckXIAOSIXI(BYTE arrHandCardData[], int len)
{

	//统计风牌中刻子、杠的数量,至少要9张牌符合条件
	int iNum = 0;
	for (size_t i = 0; i < len; i++)
	{
		if (arrHandCardData[i] >= CMJEnum::MJ_TYPE_FD&&arrHandCardData[i] <= CMJEnum::MJ_TYPE_FB && CountEachPaiNum(arrHandCardData, len, arrHandCardData[i])>=3)
			iNum++;
	}
	
	for (size_t i = 0; i < len; i++)
	{
		if (iNum == 3 * 3 && arrHandCardData[i] >= CMJEnum::MJ_TYPE_FD&&arrHandCardData[i] <= CMJEnum::MJ_TYPE_FB && CountEachPaiNum(arrHandCardData, len, arrHandCardData[i]) == 2)
			return true;
	}
	return false;
}

//小三元：和牌时有箭牌的两副刻子或杠和将牌。不计箭刻。
bool InternationalMajong::CheckXIAOSANYUAN(BYTE arrHandCardData[], int len)
{
	//统计风牌中刻子、杠的数量,至少要6张牌符合条件
	int iNum = 0;
	for (size_t i = 0; i < len; i++)
	{
		if (arrHandCardData[i] >= CMJEnum::MJ_TYPE_ZHONG&&arrHandCardData[i] <= CMJEnum::MJ_TYPE_BAI && CountEachPaiNum(arrHandCardData, len, arrHandCardData[i]) >= 3)
			iNum++;
	}

	for (size_t i = 0; i < len; i++)
	{
		if (iNum == 3 * 2 && arrHandCardData[i] >= CMJEnum::MJ_TYPE_ZHONG&&arrHandCardData[i] <= CMJEnum::MJ_TYPE_BAI && CountEachPaiNum(arrHandCardData, len, arrHandCardData[i]) == 2)
			return true;
	}
	return false;
}

//字一色：由字牌的刻子（杠）、将组成的和牌。不计碰碰和
bool InternationalMajong::CheckZIYISE(BYTE arrHandCardData[], int len)
{
	for (size_t i = 0; i < len;i++)
	{
		if (GetColor(arrHandCardData[i]) != 3)
			return false;
	}
	return true;
}

//一色双龙会：一种花色的两个老少副，5为将牌。不计平和、七对、清一色
bool InternationalMajong::CheckYISESHUANGLONGHUI(BYTE arrHandCardData[], int len)
{
//	m_byJiangNum = GetJiang(arrHandCardData, len, JIANG_FLAG);
	for (size_t i = 0; i < len-1; i++)
	{
		if (GetColor(arrHandCardData[len-1]) == 3 || GetColor(arrHandCardData[i]) == 3 || GetColor(arrHandCardData[i]) != GetColor(arrHandCardData[i + 1]))
			return false;
	}

	int c1 = CountEachPaiCardValue(arrHandCardData, len, 1);
	int c2 = CountEachPaiCardValue(arrHandCardData, len, 2);
	int c3 = CountEachPaiCardValue(arrHandCardData, len, 3);
	int c5 = CountEachPaiCardValue(arrHandCardData, len, 5);
	int c7 = CountEachPaiCardValue(arrHandCardData, len, 7);
	int c8 = CountEachPaiCardValue(arrHandCardData, len, 8);
	int c9 = CountEachPaiCardValue(arrHandCardData, len, 9);

	if (c5 == 2 &&
		c1 == 2 && c2 == 2 && c3 == 2 && c7 == 2 && c8 == 2 && c9 == 2)
		return true;

	return false;
}

//一色四同顺：一种花色4副序数相同的顺子，不计一色三节高、一般高、四归一
bool InternationalMajong::CheckYISESITONGSHUN(BYTE arrHandCardData[], int len)
{
	BYTE tmpHandCardData[HAND_CARD_MAX_REPERTORY - 2] = { 0 };
	int tmpLen = sizeof(tmpHandCardData) / sizeof(tmpHandCardData[0]);

	for (size_t i = 0,j=0; i < len,j<tmpLen; i++)
	{
		if (CountEachPaiNum(arrHandCardData, len, arrHandCardData[i]) == JIANG_FLAG)
			continue;
		tmpHandCardData[j++] = arrHandCardData[i];
	}

	for (size_t i = 0; i < tmpLen-1; i++)
	{
		if (GetColor(tmpHandCardData[i]) == 3 || GetColor(tmpHandCardData[i - 1]) == 3 || GetColor(tmpHandCardData[i]) != GetColor(tmpHandCardData[i + 1]))
			return false;
	}	
	for (size_t i = 0; i < tmpLen; i++)
	{
		if (CountEachPaiNum(tmpHandCardData, tmpLen, tmpHandCardData[i]) != 4)
			return false;
	}
	for (size_t i = 0; i < tmpLen-4; i++)
	{
		if (tmpHandCardData[i + 4] - tmpHandCardData[i] != 1)
			return false;
	}
	
	return true;
}

//一色四节高：一种花色4副依次递增一位数的刻子，不计一色三同顺、碰
bool InternationalMajong::CheckYISESIJIEGAO(BYTE arrHandCardData[], int len)
{
	BYTE tmpHandCardData[HAND_CARD_MAX_REPERTORY - 2] = { 0 };
	int tmpLen = sizeof(tmpHandCardData) / sizeof(tmpHandCardData[0]);

	for (size_t i = 0, j = 0; i < len, j < tmpLen; i++)
	{
		if (CountEachPaiNum(arrHandCardData, len, arrHandCardData[i]) == JIANG_FLAG)
			continue;
		tmpHandCardData[j++] = arrHandCardData[i];
	}

	for (size_t i = 0; i < tmpLen - 1; i++)
	{
		if (GetColor(tmpHandCardData[i]) == 3 || GetColor(tmpHandCardData[i - 1]) == 3 || GetColor(tmpHandCardData[i]) != GetColor(tmpHandCardData[i + 1]))
			return false;
	}
	for (size_t i = 0; i < tmpLen; i++)
	{
		if (CountEachPaiNum(tmpHandCardData, tmpLen, tmpHandCardData[i]) != KEZI_FLAG)
			return false;
	}
	for (size_t i = 0; i < tmpLen - 3; i++)
	{
		if (tmpHandCardData[i + 3] - tmpHandCardData[i] != 1)
			return false;
	}

	return true;
}

//一色四步高：一种花色4副依次递增一位数或依次递增二位数的顺子
bool InternationalMajong::CheckYISESIBUGAO(BYTE arrHandCardData[], int len)
{
	
	return false;
}

//三杠：3个杠
bool InternationalMajong::CheckSANGANG(BYTE arrHandCardData[], int len)
{
	return false;
}

//混幺九：由字牌和序数牌一、九的刻子及将牌组成的和牌。不计碰碰和
bool InternationalMajong::CheckHUNYAOJIU(BYTE arrHandCardData[], int len)
{
	return false;
}
