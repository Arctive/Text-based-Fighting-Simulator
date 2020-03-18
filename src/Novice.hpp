#ifndef NOVICE_HPP
#define NOVICE_HPP
#include "Character.hpp"
#include <string>

class Novice : public Character
{
private:
	int luck;
public:
	Novice();
	Novice(std::string);
	void print();
	void printAtkMsg();
	int getAttack();
	std::string getType() { return "Novice"; }
	void updateHP(int);
	void updateXP(int);
};
#endif