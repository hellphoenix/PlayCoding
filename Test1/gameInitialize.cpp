#include "gameInitialize.h"
#include "game.h"
#include <iostream>
using std::cout, std::endl;


void GameInitialize::run()
{

	loadItems();
	createPlayer();
	giveStartingItems();

	Game game;
	game.loop(playerOne, gameItems);
}

void GameInitialize::loadItems()
{
	items = &ItemLibrary::items(); // point to item library master list

	// Creates an array of vectors(gameItems) for all item slots, excluding EMPTY.
	// Currently, Consumables are in gameItems[0], Helmets are in gameItems[1], Chestpieces are in gameItems[2], etc.
	for (int i = 1; i < itemSlotToIndex(Item::ItemSlot::COUNT); i++) 
	{
		for (const auto& it : (*items))
		{
			if (itemSlotToIndex(it.getItemSlot()) == i)
			{
				gameItems[i-1].emplace_back(it);
			}		
		}		
	}	
}

void GameInitialize::createPlayer()
{
	playerOne = Player{ "Tony", 200, 10, 10};
}

const Player& GameInitialize::getPlayer() const
{
	return playerOne;
}

void GameInitialize::giveStartingItems()
{

	playerOne.getPlayerInventory().addToInventory(ItemLibrary::byId("helmet_leather_05"));
	playerOne.getPlayerInventory().addToInventory(ItemLibrary::byId("helmet_leather_06"));
	playerOne.equipItem(ItemLibrary::byId("sword_steel_01"));
	playerOne.equipItem((*items)[3]);
	playerOne.equipItem(gameItems[1][0]);
}