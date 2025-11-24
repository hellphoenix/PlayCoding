#pragma once
#include "character.h"
#include "inventory.h"
#include <map>
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

	static const std::map<EnemyType, std::string> enemyTypeToString;

          Enemy();
          Enemy(const std::string& _name, int _baseHealth, int _currentHealth, int _attack, int _defense, EnemyType _enemyType);

	EnemyType getEnemyType() const;
	Inventory& getLootTable() { return this->lootTable; }
	int getMaxHealth() const;
	void changeCurrentHealth(int _healthChanged);

  private:
          Inventory lootTable;
          EnemyType enemyType;

};

#endif // !ENEMY_H

