#include "game.h"
#include "gameInitialize.h"
#include <iostream>


void GameInitialize::run()
{

	loadItems();

	Game game;
	game.loop(gameItems);
}

void GameInitialize::loadItems()
{
	try
	{
		items = &ItemLibrary::items(); // point to item library master list

		// Creates an array of vectors(gameItems) for all item slots
		for (int i = 0; i < itemSlotToIndex(Item::ItemSlot::COUNT); i++)
		{
			for (const auto& it : (*items))
			{
				if (itemSlotToIndex(it.getItemSlot()) == i)
				{
					gameItems[i].push_back(it);
				}
			}
		}
	}
	catch (...)
	{
		std::cout << "Could not load master game items list\n";
	}
		
}

const std::array<std::vector<Item>, itemSlotToIndex(Item::ItemSlot::COUNT)>& GameInitialize::getGameItems() const
{
	return gameItems;
}