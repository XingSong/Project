#pragma once
#include "CMD_Sparrow.h"
#include <windows.h>
class CGameLogic
{
public:
	static const BYTE				m_cbCardDataArray[MAX_REPERTORY];	//�˿�����;
public:
	CGameLogic(){}
	~CGameLogic(){}
	//��Ч�ж�
	bool IsValidCard(BYTE cbCardData);

	//�˿�ת��
	BYTE SwitchToCardIndex(BYTE cbCardData);

	BYTE SwitchToCardData(BYTE cbCardIndex);
};

