#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "Entity.hpp"
#include <iostream>
#include <string>

class Character : public Entity
{
protected:
	int xp, levelUp;
public: 
	Character();
	Character(std::string, int, int, int, int, int);
	void addHP(int);
	void heal();
	virtual void print();
	virtual std::string getType() = 0;	//to be printed in character selection menu
	virtual int getAttack() = 0;		//use while fighting
	virtual void printAtkMsg() = 0;		//use while fighting
	virtual void updateHP(int) = 0;		//use while fighting
	virtual void updateXP(int) = 0;		//use if won fight
};
#endif