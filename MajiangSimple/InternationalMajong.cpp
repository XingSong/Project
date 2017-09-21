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
int InternationalMajong::CountEachPaiNum(BYTE arrHandCardData[], size_t len, BYTE paiValue)
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
int InternationalMajong::CountEachPaiCardValue(BYTE arrHandCardData[], size_t len, BYTE paiValue)
{
	int count = 0;
	for (size_t i = 0; i < len; i++)
	{
		if (GetCardValue(arrHandCardData[i]) == paiValue)
			count++;
	}
	return count;
}

bool InternationalMajong::GetHuPaiMaxCombination(BYTE arrHandCardData[], size_t len)
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
bool InternationalMajong::CheckDASIXI(BYTE arrHandCardData[], size_t len)
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
bool InternationalMajong::CheckDASANYUAN(BYTE arrHandCardData[], size_t len)
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
bool InternationalMajong::CheckLVYISE(BYTE arrHandCardData[], size_t len)
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
bool InternationalMajong::CheckJIULIANBAODENG(BYTE arrHandCardData[], size_t len)
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
bool InternationalMajong::CheckSIGANG(BYTE arrHandCardData[], size_t len)
{
	m_byGangNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, GANG_FLAG);
	if (m_byGangNum == 4)
		return true;
	return false;
}

//连七对：由一种花色序数牌组成序数相连的7个对子的和牌。不计清一色、不求人、单钓
bool InternationalMajong::CheckLIANQIDUI(BYTE arrHandCardData[], size_t len)
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
bool InternationalMajong::CheckSHISANYAO(BYTE arrHandCardData[], size_t len)
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
bool InternationalMajong::CheckQINGYAOJIU(BYTE arrHandCardData[], size_t len)
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
bool InternationalMajong::CheckXIAOSIXI(BYTE arrHandCardData[], size_t len)
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
bool InternationalMajong::CheckXIAOSANYUAN(BYTE arrHandCardData[], size_t len)
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
bool InternationalMajong::CheckZIYISE(BYTE arrHandCardData[], size_t len)
{
	for (size_t i = 0; i < len;i++)
	{
		if (GetColor(arrHandCardData[i]) != 3)
			return false;
	}
	return true;
}

