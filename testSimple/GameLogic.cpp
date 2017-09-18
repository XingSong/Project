#include "GameLogic.h"
#include <assert.h>
#include <iostream>
using namespace std;
//�˿�����
const BYTE CGameLogic::m_cbCardDataArray[MAX_REPERTORY] =
{
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,						//����
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,						//����
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,						//����
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,						//����
	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,						//����
	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,						//����
	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,						//����
	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,						//����
	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,						//ͬ��
	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,						//ͬ��
	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,						//ͬ��
	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,						//ͬ��
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,									//����
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,									//����
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,									//����
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,									//����
};

//��Ч�ж�
bool CGameLogic::IsValidCard(BYTE cbCardData)
{
	BYTE cbValue = (cbCardData&MASK_VALUE);
	BYTE cbColor = (cbCardData&MASK_COLOR) >> 4;
	return (((cbValue >= 1) && (cbValue <= 9) && (cbColor <= 2)) || ((cbValue >= 1) && (cbValue <= 7) && (cbColor == 3)));
}

//�˿�ת���ɶ�Ӧ����ֵ����
BYTE CGameLogic::SwitchToCardIndex(BYTE cbCardData)
{

	assert(IsValidCard(cbCardData));
	return ((cbCardData&MASK_COLOR) >> 4) * 9 + (cbCardData&MASK_VALUE) - 1;
}

//ͨ������ת���ɶ�Ӧ����ֵ
BYTE CGameLogic::SwitchToCardData(BYTE cbCardIndex)
{
	assert(cbCardIndex < MAX_INDEX);

	assert(cbCardIndex < 34);
	return ((cbCardIndex / 9) << 4) | (cbCardIndex % 9 + 1);
}

void CGameLogic::printPai(BYTE cbCardData)
{
	BYTE cbValue = (cbCardData&MASK_VALUE);
	BYTE cbColor = (cbCardData&MASK_COLOR) >> 4;
	if (cbColor == 3 && cbValue >= 1 && cbValue <= 7)
	{
		if (cbValue >= 1 && cbValue <= 4)
		{
			if (cbValue == 1)
				cout << "��";
			if (cbValue == 2)
				cout << "��";
			if (cbValue == 3)
				cout << "��";
			if (cbValue == 4)
				cout << "��";
			cout << "��";
		}
		else
		{
			if (cbValue == 5)
				cout << "����";
			if (cbValue == 6)
				cout << "����";
			if (cbValue == 7)
				cout << "�װ�";

		}
		return;
	}
	switch (cbValue)
	{
	case 1:
		cout << "һ";
		break;
	case 2:
		cout << "��";
		break;
	case 3:
		cout << "��";
		break;
	case 4:
		cout << "��";
		break;
	case 5:
		cout << "��";
		break;
	case 6:
		cout << "��";
		break;
	case 7:
		cout << "��";
		break;
	case 8:
		cout << "��";
		break;
	case 9:
		cout << "��";
		break;
	default:
		break;
	}

	switch (cbColor)
	{
	case 0:
		cout << "��";
		break;
	case 1:
		cout << "��";
		break;
	case 2:
		cout << "Ͳ";
		break;
	default:
		break;
	}
}

BYTE CGameLogic::getColor(BYTE cbCardData)
{
	return (cbCardData&MASK_COLOR) >> 4;
}

BYTE CGameLogic::getCardValue(BYTE cbCardData)
{
	return (cbCardData&MASK_VALUE);
}
