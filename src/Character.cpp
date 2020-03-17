#include "Entity.hpp"
#include "Character.hpp"
#include <iostream>
#include <string>

Character::Character()
{
	//default Character, initializes attributes
	xp = levelUp = 0;
}

Character::Character(std::string na, int h, int lv, int max, int x, int up):Entity(na,h,lv,max)
{
	//parameterized constructor, initializes attributes
	levelUp = up; 
	xp = x;
}

void Character::print()
{
	//prints character info (name, level, health, experience)
	std::cout << "Name:     " << name << std::endl;
	std::cout << "Level:    " << level << std::endl;
	std::cout << "Health:   " << hp << "/" << maxHP << std::endl;
	std::cout << "XP:       " << xp << "/" << levelUp << std::endl;
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