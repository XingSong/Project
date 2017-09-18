#define _CRT_SECURE_NO_WARNINGS
#include "GameLogic.h"
#include "InternationalMajong.h"
//#include "RapidJson.h"
#include "GameDataEx.h"

#include <cstdlib>
#include <iostream>
using namespace std;

//27->0x27,牌值转换
BYTE ByteToHexChar(BYTE pai)
{
	return pai / 10 * BASE_DECIMAL + pai % 10;
}
void main()
{
	//读取json start
	//char szPath[MAX_PATH] = TEXT("");
	//GetCurrentDirectory(CountArray(szPath), szPath);
	//char szFileName[MAX_PATH] = TEXT("");
	//_sntprintf(szFileName, CountArray(szFileName), TEXT("%s\\ReadPai.json"), szPath);
	//string strJsonFile(szFileName);
	//CRapidJson *pRapidJson = new CRapidJson();
	//pRapidJson->GetJsonResult() = pRapidJson->WriteToJson(strJsonFile);

	//pRapidJson->GetJsonReadResult() = pRapidJson->ReadFromJson(pRapidJson->GetJsonResult());
	//读取json end

	CGameDataEx gameData;
	gameData.ReadConfigZuoPai();
	gameData.ZuoPai();
//	BYTE arrHandCardData[HAND_CARD_MAX_REPERTORY + 4] = { 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x04, 0x04, 0x04, 0x27, 0x27, 0x01, 0x02, 0x03, 0x04};//碰碰胡测试
//	BYTE arrHandCardData[HAND_CARD_MAX_REPERTORY] = { 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x05, 0x05, 0x05, 0x27, 0x27 };//碰碰胡测试
//	BYTE arrHandCardData[HAND_CARD_MAX_REPERTORY] = { 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x05, 0x05, 0x01, 0x02, 0x03 };//7对测试
	//BYTE arrHandCardData[HAND_CARD_MAX_REPERTORY] = { 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x05, 0x05, 0x02, 0x03, 0x04 };//7对测试

	//BYTE arrHandCardData[HAND_CARD_MAX_REPERTORY] = { 0x01, 0x02, 0x03,
	//	0x21, 0x22, 0x23,
	//	0x11, 0x12, 0x13,
	//	0x24, 0x25, 0x35,
	//	0x35, 0x26 };//平和测试
	BYTE arrHandCardData[HAND_CARD_MAX_REPERTORY];
	memset(arrHandCardData, 0, sizeof(arrHandCardData));
	memcpy(arrHandCardData, gameData.m_tMatchMJ.byArHandPai[0], HAND_CARD_MAX_REPERTORY);

	CGameAlgorithm objAlgorithm;
	objAlgorithm.SortCardAsc(arrHandCardData,HAND_CARD_MAX_REPERTORY);
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
		arrHandCardData[i] =ByteToHexChar(arrHandCardData[i]);
	if (gameData.m_isHasLaiZiFlag <= 0)
	{
		bool bTagPingHu = objAlgorithm.IsPingHu(arrHandCardData,HAND_CARD_MAX_REPERTORY);
		if (bTagPingHu)
			cout << "平和" << endl;
		else
			cout << "不是平和" << endl;
		/*bool bTagIsPengPengHu = objAlgorithm.IsPengPengHu(arrHandCardData,HAND_CARD_MAX_REPERTORY);
		if (bTagIsPengPengHu)
			cout << "碰碰和" << endl;
		else
			cout << "不是碰碰和" << endl;*/
		/*bool bTagIsQiDuiHu = objAlgorithm.IsQiDuiHu(arrHandCardData, HAND_CARD_MAX_REPERTORY);
		if (bTagIsPengPengHu)
			cout << "7对" << endl;
		else
			cout << "不是7对" << endl;*/
		/*bool bTagIsQingYiSe = objAlgorithm.IsQingYiSe(arrHandCardData, HAND_CARD_MAX_REPERTORY);
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
		cout << "不是清一色" << endl;*/

		//bool bTagIsZiYiSe = objAlgorithm.IsZiYiSe(arrHandCardData, HAND_CARD_MAX_REPERTORY);
		//if (bTagIsZiYiSe)
		//	cout << "字一色" << endl;
		//else
		//	cout << "不是字一色" << endl;

		InternationalMajong objInternationalMajong;
		bool b = objInternationalMajong.CheckDASIXI(arrHandCardData,HAND_CARD_MAX_REPERTORY);
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
	}
	else
	{
		BYTE tmpLaizi = ByteToHexChar(gameData.byLaiZiCard);
		cout << "赖子值: ";
		objAlgorithm.m_pGameLogic->printPai(tmpLaizi);
		cout<< endl;
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
	system("pause");
}