#include "Test.h"
#include <iostream>
using namespace std;

CTest::CTest()
{
	memset(arrHandCardData, 0, sizeof(arrHandCardData));	
}


CTest::~CTest()
{
}

void CTest::MainTest()
{
	gameData.ReadConfigZuoPai();
	gameData.ZuoPai();

	memcpy(arrHandCardData, gameData.m_tMatchMJ.byArHandPai[0], HAND_CARD_MAX_REPERTORY);
	objAlgorithm.SortCardAsc(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	for (int i = 0; i < HAND_CARD_MAX_REPERTORY; i++)
	{
		cout << (int)arrHandCardData[i] << ",";
	}
	cout << endl;
	for (int i = 0; i < HAND_CARD_MAX_REPERTORY; i++)
	{
		BYTE tmp = ByteToHexChar(arrHandCardData[i]);
		objAlgorithm.m_pGameLogic->printPai(tmp);
		cout << " ";
	}
	cout << endl;
	for (size_t i = 0; i < HAND_CARD_MAX_REPERTORY; i++)
		arrHandCardData[i] = ByteToHexChar(arrHandCardData[i]);

	//简单胡 test
	//TestSimpleHu();
	if (gameData.m_isHasLaiZiFlag <= 0)
	{
		bool bTagPingHu = objAlgorithm.IsPingHu(arrHandCardData, HAND_CARD_MAX_REPERTORY);
		if (bTagPingHu)
		{
			cout << "平和" << endl;
			//88番 test
			//Test88Fan();
			//64番 test
			//Test64Fan();
			//48番 test
			//Test48Fan();
			//32番 test
			Test32Fan();
		}
		else
			cout << "不是平和" << endl;
	}

}

void CTest::TestSimpleHu()
{
	if (gameData.m_isHasLaiZiFlag <= 0)
	{
		bool bTagPingHu = objAlgorithm.IsPingHu(arrHandCardData, HAND_CARD_MAX_REPERTORY);
		if (bTagPingHu)
			cout << "平和" << endl;
		else
			cout << "不是平和" << endl;
		bool bTagIsPengPengHu = objAlgorithm.IsPengPengHu(arrHandCardData, HAND_CARD_MAX_REPERTORY);
		if (bTagIsPengPengHu)
			cout << "碰碰和" << endl;
		else
			cout << "不是碰碰和" << endl;
		bool bTagIsQiDuiHu = objAlgorithm.IsQiDuiHu(arrHandCardData, HAND_CARD_MAX_REPERTORY);
		if (bTagIsPengPengHu)
			cout << "7对" << endl;
		else
			cout << "不是7对" << endl;
		bool bTagIsQingYiSe = objAlgorithm.IsQingYiSe(arrHandCardData, HAND_CARD_MAX_REPERTORY);
		if (bTagIsQingYiSe)
		{
			if (bTagPingHu)
			{
				cout << "清一色平和" << endl;
			}
			else
				cout << "清一色假和" << endl;
		}
		else
			cout << "不是清一色" << endl;

	}
	else
	{
		BYTE tmpLaizi = ByteToHexChar(gameData.byLaiZiCard);
		cout << "赖子值: ";
		objAlgorithm.m_pGameLogic->printPai(tmpLaizi);
		cout << endl;
		bool bTagIsPengPengHu = objAlgorithm.IsPengPengHuWithLaizi(arrHandCardData, HAND_CARD_MAX_REPERTORY, &gameData);
		if (bTagIsPengPengHu)
			cout << "碰碰和" << endl;
		else
			cout << "不是碰碰和" << endl;
		bool bTagIsQiDuiHuWithLaizi = objAlgorithm.IsQiDuiHuWithLaizi(arrHandCardData, HAND_CARD_MAX_REPERTORY, &gameData);
		if (bTagIsQiDuiHuWithLaizi)
			cout << "7对" << endl;
		else
			cout << "不是7对" << endl;
	}
}

void CTest::Test88Fan()
{
	bool b = objInternationalMajong.CheckDASIXI(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (b)
		cout << "大四喜" << endl;
	else
		cout << "不是大四喜" << endl;

	bool bDaSanYuan = objInternationalMajong.CheckDASANYUAN(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bDaSanYuan)
		cout << "大三元" << endl;
	else
		cout << "不是大三元" << endl;

	bool bCheckLVYISE = objInternationalMajong.CheckLVYISE(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckLVYISE)
		cout << "绿一色" << endl;
	else
		cout << "不是绿一色" << endl;
	bool bCheckJIULIANBAODENG = objInternationalMajong.CheckJIULIANBAODENG(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckJIULIANBAODENG)
		cout << "九莲宝灯" << endl;
	else
		cout << "不是九莲宝灯" << endl;
	bool bCheckLIANJIDUI = objInternationalMajong.CheckLIANQIDUI(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckLIANJIDUI)
		cout << "连七对" << endl;
	else
		cout << "不是连七对" << endl;

	bool bCheckSHISANYAO = objInternationalMajong.CheckSHISANYAO(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckSHISANYAO)
		cout << "十三幺" << endl;
	else
		cout << "不是十三幺" << endl;
}

void CTest::Test64Fan()
{
	bool bCheckQINGYAOJIU = objInternationalMajong.CheckQINGYAOJIU(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckQINGYAOJIU)
		cout << "清幺九" << endl;
	else
		cout << "不是清幺九" << endl;

	bool bCheckXIAOSIXI = objInternationalMajong.CheckXIAOSIXI(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckXIAOSIXI)
		cout << "小四喜" << endl;
	else
		cout << "不是小四喜" << endl;

	bool bCheckXIAOSANYUAN = objInternationalMajong.CheckXIAOSANYUAN(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckXIAOSANYUAN)
		cout << "小三元" << endl;
	else
		cout << "不是小三元" << endl;

	bool bCheckYISESHUANGLONGHUI = objInternationalMajong.CheckYISESHUANGLONGHUI(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckYISESHUANGLONGHUI)
		cout << "一色双龙会" << endl;
	else
		cout << "不是一色双龙会" << endl;
}

void CTest::Test48Fan()
{
	bool bCheckYISESIJIEGAO = objInternationalMajong.CheckYISESIJIEGAO(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckYISESIJIEGAO)
		cout << "一色四节高" << endl;
	else
		cout << "不是一色四节高" << endl;
	bool bCheckYISESITONGSHUN = objInternationalMajong.CheckYISESITONGSHUN(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckYISESITONGSHUN)
		cout << "一色四同顺" << endl;
	else
		cout << "不是一色四同顺" << endl;

}

void CTest::Test32Fan()
{
	bool bCheckYISESIBUGAO = objInternationalMajong.CheckYISESIBUGAO(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckYISESIBUGAO)
		cout << "一色四步高" << endl;
	else
		cout << "不是一色四步高" << endl;

	bool bCheckSANGANG = objInternationalMajong.CheckSANGANG(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckSANGANG)
		cout << "三杠" << endl;
	else
		cout << "不是三杠" << endl;

	bool bCheckHUNYAOJIU = objInternationalMajong.CheckHUNYAOJIU(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckHUNYAOJIU)
		cout << "混幺九" << endl;
	else
		cout << "不是混幺九" << endl;

}
