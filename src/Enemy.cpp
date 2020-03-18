#include "Entity.hpp"
#include "Enemy.hpp"
#include <iostream>
#include <string>

Enemy::Enemy()
{
	//default constructor
	name = weapon = "None";
	hp = maxHP = level = 0;
}

Enemy::Enemy(int na, int lv, int health)
{
	//parameterized constructor, creates an enemy based on the opponent stats
	//receives number between 0-8, and the opponent's level and maxHP
	name = badNames[na];
	weapon = wpnNames[na];
	level = lv + (1 + std::rand() % 3); //level plus random num btwn 1-3
	hp = maxHP = (50 + std::rand() % health); //random num based on opponent health, plus 50
}

void Enemy::updateHP(int dmg)
{
	//receives damage, subtracts it from hp
	hp -= dmg;
	if (hp < 0) //don't have negative hp
		hp = 0;
}

int Enemy::getAttack()
{
	//generates and returns the enemy attack points
	return (std::rand()%11)+ level;
}

void Enemy::printAtkMsg()
{
	//displays an attack message
	std::cout << std::endl << name << " attacks with their " << weapon << "!" << std::endl;
}