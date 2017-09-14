#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

#define CC_SAFE_DELETE(p)	do{if(p){delete (p);(p)=nullptr;}}while(0)
#define CC_SYNTHESIZE(varType, varName, funName)\
private: varType varName; \
public:  varType get##funName(void) const{ return varName; }\
public: void set##funName(varType varName){ this->varName = varName; }\

//职责链模式（Chain Of Responsibility）：使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合。
//将这个对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止


//请求类
class Request
{
	//请求的类型、内容、数量
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

	//设置继任者
	void SetSuperior(Manager *superior)
	{
		this->superior = superior;
	}

	//处理请求的抽象方法
	virtual void RequestApplication(Request *request) = 0;
};

//经理
class CommonManager :public Manager
{
public:
	CommonManager(string name) :Manager(name){}
	void RequestApplication(Request *request)
	{
		if (request->getRequestType() == "请假"  && request->getRequestNumber() <= 2)
		{
			cout << name << ":" << request->getRequestContent() << " 数量:" << request->getRequestNumber() << " 被批准" << endl;
		}
		else
		{
			if (superior != nullptr)
				superior->RequestApplication(request);
		}
	}
};

//总监
class Majordomo :public Manager
{
public:
	Majordomo(string name) :Manager(name){}
	void RequestApplication(Request *request)
	{
		if (request->getRequestType() == "请假"  && request->getRequestNumber() <= 5)
		{
			cout << name << ":" << request->getRequestContent() << " 数量:" << request->getRequestNumber() << " 被批准" << endl;
		}
		else
		{
			if (superior != nullptr)
				superior->RequestApplication(request);
		}
	}
};

//总经理
class GeneralManager :public Manager
{
public:
	GeneralManager(string name) :Manager(name){}
	void RequestApplication(Request *request)
	{
		if (request->getRequestType() == "请假")
		{
			cout << name << ":" << request->getRequestContent() << " 数量:" << request->getRequestNumber() << " 被批准" << endl;
		}
		else if (request->getRequestType() == "加薪"&&request->getRequestNumber() <= 500)
		{
			cout << name << ":" << request->getRequestContent() << "  数量:" << request->getRequestNumber() << "  被批准" << endl;
		}
		else if (request->getRequestType() == "加薪"&&request->getRequestNumber() > 500)
		{
			cout << name << ":" << request->getRequestContent() << "  数量:" << request->getRequestNumber() << "  再说吧" << endl;
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

	//请假1天
	Request request1;
	request1.setRequestType("请假");
	request1.setRequestContent("小菜请假");
	request1.setRequestNumber(1);
	jingli->RequestApplication(&request1);

	//请假4天
	Request request2;
	request2.setRequestType("请假");
	request2.setRequestContent("小菜请假");
	request2.setRequestNumber(4);
	jingli->RequestApplication(&request2);

	//加薪500元
	Request request3;
	request3.setRequestType("加薪");
	request3.setRequestContent("小菜请求加薪");
	request3.setRequestNumber(500);
	jingli->RequestApplication(&request3);

	//加薪1000元
	Request request4;
	request4.setRequestType("加薪");
	request4.setRequestContent("小菜请求加薪");
	request4.setRequestNumber(1500);
	jingli->RequestApplication(&request4);

	CC_SAFE_DELETE(jingli);
	system("pause");
}