//一色双龙会：一种花色的两个老少副，5为将牌。不计平和、七对、清一色
bool InternationalMajong::CheckYISESHUANGLONGHUI(BYTE arrHandCardData[], size_t len)
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
bool InternationalMajong::CheckYISESITONGSHUN(BYTE arrHandCardData[], size_t len)
{
	BYTE tmpHandCardData[HAND_CARD_MAX_REPERTORY - 2] = { 0 };
	size_t tmpLen = sizeof(tmpHandCardData) / sizeof(tmpHandCardData[0]);

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
bool InternationalMajong::CheckYISESIJIEGAO(BYTE arrHandCardData[], size_t len)
{
	BYTE tmpHandCardData[HAND_CARD_MAX_REPERTORY - 2] = { 0 };
	size_t tmpLen = sizeof(tmpHandCardData) / sizeof(tmpHandCardData[0]);

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
bool InternationalMajong::CheckYISESIBUGAO(BYTE arrHandCardData[], size_t len)
{
	
	return false;
}

//三杠：3个杠
bool InternationalMajong::CheckSANGANG(BYTE arrHandCardData[], size_t len)
{
	m_byGangNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, GANG_FLAG);
	if (m_byGangNum == 3)
		return true;
	return false;
}

//混幺九：由字牌和序数牌一、九的刻子及将牌组成的和牌。不计碰碰和
bool InternationalMajong::CheckHUNYAOJIU(BYTE arrHandCardData[], size_t len)
{
	//不是字牌和序数牌一、九组成的不行，全是字牌的不行,全是序数牌的不行
	int ziPaiNum = 0;
	int xushuPaiNum = 0;
	for (size_t i = 0; i < len;i++)
	{
		if (arrHandCardData[i] != CMJEnum::MJ_TYPE_W1&&arrHandCardData[i] != CMJEnum::MJ_TYPE_T1&&arrHandCardData[i] != CMJEnum::MJ_TYPE_W9&&arrHandCardData[i] != CMJEnum::MJ_TYPE_T9&&
			arrHandCardData[i] != CMJEnum::MJ_TYPE_B1&&arrHandCardData[i] != CMJEnum::MJ_TYPE_B9&&arrHandCardData[i] != CMJEnum::MJ_TYPE_FD&&arrHandCardData[i] != CMJEnum::MJ_TYPE_FN&&
			arrHandCardData[i] != CMJEnum::MJ_TYPE_FX&&arrHandCardData[i] != CMJEnum::MJ_TYPE_FB&&arrHandCardData[i] != CMJEnum::MJ_TYPE_ZHONG&&arrHandCardData[i] != CMJEnum::MJ_TYPE_FA&&
			arrHandCardData[i] != CMJEnum::MJ_TYPE_BAI)
			return false;
		if (GetColor(arrHandCardData[0]) == GetColor(arrHandCardData[i]))
			ziPaiNum++;
		if (GetColor(arrHandCardData[i]) != 3)
			xushuPaiNum++;
	}
	if (ziPaiNum == len || xushuPaiNum == len)
		return false;

	if (m_pGameAlgorithm->IsPengPengHu(arrHandCardData, len) || m_pGameAlgorithm->IsQiDuiHu(arrHandCardData, len))
	{
		return true;
	}
	return false;
}

//七对：由7个对子组成的和牌。不计不求人、单钓。
bool InternationalMajong::CheckQIDUI(BYTE arrHandCardData[], size_t len)
{
	return m_pGameAlgorithm->IsQiDuiHu(arrHandCardData, len);
}

//七星不靠：必须有7个单张的东西南北中发白，加上3种花色，数位按147、258、369中的7张序数牌组成没有将牌的和牌。不计五门齐、不求人、单钓
bool InternationalMajong::CheckQIXINGBUKAO(BYTE arrHandCardData[], size_t len)
{
	int ziPaiNum = 0;
	BYTE tmpHandCardData[7] = { 0 };
	for (size_t i = 0; i < len; i++)
	{
		if (CountEachPaiNum(arrHandCardData, len, arrHandCardData[i]) >1)
			return false;
		if (arrHandCardData[i] != CMJEnum::MJ_TYPE_FD&&arrHandCardData[i] != CMJEnum::MJ_TYPE_FN&&arrHandCardData[i] != CMJEnum::MJ_TYPE_FX&&arrHandCardData[i] != CMJEnum::MJ_TYPE_FB&&
			arrHandCardData[i] != CMJEnum::MJ_TYPE_ZHONG&&arrHandCardData[i] != CMJEnum::MJ_TYPE_FA&&arrHandCardData[i] != CMJEnum::MJ_TYPE_BAI)
		{
			tmpHandCardData[ziPaiNum++] = arrHandCardData[i];
			if (ziPaiNum == 7)
				break;
		}
	}
	if (ziPaiNum != 7)
		return false;
	//序数牌单独判断
	for (int i = 0; i < ziPaiNum-1; i++)
	{
		if (GetColor(tmpHandCardData[i]) == GetColor(tmpHandCardData[i + 1]))
		{
			if (tmpHandCardData[i + 1] - tmpHandCardData[i] != 3 && tmpHandCardData[i + 1] - tmpHandCardData[i] != 6)
				return false;
		}
	}
	return true;
}

//全双刻：由2、4、6、8序数牌的刻子、将牌组成的和牌。不计碰碰和、断幺
bool InternationalMajong::CheckQUANSHUANGKE(BYTE arrHandCardData[], size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		if (GetColor(arrHandCardData[i]) == 3 || (GetCardValue(arrHandCardData[i]) & 1) != 0 || CountEachPaiNum(arrHandCardData, len, arrHandCardData[i]) < 2)
			return false;
	}
	m_byKeziNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, KEZI_FLAG);
	if (m_byKeziNum != 4)
		return false;
	return true;
}

//清一色：由一种花色的序数牌组成的和牌。不计无字
bool InternationalMajong::CheckQINGYISE(BYTE arrHandCardData[], size_t len)
{
	for (size_t i = 0; i < len - 1; i++)
	{
		if (GetColor(arrHandCardData[i]) == 3)
			return false;
		if (GetColor(arrHandCardData[i + 1]) != GetColor(arrHandCardData[i]))
			return false;
	}
	return true;
}

