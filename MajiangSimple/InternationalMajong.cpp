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

//ͳ��ÿ����ֵ���ֵĴ���
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

//����ϲ����4����̣��ܣ���ɵĺ��ơ�����Ȧ��̡��ŷ�̡�����̡�������
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

//����Ԫ�������У����з���3�����ӡ����Ƽ���
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

//��һɫ����23468���������е��κ�����ɵ�˳�ӡ����ӡ����ĺ��ơ����ƻ�һɫ�����ޡ���������ɵĸ��ƣ��ɼ���һɫ
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

//�������ƣ���һ�ֻ�ɫ�������Ӱ�һһһ�����������߰˾žž���ɵ��ض����ͣ���ͬ��ɫ�κ�1�������Ƽ��ɺ��ơ�������һɫ
bool InternationalMajong::CheckJIULIANBAODENG(BYTE arrHandCardData[], size_t len)
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
bool InternationalMajong::CheckSIGANG(BYTE arrHandCardData[], size_t len)
{
	m_byGangNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, GANG_FLAG);
	if (m_byGangNum == 4)
		return true;
	return false;
}

//���߶ԣ���һ�ֻ�ɫ�������������������7�����ӵĺ��ơ�������һɫ�������ˡ�����
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

//ʮ���ۣ�3�������Ƶ�һ�����ƣ�7�����ƹ�13���е�12�����ż�����һ��������ɵĺ��ơ����������롢�����ˡ�����
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

//���۾ţ���������һ���ſ��ӣ��ܣ���������ɵĺ��ơ����������͡�ͬ�̡����֡�
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

//С��ϲ������ʱ�з��Ƶ�3�����ӣ��ܣ��������ַ������������������
bool InternationalMajong::CheckXIAOSIXI(BYTE arrHandCardData[], size_t len)
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
bool InternationalMajong::CheckXIAOSANYUAN(BYTE arrHandCardData[], size_t len)
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
bool InternationalMajong::CheckZIYISE(BYTE arrHandCardData[], size_t len)
{
	for (size_t i = 0; i < len;i++)
	{
		if (GetColor(arrHandCardData[i]) != 3)
			return false;
	}
	return true;
}

//һɫ˫���᣺һ�ֻ�ɫ���������ٸ���5Ϊ���ơ�����ƽ�͡��߶ԡ���һɫ
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

//һɫ��ͬ˳��һ�ֻ�ɫ4��������ͬ��˳�ӣ�����һɫ���ڸߡ�һ��ߡ��Ĺ�һ
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

//һɫ�Ľڸߣ�һ�ֻ�ɫ4�����ε���һλ���Ŀ��ӣ�����һɫ��ͬ˳����
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

//һɫ�Ĳ��ߣ�һ�ֻ�ɫ4�����ε���һλ�������ε�����λ����˳��
bool InternationalMajong::CheckYISESIBUGAO(BYTE arrHandCardData[], size_t len)
{
	
	return false;
}

//���ܣ�3����
bool InternationalMajong::CheckSANGANG(BYTE arrHandCardData[], size_t len)
{
	m_byGangNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, GANG_FLAG);
	if (m_byGangNum == 3)
		return true;
	return false;
}

