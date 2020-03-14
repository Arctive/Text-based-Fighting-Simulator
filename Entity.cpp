#include "pch.h"
#include "Entity.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

Entity::Entity()
{
	//default constructor
	name = "None";
	hp = maxHP = level = 0;
}

Entity::Entity(string na, int h, int lv, int max)
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
	cout << right << setw(3) << hp << "/" << left << setw(3) << maxHP;
}