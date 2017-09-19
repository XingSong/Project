#pragma once

#include <windows.h>
#define MAX_REPERTORY				136									//最大库存
class CGameLogic
{
public:
	static const BYTE				m_cbCardDataArray[MAX_REPERTORY];	//扑克数据;
public:
	CGameLogic(){}
	~CGameLogic(){}
	//有效判断
	bool IsValidCard(BYTE cbCardData);

	//扑克转换
	BYTE SwitchToCardIndex(BYTE cbCardData);

	BYTE SwitchToCardData(BYTE cbCardIndex);
	//打印显示牌值，如五筒
	void printPai(BYTE cbCardData);

};

