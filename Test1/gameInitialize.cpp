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
	game.loop(playerOne);
}

void GameInitialize::loadItems()
{
	items = &ItemLibrary::items(); // not being used currently, but does point to item library map
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
}