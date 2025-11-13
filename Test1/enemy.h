#pragma once
#include "character.h"
#include "inventory.h"
#include <vector>

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Character
{
public:
	enum class EnemyType
	{
		EMPTY = 0,
		SLIME = 1,
		BAT = 2,
		GOBLIN = 3,
		TROLL = 4
	};

	static const map<EnemyType, string> enemyTypeToString;

	Enemy();
	Enemy(const string& _name, int _health, int _attack, int _defense, EnemyType _enemyType);
	EnemyType getEnemyType() const;

	Inventory& getLootTable() { return Enemy::lootTable; }

	void printEnemy() const;

private:
	Inventory lootTable;
	EnemyType enemyType;

};

#endif // !ENEMY_H

