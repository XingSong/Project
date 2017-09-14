#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

#define CC_SAFE_DELETE(p)	do{if(p){delete (p);(p)=nullptr;}}while(0)

#define CC_SYNTHESIZE_READONLY(varType, varName, funName)\
private: varType varName; \
public:  varType get##funName(void) const{ return varName; }\
public: void set##funName(varType varName){ this->varName = varName; }\

class Request
{
//申请类型
	CC_SYNTHESIZE_READONLY(string, requestType, RequestType);
//申请内容
	CC_SYNTHESIZE_READONLY(string, requestContent, RequestContent);
//数量
	CC_SYNTHESIZE_READONLY(int, requestNumber, RequestNumber);

};

class Manager
{
protected:
	string name;
public:
	Manager(string name)
	{
		this->name = name;
	}

	void GetResult(string managerLvel, Request request)
	{
		if (managerLvel == "经理")
		{
			if (request.getRequestType() == "请假" && request.getRequestNumber() <= 2)
			{
				cout << name << ":" << request.getRequestContent() << "数量" << request.getRequestNumber() << "被批准" << endl;
			}
			else
				cout << name << ":" << request.getRequestContent() << "数量" << request.getRequestNumber() << "无权批准" << endl;
		}
		else if (managerLvel == "总监")
		{
			if (request.getRequestType() == "请假" && request.getRequestNumber() <= 5)
			{
				cout << name << ":" << request.getRequestContent() << "数量" << request.getRequestNumber() << "被批准" << endl;
			}
			else
				cout << name << ":" << request.getRequestContent() << "数量" << request.getRequestNumber() << "无权批准" << endl;
		}
		else if (managerLvel == "总经理")
		{
			if (request.getRequestType() == "请假")
			{
				cout << name << ":" << request.getRequestContent() << "数量" << request.getRequestNumber() << "被批准" << endl;
			}
			else if (request.getRequestType() == "加薪" && request.getRequestNumber()<=500)
				cout << name << ":" << request.getRequestContent() << "数量" << request.getRequestNumber() << "被批准" << endl;
			else if (request.getRequestType() == "加薪" && request.getRequestNumber() > 500)
				cout << name << ":" << request.getRequestContent() << "数量" << request.getRequestNumber() << "再说吧" << endl;
		}
	}
};


void main0()
{
	Manager *A = new Manager("A");
	Manager *B = new Manager("B");
	Manager *C = new Manager("C");

	Request *request = new Request();
	request->setRequestType("加薪");
	request->setRequestContent("小菜请求加薪");
	request->setRequestNumber(1000);

	A->GetResult("经理", *request);
	B->GetResult("总监", *request);
	C->GetResult("总经理", *request);

	Request *request2 = new Request();
	request2->setRequestType("请假");
	request2->setRequestContent("小菜请假");
	request2->setRequestNumber(3);

	A->GetResult("经理", *request2);
	B->GetResult("总监", *request2);
	C->GetResult("总经理", *request2);

	CC_SAFE_DELETE(request2);
	CC_SAFE_DELETE(request);
	CC_SAFE_DELETE(A);
	CC_SAFE_DELETE(B);
	CC_SAFE_DELETE(C);

	system("pause");
}