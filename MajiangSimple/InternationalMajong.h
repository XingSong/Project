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
	HUPAI_TYPE_HUNYAOJIU,	//���۾ţ������ƺ�������һ���ŵĿ��Ӽ�������ɵĺ��ơ�����������

	//24��
	HUPAI_TYPE_QIDUI,			//�߶ԣ���7��������ɵĺ��ơ����Ʋ����ˡ�������
	HUPAI_TYPE_QIXINGBUKAO,		//���ǲ�����������7�����ŵĶ����ϱ��з��ף�����3�ֻ�ɫ����λ��147��258��369�е�7�����������û�н��Ƶĺ��ơ����������롢�����ˡ�������
	HUPAI_TYPE_QUANSHUANGKE,	//ȫ˫�̣���2��4��6��8�����ƵĿ��ӡ�������ɵĺ��ơ����������͡����ۡ�
	HUPAI_TYPE_QINGYISE,		//��һɫ����һ�ֻ�ɫ����������ɵĺ��ơ��������֡�
	HUPAI_TYPE_YISESANTONGSHUN, //һɫ��ͬ˳������ʱ��һ�ֻ�ɫ3��������ͬ��˳�ӡ�����һɫ���ڸߡ�
	HUPAI_TYPE_YISESANJIEGAO,	//һɫ���ڸߣ�����ʱ��һ�ֻ�ɫ3�����ε���һλ���ֵĿ��ӡ�����һɫ��ͬ˳��
	HUPAI_TYPE_QUANDA,			//ȫ����������789��ɵ�˳�ӡ����ӣ��ܣ������Ƶĺ��ơ��������֡�
	HUPAI_TYPE_QUANZHONG,		//ȫ�У���������456��ɵ�˳�ӡ����ӣ��ܣ������Ƶĺ��ơ����ƶ��ۡ�
	HUPAI_TYPE_QUANXIAO			//ȫС����������123��ɵ�˳�ӡ����ӣ��ܣ������Ƶĺ��ơ��������֡�

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
	int CountEachPaiNum(BYTE arrHandCardData[], size_t len, BYTE paiValue);
	//ͳ��ÿ����ֵ���ֵĴ���
	int CountEachPaiCardValue(BYTE arrHandCardData[], size_t len, BYTE paiValue);
	//��ȡ�����������
	bool GetHuPaiMaxCombination(BYTE arrHandCardData[], size_t len);
	//88��
	//����ϲ����4����̣��ܣ���ɵĺ��ơ�����Ȧ��̡��ŷ�̡�����̡�������
	bool CheckDASIXI(BYTE arrHandCardData[],size_t len);

	//����Ԫ�������У����з���3�����ӡ����Ƽ���
	bool CheckDASANYUAN(BYTE arrHandCardData[], size_t len);

	//��һɫ����23468���������е��κ�����ɵ�˳�ӡ����ӡ����ĺ��ơ����ƻ�һɫ�����ޡ���������ɵĸ��ƣ��ɼ���һɫ
	bool CheckLVYISE(BYTE arrHandCardData[], size_t len);

	//�������ƣ���һ�ֻ�ɫ�������Ӱ�һһһ�����������߰˾žž���ɵ��ض����ͣ���ͬ��ɫ�κ�1�������Ƽ��ɺ��ơ�������һɫ
	bool CheckJIULIANBAODENG(BYTE arrHandCardData[], size_t len);

	//�ĸ�
	bool CheckSIGANG(BYTE arrHandCardData[], size_t len);

	//���߶ԣ���һ�ֻ�ɫ�������������������7�����ӵĺ��ơ�������һɫ�������ˡ�����
	bool CheckLIANQIDUI(BYTE arrHandCardData[], size_t len);
	
	//64��
	//���۾ţ���������һ���ſ��ӣ��ܣ���������ɵĺ��ơ����������͡�ͬ�̡����֡�
	bool CheckQINGYAOJIU(BYTE arrHandCardData[], size_t len);

	//С��ϲ������ʱ�з��Ƶ�3�����ӣ��ܣ��������ַ������������������
	bool CheckXIAOSIXI(BYTE arrHandCardData[], size_t len);

	//С��Ԫ������ʱ�м��Ƶ��������ӻ�ܺͽ��ơ����Ƽ��̡�
	bool CheckXIAOSANYUAN(BYTE arrHandCardData[], size_t len);

	//��һɫ�������ƵĿ��ӣ��ܣ�������ɵĺ��ơ����������͡�
	bool CheckZIYISE(BYTE arrHandCardData[], size_t len);

	//һɫ˫���᣺һ�ֻ�ɫ���������ٸ���5Ϊ���ơ�����ƽ�͡��߶ԡ���һɫ
	bool CheckYISESHUANGLONGHUI(BYTE arrHandCardData[], size_t len);

	//48��
	//һɫ��ͬ˳��һ�ֻ�ɫ4��������ͬ��˳�ӣ�����һɫ���ڸߡ�һ��ߡ��Ĺ�һ
	bool CheckYISESITONGSHUN(BYTE arrHandCardData[], size_t len);

	//һɫ�Ľڸߣ�һ�ֻ�ɫ4�����ε���һλ���Ŀ��ӣ�����һɫ��ͬ˳����
	bool CheckYISESIJIEGAO(BYTE arrHandCardData[], size_t len);

	//32��
	//һɫ�Ĳ��ߣ�һ�ֻ�ɫ4�����ε���һλ�������ε�����λ����˳�ӡ�
	bool CheckYISESIBUGAO(BYTE arrHandCardData[], size_t len);

	//���ܣ�3����
	bool CheckSANGANG(BYTE arrHandCardData[], size_t len);

	//���۾ţ������ƺ�������һ���ŵĿ��Ӽ�������ɵĺ��ơ�����������
	bool CheckHUNYAOJIU(BYTE arrHandCardData[], size_t len);

	//24��
	//�߶ԣ���7��������ɵĺ��ơ����Ʋ����ˡ�������
	bool CheckQIDUI(BYTE arrHandCardData[], size_t len);

	//ȫ˫�̣���2��4��6��8�����ƵĿ��ӡ�������ɵĺ��ơ����������͡����ۡ�
	bool CheckQUANSHUANGKE(BYTE arrHandCardData[], size_t len);

	//��һɫ����һ�ֻ�ɫ����������ɵĺ��ơ��������֡�
	bool CheckQINGYISE(BYTE arrHandCardData[], size_t len);

	//һɫ��ͬ˳������ʱ��һ�ֻ�ɫ3��������ͬ��˳�ӡ�����һɫ���ڸߡ�
	bool CheckYISESANTONGSHUN(BYTE arrHandCardData[], size_t len);

	//һɫ���ڸߣ�����ʱ��һ�ֻ�ɫ3�����ε���һλ���ֵĿ��ӡ�����һɫ��ͬ˳��
	bool CheckYISESANJIEGAO(BYTE arrHandCardData[], size_t len);

	//ȫ����������789��ɵ�˳�ӡ����ӣ��ܣ������Ƶĺ��ơ��������֡�
	bool CheckQUANDA(BYTE arrHandCardData[], size_t len);

	//ȫ�У���������456��ɵ�˳�ӡ����ӣ��ܣ������Ƶĺ��ơ����ƶ��ۡ�
	bool CheckQUANZHONG(BYTE arrHandCardData[], size_t len);

	//ȫС����������123��ɵ�˳�ӡ����ӣ��ܣ������Ƶĺ��ơ��������֡�
	bool CheckQUANXIAO(BYTE arrHandCardData[], size_t len);

	/////////////////////////��������///////////////////////////////////////////////////////////////////////////////////////////////
	//12��
	//ȫ������ʮ���ã�
	bool CheckQuanBuKao(BYTE arrHandCardData[], size_t len);
	//�����
	bool CheckZuHeLong(BYTE arrHandCardData[], size_t len);
	//24��
	//���ǲ�����������7�����ŵĶ����ϱ��з��ף�����3�ֻ�ɫ����λ��147��258��369�е�7�����������û�н��Ƶĺ��ơ����������롢�����ˡ�������
	bool CheckQIXINGBUKAO(BYTE arrHandCardData[], size_t len);
	//88��
	//ʮ���ۣ�3�������Ƶ�һ�����ƣ�7�����ƹ�13���е�12�����ż�����һ��������ɵĺ��ơ����������롢�����ˡ�����
	bool CheckSHISANYAO(BYTE arrHandCardData[], size_t len);
};

