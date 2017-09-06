#pragma once
class Singleton
{
public:
	static Singleton* getInstance();
	int getTest();
	
private:
	Singleton();
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
	~Singleton();
	static Singleton* m_pInstance;
	int m_Test;
	class InnderGC
	{
	public:
		~InnderGC()
		{
			if (m_pInstance != nullptr)
			{
				delete m_pInstance;
				m_pInstance = nullptr;
			}
		}
	};
};

