#pragma once
#include "player.h"
#include "enemy.h"
#include "gameActions.h"
#ifndef GAME_H
#define GAME_H

enum class Mode
{
	Normal,
	EquipSelectSlot,
	EquipSelectItem
};



class Game
{
private:
	Player player;
	Enemy enemy;
	GameActions gameActions;
	std::array<vector<Item>, itemSlotToIndex(Item::ItemSlot::COUNT)> gameItems;
	void changeName();
	void changeBaseAttack();
	void changeBaseDefense();
	void changeBaseHealth();
	void addToInventory();
	void removeFromInventory();

	void startEquip();
	void handleEquipSlotInput(const std::string& slot);
	void handleEquipItemInput(const std::string& choice);
	void handleEquipCommand();
	void handleUnequipCommand();
	void handleDebugCommand();
	void handleSaveCommand();
	void handleLoadCommand();
	void handleFightCommand();
	void printHelp() const;
	Mode mode = Mode::Normal;
	int pendingEquipSlotIndex = -1;
	std::vector<Item> pendingFilteredItems;

public:

	void loop(Player _player, const std::array<vector<Item>, itemSlotToIndex(Item::ItemSlot::COUNT)>& _gameItems);

};
#endif // !GAME_H
