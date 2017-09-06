#pragma once
#include "CMD_Sparrow.h"
#include <windows.h>
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
};

