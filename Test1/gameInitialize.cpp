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
	helmets = &ItemLibrary::helmets();
	chestPieces = &ItemLibrary::chestPieces();
	pants = &ItemLibrary::pants();
	boots = &ItemLibrary::boots();
	shields = &ItemLibrary::shields();
	swords = &ItemLibrary::swords();
}

void GameInitialize::createPlayer()
{
	playerOne = Player{ "Tony", 100, 10, 10 , (*helmets)[0], (*chestPieces)[0], (*pants)[0], (*boots)[0], (*shields)[0], (*swords)[0] };
}

const Player& GameInitialize::getPlayer() const
{
	return playerOne;
}

void GameInitialize::giveStartingItems()
{
	
	playerOne.getInventory().addToInventory((*helmets)[1]);
	playerOne.getInventory().addToInventory((*chestPieces)[2]);
	playerOne.getInventory().addToInventory((*pants)[2]);
	playerOne.getInventory().addToInventory((*shields)[1]);
	playerOne.getInventory().addToInventory((*swords)[2]);


}