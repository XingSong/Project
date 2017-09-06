#define  _CRT_SECURE_NO_WARNINGS
#include "RapidJson.h"
#include <iostream>
#include <windows.h>
#include <atlstr.h>
using namespace std;

#define CountArray(a)	sizeof(a)/sizeof(a[0])
#define CC_SAFE_DELETE(p)	do{if(p){delete (p);(p) = nullptr;}}while(0)

void TestJson()
{
	char szPath[MAX_PATH] = TEXT("");
	GetCurrentDirectory(CountArray(szPath), szPath);
	char szFileName[MAX_PATH] = TEXT("");
	_sntprintf(szFileName, CountArray(szFileName), TEXT("%s\\ClientUpdate.json"), szPath);
	string strJsonFile(szFileName);
	CRapidJson *pRapidJson = new CRapidJson();
	pRapidJson->GetJsonResult() = pRapidJson->WriteToJson(strJsonFile);

	pRapidJson->ReadFromJson(pRapidJson->GetJsonResult());
	CC_SAFE_DELETE(pRapidJson);
}

void main()
{
	TestJson();
	system("pause");
}