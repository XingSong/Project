#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

#define CC_SAFE_DELETE(p)	do{if(p){delete (p);(p)=nullptr;}}while(0)
#define CC_SYNTHESIZE(varType, varName, funName)\
private: varType varName; \
public:  varType get##funName(void) const{ return varName; }\
public: void set##funName(varType varName){ this->varName = varName; }\

//ְ����ģʽ��Chain Of Responsibility����ʹ��������л��ᴦ�����󣬴Ӷ���������ķ����ߺͽ�����֮�����ϡ�
//�������������һ���������������������ݸ�����ֱ����һ����������Ϊֹ


//������
class Request
{
	//��������͡����ݡ�����
	CC_SYNTHESIZE(string, requestType, RequestType);
	CC_SYNTHESIZE(string, requestContent, RequestContent);
	CC_SYNTHESIZE(int, requestNumber, RequestNumber);
};

class Manager
{
protected:
	string name;
	Manager* superior;
public:
	Manager(){}
	Manager(string name)
	{
		this->name = name;
		superior = nullptr;
	}
	~Manager()
	{
		CC_SAFE_DELETE(superior);
	}

	//���ü�����
	void SetSuperior(Manager *superior)
	{
		this->superior = superior;
	}

	//��������ĳ��󷽷�
	virtual void RequestApplication(Request *request) = 0;
};

//����
class CommonManager :public Manager
{
public:
	CommonManager(string name) :Manager(name){}
	void RequestApplication(Request *request)
	{
		if (request->getRequestType() == "���"  && request->getRequestNumber() <= 2)
		{
			cout << name << ":" << request->getRequestContent() << " ����:" << request->getRequestNumber() << " ����׼" << endl;
		}
		else
		{
			if (superior != nullptr)
				superior->RequestApplication(request);
		}
	}
};

//�ܼ�
class Majordomo :public Manager
{
public:
	Majordomo(string name) :Manager(name){}
	void RequestApplication(Request *request)
	{
		if (request->getRequestType() == "���"  && request->getRequestNumber() <= 5)
		{
			cout << name << ":" << request->getRequestContent() << " ����:" << request->getRequestNumber() << " ����׼" << endl;
		}
		else
		{
			if (superior != nullptr)
				superior->RequestApplication(request);
		}
	}
};

//�ܾ���
class GeneralManager :public Manager
{
public:
	GeneralManager(string name) :Manager(name){}
	void RequestApplication(Request *request)
	{
		if (request->getRequestType() == "���")
		{
			cout << name << ":" << request->getRequestContent() << " ����:" << request->getRequestNumber() << " ����׼" << endl;
		}
		else if (request->getRequestType() == "��н"&&request->getRequestNumber() <= 500)
		{
			cout << name << ":" << request->getRequestContent() << "  ����:" << request->getRequestNumber() << "  ����׼" << endl;
		}
		else if (request->getRequestType() == "��н"&&request->getRequestNumber() > 500)
		{
			cout << name << ":" << request->getRequestContent() << "  ����:" << request->getRequestNumber() << "  ��˵��" << endl;
		}
	}
};

void main()
{
	Manager *jingli = new CommonManager("jingli");
	Manager *zongjian = new Majordomo("zongjian");
	Manager *zongjingli = new GeneralManager("zongjingli");

	jingli->SetSuperior(zongjian);
	zongjian->SetSuperior(zongjingli);

	//���1��
	Request request1;
	request1.setRequestType("���");
	request1.setRequestContent("С�����");
	request1.setRequestNumber(1);
	jingli->RequestApplication(&request1);

	//���4��
	Request request2;
	request2.setRequestType("���");
	request2.setRequestContent("С�����");
	request2.setRequestNumber(4);
	jingli->RequestApplication(&request2);

	//��н500Ԫ
	Request request3;
	request3.setRequestType("��н");
	request3.setRequestContent("С�������н");
	request3.setRequestNumber(500);
	jingli->RequestApplication(&request3);

	//��н1000Ԫ
	Request request4;
	request4.setRequestType("��н");
	request4.setRequestContent("С�������н");
	request4.setRequestNumber(1500);
	jingli->RequestApplication(&request4);

	CC_SAFE_DELETE(jingli);
	system("pause");
}
