#ifndef WIZARD_H
#define WIZARD_H
#include "Character.h"
#include <string>
using namespace std;

class Wizard : public Character
{
private:
	string source;
	int magic;
public:
	Wizard();
	Wizard(string, string, int);
	void print();
	void printAtkMsg();
	int getAttack();
	string getType() { return "Wizard"; }
	void updateHP(int);
	void updateXP(int);
};
#endif