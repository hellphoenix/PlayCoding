#pragma once
#include "player.h"
#include "enemy.h"
#ifndef GAME_H
#define GAME_H

class Game
{
	Player player;
	Enemy slimeEnemy;

public:
	void loop(Player _player);
	void handleEquipCommand();
	void handleUnequipCommand();
	void handleDebugCommand();
	void handleSaveCommand();
	void handleLoadCommand();
	Enemy createSlimeEnemy();
	void handleFightCommand();
	void printHelp() const;
	int attacking(const Enemy& _enemy, const Player& _player);
	int defending(const Enemy& _enemy, const Player& _player);

};
#endif // !GAME_H
