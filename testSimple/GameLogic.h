#pragma once

#include <windows.h>
#define MAX_REPERTORY				136									//�����
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
	//��ӡ��ʾ��ֵ������Ͳ
	void printPai(BYTE cbCardData);

};

