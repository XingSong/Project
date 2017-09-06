#include <iostream>
#include <cstdlib>
using namespace std;

class WeaponBehavior
{
public:
	virtual void useWeapon() = 0;
};

class AK47 :public WeaponBehavior
{
public:
	void useWeapon()
	{
		cout << "Use 47" << endl;
	}
};

class Knife :public WeaponBehavior
{
public:
	void useWeapon()
	{
		cout << "Use Knife" << endl;
	}
};

class Character
{
public:
	Character(){ pWeapon = 0; }
	void setWeapon(WeaponBehavior *w){ pWeapon = w; }
	virtual void fight() = 0;
protected:
	WeaponBehavior *pWeapon;
};

class King :public Character
{
public:
	void fight()
	{
		cout << "The King:";
		if (pWeapon == NULL)
			cout << "No weapon!" << endl;
		else
			pWeapon->useWeapon();
	}
};

void main()
{
	WeaponBehavior *pAK47 = new AK47();
	WeaponBehavior *pKnife = new Knife();

	Character *pKing = new King();

	pKing->fight();
	cout << endl;
	pKing->setWeapon(pAK47);
	pKing->fight();
	cout << endl;
	pKing->setWeapon(pKnife);
	pKing->fight();

	system("pause");
}