#include "character.h"
#include <iostream>
using std::cout, std::endl;

Character::Character() :name(), baseHealth(1), baseAttack(0), baseDefense(0), alive(true)
{

}
Character::Character(const string& _name, int _health, int _attack, int _defense): name(_name), baseHealth(_health), baseAttack(_attack), baseDefense(_defense), alive(true)
{

}

string Character::getName() const
{
	return name;
}

int Character::getBaseHealth() const
{
	return baseHealth;
}

int Character::getBaseAttack() const
{
	return baseAttack;
}

int Character::getBaseDefense() const
{
	return baseDefense;
}

bool Character::isAlive() const
{
	return alive;
}

void Character::setName(string _name)
{
	name = _name;
}

void Character::setBaseHealth(int _health)
{
	baseHealth = _health;
}

void Character::setBaseAttack(int _attack)
{
	baseAttack = _attack;
}

void Character::setBaseDefense(int _defense)
{
	baseDefense = _defense;
}

void Character::setAlive(bool _alive)
{
	alive = _alive;
}

void Character::printCharacter() const
{
	cout << "Character Name: " << getName() << ", Health: " << getBaseHealth() << ", Attack: " << getBaseAttack() << ", Defense: " << getBaseDefense() << endl;
}