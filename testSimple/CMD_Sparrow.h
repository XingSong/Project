#define MAX_INDEX					34									//�������
#define MAX_REPERTORY				136									//�����
#define	MASK_COLOR					0xF0								//��ɫ����
#define	MASK_VALUE					0x0F								//��ֵ����

#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))				//����ά��
#define HAND_CARD_MAX_REPERTORY		14									//��������

#define CC_SAFE_DELETE(p)	do{if(p){delete (p);(p) = nullptr;}}while(0)
#define MAX_COUNT					14									//�����Ŀ
#define BASE_DECIMAL  16

#define GAME_NAME					TEXT("�齫")						//��Ϸ����

//��ֵ�о�
class CMJEnum
{
public:
	enum MJ_TYPE
	{
		MJ_TYPE_W1 = 0x01,		//��
		MJ_TYPE_W2 = 0x02,
		MJ_TYPE_W3 = 0x03,
		MJ_TYPE_W4 = 0x04,
		MJ_TYPE_W5 = 0x05,
		MJ_TYPE_W6 = 0x06,
		MJ_TYPE_W7 = 0x07,
		MJ_TYPE_W8 = 0x08,
		MJ_TYPE_W9 = 0x09,

		MJ_TYPE_T1 = 0x11,		//��
		MJ_TYPE_T2 = 0x12,
		MJ_TYPE_T3 = 0x13,
		MJ_TYPE_T4 = 0x14,
		MJ_TYPE_T5 = 0x15,
		MJ_TYPE_T6 = 0x16,
		MJ_TYPE_T7 = 0x17,
		MJ_TYPE_T8 = 0x18,
		MJ_TYPE_T9 = 0x19,

		MJ_TYPE_B1 = 0x21,		//Ͳ
		MJ_TYPE_B2 = 0x22,
		MJ_TYPE_B3 = 0x23,
		MJ_TYPE_B4 = 0x24,
		MJ_TYPE_B5 = 0x25,
		MJ_TYPE_B6 = 0x26,
		MJ_TYPE_B7 = 0x27,
		MJ_TYPE_B8 = 0x28,
		MJ_TYPE_B9 = 0x29,
								//����
		MJ_TYPE_FD = 0x31,		//��
		MJ_TYPE_FN = 0x32,		//��
		MJ_TYPE_FX = 0x33,		//��
		MJ_TYPE_FB = 0x34,		//��
								//����
		MJ_TYPE_ZHONG = 0x35,	//����
		MJ_TYPE_FA = 0x36,		//����
		MJ_TYPE_BAI = 0x37		//�װ�

	};
};

#define GetColor(cbCardData)	(((cbCardData)&MASK_COLOR) >> 4)		//��û�ɫ
#define GetCardValue(cbCardData)	((cbCardData)&MASK_VALUE)			//�����ֵ
