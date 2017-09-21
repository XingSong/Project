#define MAX_INDEX					34									//最大索引
#define MAX_REPERTORY				136									//最大库存
#define	MASK_COLOR					0xF0								//花色掩码
#define	MASK_VALUE					0x0F								//数值掩码

#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))				//数组维数
#define HAND_CARD_MAX_REPERTORY		14									//手牌张数

#define CC_SAFE_DELETE(p)	do{if(p){delete (p);(p) = nullptr;}}while(0)
#define MAX_COUNT					14									//最大数目
#define BASE_DECIMAL  16

#define GAME_NAME					TEXT("麻将")						//游戏名字

//牌值列举
class CMJEnum
{
public:
	enum MJ_TYPE
	{
		MJ_TYPE_W1 = 0x01,		//万
		MJ_TYPE_W2 = 0x02,
		MJ_TYPE_W3 = 0x03,
		MJ_TYPE_W4 = 0x04,
		MJ_TYPE_W5 = 0x05,
		MJ_TYPE_W6 = 0x06,
		MJ_TYPE_W7 = 0x07,
		MJ_TYPE_W8 = 0x08,
		MJ_TYPE_W9 = 0x09,

		MJ_TYPE_T1 = 0x11,		//条
		MJ_TYPE_T2 = 0x12,
		MJ_TYPE_T3 = 0x13,
		MJ_TYPE_T4 = 0x14,
		MJ_TYPE_T5 = 0x15,
		MJ_TYPE_T6 = 0x16,
		MJ_TYPE_T7 = 0x17,
		MJ_TYPE_T8 = 0x18,
		MJ_TYPE_T9 = 0x19,

		MJ_TYPE_B1 = 0x21,		//筒
		MJ_TYPE_B2 = 0x22,
		MJ_TYPE_B3 = 0x23,
		MJ_TYPE_B4 = 0x24,
		MJ_TYPE_B5 = 0x25,
		MJ_TYPE_B6 = 0x26,
		MJ_TYPE_B7 = 0x27,
		MJ_TYPE_B8 = 0x28,
		MJ_TYPE_B9 = 0x29,
								//风牌
		MJ_TYPE_FD = 0x31,		//东
		MJ_TYPE_FN = 0x32,		//南
		MJ_TYPE_FX = 0x33,		//西
		MJ_TYPE_FB = 0x34,		//北
								//箭牌
		MJ_TYPE_ZHONG = 0x35,	//红中
		MJ_TYPE_FA = 0x36,		//发财
		MJ_TYPE_BAI = 0x37		//白板

	};
};

#define GetColor(cbCardData)	(((cbCardData)&MASK_COLOR) >> 4)		//获得花色
#define GetCardValue(cbCardData)	((cbCardData)&MASK_VALUE)			//获得牌值
