//Facade
#include <iostream>
#include <cstdlib>
using namespace std;

namespace Facade
{
	class KillVirusSystem
	{
	public:
		void Operation1(){ cout << "Kill Virus" << endl; }
	};

	class EncryptFileSystem
	{
	public:
		void Operation2(){ cout << "Encrypt File" << endl; }
	};

	class ZipFileSystem
	{
	public:
		void Operation3(){ cout << "Zip File" << endl; }
	};

	class BurnCDSystem
	{
	public:
		void Operation4(){ cout << "Burn CD" << endl; }
	};

	class Facade
	{
	private:
		KillVirusSystem *kill;
		EncryptFileSystem *encrypt;
		ZipFileSystem *zipFile;
		BurnCDSystem *burnCD;
	public:
		Facade()
		{
			kill = new KillVirusSystem();
			encrypt = new EncryptFileSystem();
			zipFile = new ZipFileSystem();
			burnCD = new BurnCDSystem();
		}
		~Facade()
		{
			delete kill;
			delete encrypt;
			delete zipFile;
			delete burnCD;
		}

		void Normal()
		{
			kill->Operation1();
			encrypt->Operation2();
			zipFile->Operation3();
			burnCD->Operation4();
		}

		void simple()
		{
			kill->Operation1();
			burnCD->Operation4();
		}
	};
}

void main()
{
	Facade::Facade objFacade;
	objFacade.Normal();
	objFacade.simple();
	system("pause");
}