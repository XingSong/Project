#pragma once
#include "GameAlgorithm.h"
enum HUPAI_TYPE
{
	//88��
	HUPAI_TYPE_DASIXI,    //����ϲ����4����̣��ܣ���ɵĺ��ơ�����Ȧ��̡��ŷ�̡�����̡�������
	HUPAI_TYPE_DASANYUAN,    //����Ԫ�������У����з���3�����ӡ����Ƽ���
	HUPAI_TYPE_LVYISE,    //��һɫ����23468���������е��κ�����ɵ�˳�ӡ����ӡ����ĺ��ơ����ƻ�һɫ�����ޡ���������ɵĸ��ƣ��ɼ���һɫ
	HUPAI_TYPE_JIULIANBAODENG,    //�������ƣ���һ�ֻ�ɫ�������Ӱ�һһһ�����������߰˾žž���ɵ��ض����ͣ���ͬ��ɫ�κ�1�������Ƽ��ɺ��ơ�������һɫ
	HUPAI_TYPE_SIGANG,    //�ĸܣ�ʮ��ѧʿ����4����
	HUPAI_TYPE_LIANJIDUI,    //���߶ԣ���һ�ֻ�ɫ�������������������7�����ӵĺ��ơ�������һɫ�������ˡ�����
	HUPAI_TYPE_SHISANYAO    //ʮ���ۣ�3�������Ƶ�һ�����ƣ�7�����ƹ�13���е�12�����ż�����һ��������ɵĺ��ơ����������롢�����ˡ�����


};
class InternationalMajong
{
private:
	int m_byGangNum;
	int m_byKeziNum;
	int m_byJiangNum;
	CGameAlgorithm *m_pGameAlgorithm;
public:
//���Ʒ���
	BYTE byDaSiXi;
	BYTE byDaSanYuan;
	BYTE byLvYiSe;
	BYTE byJiuLianBaoDeng;
	BYTE bySiGang;
public:
	InternationalMajong();
	~InternationalMajong();
	
	//ͳ��ÿ�����г��ֵĴ���
	int CountEachPaiNum(BYTE arrHandCardData[], int len, BYTE paiValue);

	//��ȡ�����������
	bool GetHuPaiMaxCombination(BYTE arrHandCardData[], int len);
	
	//����ϲ����4����̣��ܣ���ɵĺ��ơ�����Ȧ��̡��ŷ�̡�����̡�������
	bool CheckDASIXI(BYTE arrHandCardData[],int len);

	//����Ԫ�������У����з���3�����ӡ����Ƽ���
	bool CheckDASANYUAN(BYTE arrHandCardData[], int len);

	//��һɫ����23468���������е��κ�����ɵ�˳�ӡ����ӡ����ĺ��ơ����ƻ�һɫ�����ޡ���������ɵĸ��ƣ��ɼ���һɫ
	bool CheckLVYISE(BYTE arrHandCardData[], int len);

	//�������ƣ���һ�ֻ�ɫ�������Ӱ�һһһ�����������߰˾žž���ɵ��ض����ͣ���ͬ��ɫ�κ�1�������Ƽ��ɺ��ơ�������һɫ
	bool CheckJIULIANBAODENG(BYTE arrHandCardData[], int len);

	//�ĸ�
	bool CheckSIGANG(BYTE arrHandCardData[], int len);

};

