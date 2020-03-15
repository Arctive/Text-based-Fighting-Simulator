#ifndef NOVICE_HPP
#define NOVICE_HPP
#include "Character.hpp"
#include <string>
using namespace std;

class Novice : public Character
{
private:
	int luck;
public:
	Novice();
	Novice(string);
	void print();
	void printAtkMsg();
	int getAttack();
	string getType() { return "Novice"; }
	void updateHP(int);
	void updateXP(int);
};
#endif