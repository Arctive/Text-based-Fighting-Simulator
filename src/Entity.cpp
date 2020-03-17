#include "Entity.hpp"
#include <iostream>
#include <iomanip>
#include <string>

Entity::Entity()
{
	//default constructor
	name = "None";
	hp = maxHP = level = 0;
}

Entity::Entity(std::string na, int h, int lv, int max)
{
	//parameterized constructor
	name = na;
	hp = h;
	level = lv;
	maxHP = max;
}

void Entity::printHealth()
{
	//displays the health as hp/maxHP
	std::cout << std::right << std::setw(3) << hp << "/" << std::left << std::setw(3) << maxHP;
}