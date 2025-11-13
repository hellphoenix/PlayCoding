#include "gameActions.h"

GameActions::GameActions()
{

}

int GameActions::playerAttack(const Enemy& _enemy, const Player& _player)
{
	if (_enemy.getBaseDefense() >= _player.getMaxAttack()) return 1;
	else return _player.getMaxAttack() - _enemy.getBaseDefense();
}

int GameActions::enemyAttack(const Enemy& _enemy, const Player& _player)
{
	if (_player.getMaxDefense() >= _enemy.getBaseAttack()) return 1;
	else return _enemy.getBaseAttack() - _player.getMaxDefense();
}

Enemy GameActions::spawnEnemy(Enemy::EnemyType _enemyType)
{

	Enemy enemy("King Slime", 1000, 50, 40, _enemyType);
	return enemy;
}