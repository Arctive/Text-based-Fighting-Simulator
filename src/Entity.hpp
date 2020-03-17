#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <string>

class Entity
{
protected:
	std::string name;
	int hp, maxHP, level;
public:
	Entity();
	Entity(std::string, int, int, int);
	std::string getName() { return name; }
	int getHP() { return hp; }
	int getMaxHP() { return maxHP; }
	int getLevel() { return level; }
	void printHealth();
};
#endif