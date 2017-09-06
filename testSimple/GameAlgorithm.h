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
private:
	CGameLogic *m_pGameLogic;
	BYTE m_HandCardData[HAND_CARD_MAX_REPERTORY];
public:
	CGameAlgorithm();
	~CGameAlgorithm();
	//����AA��AAA��AAAA������
	UINT CountPai(BYTE arrHandCardData[], int len, PAI_REPRESS_FLAG iFlag = NONE_FLAG);

	//ͳ������arrHandCardData��ÿ��Ԫ�س��ֵĴ���,���ظ�countArray
	int* CountElemCount(BYTE arrHandCardData[], int len, int countArray[]);
//��Ū�������ӵ�
	//�ж�������
	bool IsPengPengHu(BYTE arrHandCardData[], int len);

	//�ж�7��
	bool IsQiDuiHu(BYTE arrHandCardData[], int len);

	//�ж�ƽ��
	bool IsPingHu(BYTE arrHandCardData[], int len);
//�����ӵ����Ų���
	//�ж�������
	bool IsPengPengHuWithLaizi(BYTE arrHandCardData[], int len,CGameDataEx *pGameDataEx);

	//����ɫ����ֵ��������
	void SortCardAsc(BYTE arr[], int len);

	//��ֵ�����С�Ƚϣ��ȱȽϻ�ɫ
	bool MaxValue(BYTE a, BYTE b);
public:
	//����Ƿ�����N * ABC + M *DDD
	bool Check_3n(BYTE arr[], int len);

	//ɾ��˳�� 
	bool RemoveABC(BYTE arr[], int len);

	//ɾ������ 
	bool RemoveAAA(BYTE arr[], int len);
};
