#include "Knight.h"
#include <iostream>
#include <string>
using namespace std;

Knight::Knight()
{
	//default constructor, initializes Knight values
	hp = maxHP = 120;
	levelUp = 15;
	armor = 1;
	wName = "No name";
	wPower = 5;
}

Knight::Knight(string n, string wna)
{
	//parameterized constructor, receives and initializes Knight attributes
	name = n;
	armor = 1;
	wName = wna;
	wPower = 5;
	hp = maxHP = 120;
	levelUp = 15;
}

void Knight::print()
{
	//prints Character info and Knight attributes
	Character::print();
	cout << "Armor:    " << armor << endl;
	cout << "Weapon name:  " << wName << endl;
	cout << "Weapon power: " << wPower << endl;
}

void Knight::printAtkMsg()
{
	//prints attack message
	cout << endl << name << " strikes with " << wName << "!" << endl;
}

int Knight::getAttack()
{
	//generates and returns attack points, num btwn 10-20 plus weapon power
	return ((10 + rand() % 11) + wPower);
}

void Knight::updateHP(int dmg)
{
	//receives monster's damage, subtracts it from hp and armor
	if (dmg > armor)
		hp -= (dmg - armor);
	else
		cout << "Your armor absorbed the attack!" << endl << "No damage taken!" << endl;
	if (hp < 0) //don't have negative hp
		hp = 0;
}

void Knight::updateXP(int mlev)
{
	//receives monster's level, adds it to xp minus 1, plus 5
	int change = mlev - 1 + 5;
	if (change < 0)
		xp += mlev + 5;
	else
		xp += change;
	//check for level up, adjust stats accordingly 
	if (xp >= levelUp)
	{
		maxHP += 15; //hp increases by 15
		hp += 15;
		wPower += 1;
		armor += 1; //armor increases by 1
		xp = 0; //reset xp
		level++; //increment level
		levelUp += 10; //increase levelUp by 10
	}
}