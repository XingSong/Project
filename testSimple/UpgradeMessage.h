#define HAND_CARD_NUM			14				//�����������
#define PLAY_COUNT				4				// ��Ϸ����	
#include <windows.h>
//��������
struct tagMatchMJ
{
	//���Ʋ�����14�� 
	BYTE byArHandPai[PLAY_COUNT][HAND_CARD_NUM];
	//��������	  
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