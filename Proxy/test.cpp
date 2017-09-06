#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

#define CC_SAFE_DELETE(p)	do{if(p){delete (p);p = nullptr;}}while(0)

class Women
{
public:
	void setName(string name)
	{
		this->name = name;
	}
	string getName()const
	{
		return name;
	}

private:
	string name;
};

class SearchWomen
{
public:
	virtual void Love() = 0;
	virtual void MakeEyes() = 0;
	virtual void MakeLove() = 0;
};

class Man :public SearchWomen
{
	Women *women;
	string name;
public:
	Man(string name,Women *women)
	{
		this->women = women;
		this->name = name;
	}
	void Love()
	{
		cout << name<<"喜欢" << women->getName() << endl;
	}
	void MakeEyes()
	{
		cout << women->getName() << "向"<<name<<"抛媚眼" << endl;
	}
	void MakeLove()
	{
		cout << women->getName() << "和"<<name<<" XXOO" << endl;
	}
	string getName()const
	{
		return name;
	}
};

class Proxy :public SearchWomen
{
	Man *man;
public:
	Proxy(string name,Women *women)
	{
		man = new Man(name, women);
	}
	void Love()
	{
		man->Love();
	}
	void MakeEyes()
	{
		man->MakeEyes();
	}
	void MakeLove()
	{
		man->MakeLove();
	}
};

void main()
{
	string strWomen[] = { "潘金莲", "贾氏" };
	string strMan = "西门庆";
	Women *pWomen = new Women[2];
	for (int i = 0; i < 2;i++)
	(&pWomen[i])->setName(strWomen[i]);

	Proxy *pProxy[2];
	for (int i = 0; i < 2; i++)
	{
		pProxy[i] = new Proxy(strMan, &pWomen[i]);
		pProxy[i]->Love();
		pProxy[i]->MakeEyes();
		pProxy[i]->MakeLove();
	}
	
	for (int i = 0; i < 2; i++)
	{
		CC_SAFE_DELETE(pProxy[i]);
	}

	delete[] pWomen;
	pWomen = nullptr;
	system("pause");
}