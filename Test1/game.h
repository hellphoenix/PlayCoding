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
	std::array<vector<Item>, itemSlotToIndex(Item::ItemSlot::COUNT)> gameItems;

public:
	void loop(Player _player, const std::array<vector<Item>, itemSlotToIndex(Item::ItemSlot::COUNT)>& _gameItems);
	void handleEquipCommand();
	void handleUnequipCommand();
	void handleDebugCommand();
	void handleSaveCommand();
	void handleLoadCommand();
	void handleFightCommand();
	void printHelp() const;

};
#endif // !GAME_H
