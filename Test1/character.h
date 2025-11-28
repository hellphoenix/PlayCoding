#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
struct Character
{
	std::string getName() const { return this->name; }
	int getBaseHealth() const { return this->baseHealth; }
	int getCurrentHealth() const { return this->currentHealth; }
	int getBaseAttack() const { return this->baseAttack; }
	int getBaseDefense() const { return this->baseDefense; }
	bool isAlive() const { return this->alive; }

protected:
	std::string name;
	int baseHealth;
	int currentHealth;
	int baseAttack;
	int baseDefense;
	bool alive;

	Character() :name("Dan Tae"), baseHealth(1), currentHealth(1), baseAttack(0), baseDefense(0), alive(true)
	{

	}
	Character(const std::string& _name, int _baseHealth, int _currentHealth, int _attack, int _defense) : alive(true)
	{
		setName(_name);
		setBaseHealth(_baseHealth);
		setCurrentHealth(_currentHealth);
		setBaseAttack(_attack);
		setBaseDefense(_defense);
	}

	void setName(const std::string& _name)
	{
		if (_name.empty()) name = "Dan Tae";
		else name = _name;
	}
	void setBaseHealth(int _newBaseHealth)
	{
		if (_newBaseHealth < 0) baseHealth = 0;
		else baseHealth = _newBaseHealth;
	}
	void setCurrentHealth(int _newCurrentHealth)
	{
		if (_newCurrentHealth < 0) currentHealth = 0;
		else currentHealth = _newCurrentHealth;
	}
	void setBaseAttack(int _attack)
	{
		if (_attack < 0) baseAttack = 0;
		else baseAttack = _attack;
	}
	void setBaseDefense(int _defense)
	{
		if (_defense < 0) baseDefense = 0;
		else baseDefense = _defense;
	}
	void setAlive(bool _alive)
	{
		alive = _alive;
	}
};


#endif // !CHARACTER_H
