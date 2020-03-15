#ifndef BOSS_H
#define BOSS_H
#include "Enemy.h"
#include <string>
using namespace std;

class Boss : public Enemy
{
private:
	string bossWeapon;
	string miniNames[9] = { "Mega Scout", "Mega Soldier", "Mega Pyro", "Mega Hoovy",
		"Mega Demoman", "Mecha Engineer", "Mega Medic", "Mega Sniper", "Mega Spy" };
	string miniWeapons[9] = { "Scattergun", "Beggar's Bazooka", "Nostromo Napalmer",
		"Family Business", "Eyelander", "Shotgun", "Ubersaw", "Machina", "Ambassador"};
public:
	Boss();
	Boss(int, int, int);
	Boss(string, string, int, int);
	void updateHP(int);
	int getAttack();
	void printAtkMsg();
};
#endif