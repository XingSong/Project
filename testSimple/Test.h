#pragma once
#include "GameLogic.h"
#include "InternationalMajong.h"
//#include "RapidJson.h"
#include "GameDataEx.h"

class CTest
{
private:
	CGameDataEx gameData;
	CGameAlgorithm objAlgorithm;
	InternationalMajong objInternationalMajong;

public:
	CTest();
	~CTest();
	void MainTest();
	void TestSimpleHu();
	void Test88Fan();
	void Test64Fan();
	void Test48Fan();
	void Test32Fan();

	//27->0x27,ÅÆÖµ×ª»»
	inline BYTE ByteToHexChar(BYTE pai)
	{
		return pai / 10 * BASE_DECIMAL + pai % 10;
	}
private:
	BYTE arrHandCardData[HAND_CARD_MAX_REPERTORY];

};

