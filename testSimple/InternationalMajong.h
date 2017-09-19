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
	HUPAI_TYPE_LIANQIDUI,    //���߶ԣ���һ�ֻ�ɫ�������������������7�����ӵĺ��ơ�������һɫ�������ˡ�����
	HUPAI_TYPE_SHISANYAO,    //ʮ���ۣ�3�������Ƶ�һ�����ƣ�7�����ƹ�13���е�12�����ż�����һ��������ɵĺ��ơ����������롢�����ˡ�����

	//64��
	HUPAI_TYPE_QINGYAOJIU,		//���۾ţ���������һ���ſ�����ɵĺ��ơ����������͡�ͬ�̡����֡�
	HUPAI_TYPE_XIAOSIXI,		//С��ϲ������ʱ�з��Ƶ�3�����ӣ��ܣ��������ַ�����������������̡�
	HUPAI_TYPE_XIAOSANYUAN,		//С��Ԫ������ʱ�м��Ƶ��������ӻ�ܺͽ��ơ����Ƽ��̡�
	HUPAI_TYPE_ZIYISE,			//��һɫ�������ƵĿ��ӣ��ܣ�������ɵĺ��ơ����������͡�
	HUPAI_TYPE_SIANKE,			//�İ��̣�4�����̣����ܣ���������ǰ�塢�����͡�
	HUPAI_TYPE_YISESHUANGLONGHUI, //һɫ˫���᣺һ�ֻ�ɫ���������ٸ���5Ϊ���ơ�����ƽ�͡��߶ԡ���һɫ��

	//48��
	HUPAI_TYPE_YISESITONGSHUN, //һɫ��ͬ˳��һ�ֻ�ɫ4��������ͬ��˳�ӣ�����һɫ���ڸߡ�һ��ߡ��Ĺ�һ��
	HUPAI_TYPE_YISESIJIEGAO,	//һɫ�Ľڸߣ�һ�ֻ�ɫ4�����ε���һλ���Ŀ��ӣ�����һɫ��ͬ˳������

	//32��
	HUPAI_TYPE_YISESIBUGAO, //һɫ�Ĳ��ߣ�һ�ֻ�ɫ4�����ε���һλ�������ε�����λ����˳�ӡ�
	HUPAI_TYPE_SANGANG,		//���ܣ�3���ܡ�
	HUPAI_TYPE_HUNYAOJIU	//���۾ţ������ƺ�������һ���ŵĿ��Ӽ�������ɵĺ��ơ�����������

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
	BYTE byLianQIDUI;
	BYTE byShiSanYao;
public:
	InternationalMajong();
	~InternationalMajong();

	//ͳ��ÿ�����г��ֵĴ���
	int CountEachPaiNum(BYTE arrHandCardData[], int len, BYTE paiValue);
	//ͳ��ÿ����ֵ���ֵĴ���
	int CountEachPaiCardValue(BYTE arrHandCardData[], int len, BYTE paiValue);
	//��ȡ�����������
	bool GetHuPaiMaxCombination(BYTE arrHandCardData[], int len);
	//88��
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

	//���߶ԣ���һ�ֻ�ɫ�������������������7�����ӵĺ��ơ�������һɫ�������ˡ�����
	bool CheckLIANQIDUI(BYTE arrHandCardData[], int len);

	//ʮ���ۣ�3�������Ƶ�һ�����ƣ�7�����ƹ�13���е�12�����ż�����һ��������ɵĺ��ơ����������롢�����ˡ�����
	bool CheckSHISANYAO(BYTE arrHandCardData[], int len);
	
	//64��
	//���۾ţ���������һ���ſ��ӣ��ܣ���������ɵĺ��ơ����������͡�ͬ�̡����֡�
	bool CheckQINGYAOJIU(BYTE arrHandCardData[], int len);

	//С��ϲ������ʱ�з��Ƶ�3�����ӣ��ܣ��������ַ������������������
	bool CheckXIAOSIXI(BYTE arrHandCardData[], int len);

	//С��Ԫ������ʱ�м��Ƶ��������ӻ�ܺͽ��ơ����Ƽ��̡�
	bool CheckXIAOSANYUAN(BYTE arrHandCardData[], int len);

	//��һɫ�������ƵĿ��ӣ��ܣ�������ɵĺ��ơ����������͡�
	bool CheckZIYISE(BYTE arrHandCardData[], int len);

	//һɫ˫���᣺һ�ֻ�ɫ���������ٸ���5Ϊ���ơ�����ƽ�͡��߶ԡ���һɫ
	bool CheckYISESHUANGLONGHUI(BYTE arrHandCardData[], int len);

	//48��
	//һɫ��ͬ˳��һ�ֻ�ɫ4��������ͬ��˳�ӣ�����һɫ���ڸߡ�һ��ߡ��Ĺ�һ
	bool CheckYISESITONGSHUN(BYTE arrHandCardData[], int len);

	//һɫ�Ľڸߣ�һ�ֻ�ɫ4�����ε���һλ���Ŀ��ӣ�����һɫ��ͬ˳����
	bool CheckYISESIJIEGAO(BYTE arrHandCardData[], int len);

	//32��
	//һɫ�Ĳ��ߣ�һ�ֻ�ɫ4�����ε���һλ�������ε�����λ����˳�ӡ�
	bool CheckYISESIBUGAO(BYTE arrHandCardData[], int len);

	//���ܣ�3����
	bool CheckSANGANG(BYTE arrHandCardData[], int len);

	//���۾ţ������ƺ�������һ���ŵĿ��Ӽ�������ɵĺ��ơ�����������
	bool CheckHUNYAOJIU(BYTE arrHandCardData[], int len);

};

