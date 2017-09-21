#pragma once
#include <string>

class CRapidJson
{
public:
	CRapidJson();
	virtual ~CRapidJson();
	std::string WriteToJson(std::string strJsonFile);
	std::string ReadFromJson(std::string strJsonResult);
	std::string GetJsonResult()const;
	std::string GetJsonReadResult();
private:
	//写入json的结果传给读取json
	std::string m_strJsonResult;
	//读取json的结果，传给要用到数组
	std::string m_strJsonReadResult;
};

