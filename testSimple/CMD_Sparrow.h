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