//一色三同顺：和牌时有一种花色3副序数相同的顺子。不计一色三节高
bool InternationalMajong::CheckYISESANTONGSHUN(BYTE arrHandCardData[], size_t len)
{
	BYTE tmpHandCardData[HAND_CARD_MAX_REPERTORY - JIANG_FLAG] = { 0 };
	size_t tmpLen = CountArray(tmpHandCardData);
	BYTE tmpHandCardDataKezi[HAND_CARD_MAX_REPERTORY - JIANG_FLAG - KEZI_FLAG] = { 0 };
	size_t tmpLenKezi = CountArray(tmpHandCardDataKezi);

	m_byKeziNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, KEZI_FLAG);
	if (m_byKeziNum != 3)
		return false;
	//先移走将
	for (size_t i = 0, j = 0; i < len, j < tmpLen; i++)
	{
		if (CountEachPaiNum(arrHandCardData, len, arrHandCardData[i]) == JIANG_FLAG)
			continue;
		tmpHandCardData[j++] = arrHandCardData[i];
	}
	//再移走花色不一样的那个顺子
	for (size_t i = 0, j = 0; i < tmpLen, j < tmpLenKezi; i++)
	{
		if (GetColor(tmpHandCardData[i]) == 3)
			return false;

		if (CountEachPaiNum(tmpHandCardData, tmpLen, tmpHandCardData[i]) != KEZI_FLAG)
			continue;
		tmpHandCardDataKezi[j++] = tmpHandCardData[i];
	}
	//剩下的就是所需要的
	for (size_t i = 0; i < tmpLenKezi - 3; i++)
	{
		if (tmpHandCardDataKezi[i + 3] - tmpHandCardDataKezi[i] != 1)
			return false;
	}

	return true;
}

//一色三节高：和牌时有一种花色3副依次递增一位数字的刻子。不计一色三同顺
bool InternationalMajong::CheckYISESANJIEGAO(BYTE arrHandCardData[], size_t len)
{
	BYTE tmpHandCardData[HAND_CARD_MAX_REPERTORY - 2] = { 0 };
	size_t tmpLen = CountArray(tmpHandCardData);
	BYTE tmpHandCardDataKezi[HAND_CARD_MAX_REPERTORY - JIANG_FLAG - KEZI_FLAG] = { 0 };
	size_t tmpLenKezi = CountArray(tmpHandCardDataKezi);
	for (size_t i = 0,j = 0; i < len,j < tmpLen; i++)
	{
		if (CountEachPaiNum(arrHandCardData,len,arrHandCardData[i]) == 2)
			continue;
		tmpHandCardData[j++] = arrHandCardData[i];
	}
	//移走不符合要求的那组刻子,先让那组刻子牌值置为0，再移除掉
	for (size_t i = 0,j = 0; i < tmpLen - 3,j < tmpLenKezi; i++)
	{
		if (CountEachPaiNum(tmpHandCardData, tmpLen, tmpHandCardData[i]) == KEZI_FLAG && tmpHandCardData[i + 3] - tmpHandCardData[i] != 1)
			tmpHandCardData[i + 3] = 0;
		if (tmpHandCardData[i]!=0)
			tmpHandCardDataKezi[j++] = tmpHandCardData[i];
	}
	//剩下的就是所需要的
	for (size_t i = 0; i < tmpLenKezi - 3; i++)
	{
		if (tmpHandCardDataKezi[i + 3] - tmpHandCardDataKezi[i] != 1)
			return false;
	}

	return true;
}

//全大：由序数牌789组成的顺子、刻子（杠）、将牌的和牌。不计无字
bool InternationalMajong::CheckQUANDA(BYTE arrHandCardData[], size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		if (GetColor(arrHandCardData[i]) == 3 || (GetCardValue(arrHandCardData[i]) != 7 && GetCardValue(arrHandCardData[i]) != 8 && GetCardValue(arrHandCardData[i]) != 9))
			return false;
	}
	return true;
}

//全中：由序数牌456组成的顺子、刻子（杠）、将牌的和牌。不计断幺
bool InternationalMajong::CheckQUANZHONG(BYTE arrHandCardData[], size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		if (GetColor(arrHandCardData[i]) == 3 || (GetCardValue(arrHandCardData[i]) != 4 && GetCardValue(arrHandCardData[i]) != 5 && GetCardValue(arrHandCardData[i]) != 6))
			return false;
	}
	return true;
}

//全小：由序数牌123组成的顺子、刻子（杠）、将牌的和牌。不计无字
bool InternationalMajong::CheckQUANXIAO(BYTE arrHandCardData[], size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		if (GetColor(arrHandCardData[i]) == 3 || (GetCardValue(arrHandCardData[i]) != 1 && GetCardValue(arrHandCardData[i]) != 2 && GetCardValue(arrHandCardData[i]) != 3))
			return false;
	}
	return true;
}

//全不靠（十三烂）
bool InternationalMajong::CheckQuanBuKao(BYTE arrHandCardData[], size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		if (CountEachPaiNum(arrHandCardData, len, arrHandCardData[i])>1)
			return false;
		if (GetColor(arrHandCardData[i]) != 3)
		{
			if (GetColor(arrHandCardData[i]) == GetColor(arrHandCardData[i + 1]))
			{
				if (arrHandCardData[i + 1] - arrHandCardData[i] != 3 && arrHandCardData[i + 1] - arrHandCardData[i] != 6)
					return false;
			}
		}
	}
	return true;
}
