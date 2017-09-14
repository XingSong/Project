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
//��������
	CC_SYNTHESIZE_READONLY(string, requestType, RequestType);
//��������
	CC_SYNTHESIZE_READONLY(string, requestContent, RequestContent);
//����
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
		if (managerLvel == "����")
		{
			if (request.getRequestType() == "���" && request.getRequestNumber() <= 2)
			{
				cout << name << ":" << request.getRequestContent() << "����" << request.getRequestNumber() << "����׼" << endl;
			}
			else
				cout << name << ":" << request.getRequestContent() << "����" << request.getRequestNumber() << "��Ȩ��׼" << endl;
		}
		else if (managerLvel == "�ܼ�")
		{
			if (request.getRequestType() == "���" && request.getRequestNumber() <= 5)
			{
				cout << name << ":" << request.getRequestContent() << "����" << request.getRequestNumber() << "����׼" << endl;
			}
			else
				cout << name << ":" << request.getRequestContent() << "����" << request.getRequestNumber() << "��Ȩ��׼" << endl;
		}
		else if (managerLvel == "�ܾ���")
		{
			if (request.getRequestType() == "���")
			{
				cout << name << ":" << request.getRequestContent() << "����" << request.getRequestNumber() << "����׼" << endl;
			}
			else if (request.getRequestType() == "��н" && request.getRequestNumber()<=500)
				cout << name << ":" << request.getRequestContent() << "����" << request.getRequestNumber() << "����׼" << endl;
			else if (request.getRequestType() == "��н" && request.getRequestNumber() > 500)
				cout << name << ":" << request.getRequestContent() << "����" << request.getRequestNumber() << "��˵��" << endl;
		}
	}
};


void main0()
{
	Manager *A = new Manager("A");
	Manager *B = new Manager("B");
	Manager *C = new Manager("C");

	Request *request = new Request();
	request->setRequestType("��н");
	request->setRequestContent("С�������н");
	request->setRequestNumber(1000);

	A->GetResult("����", *request);
	B->GetResult("�ܼ�", *request);
	C->GetResult("�ܾ���", *request);

	Request *request2 = new Request();
	request2->setRequestType("���");
	request2->setRequestContent("С�����");
	request2->setRequestNumber(3);

	A->GetResult("����", *request2);
	B->GetResult("�ܼ�", *request2);
	C->GetResult("�ܾ���", *request2);

	CC_SAFE_DELETE(request2);
	CC_SAFE_DELETE(request);
	CC_SAFE_DELETE(A);
	CC_SAFE_DELETE(B);
	CC_SAFE_DELETE(C);

	system("pause");
}