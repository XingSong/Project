#include <cstdlib>
#include <iostream>
using namespace std;

#define	CC_SAFE_DELETE(p) do{if(p){delete (p);p=nullptr;}}while(0)

//常用场景
//基本就是你需要从A的实例得到一份与A内容相同，但是又互不干扰的实例的话，就需要使用原型模式。
//
//
//
//优点
//1.使用拷贝模式比直接new一个对象的开销要小的多。
//
//2.可以在程序运行时（对象属性发生了变化），得到一份内容相同的实例，但之间还不会相互干扰。

class Prototype
{
public:
	virtual Prototype* Clone() = 0;
};

class ConcretPrototype :public Prototype
{
public:
	ConcretPrototype() :m_iCount(0)
	{
		cout << "m_iCount = " << m_iCount << "\n"
			<< "ConcretPrototype copy constructor" << endl;
	}
	~ConcretPrototype(){}
	ConcretPrototype(const ConcretPrototype& rhs)
	{
		m_iCount = rhs.m_iCount;
	}
	Prototype* Clone()
	{
		return new ConcretPrototype(*this);
	}
private:
	int m_iCount;
};

void main()
{
	Prototype* pConcretProA = new ConcretPrototype();
	Prototype* pConcretProB = pConcretProA->Clone();
	system("pause");
}