#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
#include <string>
using namespace std;

class Enemy : public Entity
{
private:
	string weapon;
	string badNames[9] = { "Scout", "Soldier", "Pyro", "Heavy Weapons Guy",
		"Demoman", "Engineer", "Medic", "Sniper", "Spy" };
	string wpnNames[9] = { "Baseball bat", "Rocket launcher", "Flamethrower",
		"Minigun", "Grenade launcher", "Wrench", "Bonesaw", "Sniper rifle", "Kunai"};
public:
	Enemy();
	Enemy(int, int, int);
	virtual void updateHP(int);
	virtual int getAttack();
	virtual void printAtkMsg();
};
#endif