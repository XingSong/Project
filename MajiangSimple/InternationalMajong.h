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
	HUPAI_TYPE_LIANQIDUI,    //连七对：由一种花色序数牌组成序数相连的7个对子的和牌。不计清一色、不求人、单钓
	HUPAI_TYPE_SHISANYAO,    //十三幺：3种序数牌的一、九牌，7种字牌共13张中的12个单张及另外一对作将组成的和牌。不计五门齐、不求人、单钓

	//64番
	HUPAI_TYPE_QINGYAOJIU,		//清幺九：由序数牌一、九刻子组成的和牌。不计碰碰和、同刻、无字。
	HUPAI_TYPE_XIAOSIXI,		//小四喜：和牌时有风牌的3副刻子（杠），第四种风牌作将。不计三风刻。
	HUPAI_TYPE_XIAOSANYUAN,		//小三元：和牌时有箭牌的两副刻子或杠和将牌。不计箭刻。
	HUPAI_TYPE_ZIYISE,			//字一色：由字牌的刻子（杠）、将组成的和牌。不计碰碰和。
	HUPAI_TYPE_SIANKE,			//四暗刻：4个暗刻（暗杠）。不计门前清、碰碰和。
	HUPAI_TYPE_YISESHUANGLONGHUI, //一色双龙会：一种花色的两个老少副，5为将牌。不计平和、七对、清一色。

	//48番
	HUPAI_TYPE_YISESITONGSHUN, //一色四同顺：一种花色4副序数相同的顺子，不计一色三节高、一般高、四归一。
	HUPAI_TYPE_YISESIJIEGAO,	//一色四节高：一种花色4副依次递增一位数的刻子，不计一色三同顺、碰。

	//32番
	HUPAI_TYPE_YISESIBUGAO, //一色四步高：一种花色4副依次递增一位数或依次递增二位数的顺子。
	HUPAI_TYPE_SANGANG,		//三杠：3个杠。
	HUPAI_TYPE_HUNYAOJIU,	//混幺九：由字牌和序数牌一、九的刻子及将牌组成的和牌。不计碰碰和

	//24番
	HUPAI_TYPE_QIDUI,			//七对：由7个对子组成的和牌。不计不求人、单钓。
	HUPAI_TYPE_QIXINGBUKAO,		//七星不靠：必须有7个单张的东西南北中发白，加上3种花色，数位按147、258、369中的7张序数牌组成没有将牌的和牌。不计五门齐、不求人、单钓。
	HUPAI_TYPE_QUANSHUANGKE,	//全双刻：由2、4、6、8序数牌的刻子、将牌组成的和牌。不计碰碰和、断幺。
	HUPAI_TYPE_QINGYISE,		//清一色：由一种花色的序数牌组成的和牌。不计无字。
	HUPAI_TYPE_YISESANTONGSHUN, //一色三同顺：和牌时有一种花色3副序数相同的顺子。不计一色三节高。
	HUPAI_TYPE_YISESANJIEGAO,	//一色三节高：和牌时有一种花色3副依次递增一位数字的刻子。不计一色三同顺。
	HUPAI_TYPE_QUANDA,			//全大：由序数牌789组成的顺子、刻子（杠）、将牌的和牌。不计无字。
	HUPAI_TYPE_QUANZHONG,		//全中：由序数牌456组成的顺子、刻子（杠）、将牌的和牌。不计断幺。
	HUPAI_TYPE_QUANXIAO			//全小：由序数牌123组成的顺子、刻子（杠）、将牌的和牌。不计无字。

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
	BYTE byLianQIDUI;
	BYTE byShiSanYao;
