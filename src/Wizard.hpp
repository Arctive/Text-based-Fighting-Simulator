#ifndef WIZARD_HPP
#define WIZARD_HPP
#include "Character.hpp"
#include <string>

class Wizard : public Character
{
private:
	std::string source;
	int magic;
public:
	Wizard();
	Wizard(std::string, std::string, int);
	void print();
	void printAtkMsg();
	int getAttack();
	std::string getType() { return "Wizard"; }
	void updateHP(int);
	void updateXP(int);
};
#endif