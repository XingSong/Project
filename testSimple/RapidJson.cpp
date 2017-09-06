#define _CRT_SECURE_NO_WARNINGS
#include "RapidJson.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include <iostream>
using namespace rapidjson;
using namespace std;

CRapidJson::CRapidJson()
{

}


CRapidJson::~CRapidJson()
{
}

string CRapidJson::WriteToJson(std::string strJsonFile)
{
	Document writedoc;
	writedoc.SetObject();
	Document::AllocatorType& allocator = writedoc.GetAllocator();
	rapidjson::Value arr(kArrayType);
	rapidjson::Value object(kObjectType);

	object.AddMember("HandCardData", "0x01,0x02,0x03,0x21,0x22,0x23,0x11,0x12,0x13,0x24,0x25,0x35,0x35,0x26", allocator);

	arr.PushBack(object, allocator);
	writedoc.AddMember("PaiZhi", arr, allocator);

	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	writedoc.Accept(writer);

	string path = strJsonFile;
	FILE *fpFile = fopen(path.c_str(), "wb");
	if (fpFile)
	{
		fputs(buffer.GetString(), fpFile);
		fclose(fpFile);
	}
	printf("%s\n", buffer.GetString());
	m_strJsonResult = string(buffer.GetString());
	return m_strJsonResult;
}

string CRapidJson::ReadFromJson(std::string strJsonResult)
{
	Document readdoc;
//	std::string load_str = FileUtils::getInstance()->getStringFromFile(strJsonFile);	
//	readdoc.Parse<0>(load_str.c_str());	

	string load_str(strJsonResult);
	readdoc.Parse<kParseDefaultFlags>(load_str.c_str());

	if (readdoc.HasParseError())
	{//why can enter here?
		printf("GetParsError %d\n", readdoc.GetParseError());
		return "HasParseError";
	}
	if (!readdoc.IsObject())
	{
		return "IsObject";
	}
	rapidjson::Value& _arr = readdoc["PaiZhi"];
	if (_arr.IsArray())
	{
		for (int i = 0; i < _arr.Capacity(); i++)
		{
			rapidjson::Value& arrydoc = _arr[i];
			if (arrydoc.HasMember("HandCardData"))
			{

				printf("HandCardData = %s\n", arrydoc["HandCardData"].GetString());
				m_strJsonReadResult = (string)arrydoc["HandCardData"].GetString();
			}
			
		}

	}
	return m_strJsonReadResult;
 }

std::string CRapidJson::GetJsonResult() const
{
	return m_strJsonResult;
}

std::string CRapidJson::GetJsonReadResult() 
{
	return m_strJsonReadResult;
}
