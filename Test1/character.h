#pragma once
#include <string>
using std::string;

#ifndef CHARACTER_H
#define CHARACTER_H

class Character
{
private:
	string name;
	int baseHealth;
	int currentHealth;
	int baseAttack;
	int baseDefense;
	bool alive;

public:
	Character();
	Character(const string& _name, int _baseHealth, int _attack, int _defense);
	
	string getName() const;
	int getBaseHealth() const; 
	int getCurrentHealth() const;
	int getBaseAttack() const;
	int getBaseDefense() const;
	bool isAlive() const;

	void setName(const string& _name);
	void setBaseHealth(int _newBaseHealth);
	void setCurrentHealth(int _newCurrentHealth);
	void setBaseAttack(int _attack);
	void setBaseDefense(int _defense);
	void setAlive(bool _isAlive);

	void printCharacter() const; // For debugging
};


#endif // !CHARACTER_H
