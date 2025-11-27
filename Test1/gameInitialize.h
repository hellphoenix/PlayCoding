#pragma once
#include "enemy.h"
#include "item_library.h"
#include "player.h"
#include "uiFonts.h"
#include "game.h"
#include <vector>

#ifndef GAME_INITIALIZE_H
#define GAME_INITIALIZE_H

class GameInitialize
{
public:

	void run();
	typedef std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)> equipmentArray;
	UiFonts uiFont;
	equipmentArray gameEquipment{};
	Game game;

private:
	void loadEquipment(); // Loads all items from item slot libraries

	const std::vector<Equipment>* equipment = nullptr; // pointer for master items list.
};

//constexpr std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)>& getGameEquipment();



#endif // !GAME_INITIALIZE_H


