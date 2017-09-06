#include <iostream>
#include <cstdlib>
using namespace std;

class Base
{
public:
	void Foo()
	{
//		cout << "Locking" << endl;
		DoFoo1();
		DoFoo2();
//		cout << "UnLocking" << endl;
	}
protected:
	virtual void DoFoo1()
	{
		cout << "Base's DoFool" << endl;
	}
	virtual void DoFoo2()
	{
		cout << "Base's DoFoo2" << endl;
	}
};

class Derived :public Base
{
private:
	virtual void DoFoo1()
	{
		cout << "Derived' s DoFoo1" << endl;
	}
};

void main()
{
	//Base *pBase = new Base();
	//pBase->Foo();
	cout << "\n";
	Base *pDerived = new Derived();
	pDerived->Foo();
	if (pDerived != nullptr)
	{
		delete pDerived;
		pDerived = nullptr;
	}
	system("pause");
}