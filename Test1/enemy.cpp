#include "enemy.h"
#include <iostream>

Enemy::Enemy() : Character(" ", 1, 1, 0, 0), enemyType(EnemyType::EMPTY)
{

}

Enemy::Enemy(const std::string& _name, int _baseHealth, int _currentHealth, int _attack, int _defense, EnemyType _enemyType) : 
	Character(_name, _baseHealth, _currentHealth, _attack, _defense), enemyType(_enemyType)
{

}

const std::map<Enemy::EnemyType, std::string> Enemy::enemyTypeToString =
{
	{EnemyType::EMPTY, "Empty"}, {EnemyType::SLIME, "Slime"}, {EnemyType::BAT, "Bat"}, {EnemyType::GOBLIN, "Goblin"}, {EnemyType::TROLL, "Troll"}
};

Enemy::EnemyType Enemy::getEnemyType() const
{
	return enemyType;
}

//void Enemy::printEnemy() const
//{
//	std::cout << "Enemy Name: " << Enemy::getName() << ", Hp: " << Enemy::getCurrentHealth() 
//		<< "/" << Enemy::getBaseHealth() << ", Attack: " << Enemy::getBaseAttack() << ", Defense: " << Enemy::getBaseDefense() << std::endl;
//}