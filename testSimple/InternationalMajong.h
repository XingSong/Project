#pragma once
#include "GameAlgorithm.h"
enum HUPAI_TYPE
{
	//88番
	HUPAI_TYPE_DASIXI,    //大四喜：由4副风刻（杠）组成的和牌。不计圈风刻、门风刻、三风刻、碰碰和
	HUPAI_TYPE_DASANYUAN,    //大三元：和牌中，有中发白3副刻子。不计箭刻
	HUPAI_TYPE_LVYISE,    //绿一色：由23468条及发字中的任何牌组成的顺子、刻子、将的和牌。不计混一色。如无“发”字组成的各牌，可计清一色
	HUPAI_TYPE_JIULIANBAODENG,    //九莲宝灯：由一种花色序数牌子按一一一二三四五六七八九九九组成的特定牌型，见同花色任何1张序数牌即成和牌。不计清一色
	HUPAI_TYPE_SIGANG,    //四杠（十八学士）：4个杠
	HUPAI_TYPE_LIANJIDUI,    //连七对：由一种花色序数牌组成序数相连的7个对子的和牌。不计清一色、不求人、单钓
	HUPAI_TYPE_SHISANYAO    //十三幺：3种序数牌的一、九牌，7种字牌共13张中的12个单张及另外一对作将组成的和牌。不计五门齐、不求人、单钓


};
class InternationalMajong
{
private:
	int m_byGangNum;
	int m_byKeziNum;
	int m_byJiangNum;
	CGameAlgorithm *m_pGameAlgorithm;
public:
//胡牌番数
	BYTE byDaSiXi;
	BYTE byDaSanYuan;
	BYTE byLvYiSe;
	BYTE byJiuLianBaoDeng;
	BYTE bySiGang;
public:
	InternationalMajong();
	~InternationalMajong();
	
	//统计每张牌中出现的次数
	int CountEachPaiNum(BYTE arrHandCardData[], int len, BYTE paiValue);

	//获取最大的组合牌型
	bool GetHuPaiMaxCombination(BYTE arrHandCardData[], int len);
	
	//大四喜：由4副风刻（杠）组成的和牌。不计圈风刻、门风刻、三风刻、碰碰和
	bool CheckDASIXI(BYTE arrHandCardData[],int len);

	//大三元：和牌中，有中发白3副刻子。不计箭刻
	bool CheckDASANYUAN(BYTE arrHandCardData[], int len);

	//绿一色：由23468条及发字中的任何牌组成的顺子、刻子、将的和牌。不计混一色。如无“发”字组成的各牌，可计清一色
	bool CheckLVYISE(BYTE arrHandCardData[], int len);

	//九莲宝灯：由一种花色序数牌子按一一一二三四五六七八九九九组成的特定牌型，见同花色任何1张序数牌即成和牌。不计清一色
	bool CheckJIULIANBAODENG(BYTE arrHandCardData[], int len);

	//四杠
	bool CheckSIGANG(BYTE arrHandCardData[], int len);

};

