#ifndef KNIGHT_HPP
#define KNIGHT_HPP
#include "Character.hpp"
#include <string>

class Knight : public Character
{
private:
	std::string wName;
	int wPower, armor;
public:
	Knight();
	Knight(std::string, std::string);
	void print();
	void printAtkMsg();
	int getAttack();
	std::string getType() { return "Knight"; }
	void updateHP(int);
	void updateXP(int);
};
#endif