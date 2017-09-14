#include <map>
#include <cstdlib>
#include <iostream>
using namespace std;

#define CC_SAFE_DELETE(p)	do{if(p){delete (p);(p)=nullptr;}}while(0)
#define CC_SYNTHESIZE_READONLY(varType, varName, funName)\
private: varType varName; \
public:  varType get##funName(void) const{ return varName; }\

#define CountArray(arr)	sizeof(arr)/sizeof(arr)[0]
/*
个税起征点3500元
级数   全月应纳税所得额        　　　　税率（%）
1   　不超过1500元的             　　　3
2   　超过1500元至4500元的部分   　　　10
3   　超过4500元至9000元的部分   　　　20
4   　超过9000元至35000元的部分 　　　 25
5  　 超过35000元至55000元的部分 　　　30
6 　  超过55000元至80000元的部分 　　　35
7  　 超过80000元的部分          　　  45
**/

float arrSalary[] = { 1500, 4500, 9000, 35000, 55000, 80000,81000};
float arrTax[]	  = { 0.03, 0.1, 0.2, 0.25, 0.3, 0.35, 0.45 };

const float incomeTaxStart = 3500;
//请求类
class Person
{

	CC_SYNTHESIZE_READONLY(float, salary, Salary);
public: 
	void setSalary(float salary)
	{
		this->salary = (salary > incomeTaxStart) ? (salary - incomeTaxStart):0;
	}
};

class Handler
{
protected:
	float income;
	Handler *superior;
public:
	Handler(float income)
	{
		this->income = income;
		superior = nullptr;
	}
	~Handler()
	{
		CC_SAFE_DELETE(superior);
	}
	void SetSuperior(Handler *superior)
	{
		this->superior = superior;
	}

	virtual void RequestApplication(Person *request) = 0;
};



//不超过1500
class C1500IncomeAfterTax :public Handler
{
public:
	C1500IncomeAfterTax(float income) :Handler(income){}
	void RequestApplication(Person *request)
	{
		if (request->getSalary() <= 1500)
		{
			cout << "tax is " << arrTax[0] << endl;
		}
		else
		{
			if (superior != nullptr)
				superior->RequestApplication(request);
		}

	}
};

//不超过4500
class C4500IncomeAfterTax :public Handler
{
public:
	C4500IncomeAfterTax(float income) :Handler(income){}
	void RequestApplication(Person *request)
	{
		if (request->getSalary() <= 4500)
			cout << "tax is " << arrTax[1] << endl;
		else
		{
			if (superior != nullptr)
				superior->RequestApplication(request);
		}
	}
};

//不超过9000
class C9000IncomeAfterTax :public Handler
{
public:
	C9000IncomeAfterTax(float income) :Handler(income){}
	void RequestApplication(Person *request)
	{
		if (request->getSalary() <= 9000)
			cout << "tax is " << arrTax[2] << endl;
		else
		{
			if (superior != nullptr)
				superior->RequestApplication(request);
		}
	}
};

//不超过35000
class C35000IncomeAfterTax :public Handler
{
public:
	C35000IncomeAfterTax(float income) :Handler(income){}
	void RequestApplication(Person *request)
	{
		if (request->getSalary() <= 35000)
			cout << "tax is " << arrTax[3] << endl;
		else
		{
			if (superior != nullptr)
				superior->RequestApplication(request);
		}
	}
};

//不超过55000
class C55000IncomeAfterTax :public Handler
{
public:
	C55000IncomeAfterTax(float income) :Handler(income){}
	void RequestApplication(Person *request)
	{
		if (request->getSalary() <= 55000)
			cout << "tax is " << arrTax[4] << endl;
		else
		{
			if (superior != nullptr)
				superior->RequestApplication(request);
		}
	}
};

//80000
class C80000IncomeAfterTax :public Handler
{
public:
	C80000IncomeAfterTax(float income) :Handler(income){}
	void RequestApplication(Person *request)
	{
		if (request->getSalary() <= 80000)
			cout << "tax is " << arrTax[5] << endl;
		else
		{
			/*if (superior != nullptr)
				superior->RequestApplication(request);*/
			cout << "tax is " << arrTax[6] << endl;
		}
	}
};


void main1()
{
	Handler *p1500 = new C1500IncomeAfterTax(1500);
	Handler *p4500 = new C4500IncomeAfterTax(4500);
	Handler *p9000 = new C9000IncomeAfterTax(9000);
	Handler *p35000 = new C35000IncomeAfterTax(35000);
	Handler *p55000 = new C55000IncomeAfterTax(55000);
	Handler *p80000 = new C80000IncomeAfterTax(80000);

	p1500->SetSuperior(p4500);
	p4500->SetSuperior(p9000);
	p9000->SetSuperior(p35000);
	p35000->SetSuperior(p55000);
	p55000->SetSuperior(p80000);

	Person requestSalary;
	requestSalary.setSalary(3500);
	p1500->RequestApplication(&requestSalary);
	CC_SAFE_DELETE(p1500);
	system("pause");
}