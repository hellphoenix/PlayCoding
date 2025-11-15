#pragma once
#include "player.h"
#include "enemy.h"
#include "gameActions.h"
#include "gameInitialize.h"
#ifndef GAME_H
#define GAME_H





class Game
{
private:

	enum class Mode
	{
		Normal,
		EquipSelectSlot,
		EquipSelectItem,
		UnequipSelectSlot,
		DebugName,
		DebugAttack,
		DebugDefense,
		DebugHealth,
		DebugAddToInventorySlot,
		DebugAddToInventoryItem,
		DebugRemoveFromInventorySlot,
		DebugRemoveFromInventoryItem,
		Save,
		Load,
		SpawnEnemy,
		FightEnemy,
		Quit
	};


	Mode mode = Mode::Normal;
	//int selectedSlotIndex = -1;
	std::vector<Item> equipCandidates;


	Player player;
	Enemy enemy;
	GameActions gameActions;
	std::array<vector<Item>, itemSlotToIndex(Item::ItemSlot::COUNT)> gameItems;

	//Functions below this will change

	//void changeName();
	//void changeBaseAttack();
	//void changeBaseDefense();
	//void changeBaseHealth();
	//void addToInventory();
	//void removeFromInventory();

	void startEquip();
	void handleEquipSlotInput(int _slotNumber);
	void handleEquipItemInput(int _itemNumber);
	void startUnequip();
	void handleUnequipSlotInput(int _slotNumber);
	void startDebug();
	void startSave();
	void startLoad();
	void Quit();
	void startFight();
	//void handleDebugCommand();
	//void handleSaveCommand();
	//void handleLoadCommand();
	//void handleFightCommand();
	void printHelp() const;


public:

	void loop(Player _player, const std::array<vector<Item>, itemSlotToIndex(Item::ItemSlot::COUNT)>& _gameItems);
	void handleEvent(const sf::Event& _event);
	//void update(float dt);
	//void draw(sf::RenderWindow& window);

};
#endif // !GAME_H
