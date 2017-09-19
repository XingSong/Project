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

//ͳ��ÿ�����г��ֵĴ���
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

//ͳ��ÿ����ֵ���ֵĴ���
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

//����ϲ����4����̣��ܣ���ɵĺ��ơ�����Ȧ��̡��ŷ�̡�����̡�������
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

//����Ԫ�������У����з���3�����ӡ����Ƽ���
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

//��һɫ����23468���������е��κ�����ɵ�˳�ӡ����ӡ����ĺ��ơ����ƻ�һɫ�����ޡ���������ɵĸ��ƣ��ɼ���һɫ
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

//�������ƣ���һ�ֻ�ɫ�������Ӱ�һһһ�����������߰˾žž���ɵ��ض����ͣ���ͬ��ɫ�κ�1�������Ƽ��ɺ��ơ�������һɫ
bool InternationalMajong::CheckJIULIANBAODENG(BYTE arrHandCardData[], int len)
{
	m_pGameAlgorithm->SortCardAsc(arrHandCardData, len);//�����ƺ�û��Ҫ
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

//�ĸ�
bool InternationalMajong::CheckSIGANG(BYTE arrHandCardData[], int len)
{
	m_byGangNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, GANG_FLAG);
	if (m_byGangNum == 4)
		return true;
	return false;
}

//���߶ԣ���һ�ֻ�ɫ�������������������7�����ӵĺ��ơ�������һɫ�������ˡ�����
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

//ʮ���ۣ�3�������Ƶ�һ�����ƣ�7�����ƹ�13���е�12�����ż�����һ��������ɵĺ��ơ����������롢�����ˡ�����
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

//���۾ţ���������һ���ſ��ӣ��ܣ���������ɵĺ��ơ����������͡�ͬ�̡����֡�
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

//С��ϲ������ʱ�з��Ƶ�3�����ӣ��ܣ��������ַ������������������
bool InternationalMajong::CheckXIAOSIXI(BYTE arrHandCardData[], int len)
{

	//ͳ�Ʒ����п��ӡ��ܵ�����,����Ҫ9���Ʒ�������
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

//С��Ԫ������ʱ�м��Ƶ��������ӻ�ܺͽ��ơ����Ƽ��̡�
bool InternationalMajong::CheckXIAOSANYUAN(BYTE arrHandCardData[], int len)
{
	//ͳ�Ʒ����п��ӡ��ܵ�����,����Ҫ6���Ʒ�������
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

//��һɫ�������ƵĿ��ӣ��ܣ�������ɵĺ��ơ�����������
bool InternationalMajong::CheckZIYISE(BYTE arrHandCardData[], int len)
{
	for (size_t i = 0; i < len;i++)
	{
		if (GetColor(arrHandCardData[i]) != 3)
			return false;
	}
	return true;
}

//һɫ˫���᣺һ�ֻ�ɫ���������ٸ���5Ϊ���ơ�����ƽ�͡��߶ԡ���һɫ
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

//һɫ��ͬ˳��һ�ֻ�ɫ4��������ͬ��˳�ӣ�����һɫ���ڸߡ�һ��ߡ��Ĺ�һ
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

//һɫ�Ľڸߣ�һ�ֻ�ɫ4�����ε���һλ���Ŀ��ӣ�����һɫ��ͬ˳����
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

//һɫ�Ĳ��ߣ�һ�ֻ�ɫ4�����ε���һλ�������ε�����λ����˳��
bool InternationalMajong::CheckYISESIBUGAO(BYTE arrHandCardData[], int len)
{
	
	return false;
}

//���ܣ�3����
bool InternationalMajong::CheckSANGANG(BYTE arrHandCardData[], int len)
{
	return false;
}

//���۾ţ������ƺ�������һ���ŵĿ��Ӽ�������ɵĺ��ơ�����������
bool InternationalMajong::CheckHUNYAOJIU(BYTE arrHandCardData[], int len)
{
	return false;
}
