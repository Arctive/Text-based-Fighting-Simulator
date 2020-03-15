#ifndef KNIGHT_HPP
#define KNIGHT_HPP
#include "Character.hpp"
#include <string>
using namespace std;

class Knight : public Character
{
private:
	string wName;
	int wPower, armor;
public:
	Knight();
	Knight(string, string);
	void print();
	void printAtkMsg();
	int getAttack();
	string getType() { return "Knight"; }
	void updateHP(int);
	void updateXP(int);
};
#endif