public:
	InternationalMajong();
	~InternationalMajong();

	//统计每张牌中出现的次数
	int CountEachPaiNum(BYTE arrHandCardData[], size_t len, BYTE paiValue);
	//统计每张牌值出现的次数
	int CountEachPaiCardValue(BYTE arrHandCardData[], size_t len, BYTE paiValue);
	//获取最大的组合牌型
	bool GetHuPaiMaxCombination(BYTE arrHandCardData[], size_t len);
	//88番
	//大四喜：由4副风刻（杠）组成的和牌。不计圈风刻、门风刻、三风刻、碰碰和
	bool CheckDASIXI(BYTE arrHandCardData[],size_t len);

	//大三元：和牌中，有中发白3副刻子。不计箭刻
	bool CheckDASANYUAN(BYTE arrHandCardData[], size_t len);

	//绿一色：由23468条及发字中的任何牌组成的顺子、刻子、将的和牌。不计混一色。如无“发”字组成的各牌，可计清一色
	bool CheckLVYISE(BYTE arrHandCardData[], size_t len);

	//九莲宝灯：由一种花色序数牌子按一一一二三四五六七八九九九组成的特定牌型，见同花色任何1张序数牌即成和牌。不计清一色
	bool CheckJIULIANBAODENG(BYTE arrHandCardData[], size_t len);

	//四杠
	bool CheckSIGANG(BYTE arrHandCardData[], size_t len);

	//连七对：由一种花色序数牌组成序数相连的7个对子的和牌。不计清一色、不求人、单钓
	bool CheckLIANQIDUI(BYTE arrHandCardData[], size_t len);
	
	//64番
	//清幺九：由序数牌一、九刻子（杠）、将牌组成的和牌。不计碰碰和、同刻、无字。
	bool CheckQINGYAOJIU(BYTE arrHandCardData[], size_t len);

	//小四喜：和牌时有风牌的3副刻子（杠），第四种风牌作将。不计三风刻
	bool CheckXIAOSIXI(BYTE arrHandCardData[], size_t len);

	//小三元：和牌时有箭牌的两副刻子或杠和将牌。不计箭刻。
	bool CheckXIAOSANYUAN(BYTE arrHandCardData[], size_t len);

	//字一色：由字牌的刻子（杠）、将组成的和牌。不计碰碰和。
	bool CheckZIYISE(BYTE arrHandCardData[], size_t len);

	//一色双龙会：一种花色的两个老少副，5为将牌。不计平和、七对、清一色
	bool CheckYISESHUANGLONGHUI(BYTE arrHandCardData[], size_t len);

	//48番
	//一色四同顺：一种花色4副序数相同的顺子，不计一色三节高、一般高、四归一
	bool CheckYISESITONGSHUN(BYTE arrHandCardData[], size_t len);

	//一色四节高：一种花色4副依次递增一位数的刻子，不计一色三同顺、碰
	bool CheckYISESIJIEGAO(BYTE arrHandCardData[], size_t len);

	//32番
	//一色四步高：一种花色4副依次递增一位数或依次递增二位数的顺子。
	bool CheckYISESIBUGAO(BYTE arrHandCardData[], size_t len);

	//三杠：3个杠
	bool CheckSANGANG(BYTE arrHandCardData[], size_t len);

	//混幺九：由字牌和序数牌一、九的刻子及将牌组成的和牌。不计碰碰和
	bool CheckHUNYAOJIU(BYTE arrHandCardData[], size_t len);

	//24番
	//七对：由7个对子组成的和牌。不计不求人、单钓。
	bool CheckQIDUI(BYTE arrHandCardData[], size_t len);

	//全双刻：由2、4、6、8序数牌的刻子、将牌组成的和牌。不计碰碰和、断幺。
	bool CheckQUANSHUANGKE(BYTE arrHandCardData[], size_t len);

	//清一色：由一种花色的序数牌组成的和牌。不计无字。
	bool CheckQINGYISE(BYTE arrHandCardData[], size_t len);

	//一色三同顺：和牌时有一种花色3副序数相同的顺子。不计一色三节高。
	bool CheckYISESANTONGSHUN(BYTE arrHandCardData[], size_t len);

	//一色三节高：和牌时有一种花色3副依次递增一位数字的刻子。不计一色三同顺。
	bool CheckYISESANJIEGAO(BYTE arrHandCardData[], size_t len);

	//全大：由序数牌789组成的顺子、刻子（杠）、将牌的和牌。不计无字。
	bool CheckQUANDA(BYTE arrHandCardData[], size_t len);

	//全中：由序数牌456组成的顺子、刻子（杠）、将牌的和牌。不计断幺。
	bool CheckQUANZHONG(BYTE arrHandCardData[], size_t len);

	//全小：由序数牌123组成的顺子、刻子（杠）、将牌的和牌。不计无字。
	bool CheckQUANXIAO(BYTE arrHandCardData[], size_t len);

	/////////////////////////特殊牌型///////////////////////////////////////////////////////////////////////////////////////////////
	//12番
	//全不靠（十三烂）
	bool CheckQuanBuKao(BYTE arrHandCardData[], size_t len);
	//组合龙
	bool CheckZuHeLong(BYTE arrHandCardData[], size_t len);
	//24番
	//七星不靠：必须有7个单张的东西南北中发白，加上3种花色，数位按147、258、369中的7张序数牌组成没有将牌的和牌。不计五门齐、不求人、单钓。
	bool CheckQIXINGBUKAO(BYTE arrHandCardData[], size_t len);
	//88番
	//十三幺：3种序数牌的一、九牌，7种字牌共13张中的12个单张及另外一对作将组成的和牌。不计五门齐、不求人、单钓
	bool CheckSHISANYAO(BYTE arrHandCardData[], size_t len);
};

