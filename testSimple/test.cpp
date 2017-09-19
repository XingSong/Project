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

	//�򵥺� test
	//TestSimpleHu();
	if (gameData.m_isHasLaiZiFlag <= 0)
	{
		bool bTagPingHu = objAlgorithm.IsPingHu(arrHandCardData, HAND_CARD_MAX_REPERTORY);
		if (bTagPingHu)
		{
			cout << "ƽ��" << endl;
			//88�� test
			//Test88Fan();
			//64�� test
			//Test64Fan();
			//48�� test
			//Test48Fan();
			//32�� test
			Test32Fan();
		}
		else
			cout << "����ƽ��" << endl;
	}

}

void CTest::TestSimpleHu()
{
	if (gameData.m_isHasLaiZiFlag <= 0)
	{
		bool bTagPingHu = objAlgorithm.IsPingHu(arrHandCardData, HAND_CARD_MAX_REPERTORY);
		if (bTagPingHu)
			cout << "ƽ��" << endl;
		else
			cout << "����ƽ��" << endl;
		bool bTagIsPengPengHu = objAlgorithm.IsPengPengHu(arrHandCardData, HAND_CARD_MAX_REPERTORY);
		if (bTagIsPengPengHu)
			cout << "������" << endl;
		else
			cout << "����������" << endl;
		bool bTagIsQiDuiHu = objAlgorithm.IsQiDuiHu(arrHandCardData, HAND_CARD_MAX_REPERTORY);
		if (bTagIsPengPengHu)
			cout << "7��" << endl;
		else
			cout << "����7��" << endl;
		bool bTagIsQingYiSe = objAlgorithm.IsQingYiSe(arrHandCardData, HAND_CARD_MAX_REPERTORY);
		if (bTagIsQingYiSe)
		{
			if (bTagPingHu)
			{
				cout << "��һɫƽ��" << endl;
			}
			else
				cout << "��һɫ�ٺ�" << endl;
		}
		else
			cout << "������һɫ" << endl;

	}
	else
	{
		BYTE tmpLaizi = ByteToHexChar(gameData.byLaiZiCard);
		cout << "����ֵ: ";
		objAlgorithm.m_pGameLogic->printPai(tmpLaizi);
		cout << endl;
		bool bTagIsPengPengHu = objAlgorithm.IsPengPengHuWithLaizi(arrHandCardData, HAND_CARD_MAX_REPERTORY, &gameData);
		if (bTagIsPengPengHu)
			cout << "������" << endl;
		else
			cout << "����������" << endl;
		bool bTagIsQiDuiHuWithLaizi = objAlgorithm.IsQiDuiHuWithLaizi(arrHandCardData, HAND_CARD_MAX_REPERTORY, &gameData);
		if (bTagIsQiDuiHuWithLaizi)
			cout << "7��" << endl;
		else
			cout << "����7��" << endl;
	}
}

void CTest::Test88Fan()
{
	bool b = objInternationalMajong.CheckDASIXI(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (b)
		cout << "����ϲ" << endl;
	else
		cout << "���Ǵ���ϲ" << endl;

	bool bDaSanYuan = objInternationalMajong.CheckDASANYUAN(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bDaSanYuan)
		cout << "����Ԫ" << endl;
	else
		cout << "���Ǵ���Ԫ" << endl;

	bool bCheckLVYISE = objInternationalMajong.CheckLVYISE(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckLVYISE)
		cout << "��һɫ" << endl;
	else
		cout << "������һɫ" << endl;
	bool bCheckJIULIANBAODENG = objInternationalMajong.CheckJIULIANBAODENG(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckJIULIANBAODENG)
		cout << "��������" << endl;
	else
		cout << "���Ǿ�������" << endl;
	bool bCheckLIANJIDUI = objInternationalMajong.CheckLIANQIDUI(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckLIANJIDUI)
		cout << "���߶�" << endl;
	else
		cout << "�������߶�" << endl;

	bool bCheckSHISANYAO = objInternationalMajong.CheckSHISANYAO(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckSHISANYAO)
		cout << "ʮ����" << endl;
	else
		cout << "����ʮ����" << endl;
}

void CTest::Test64Fan()
{
	bool bCheckQINGYAOJIU = objInternationalMajong.CheckQINGYAOJIU(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckQINGYAOJIU)
		cout << "���۾�" << endl;
	else
		cout << "�������۾�" << endl;

	bool bCheckXIAOSIXI = objInternationalMajong.CheckXIAOSIXI(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckXIAOSIXI)
		cout << "С��ϲ" << endl;
	else
		cout << "����С��ϲ" << endl;

	bool bCheckXIAOSANYUAN = objInternationalMajong.CheckXIAOSANYUAN(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckXIAOSANYUAN)
		cout << "С��Ԫ" << endl;
	else
		cout << "����С��Ԫ" << endl;

	bool bCheckYISESHUANGLONGHUI = objInternationalMajong.CheckYISESHUANGLONGHUI(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckYISESHUANGLONGHUI)
		cout << "һɫ˫����" << endl;
	else
		cout << "����һɫ˫����" << endl;
}

void CTest::Test48Fan()
{
	bool bCheckYISESIJIEGAO = objInternationalMajong.CheckYISESIJIEGAO(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckYISESIJIEGAO)
		cout << "һɫ�Ľڸ�" << endl;
	else
		cout << "����һɫ�Ľڸ�" << endl;
	bool bCheckYISESITONGSHUN = objInternationalMajong.CheckYISESITONGSHUN(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckYISESITONGSHUN)
		cout << "һɫ��ͬ˳" << endl;
	else
		cout << "����һɫ��ͬ˳" << endl;

}

void CTest::Test32Fan()
{
	bool bCheckYISESIBUGAO = objInternationalMajong.CheckYISESIBUGAO(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckYISESIBUGAO)
		cout << "һɫ�Ĳ���" << endl;
	else
		cout << "����һɫ�Ĳ���" << endl;

	bool bCheckSANGANG = objInternationalMajong.CheckSANGANG(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckSANGANG)
		cout << "����" << endl;
	else
		cout << "��������" << endl;

	bool bCheckHUNYAOJIU = objInternationalMajong.CheckHUNYAOJIU(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	if (bCheckHUNYAOJIU)
		cout << "���۾�" << endl;
	else
		cout << "���ǻ��۾�" << endl;

}
