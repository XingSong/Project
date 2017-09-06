#include <cstdlib>
#include <iostream>
using namespace std;

#define CC_SAFE_DELETE(p) do {if(p){delete (p);p = nullptr;}} while (0)

class Product
{
public:
	void show()
	{
		fprintf(stderr, "partA = %d partB = %d partC = %d\n", partA, partB, partC);
	}
	void setPartA(int param){ partA = param; }
	void setPartB(int param){ partB = param; }
	void setPartC(int param){ partC = param; }

private:
	int partA;
	int partB;
	int partC;
};

class AbstractBuilder
{
public:
	AbstractBuilder(){}
	virtual ~AbstractBuilder(){}
	virtual void createProduct() = 0;
	virtual Product* getProduct() = 0;
	virtual void buildPartA(int param) = 0;
	virtual void buildPartB(int param) = 0;
	virtual void buildPartC(int param) = 0;

};

class Builder :public AbstractBuilder
{
public:
	Builder():curProduct(nullptr){}
	~Builder(){}
	void createProduct()
	{
		fprintf(stderr, "创建一个产品空壳\n");
		curProduct = new Product();
	}
	Product* getProduct()
	{
		return curProduct;
	}
	void buildPartA(int param)
	{
		fprintf(stderr, "正在构建产品的A部分\n");
		curProduct->setPartA(param);
	}
	void buildPartB(int param)
	{
		fprintf(stderr, "正在构建产品的B部分\n");
		curProduct->setPartB(param);
	}
	void buildPartC(int param)
	{
		fprintf(stderr, "正在构建产品的C部分\n");
		curProduct->setPartC(param);
	}
private:
	Product* curProduct;
};

class Director
{
public:
	Director(AbstractBuilder *builder)
	{
		curBuilder = builder;
	}
	~Director(){}
	void construct()
	{
		if (!curBuilder)
			return;
		curBuilder->createProduct();
		curBuilder->buildPartA(1);
		curBuilder->buildPartB(2);
		curBuilder->buildPartC(3);

	}
private:
	AbstractBuilder *curBuilder;
};

void main()
{
	AbstractBuilder* builder = new Builder();
	Director *pDirector = new Director(builder);
	pDirector->construct();

	Product* product = builder->getProduct();
	product->show();

	CC_SAFE_DELETE(pDirector);
	CC_SAFE_DELETE(builder);
	system("pause");
}