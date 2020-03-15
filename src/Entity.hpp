#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <string>
using namespace std;

class Entity
{
protected:
	string name;
	int hp, maxHP, level;
public:
	Entity();
	Entity(string, int, int, int);
	string getName() { return name; }
	int getHP() { return hp; }
	int getMaxHP() { return maxHP; }
	int getLevel() { return level; }
	void printHealth();
};
#endif