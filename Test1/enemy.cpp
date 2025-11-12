#include "enemy.h"
#include <iostream>
using std::cout, std::endl;

Enemy::Enemy() : Character(" ", 1, 0, 0)
{

}

Enemy::Enemy(const string& _name, int _health, int _attack, int _defense) : Character(_name, _health, _attack, _defense)
{

}

Enemy::~Enemy()
{

}

void Enemy::printEnemy() const
{
	cout << "Enemy Name: " << Enemy::getName() << ", Health: " << Enemy::getBaseHealth() << ", Attack: " << Enemy::getBaseAttack() << ", Defense: " << Enemy::getBaseDefense() << endl;
}