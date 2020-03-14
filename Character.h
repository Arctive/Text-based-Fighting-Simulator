#include "Entity.h"
#include <iostream>
#include <string>
using namespace std;

class Character : public Entity
{
protected:
	int xp, levelUp;
public: 
	Character();
	Character(string, int, int, int, int, int);
	void addHP(int);
	void heal();
	virtual void print();
	virtual string getType() = 0;		//to be printed in character selection menu
	virtual int getAttack() = 0;		//use while fighting
	virtual void printAtkMsg() = 0;		//use while fighting
	virtual void updateHP(int) = 0;		//use while fighting
	virtual void updateXP(int) = 0;		//use if won fight
};