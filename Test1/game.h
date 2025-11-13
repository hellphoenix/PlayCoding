#pragma once
#include "player.h"
#include "enemy.h"
#include "gameActions.h"
#ifndef GAME_H
#define GAME_H

class Game
{
	Player player;
	Enemy enemy;
	GameActions gameActions;

public:
	void loop(Player _player);
	void handleEquipCommand();
	void handleUnequipCommand();
	void handleDebugCommand();
	void handleSaveCommand();
	void handleLoadCommand();
	void handleFightCommand();
	void printHelp() const;

};
#endif // !GAME_H
