#pragma once
#include <string>

class CRapidJson
{
public:
	CRapidJson();
	virtual ~CRapidJson();
	std::string WriteToJson(std::string strJsonFile);
	void ReadFromJson(std::string strJsonResult);
	std::string GetJsonResult()const;
private:
	std::string m_strJsonResult;
};

