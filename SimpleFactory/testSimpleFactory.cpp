#include <cstdlib>
#include <iostream>
using namespace std;

#define	CC_SAFE_DELETE(p) do{if(p){delete (p);p=nullptr;}}while(0)

typedef enum MyEnum
{
	TypeA,
	TypeB,
	TypeC
}PRODUCTTYPE;

class Product
{
public:
	virtual void Show() = 0;
};

class ProductA :public Product
{
public:
	void Show()
	{
		cout << "I'm ProductA" << endl;
	}
};

class ProductB :public Product
{
public:
	void Show()
	{
		cout << "I'm ProductB" << endl;
	}
};
class ProductC :public Product
{
public:
	void Show()
	{
		cout << "I'm ProductC" << endl;
	}
};

class SimpleFactory
{
public:
	Product* createProduct(PRODUCTTYPE type)
	{
		switch (type)
		{
		case TypeA:
			return new ProductA();
		case TypeB:
			return new ProductB();
		case TypeC:
			return new ProductC();
		default:
			return nullptr;
		}
	}
};

void createFuncProduct(SimpleFactory *p, PRODUCTTYPE type)
{
	Product* product = p->createProduct(type);
	if (product != nullptr)
		product->Show();
	CC_SAFE_DELETE(product);
}

void main()
{
	SimpleFactory *pSimpleFactory = new SimpleFactory();
	//Product *pA = pSimpleFactory->createProduct(TypeA);
	//if (pA != nullptr)
	//	pA->Show();
	//CC_SAFE_DELETE(pA);

	//Product *pB = pSimpleFactory->createProduct(TypeB);
	//if (pB != nullptr)
	//	pB->Show();
	//CC_SAFE_DELETE(pB);
	createFuncProduct(pSimpleFactory, TypeA);
	createFuncProduct(pSimpleFactory, TypeB);
	createFuncProduct(pSimpleFactory, TypeC);

	system("pause");
}