#ifndef BOSS_HPP
#define BOSS_HPP
#include "Enemy.hpp"

class Boss : public Enemy
{
private:
	std::string bossWeapon;
	std::string miniNames[9] = { "Mega Scout", "Mega Soldier", "Mega Pyro", "Mega Hoovy",
		"Mega Demoman", "Mecha Engineer", "Mega Medic", "Mega Sniper", "Mega Spy" };
	std::string miniWeapons[9] = { "Scattergun", "Beggar's Bazooka", "Nostromo Napalmer",
		"Family Business", "Eyelander", "Shotgun", "Ubersaw", "Machina", "Ambassador"};
public:
	Boss();
	Boss(int, int, int);
	Boss(std::string, std::string, int, int);
	void updateHP(int);
	int getAttack();
	void printAtkMsg();
};
#endif