#pragma once
#include "character.h"
#include "inventory.h"
#include <vector>

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Character
{
private:
	Inventory lootTable;
public:
	Enemy();
	Enemy(const string& _name, int _health, int _attack, int _defense);
	~Enemy();

	Inventory& getLootTable() { return Enemy::lootTable; }

	void printEnemy() const;
};

#endif // !ENEMY_H

