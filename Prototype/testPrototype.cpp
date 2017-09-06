#include <cstdlib>
#include <iostream>
using namespace std;

#define	CC_SAFE_DELETE(p) do{if(p){delete (p);p=nullptr;}}while(0)

//���ó���
//������������Ҫ��A��ʵ���õ�һ����A������ͬ�������ֻ������ŵ�ʵ���Ļ�������Ҫʹ��ԭ��ģʽ��
//
//
//
//�ŵ�
//1.ʹ�ÿ���ģʽ��ֱ��newһ������Ŀ���ҪС�Ķࡣ
//
//2.�����ڳ�������ʱ���������Է����˱仯�����õ�һ��������ͬ��ʵ������֮�仹�����໥���š�

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