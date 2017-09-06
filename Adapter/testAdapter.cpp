#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Target
{
public:
	Target(){}
	virtual ~Target(){}
	virtual void Request()
	{
		cout << "Target::Request()" << endl;
	}
};

class Adaptee
{
public:
	Adaptee(){}
	~Adaptee(){}
	void SpecificRequest()
	{
		cout << "Adaptee::SpecificRequest()" << endl;
	}
};

//��ģʽ
class Adapter :public Target,private Adaptee
{
public:
	Adapter(){}
	~Adapter(){}
	virtual void Request()
	{
		cout << "Adapter::Request()" << endl;
		this->SpecificRequest();
		cout << "----------" << endl;
	}
};

//����ģʽ
class Adapter1 :public Target
{
public:
	Adapter1(Adaptee* adaptee)
	{
		this->_adptee = adaptee;
	}
	Adapter1(){}
	~Adapter1(){}
	virtual void Request()
	{
		cout << "Adapter1::Request()" << endl;
		this->_adptee->SpecificRequest();
		cout << "--------------" << endl;
	}
private:
	Adaptee *_adptee;
};


void main()
{
	//��ģʽ
	Target *p = new Adapter();
	p->Request();

	//����ģʽ1
	Adaptee *ada = new Adaptee();
	Target *pTarget1 = new Adapter1(ada);
	pTarget1->Request();

	//����ģʽ2
	Target *pTarget2 = new Adapter1();
	pTarget2->Request();
	system("pause");
}