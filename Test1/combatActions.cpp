#include "combatActions.h"

CombatActions::CombatActions()
{

}

int CombatActions::playerAttack(const Enemy& _enemy, const Player& _player)
{
	if (_enemy.getBaseDefense() >= _player.getMaxAttack()) return 1;
	else return _player.getMaxAttack() - _enemy.getBaseDefense();
}

int CombatActions::enemyAttack(const Enemy& _enemy, const Player& _player)
{
	if (_player.getMaxDefense() >= _enemy.getBaseAttack()) return 1;
	else return _enemy.getBaseAttack() - _player.getMaxDefense();
}

Enemy CombatActions::spawnEnemy(EnemyType _enemyType)
{

	Enemy enemy("King Slime", 1000, 1000, 50, 40, _enemyType);
	return enemy;
}