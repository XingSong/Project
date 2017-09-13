#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;
#define CC_SAFE_DELETE(p) do{if(p) delete (p);(p)=nullptr;}while(0)

////烤肉师傅
//class RoastCook
//{
//public:
//	void MakeMutton()
//	{
//		cout << "烤羊肉" << endl;
//	}
//	void MakeChickenWing()
//	{
//		cout << "烤鸡翅" << endl;
//	}
//};
//
//class Command
//{
//public:
//	Command(RoastCook* temp)
//	{
//		receiver = temp;
//	}
//	virtual void ExecuteCmd() = 0;
//protected:
//	RoastCook *receiver;
//};
//
////烤羊肉命令
//class MakeMuttonCmd :public Command
//{
//public:
//	MakeMuttonCmd(RoastCook *temp) :Command(temp){}
//	virtual void ExecuteCmd()
//	{
//		receiver->MakeMutton();
//	}
//};
//
////烤鸡翅命令
//class MakeChickenWingCmd :public Command
//{
//public:
//	MakeChickenWingCmd(RoastCook *temp) :Command(temp){}
//	virtual void ExecuteCmd()
//	{
//		receiver->MakeChickenWing();
//	}
//};
//
//class Waiter
//{
//public:
//	void SetCmd(Command *temp)
//	{
//		m_commandList.push_back(temp);
//		cout << "增加订单" << endl;
//	}
//	void Notify()
//	{
//		vector<Command*>::iterator it;
//		for (it = m_commandList.begin(); it != m_commandList.end(); it++)
//		{
//			(*it)->ExecuteCmd();
//		}
//	}
//protected:
//	vector<Command*> m_commandList;
//};
//
//void main()
//{
//	RoastCook *cook = new RoastCook();
//	Command *cmd1 = new MakeMuttonCmd(cook);
//	Command *cmd2 = new MakeChickenWingCmd(cook);
//	Waiter *girl = new Waiter();
//	//点菜
//	girl->SetCmd(cmd1);
//	girl->SetCmd(cmd2);
//	//服务员通知
//	girl->Notify();
//	system("pause");
//}

//烧烤
class RoastCook
{
public:
	void BakeMutton()
	{
		cout << "烤羊肉串" << endl;
	}
	void BakeChikenWing()
	{
		cout << "烤鸡翅" << endl;
	}
};

class Command
{
public:
	Command(RoastCook *receiver)
	{
		this->receiver = receiver;
	}
	virtual void ExecuteCommand() = 0;
protected:
	RoastCook *receiver;
};

class BakeMuttonCommand :public Command
{
public:
	BakeMuttonCommand(RoastCook *receiver):Command(receiver){}
	void ExecuteCommand()
	{
		receiver->BakeMutton();
	}
};


class BakeChikenWingCommand :public Command
{
public:
	BakeChikenWingCommand(RoastCook *receiver):Command(receiver){}
	void ExecuteCommand()
	{
		receiver->BakeChikenWing();
	}
};

class Waiter
{
private:
	vector<Command*> *orders;
public:
	Waiter()
	{
		orders = new vector<Command *>;
	}

	~Waiter()
	{
		delete orders;
	};

	void SetOrder(Command* command)
	{
		if (typeid(*command) == typeid(BakeChikenWingCommand))
		{
			cout << "日志：服务员：鸡翅没有了，请点别的烧烤" << endl;
		}
		else if (typeid(*command) == typeid(BakeMuttonCommand))
		{
			orders->push_back(command);
			time_t now = time(0);
			cout << "日志：增加订单：命令模式.烤羊肉串	" << "时间: " << asctime(gmtime(&now));
		}
		else
		{
			cout << "日志：暂时没有该服务!" << endl;
		}
	}

	void Notify()
	{
		vector<Command*>::iterator it;
		for (it = orders->begin(); it != orders->end(); it++)
		{
			(*it)->ExecuteCommand();
		}
	}
};


void main()
{
	//开店前的准备
	RoastCook *cook = new RoastCook();
	Command *cmd1 = new BakeMuttonCommand(cook);
	Command *cmd2 = new BakeChikenWingCommand(cook);

	Waiter *girl = new Waiter();

	//开门营业，顾客点菜
	girl->SetOrder(cmd1);
	girl->SetOrder(cmd2);

	//点菜完毕，通知厨房 
	girl->Notify();

	CC_SAFE_DELETE(cmd2);
	CC_SAFE_DELETE(cmd1);
	CC_SAFE_DELETE(girl);
	CC_SAFE_DELETE(cook);
	system("pause");
}