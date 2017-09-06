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
	//д��json�Ľ��������ȡjson
	std::string m_strJsonResult;
	//��ȡjson�Ľ��������Ҫ�õ�����
	std::string m_strJsonReadResult;
};

