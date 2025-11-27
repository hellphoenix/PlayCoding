#include "gameInitialize.h"
#include <iostream>


void GameInitialize::run()
{

	loadEquipment();
	game.loop(gameEquipment);
}

void GameInitialize::loadEquipment()
{
	try
	{
		equipment = &ItemLibrary::equipment(); // point to item library master list

		// Creates an array of vectors(gameEquipment) for all equipment slots
		for (int i = 0; i < equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT); i++)
		{
			for (const auto& it : (*equipment))
			{
				if (equipmentSlotToIndex(it.getEquipmentSlot()) == i)
				{
					gameEquipment[i].push_back(it);
				}
			}
		}
	}
	catch (...)
	{
		std::cout << "Could not load master game items list\n";
	}
		
}