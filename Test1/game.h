#pragma once
#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "combatActions.h"
#include "inventoryActions.h"
#include "gameInitialize.h"
#include "player.h"
#include "equipment.h"
class Game
{

public:

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
		DebugRemoveFromInventoryItem,
		Save,
		Load,
		SpawnEnemy,
		FightEnemy,
		Quit
	};

	Player player = Player{ "Tony", 200, 200, 10, 10 };
	void loop(std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)>& _gameEquipment);
	bool pendingEquipSelectItem = false;
private:

	bool normal = false;
	bool pendingDebugName = false;
	bool pendingDebugAttack = false;
	bool pendingDebugDefense = false;
	bool pendingDebugHealth = false;
	bool pendingDebugAddToInventoryItemInput = false;
	bool pendingDebugRemoveFromInventory = false;
	bool pendingSave = false;
	bool pendingLoad = false;

	Mode mode = Mode::Normal;
	std::vector<Equipment> equipCandidates;
	std::string textBuffer;	
	Enemy enemy;
	CombatActions combatActions ;
	InventoryActions inventoryActions;
	std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)> gameEquipment;


	void startEquip();
	//void handleEquipSlotInput(int _slotNumber);
	//void handleEquipItemInput(const sf::Event::TextEntered& _text);

	void startUnequip();
	//void handleUnequipSlotInput(int _slotNumber);

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
	//void debugAddToInventorySlotInput(int _slotNumber);
	//void debugAddToInventoryItemInput(const sf::Event::TextEntered& _text);

	void startDebugRemoveFromInventory();
	//void debugRemoveFromInventory(const sf::Event::TextEntered& _text);

	void startSave();
	void save(const sf::Event::TextEntered& _text);

	void startLoad();
	void load(const sf::Event::TextEntered& _text);

	void Quit();

	void startFight();

	void printHelp() const;

	void giveStartingItems()
	{

		player.getPlayerInventory().addEquipmentToInventory(ItemLibrary::equipmentById("helmet_leather_05"));
		player.getPlayerInventory().addEquipmentToInventory(ItemLibrary::equipmentById("helmet_leather_06"));
		player.equipItem(ItemLibrary::equipmentById("sword_steel_01"));
		player.equipItem(gameEquipment[1][0]);
	}


	
	void handleEvent(const sf::Event& _event);
	void handleKeyPressed(const sf::Event::KeyPressed& _keyPressed);
	void handleTextEntered(const sf::Event::TextEntered& _textEntered);
	void update(float dt);
	//void draw(sf::RenderWindow& window);
};
#endif // !GAME_H
