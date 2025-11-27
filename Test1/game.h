#pragma once
#ifndef GAME_H
#define GAME_H
#include "button.h"
#include "characterRenderer.h"
#include "combatActions.h"
#include "dragSource.h"
#include "enemy.h"
#include "equipment.h"
#include "gameMode.h"
#include "hudRenderer.h"
#include "inventoryActions.h"
#include "inventoryRenderer.h"
#include "menuRenderer.h"
#include "player.h"
#include "uiFonts.h"
#include "textures.h"
#include <array>
#include <SFML/Graphics.hpp>
#include <vector>
class Game
{

public:
	typedef std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)> equipmentArray;
	typedef std::array<sf::FloatRect, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)> slotFloatRects;

	Player player = Player{ "Tony", 200, 200, 10, 10 };
	void loop(const equipmentArray& _gameEquipment);
	Game() {}

	std::vector<Button*> buttonVectors;
	float keyTimeMax = 1000.f;
	float keyTime = keyTimeMax;

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
	Textures texture;
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



	void handleEvent(const sf::Event& _event, const sf::RenderWindow& window);
	void handleKeyPressed(const sf::Event::KeyPressed& _keyPressed, const sf::RenderWindow& window);
	void handleTextEntered(const sf::Event::TextEntered& _textEntered);
	void handleMousePressed(const sf::Event::MouseButtonPressed _mousePressed, const sf::RenderWindow& window);
	void handleMouseReleased(const sf::Event::MouseButtonReleased _mouseReleased, const sf::RenderWindow& window);
	void handleMouseMoved(const sf::Event::MouseMoved _mouseMoved, const sf::RenderWindow& window);
	void update(float dt, const sf::RenderWindow& window);

	void draw(sf::RenderWindow& window, float windowWidth, float windowHeight);

	void handleDropOnCharacter(const sf::Vector2f& dropPos);
	void handleDropOnInventory(const sf::Vector2f& dropPos);

	std::vector<sf::FloatRect> inventoryItemRects;
	std::vector<sf::FloatRect> masterItemRects;
	slotFloatRects slotRects;
	sf::RectangleShape inventoryRect;
};
#endif // !GAME_H
