#include "character.h"
#include <iostream>

// Default Character constructor. Sets base health and current health to 1, and all other stats to 0.
Character::Character() :name("Dan Tae"), baseHealth(1), currentHealth(1), baseAttack(0), baseDefense(0), alive(true)
{

}

// Character constructor. Input is all basic stats, plus current health
Character::Character(const std::string& _name, int _baseHealth, int _currentHealth, int _attack, int _defense) : alive(true)
{
	setName(_name);
	setBaseHealth(_baseHealth);
	setCurrentHealth(_currentHealth);
	setBaseAttack(_attack);
	setBaseDefense(_defense);
}

std::string Character::getName() const
{
	return name;
}

int Character::getBaseHealth() const
{
	return baseHealth;
}

int Character::getCurrentHealth() const
{
	return currentHealth;
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

void Character::setName(const std::string& _name)
{
	if (_name.empty()) name = "Dan Tae";
	else name = _name;
}

void Character::setBaseHealth(int _newBaseHealth)
{
	if (_newBaseHealth < 0) baseHealth = 0;
	else baseHealth = _newBaseHealth;
}

void Character::setCurrentHealth(int _newCurrentHealth)
{
	if (_newCurrentHealth < 0) currentHealth = 0;
	else currentHealth = _newCurrentHealth;
}

void Character::setBaseAttack(int _attack)
{
	if (_attack < 0) baseAttack = 0;
	else baseAttack = _attack;
}

void Character::setBaseDefense(int _defense)
{
	if (_defense < 0) baseDefense = 0;
	else baseDefense = _defense;
}

void Character::setAlive(bool _alive)
{
	alive = _alive;
}