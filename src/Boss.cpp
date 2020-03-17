#include "Boss.hpp"
#include "Enemy.hpp"
#include <string>
#include <iostream>

Boss::Boss()
{
	//default constructor, initializes Boss values
	name = "None";
	hp = maxHP = level = 10;
}

Boss::Boss(int na, int lv, int h)
{
	//parameterized constructor, creates a Boss based on the opponent team stats
	//receives number between 0-8, and the team's total level and maxHP
	name = miniNames[na];
	bossWeapon = miniWeapons[na];
	level = lv + (1 + rand() % 3); //level plus random num btwn 1-3
	hp = maxHP = (50 + rand() % h); //random num based on opponent health, plus 50
}

Boss::Boss(std::string na, std::string wna, int lv, int h)
{
	//receives the name, weapon name, level, and health
	//USE FOR FINAL BOSS
	name = na;
	bossWeapon = wna;
	level = lv;
	hp = maxHP = h;
}

void Boss::updateHP(int dmg)
{
	//receives damage, subtracts it from hp
	hp -= dmg;
	if (hp < 0) //don't have negative hp
		hp = 0;
}

int Boss::getAttack()
{
	//generates and returns the enemy attack points
	return (rand() % 11) + level;
}

void Boss::printAtkMsg()
{
	//displays an attack message
	std::cout << endl << name << " attacks with the " << bossWeapon << "!" << endl;
}