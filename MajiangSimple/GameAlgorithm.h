#pragma once
#include "CMD_Sparrow.h"
#include <windows.h>

//AA��AAA��AAAA��������ʾ
enum PAI_REPRESS_FLAG
{
	NONE_FLAG,
	DANZHANG_FALG,
	JIANG_FLAG = 2,
	KEZI_FLAG,
	GANG_FLAG
};

class CGameDataEx;
class CGameLogic;
class CGameAlgorithm
{
public:
	CGameLogic *m_pGameLogic;
private:
	BYTE m_HandCardData[HAND_CARD_MAX_REPERTORY];
	struct tagMJKindNum
	{
		int iDanzhangNum;
		int iKeziNum;
		int iGangNum;
		int iJiangNum;
		int iLaiziNum;
	}m_tMJKindNum;
public:
	CGameAlgorithm();
	~CGameAlgorithm();
	//����A��AA��AAA��AAAA������
	int CountPai(BYTE arrHandCardData[], size_t len,PAI_REPRESS_FLAG iFlag);
	UINT CountPaiWithLaizi(BYTE arrHandCardData[], size_t len, PAI_REPRESS_FLAG iFlag, CGameDataEx *m_pGameDataEx = nullptr);
	
	//ͳ������arrHandCardData��ÿ��Ԫ�س��ֵĴ���,���ظ�countArray
	int* CountElemCount(BYTE arrHandCardData[], size_t len, int countArray[]);
//��Ū�������ӵ�
	//�ж�������
	bool IsPengPengHu(BYTE arrHandCardData[], size_t len);

	//�ж�7��
	bool IsQiDuiHu(BYTE arrHandCardData[], size_t len);

	//�ж�ƽ��
	bool IsPingHu(BYTE arrHandCardData[], size_t len);

	//�ж���һɫ
	bool IsQingYiSe(BYTE arrHandCardData[], size_t len);

//�����ӵ����Ų���
	//����A��AA��AAA��AAAA�����ӵ��������ܣ��������
	void CalKindMJKindNum(BYTE arrHandCardData[], size_t len, CGameDataEx *m_pGameDataEx = nullptr);
	//�ж�������
	bool IsPengPengHuWithLaizi(BYTE arrHandCardData[], size_t len,CGameDataEx *m_pGameDataEx=nullptr);

	//�ж�7��
	bool IsQiDuiHuWithLaizi(BYTE arrHandCardData[], size_t len, CGameDataEx *m_pGameDataEx = nullptr);

	//�ж�ƽ��
	bool IsPingHuWithLaizi(BYTE arrHandCardData[], size_t len, CGameDataEx *m_pGameDataEx);

	//����ɫ����ֵ��������
	void SortCardAsc(BYTE arr[], int len);

	//��ֵ�����С�Ƚϣ��ȱȽϻ�ɫ
	bool MaxValue(BYTE a, BYTE b);
public:
	//����Ƿ�����N * ABC + M *DDD
	bool Check_3n(BYTE arr[], size_t len);

	//ɾ��˳�� 
	bool RemoveABC(BYTE arr[], size_t len);

	//ɾ������ 
	bool RemoveAAA(BYTE arr[], size_t len);
};

