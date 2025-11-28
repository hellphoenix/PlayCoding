#include "gameInitialize.h"
#include <iostream>
#include <stdexcept>


void GameInitialize::run()
{

	loadEquipment();
	game.loop(gameEquipment);
}

void GameInitialize::loadEquipment()
{
	equipment = &ItemLibrary::equipment(); // point to item library master list

	if (!equipment->empty())
	{
		for (const auto& it : *equipment)
		{
			auto index = equipmentSlotToIndex(it.getEquipmentSlot());
			gameEquipment[index].push_back(it);
		}
	}
	else
	{
		throw std::runtime_error("Game Equipment Failed to Load. items.json may be missing, empty, or invalid.\n");
	}
}