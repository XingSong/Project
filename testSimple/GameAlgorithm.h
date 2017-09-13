#pragma once
#include "CMD_Sparrow.h"
#include <windows.h>

//AA、AAA、AAAA的数量表示
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
	//计算A、AA、AAA、AAAA的数量
	UINT CountPai(BYTE arrHandCardData[], int len, PAI_REPRESS_FLAG iFlag = NONE_FLAG, CGameDataEx *m_pGameDataEx=nullptr);

	//统计数组arrHandCardData中每个元素出现的次数,返回给countArray
	int* CountElemCount(BYTE arrHandCardData[], int len, int countArray[]);
//先弄不带赖子的
	//判断碰碰和
	bool IsPengPengHu(BYTE arrHandCardData[], int len);

	//判断7对
	bool IsQiDuiHu(BYTE arrHandCardData[], int len);

	//判断平和
	bool IsPingHu(BYTE arrHandCardData[], int len);
//带赖子的试着操作
	//计算A、AA、AAA、AAAA、赖子的数量汇总，方便调用
	void CalKindMJKindNum(BYTE arrHandCardData[], int len, CGameDataEx *m_pGameDataEx = nullptr);
	//判断碰碰和
	bool IsPengPengHuWithLaizi(BYTE arrHandCardData[], int len,CGameDataEx *m_pGameDataEx=nullptr);

	//判断7对
	bool IsQiDuiHuWithLaizi(BYTE arrHandCardData[], int len, CGameDataEx *m_pGameDataEx = nullptr);

	//判断平和
	bool IsPingHuWithLaizi(BYTE arrHandCardData[], int len, CGameDataEx *m_pGameDataEx);

	//按花色、牌值升序排序
	void SortCardAsc(BYTE arr[], int len);

	//数值掩码大小比较，先比较花色
	bool MaxValue(BYTE a, BYTE b);
public:
	//检测是否满足N * ABC + M *DDD
	bool Check_3n(BYTE arr[], int len);

	//删除顺子 
	bool RemoveABC(BYTE arr[], int len);

	//删除刻子 
	bool RemoveAAA(BYTE arr[], int len);
};

