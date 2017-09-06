#define _CRT_SECURE_NO_WARNINGS
#include "GameLogic.h"
#include "GameAlgorithm.h"
//#include "RapidJson.h"
#include "GameDataEx.h"

#include <cstdlib>
#include <iostream>
using namespace std;


void main()
{
	//��ȡjson start
	//char szPath[MAX_PATH] = TEXT("");
	//GetCurrentDirectory(CountArray(szPath), szPath);
	//char szFileName[MAX_PATH] = TEXT("");
	//_sntprintf(szFileName, CountArray(szFileName), TEXT("%s\\ReadPai.json"), szPath);
	//string strJsonFile(szFileName);
	//CRapidJson *pRapidJson = new CRapidJson();
	//pRapidJson->GetJsonResult() = pRapidJson->WriteToJson(strJsonFile);

	//pRapidJson->GetJsonReadResult() = pRapidJson->ReadFromJson(pRapidJson->GetJsonResult());
	//��ȡjson end

	CGameDataEx gameData;
	gameData.ReadConfigZuoPai();
	gameData.ZuoPai();
//	BYTE arrHandCardData[HAND_CARD_MAX_REPERTORY + 4] = { 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x04, 0x04, 0x04, 0x27, 0x27, 0x01, 0x02, 0x03, 0x04};//����������
//	BYTE arrHandCardData[HAND_CARD_MAX_REPERTORY] = { 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x05, 0x05, 0x05, 0x27, 0x27 };//����������
//	BYTE arrHandCardData[HAND_CARD_MAX_REPERTORY] = { 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x05, 0x05, 0x01, 0x02, 0x03 };//7�Բ���
	//BYTE arrHandCardData[HAND_CARD_MAX_REPERTORY] = { 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x01, 0x02, 0x03, 0x05, 0x05, 0x02, 0x03, 0x04 };//7�Բ���

	//BYTE arrHandCardData[HAND_CARD_MAX_REPERTORY] = { 0x01, 0x02, 0x03,
	//	0x21, 0x22, 0x23,
	//	0x11, 0x12, 0x13,
	//	0x24, 0x25, 0x35,
	//	0x35, 0x26 };//ƽ�Ͳ���
	BYTE arrHandCardData[HAND_CARD_MAX_REPERTORY];
	memset(arrHandCardData, 0, sizeof																			(arrHandCardData));
	memcpy(arrHandCardData, gameData.m_tMatchMJ.byArHandPai[0], HAND_CARD_MAX_REPERTORY);

	CGameAlgorithm objAlgorithm;
	objAlgorithm.SortCardAsc(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	for (int i = 0; i < HAND_CARD_MAX_REPERTORY; i++)
	{
		cout << (int)arrHandCardData[i] << ",";
	}
	cout << endl;
	//bool bTagIsPengPengHu = objAlgorithm.IsPengPengHu(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	bool bTagIsPengPengHu = objAlgorithm.IsPengPengHuWithLaizi(arrHandCardData, HAND_CARD_MAX_REPERTORY,&gameData);
	if (bTagIsPengPengHu)
		cout << "������" << endl;
	else
		cout << "����������" << endl;
	//bool bTagIsQiDuiHu = objAlgorithm.IsQiDuiHu(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	//if (bTagIsPengPengHu)
	//	cout << "7��" << endl;
	//else
	//	cout << "����7��" << endl;
	//bool bTagPingHu = objAlgorithm.IsPingHu(arrHandCardData, HAND_CARD_MAX_REPERTORY);
	//if (bTagPingHu)
	//	cout << "ƽ��" << endl;
	//else
	//	cout << "����ƽ��" << endl;

	system("pause");
}