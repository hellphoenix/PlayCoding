#pragma once
#ifndef GAME_H
#define GAME_H
#include "characterRenderer.h"
#include "combatActions.h"
#include "dragSource.h"
#include "enemy.h"
#include "equipment.h"
#include "gameInitialize.h"
#include "gameMode.h"
#include "hudRenderer.h"
#include "inventoryActions.h"
#include "inventoryRenderer.h"
#include "menuRenderer.h"
#include "player.h"
#include "uiFonts.h"
#include <array>
#include <SFML/Graphics.hpp>
class Game
{

public:
	typedef std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)> equipmentArray;
	typedef std::array<sf::FloatRect, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)> slotFloatRects;

	Player player = Player{ "Tony", 200, 200, 10, 10 };
	void loop(equipmentArray& _gameEquipment);
	Game() {}

private:

	bool pendingSave = false;
	bool pendingLoad = false;

	bool showCharacterSheet = false;
	bool showInventorySheet = false;
	bool showMasterEquipmentSheet = false;

	bool leftMouseButtonPressed = false;
	bool rightMouseButtonPressed = false;
	bool mouseMoving = false;

	GameMode gameMode = GameMode::Normal;
	DragSource::DragState dragState;
	UiFonts baseUiFont;
	sf::Font uiFont = baseUiFont.uiFont;
	//std::string textBuffer;

	Enemy enemy;
	CombatActions combatActions;

	InventoryActions inventoryActions = InventoryActions(uiFont);
	HudRenderer hudRenderer = HudRenderer(uiFont);
	CharacterRenderer characterRenderer = CharacterRenderer(uiFont);
	InventoryRenderer inventoryRenderer = InventoryRenderer(uiFont);
	//MenuRenderer menuRenderer;

	equipmentArray gameEquipment;

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
		player.equipEquipment(ItemLibrary::equipmentById("sword_steel_01"));
		player.equipEquipment(gameEquipment[1][0]);
	}



	void handleEvent(const sf::Event& _event);
	void handleKeyPressed(const sf::Event::KeyPressed& _keyPressed);
	void handleTextEntered(const sf::Event::TextEntered& _textEntered);
	void handleMousePressed(const sf::Event::MouseButtonPressed _mousePressed);
	void handleMouseReleased(const sf::Event::MouseButtonReleased _mouseReleased);
	void handleMouseMoved(const sf::Event::MouseMoved _mouseMoved);
	void update(float dt);

	void draw(sf::RenderWindow& window, float windowWidth, float windowHeight);

	void handleDropOnCharacter(const sf::Vector2f& dropPos);
	void handleDropOnInventory(const sf::Vector2f& dropPos);

	std::vector<sf::FloatRect> inventoryItemRects;
	std::vector<sf::FloatRect> masterItemRects;
	slotFloatRects slotRects;
	sf::RectangleShape inventoryRect;
};
#endif // !GAME_H
