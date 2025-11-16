#include "character.h"
#include <iostream>

// Default Character constructor. Sets base health and current health to 1, and all other stats to 0.
Character::Character() :name(), baseHealth(1), currentHealth(1), baseAttack(0), baseDefense(0), alive(true)
{

}

// Character constructor. Input is all basic stats, plus current health
Character::Character(const std::string& _name, int _baseHealth, int _currentHealth, int _attack, int _defense) : name(_name), baseHealth(_baseHealth), currentHealth(_currentHealth), baseAttack(_attack), baseDefense(_defense), alive(true)
{

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
	name = _name;
}

void Character::setBaseHealth(int _newBaseHealth)
{
	
	baseHealth = _newBaseHealth;
}

void Character::setCurrentHealth(int _newCurrentHealth)
{

	currentHealth = _newCurrentHealth;
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
	std::cout << "Character Name: " << getName() << ", HP: " << getCurrentHealth() << "/" << getBaseHealth() << ", Attack: " << getBaseAttack() << ", Defense: " << getBaseDefense() << std::endl;
}