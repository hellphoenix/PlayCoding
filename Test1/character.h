#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
struct Character
{
	std::string getName() const;
	int getBaseHealth() const; 
	int getCurrentHealth() const;
	int getBaseAttack() const;
	int getBaseDefense() const;
	bool isAlive() const;



protected:
	std::string name;
	int baseHealth;
	int currentHealth;
	int baseAttack;
	int baseDefense;
	bool alive;

	Character();
	Character(const std::string& _name, int _baseHealth, int _currentHealth, int _attack, int _defense);

	void setName(const std::string& _name);
	void setBaseHealth(int _newBaseHealth);
	void setCurrentHealth(int _newCurrentHealth);
	void setBaseAttack(int _attack);
	void setBaseDefense(int _defense);
	void setAlive(bool _isAlive);
};


#endif // !CHARACTER_H
