#pragma once
#include "player.h"
#ifndef GAME_H
#define GAME_H

class Game
{
	Player player;

public:
	void loop(const Player& _player);
	void handleEquipCommand();
	void handleUnequipCommand();
	void handleDebugCommand();
	void printHelp() const;

};
#endif // !GAME_H
