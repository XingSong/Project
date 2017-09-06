#include "Singleton.h"
#include <cstdlib>
#include <iostream>
using namespace std;


int main()
{
	Singleton *pObj = Singleton::getInstance();
	cout<<pObj->getTest() << endl;
	system("pause");
	return 0;
}