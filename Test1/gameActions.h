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
	//const Player& getPlayer() const;
private:
	//void createPlayer(); // Creates a player with defined stats
	//void giveStartingItems(); // Gives player some items at the start of the game. Will change when inventory testing is complete.
};

#endif // !GAME_ACTIONS_H
