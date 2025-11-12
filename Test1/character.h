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
	int baseAttack;
	int baseDefense;
	bool alive;

public:
	Character();
	Character(const string& _name, int _health, int _attack, int _defense);

	string getName() const;
	int getBaseHealth() const;
	int getBaseAttack() const;
	int getBaseDefense() const;
	bool isAlive() const;

	void setName(const string& _name);
	void setBaseHealth(int _health);
	void setBaseAttack(int _attack);
	void setBaseDefense(int _defense);
	void setAlive(bool _isAlive);

	void printCharacter() const;
};


#endif // !CHARACTER_H
