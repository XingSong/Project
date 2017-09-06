#include<cstdlib>
#include <iostream>
#include <string>
using namespace std;

class Phone
{
public:
	Phone(){}
	virtual ~Phone(){}
	virtual void ShowDecorator() = 0;
};

class NokiaPhone :public Phone
{
public:
	NokiaPhone(string name) :m_strName(name){}
	~NokiaPhone(){}
	void ShowDecorator(){ cout << m_strName << "的装饰" << endl; }
	
private:
	string m_strName;
};

class iPhone :public Phone
{
public:
	iPhone(string name) :m_strName(name){}
	~iPhone(){}
	void ShowDecorator(){ cout << m_strName << "的装饰" << endl; }
private:
	string m_strName;
};

class DecoratorPhone :public Phone
{
private:
	Phone *m_phone;
public:
	DecoratorPhone(Phone *phone) :m_phone(phone){}
	virtual void ShowDecorator(){ m_phone->ShowDecorator(); }
};

class DecoratorB :public DecoratorPhone
{
public:
	DecoratorB(Phone *phone) :DecoratorPhone(phone){}
	void ShowDecorator(){ DecoratorPhone::ShowDecorator(); AddDecorator(); }
private:
	void AddDecorator(){ cout << "增加挂件" << endl; }
};

class DecoratorA :public DecoratorPhone
{
public:
	DecoratorA(Phone *phone) :DecoratorPhone(phone){}
	void ShowDecorator(){ DecoratorPhone::ShowDecorator(); AddDecorator(); }
private:
	void AddDecorator(){ cout << "增加屏幕贴膜" << endl; }
};

void main()
{
	Phone *pIphone8 = new iPhone("iPhone8");
	Phone *pa = new DecoratorA(pIphone8);
//	pa->ShowDecorator();
	Phone *pb = new DecoratorB(pa);
	pb->ShowDecorator();
	system("pause");
}