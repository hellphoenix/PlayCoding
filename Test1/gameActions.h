#pragma once
#include "enemy.h"
#include "player.h"

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

class GameActions
{
public:
	GameActions();
	int playerAttack(const Enemy& _enemy, const Player& _player);
	int enemyAttack(const Enemy& _enemy, const Player& _player);
	Enemy spawnEnemy(Enemy::EnemyType _type);
};

#endif // !GAME_ACTIONS_H
