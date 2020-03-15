#include "Character.h"
#include <iostream>
#include <string>
using namespace std;

Character::Character()
{
	//default Character, initializes attributes
	xp = levelUp = 0;
}

Character::Character(string na, int h, int lv, int max, int x, int up):Entity(na,h,lv,max)
{
	//parameterized constructor, initializes attributes
	levelUp = up; 
	xp = x;
}

void Character::print()
{
	//prints character info (name, level, health, experience)
	cout << "Name:     " << name << endl;
	cout << "Level:    " << level << endl;
	cout << "Health:   " << hp << "/" << maxHP << endl;
	cout << "XP:       " << xp << "/" << levelUp << endl;
}

void Character::addHP(int num)
{
	//receives number to add to hp
	hp += num;
	if (hp > maxHP) //don't go over max
		hp = maxHP;
}

void Character::heal()
{
	//restores hp to maxHP
	hp = maxHP;
}