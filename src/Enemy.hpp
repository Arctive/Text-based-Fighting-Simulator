#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "Entity.hpp"
#include <string>

class Enemy : public Entity
{
private:
	std::string weapon;
	std::string badNames[9] = { "Scout", "Soldier", "Pyro", "Heavy Weapons Guy",
		"Demoman", "Engineer", "Medic", "Sniper", "Spy" };
	std::string wpnNames[9] = { "Baseball bat", "Rocket launcher", "Flamethrower",
		"Minigun", "Grenade launcher", "Wrench", "Bonesaw", "Sniper rifle", "Kunai"};
public:
	Enemy();
	Enemy(int, int, int);
	virtual void updateHP(int);
	virtual int getAttack();
	virtual void printAtkMsg();
};
#endif