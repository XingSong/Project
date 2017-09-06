#include <cstdlib>
#include <iostream>
using namespace std;

#define	CC_SAFE_DELETE(p) do{if(p){delete (p);p=nullptr;}}while(0)
#define psln(x) #x

class Product
{
public:
	virtual void show() = 0;
};

#define classProductImpl(classTypeProduct)\
class classTypeProduct :public Product\
{\
public:\
	void show()\
	{\
		cout << "I'm " << psln(classTypeProduct) << endl; \
	}\
}

classProductImpl(ProductA);
classProductImpl(ProductB);
classProductImpl(ProductC);

class FactoryMethod
{
public:
	virtual Product *createProduct() = 0;
};

#define classFacotryImpl(classTypeFactory,classTypeProduct)\
class classTypeFactory :public FactoryMethod\
{\
public:\
	Product *createProduct()\
	{\
		return new classTypeProduct(); \
	}\
}

classFacotryImpl(FactoryA, ProductA);
classFacotryImpl(FactoryB, ProductB);
classFacotryImpl(FactoryC, ProductC);

#define createFunc(classType)\
do\
{\
	FactoryMethod *pFactoryMethod = new classType(); \
	Product	*pProduct = pFactoryMethod->createProduct(); \
	pProduct->show(); \
	CC_SAFE_DELETE(pProduct); \
	CC_SAFE_DELETE(pFactoryMethod); \
} while (0)


void main()
{
	createFunc(FactoryA);
	createFunc(FactoryB);
	createFunc(FactoryC);

	system("pause");
}