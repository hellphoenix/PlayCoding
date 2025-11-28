#pragma once
#include "enemy.h"
#include "player.h"

#ifndef COMBAT_ACTIONS_H
#define COMBAT_ACTIONS_H

class CombatActions
{
public:
	CombatActions();
	int playerAttack(const Enemy& _enemy, const Player& _player);
	int enemyAttack(const Enemy& _enemy, const Player& _player);
	Enemy spawnEnemy(EnemyType _type);

private:
};

#endif // !COMBAT_ACTIONS_H