//���۾ţ������ƺ�������һ���ŵĿ��Ӽ�������ɵĺ��ơ�����������
bool InternationalMajong::CheckHUNYAOJIU(BYTE arrHandCardData[], size_t len)
{
	//�������ƺ�������һ������ɵĲ��У�ȫ�����ƵĲ���,ȫ�������ƵĲ���
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

//�߶ԣ���7��������ɵĺ��ơ����Ʋ����ˡ�������
bool InternationalMajong::CheckQIDUI(BYTE arrHandCardData[], size_t len)
{
	return m_pGameAlgorithm->IsQiDuiHu(arrHandCardData, len);
}

//���ǲ�����������7�����ŵĶ����ϱ��з��ף�����3�ֻ�ɫ����λ��147��258��369�е�7�����������û�н��Ƶĺ��ơ����������롢�����ˡ�����
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
	//�����Ƶ����ж�
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

//ȫ˫�̣���2��4��6��8�����ƵĿ��ӡ�������ɵĺ��ơ����������͡�����
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

//��һɫ����һ�ֻ�ɫ����������ɵĺ��ơ���������
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

//һɫ��ͬ˳������ʱ��һ�ֻ�ɫ3��������ͬ��˳�ӡ�����һɫ���ڸ�
bool InternationalMajong::CheckYISESANTONGSHUN(BYTE arrHandCardData[], size_t len)
{
	BYTE tmpHandCardData[HAND_CARD_MAX_REPERTORY - JIANG_FLAG] = { 0 };
	size_t tmpLen = CountArray(tmpHandCardData);
	BYTE tmpHandCardDataKezi[HAND_CARD_MAX_REPERTORY - JIANG_FLAG - KEZI_FLAG] = { 0 };
	size_t tmpLenKezi = CountArray(tmpHandCardDataKezi);

	m_byKeziNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, KEZI_FLAG);
	if (m_byKeziNum != 3)
		return false;
	//�����߽�
	for (size_t i = 0, j = 0; i < len, j < tmpLen; i++)
	{
		if (CountEachPaiNum(arrHandCardData, len, arrHandCardData[i]) == JIANG_FLAG)
			continue;
		tmpHandCardData[j++] = arrHandCardData[i];
	}
	//�����߻�ɫ��һ�����Ǹ�˳��
	for (size_t i = 0, j = 0; i < tmpLen, j < tmpLenKezi; i++)
	{
		if (GetColor(tmpHandCardData[i]) == 3)
			return false;

		if (CountEachPaiNum(tmpHandCardData, tmpLen, tmpHandCardData[i]) != KEZI_FLAG)
			continue;
		tmpHandCardDataKezi[j++] = tmpHandCardData[i];
	}
	//ʣ�µľ�������Ҫ��
	for (size_t i = 0; i < tmpLenKezi - 3; i++)
	{
		if (tmpHandCardDataKezi[i + 3] - tmpHandCardDataKezi[i] != 1)
			return false;
	}

	return true;
}

//һɫ���ڸߣ�����ʱ��һ�ֻ�ɫ3�����ε���һλ���ֵĿ��ӡ�����һɫ��ͬ˳
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
	//���߲�����Ҫ����������,�������������ֵ��Ϊ0�����Ƴ���
	for (size_t i = 0,j = 0; i < tmpLen - 3,j < tmpLenKezi; i++)
	{
		if (CountEachPaiNum(tmpHandCardData, tmpLen, tmpHandCardData[i]) == KEZI_FLAG && tmpHandCardData[i + 3] - tmpHandCardData[i] != 1)
			tmpHandCardData[i + 3] = 0;
		if (tmpHandCardData[i]!=0)
			tmpHandCardDataKezi[j++] = tmpHandCardData[i];
	}
	//ʣ�µľ�������Ҫ��
	for (size_t i = 0; i < tmpLenKezi - 3; i++)
	{
		if (tmpHandCardDataKezi[i + 3] - tmpHandCardDataKezi[i] != 1)
			return false;
	}

	return true;
}

//ȫ����������789��ɵ�˳�ӡ����ӣ��ܣ������Ƶĺ��ơ���������
bool InternationalMajong::CheckQUANDA(BYTE arrHandCardData[], size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		if (GetColor(arrHandCardData[i]) == 3 || (GetCardValue(arrHandCardData[i]) != 7 && GetCardValue(arrHandCardData[i]) != 8 && GetCardValue(arrHandCardData[i]) != 9))
			return false;
	}
	return true;
}

//ȫ�У���������456��ɵ�˳�ӡ����ӣ��ܣ������Ƶĺ��ơ����ƶ���
bool InternationalMajong::CheckQUANZHONG(BYTE arrHandCardData[], size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		if (GetColor(arrHandCardData[i]) == 3 || (GetCardValue(arrHandCardData[i]) != 4 && GetCardValue(arrHandCardData[i]) != 5 && GetCardValue(arrHandCardData[i]) != 6))
			return false;
	}
	return true;
}

//ȫС����������123��ɵ�˳�ӡ����ӣ��ܣ������Ƶĺ��ơ���������
bool InternationalMajong::CheckQUANXIAO(BYTE arrHandCardData[], size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		if (GetColor(arrHandCardData[i]) == 3 || (GetCardValue(arrHandCardData[i]) != 1 && GetCardValue(arrHandCardData[i]) != 2 && GetCardValue(arrHandCardData[i]) != 3))
			return false;
	}
	return true;
}

//ȫ������ʮ���ã�
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
