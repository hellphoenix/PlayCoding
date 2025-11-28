#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
#include "inventory.h"
#include <map>
#include <vector>

enum class EnemyType
{
	EMPTY = 0,
	SLIME = 1,
	BAT = 2,
	GOBLIN = 3,
	TROLL = 4
};

static const std::map<EnemyType, std::string> enemyTypeToString =
{
	{EnemyType::EMPTY, "Empty"}, {EnemyType::SLIME, "Slime"}, {EnemyType::BAT, "Bat"}, {EnemyType::GOBLIN, "Goblin"}, {EnemyType::TROLL, "Troll"}
};

class Enemy : public Character
{
public:

	Enemy() : Character("Casper", 1, 1, 0, 0), enemyType(EnemyType::EMPTY)
	{

	}
	Enemy(const std::string& _name, int _baseHealth, int _currentHealth, int _attack, int _defense, EnemyType _enemyType) :
		Character(_name, _baseHealth, _currentHealth, _attack, _defense), enemyType(_enemyType)
	{

	}

	EnemyType getEnemyType() const {return this->enemyType;}
	Inventory& getLootTable() { return this->lootTable; }
	int getMaxHealth() const { return this->baseHealth; }
	void changeCurrentHealth(int _healthChanged) 
	{
		int newHealth = this->currentHealth + _healthChanged;
		if (newHealth < 0) newHealth = 0;
		else if (newHealth > this->baseHealth) newHealth = this->baseHealth;

		this->currentHealth = newHealth;
		this->setAlive(this->currentHealth > 0);
	}

private:
	Inventory lootTable;
	EnemyType enemyType;

};

#endif // !ENEMY_H

