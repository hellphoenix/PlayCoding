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
		DebugSelect,
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
	std::string textBuffer;
	bool pendingEquipSelectItem = false;
	bool pendingDebugName = false;
	bool pendingDebugAttack = false;
	bool pendingDebugDefense = false;
	bool pendingDebugHealth = false;
	bool pendingDebugEquipmentSelection = false;


	
	Enemy enemy;
	GameActions gameActions ;
	GameInitialize gameInitialize;
	Player player = Player{ "Tony", 200, 10, 10 };
	std::array<vector<Item>, itemSlotToIndex(Item::ItemSlot::COUNT)> gameItems;


	void startEquip();
	void handleEquipSlotInput(int _slotNumber);
	void handleEquipItemInput(const sf::Event::TextEntered& _text);

	void startUnequip();
	void handleUnequipSlotInput(int _slotNumber);

	void startDebug();

	void startDebugName();
	void debugName(const sf::Event::TextEntered& _text);

	void startDebugAttack();
	void debugAttack(const sf::Event::TextEntered& _text);

	void startDebugDefense();
	void debugDefense(const sf::Event::TextEntered& _text);

	void startDebugHealth();
	void debugHealth(const sf::Event::TextEntered& _text);

	void startDebugAddToInventory();
	void debugEquipmentSlotInput(int _slotNumber);
	void debugEquipmentItemInput(const sf::Event::TextEntered& _text); // change to text input

	void startSave();
	void startLoad();

	void Quit();

	void startFight();

	void printHelp() const;

	void giveStartingItems()
	{
		player.getPlayerInventory().addToInventory(ItemLibrary::byId("helmet_leather_05"));
		player.getPlayerInventory().addToInventory(ItemLibrary::byId("helmet_leather_06"));
		player.equipItem(ItemLibrary::byId("sword_steel_01"));
		player.equipItem(gameItems[1][0]);
	}


public:

	void loop(std::array<vector<Item>, itemSlotToIndex(Item::ItemSlot::COUNT)>& _gameItems);
	void handleEvent(const sf::Event& _event);
	void handleKeyPressed(const sf::Event::KeyPressed& _keyPressed);
	//void handleTextEntered();
	void update(float dt);
	//void draw(sf::RenderWindow& window);

};
#endif // !GAME_H
