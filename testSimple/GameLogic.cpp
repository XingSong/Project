#include "GameLogic.h"
#include <assert.h>
#include <iostream>
using namespace std;
//扑克数据
const BYTE CGameLogic::m_cbCardDataArray[MAX_REPERTORY] =
{
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,						//万子
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,						//万子
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,						//万子
	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,						//万子
	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,						//索子
	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,						//索子
	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,						//索子
	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,						//索子
	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,						//同子
	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,						//同子
	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,						//同子
	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,						//同子
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,									//番子
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,									//番子
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,									//番子
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,									//番子
};

//有效判断
bool CGameLogic::IsValidCard(BYTE cbCardData)
{
	BYTE cbValue = (cbCardData&MASK_VALUE);
	BYTE cbColor = (cbCardData&MASK_COLOR) >> 4;
	return (((cbValue >= 1) && (cbValue <= 9) && (cbColor <= 2)) || ((cbValue >= 1) && (cbValue <= 7) && (cbColor == 3)));
}

//扑克转换成对应的牌值索引
BYTE CGameLogic::SwitchToCardIndex(BYTE cbCardData)
{

	assert(IsValidCard(cbCardData));
	return ((cbCardData&MASK_COLOR) >> 4) * 9 + (cbCardData&MASK_VALUE) - 1;
}

//通过索引转换成对应的牌值
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
				cout << "东";
			if (cbValue == 2)
				cout << "南";
			if (cbValue == 3)
				cout << "西";
			if (cbValue == 4)
				cout << "北";
			cout << "风";
		}
		else
		{
			if (cbValue == 5)
				cout << "红中";
			if (cbValue == 6)
				cout << "发财";
			if (cbValue == 7)
				cout << "白板";

		}
		return;
	}
	switch (cbValue)
	{
	case 1:
		cout << "一";
		break;
	case 2:
		cout << "二";
		break;
	case 3:
		cout << "三";
		break;
	case 4:
		cout << "四";
		break;
	case 5:
		cout << "五";
		break;
	case 6:
		cout << "六";
		break;
	case 7:
		cout << "七";
		break;
	case 8:
		cout << "八";
		break;
	case 9:
		cout << "九";
		break;
	default:
		break;
	}

	switch (cbColor)
	{
	case 0:
		cout << "万";
		break;
	case 1:
		cout << "条";
		break;
	case 2:
		cout << "筒";
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
