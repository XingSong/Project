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
	object.AddMember("isOpenUpdate", 1, allocator);
	object.AddMember("UPDATE_URL", "http://new.13shui.cc:81/CheckUpdating.aspx", allocator);
	object.AddMember("HandCardData", "com.xianwan.androidssz", allocator);
	object.AddMember("PACKAGE_PLATFORM_IOS", "com.xianwan.iosssz", allocator);
	arr.PushBack(object, allocator);
	writedoc.AddMember("PaiZhi", arr, allocator);

	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	writedoc.Accept(writer);
	
	/*string path = FileUtils::getInstance()->getWritablePath();
	path.append(strJsonFile);*/
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

void CRapidJson::ReadFromJson(std::string strJsonResult)
{
	Document readdoc;
//	std::string load_str = FileUtils::getInstance()->getStringFromFile(strJsonFile);	
//	readdoc.Parse<0>(load_str.c_str());	

	string load_str(strJsonResult);
	readdoc.Parse<kParseDefaultFlags>(load_str.c_str());

	if (readdoc.HasParseError())
	{//why can enter here?
		printf("GetParsError %d\n", readdoc.GetParseError());
		return;
	}
	if (!readdoc.IsObject())
	{
		return;
	}
	rapidjson::Value& _arr = readdoc["ClientUpdate"];
	if (_arr.IsArray())
	{
		for (int i = 0; i < _arr.Capacity(); i++)
		{
			rapidjson::Value& arrydoc = _arr[i];
			if (arrydoc.HasMember("isOpenUpdate"))
			{
				//rapidjson::Value& _jsonisOpenUpdate = _arr["isOpenUpdate"];
				printf("isOpenUpdate = %d\n", arrydoc["isOpenUpdate"].GetInt());
			}
			if (arrydoc.HasMember("UPDATE_URL"))
			{
				//rapidjson::Value& _jsonUPDATE_URL = _arr["UPDATE_URL"];
				printf("UPDATE_URL = %s\n", arrydoc["UPDATE_URL"].GetString());
			}
			if (arrydoc.HasMember("PACKAGE_PLATFORM_ANDROID"))
			{
				//rapidjson::Value& _jsonPACKAGE_PLATFORM_ANDROID = _arr["PACKAGE_PLATFORM_ANDROID"];
				printf("PACKAGE_PLATFORM_ANDROID = %s\n", arrydoc["PACKAGE_PLATFORM_ANDROID"].GetString());
			}
			if (arrydoc.HasMember("PACKAGE_PLATFORM_IOS"))
			{
				//rapidjson::Value& _jsonPACKAGE_PLATFORM_IOS = _arr["PACKAGE_PLATFORM_IOS"];
				printf("PACKAGE_PLATFORM_IOS = %s\n", arrydoc["PACKAGE_PLATFORM_IOS"].GetString());
			}
		}
	}
 }

std::string CRapidJson::GetJsonResult() const
{
	return m_strJsonResult;
}
