#include "enemy.h"
#include <iostream>
using std::cout, std::endl;

Enemy::Enemy() : Character(" ", 1, 0, 0), enemyType(EnemyType::EMPTY)
{

}

Enemy::Enemy(const string& _name, int _health, int _attack, int _defense, EnemyType _enemyType) : Character(_name, _health, _attack, _defense), enemyType(_enemyType)
{

}

const map<Enemy::EnemyType, string> Enemy::enemyTypeToString =
{
	{EnemyType::EMPTY, "Empty"}, {EnemyType::SLIME, "Slime"}, {EnemyType::BAT, "Bat"}, {EnemyType::GOBLIN, "Goblin"}, {EnemyType::TROLL, "Troll"}
};

Enemy::EnemyType Enemy::getEnemyType() const
{
	return enemyType;
}

void Enemy::printEnemy() const
{
	cout << "Enemy Name: " << Enemy::getName() << ", Hp: " << Enemy::getCurrentHealth() << "/" << Enemy::getBaseHealth() << ", Attack: " << Enemy::getBaseAttack() << ", Defense: " << Enemy::getBaseDefense() << endl;
}