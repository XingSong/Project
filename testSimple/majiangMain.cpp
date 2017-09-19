#define _CRT_SECURE_NO_WARNINGS
#include "Test.h"
#include <cstdlib>
using namespace std;


void main()
{
	CTest objTest;
	objTest.MainTest();
	//∂¡»°json start
	//char szPath[MAX_PATH] = TEXT("");
	//GetCurrentDirectory(CountArray(szPath), szPath);
	//char szFileName[MAX_PATH] = TEXT("");
	//_sntprintf(szFileName, CountArray(szFileName), TEXT("%s\\ReadPai.json"), szPath);
	//string strJsonFile(szFileName);
	//CRapidJson *pRapidJson = new CRapidJson();
	//pRapidJson->GetJsonResult() = pRapidJson->WriteToJson(strJsonFile);

	//pRapidJson->GetJsonReadResult() = pRapidJson->ReadFromJson(pRapidJson->GetJsonResult());
	//∂¡»°json end
	system("pause");
}