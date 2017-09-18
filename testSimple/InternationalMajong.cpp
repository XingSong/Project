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
	BYTE iPaiValue = 0x31;
	
	if (CountEachPaiNum(arrHandCardData, len, iPaiValue) >= 3 &&
		CountEachPaiNum(arrHandCardData, len, iPaiValue + 1) >= 3 &&
		CountEachPaiNum(arrHandCardData, len, iPaiValue + 2) >= 3 &&
		CountEachPaiNum(arrHandCardData, len, iPaiValue + 3) >= 3
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
	BYTE iPaiValue = 0x35;

	if (CountEachPaiNum(arrHandCardData, len, iPaiValue) >= 3 &&
		CountEachPaiNum(arrHandCardData, len, iPaiValue + 1) >= 3 &&
		CountEachPaiNum(arrHandCardData, len, iPaiValue + 2) >= 3 
		)
		return true;
	return false;
}

//��һɫ����23468���������е��κ�����ɵ�˳�ӡ����ӡ����ĺ��ơ����ƻ�һɫ�����ޡ���������ɵĸ��ƣ��ɼ���һɫ
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

//�������ƣ���һ�ֻ�ɫ�������Ӱ�һһһ�����������߰˾žž���ɵ��ض����ͣ���ͬ��ɫ�κ�1�������Ƽ��ɺ��ơ�������һɫ
bool InternationalMajong::CheckJIULIANBAODENG(BYTE arrHandCardData[], int len)
{
	m_pGameAlgorithm->SortCardAsc(arrHandCardData, len);//�����ƺ�û��Ҫ
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

//�ĸ�
bool InternationalMajong::CheckSIGANG(BYTE arrHandCardData[], int len)
{
	m_byGangNum = m_pGameAlgorithm->CountPai(arrHandCardData, len, GANG_FLAG);
	if (m_byGangNum == 4)
		return true;
	return false;
}
