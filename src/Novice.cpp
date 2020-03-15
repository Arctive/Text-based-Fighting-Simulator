#include "Character.hpp"
#include "Novice.hpp"
#include <iostream>
#include <string>

using namespace std;

Novice::Novice()
{
	//default constructor, initializes Novice values
	hp = maxHP = 80;
	levelUp = 10;
	luck = 1;
}

Novice::Novice(string na)
{
	//parameterized constructor, receives name, initializes the rest
	name = na;
	hp = maxHP = 80;
	levelUp = 10;
	luck = 1;
}

void Novice::print()
{
	//prints Character info and luck
	Character::print();
	cout << "Luck:     " << luck << endl;
}

void Novice::printAtkMsg()
{
	//prints attack message
	cout << endl << name << " attacks!" << endl;
}

int Novice::getAttack()
{
	//generates and returns attack points, num btwn 1-10 plus luck
	return ((1 + rand() % 10) + luck);
}

void Novice::updateHP(int dmg)
{
	//receives monster's damage, subtracts it from hp
	hp -= dmg;
	if (hp < 0) //don't have negative hp
		hp = 0;
}

void Novice::updateXP(int mlev)
{
	//receives monster's level, adds it to xp, plus 5
	xp += mlev + 5;
	//check for level up, adjust stats accordingly 
	if (xp >= levelUp)
	{
		maxHP += 10; //hp increases by 10 
		hp += 10;
		luck += (3 + rand() % 3); //increase luck by num btwn 3-5 points
		xp = 0; //reset xp
		level++; //increment level
		levelUp += 10; //increase levelUp by 10
	}
}