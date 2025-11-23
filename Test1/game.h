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
		Save,
		Load,
		SpawnEnemy,
		FightEnemy,
		Quit
	};

	enum class DragSource
	{
		None,
		Inventory,
		EquippedSlot,
		MasterList
	};

	Player player = Player{ "Tony", 200, 200, 10, 10 };
	void loop(std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)>& _gameEquipment);
	Game();

private:

	bool normal = false;
	bool pendingSave = false;
	bool pendingLoad = false;

	bool showCharacterSheet = false;
	bool showInventorySheet = false;
	bool showMasterEquipmentSheet = false;

	bool leftMouseButtonPressed = false;
	bool rightMouseButtonPressed = false;
	bool mouseMoving = false;

	Mode mode = Mode::Normal;
	std::string textBuffer;	
	Enemy enemy;
	CombatActions combatActions ;
	InventoryActions inventoryActions;
	std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)> gameEquipment;

	sf::Font uiFont;

	/*void startSave();*/
	/*void save(const sf::Event::TextEntered& _text);*/

	/*void startLoad();*/
	/*void load(const sf::Event::TextEntered& _text);*/

	void Quit();

	void startFight();

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
	void handleMousePressed(const sf::Event::MouseButtonPressed _mousePressed);
	void handleMouseReleased(const sf::Event::MouseButtonReleased _mouseReleased);
	void handleMouseMoved(const sf::Event::MouseMoved _mouseMoved);
	void update(float dt);

	void draw(sf::RenderWindow& window, float windowWidth, float windowHeight);
	void drawCharacterSheet(sf::RenderWindow& window, float windowWidth, float windowHeight);
	void drawInventorySheet(sf::RenderWindow& window, float windowWidth, float windowHeight);
	void drawMasterEquipmentSheet(sf::RenderWindow& window, float windowWidth, float windowHeight);

	void handleDropOnCharacter(const sf::Vector2f& dropPos);
	void handleDropOnInventory(const sf::Vector2f& dropPos);

	// new: drag state
	struct DragState
	{
		bool active = false;
		DragSource source = DragSource::None;
		std::size_t inventoryIndex = 0;           // which item in inventory
		Equipment::EquipmentSlot slot{};
		sf::Vector2f cursorPos{ 0.f, 0.f };         // current mouse position
		sf::Vector2f offset{ 0.f, 0.f };
	} drag;

	// new: per frame hitboxes
	std::vector<sf::FloatRect> inventoryItemRects; // same order as inventory vector
	std::vector<sf::FloatRect> masterItemRects;
	std::array<sf::FloatRect, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)> slotRects;
	sf::RectangleShape inventoryRect;

	
};
#endif // !GAME_H
