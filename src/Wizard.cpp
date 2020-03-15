#include "Character.hpp"
#include "Wizard.hpp"
#include <iostream>
#include <string>
using namespace std;

Wizard::Wizard()
{
	//default constructor, initializes Wizard attributes
	hp = maxHP = 100;
	levelUp = 12;
	source = "None";
	magic = 0;
}

Wizard::Wizard(string n, string so, int mag)
{
	//parameterized contructor, receives and initializes Wizard attributes
	name = n;
	source = so;
	hp = maxHP = 100;
	levelUp = 12;
	magic = mag;
}

void Wizard::print()
{
	//prints Character info and Wizard attributes
	Character::print();
	cout << "Type:     " << source << endl;
	cout << "Magic:    " << magic << endl;
}

void Wizard::printAtkMsg()
{
	//prints attack message
	cout << endl << name << " conjures the dark spirits to strike!" << endl;
}

int Wizard::getAttack()
{
	//generates and returns attack points, num btwn 5-15 plus magic
	return ((5 + rand() % 11) + magic);
}

void Wizard::updateHP(int dmg)
{
	//receives monster's damage, subracts dmg from hp accordingly
	if (dmg > level)
		hp -= (dmg - level);
	else
		cout << "Your magic shields you!" << endl << "No damage taken!" << endl;
	if (hp < 0) //don't have negative hp
		hp = 0;
}

void Wizard::updateXP(int mlev)
{
	//receives monster's level, adds it to xp minus 2, plus 5
	int change;
	change = mlev - 2 + 5;
	if (change < 0)
		xp += mlev + 5;
	else
		xp += change;
	//check for level up, adjust stats accordingly 
	if (xp >= levelUp)
	{
		maxHP += 8; //hp increases by 8
		hp += 8;
		magic += 3; //magic increases by 3
		xp = 0; //reset xp
		level++; //increment level
		levelUp += 10; //increase levelUp by 10
	}
}