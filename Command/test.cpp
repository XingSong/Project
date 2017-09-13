#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;
#define CC_SAFE_DELETE(p) do{if(p) delete (p);(p)=nullptr;}while(0)

////����ʦ��
//class RoastCook
//{
//public:
//	void MakeMutton()
//	{
//		cout << "������" << endl;
//	}
//	void MakeChickenWing()
//	{
//		cout << "������" << endl;
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
////����������
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
////����������
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
//		cout << "���Ӷ���" << endl;
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
//	//���
//	girl->SetCmd(cmd1);
//	girl->SetCmd(cmd2);
//	//����Ա֪ͨ
//	girl->Notify();
//	system("pause");
//}

//�տ�
class RoastCook
{
public:
	void BakeMutton()
	{
		cout << "�����⴮" << endl;
	}
	void BakeChikenWing()
	{
		cout << "������" << endl;
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
			cout << "��־������Ա������û���ˣ�������տ�" << endl;
		}
		else if (typeid(*command) == typeid(BakeMuttonCommand))
		{
			orders->push_back(command);
			time_t now = time(0);
			cout << "��־�����Ӷ���������ģʽ.�����⴮	" << "ʱ��: " << asctime(gmtime(&now));
		}
		else
		{
			cout << "��־����ʱû�и÷���!" << endl;
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
	//����ǰ��׼��
	RoastCook *cook = new RoastCook();
	Command *cmd1 = new BakeMuttonCommand(cook);
	Command *cmd2 = new BakeChikenWingCommand(cook);

	Waiter *girl = new Waiter();

	//����Ӫҵ���˿͵��
	girl->SetOrder(cmd1);
	girl->SetOrder(cmd2);

	//�����ϣ�֪ͨ���� 
	girl->Notify();

	CC_SAFE_DELETE(cmd2);
	CC_SAFE_DELETE(cmd1);
	CC_SAFE_DELETE(girl);
	CC_SAFE_DELETE(cook);
	system("pause");
}