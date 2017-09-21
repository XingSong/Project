#define HAND_CARD_NUM			14				//最大手牌张数
#define PLAY_COUNT				4				// 游戏人数	
#include <windows.h>
//配牌数据
struct tagMatchMJ
{
	//手牌不超过14张 
	BYTE byArHandPai[PLAY_COUNT][HAND_CARD_NUM];
	//手牌张数	  
	BYTE byArHandPaiCount[PLAY_COUNT];
	tagMatchMJ()
	{
		Init();
	}
	void Init()
	{
		memset(byArHandPai, 255, sizeof(byArHandPai));
		memset(byArHandPaiCount, 0, sizeof(byArHandPaiCount));
	}
};