#include "Singleton.h"

Singleton* Singleton::getInstance()
{
	return m_pInstance;
}

int Singleton::getTest()
{
	return m_Test;
}

Singleton::Singleton()
{
	m_Test = 20;
}

Singleton* Singleton::m_pInstance = new Singleton();
