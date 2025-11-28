#pragma once
#ifndef INVENTORY_ACTIONS_H
#define INVENTORY_ACTIONS_H
#include "mouseDragCheck.h"
#include "equipment.h"
#include "hudRenderer.h"
#include "player.h"
#include "SFML/Graphics.hpp"
#include <string>
#include <vector>

enum class NumberInputKey
{
	Confirm,    // Enter
	Cancel,     // Escape
	Backspace,  // Backspace
	Digit       // '0'..'9'
};

class InventoryActions
{
public:
	typedef std::array<std::vector<Equipment>, equipmentSlotToIndex(EquipmentSlot::COUNT)> equipmentArray;
	typedef std::array<sf::FloatRect, equipmentSlotToIndex(EquipmentSlot::COUNT)> slotFloatRects;
	HudRenderer hudRenderer;
	sf::Font uiFont;
	InventoryActions() {}
	InventoryActions(const sf::Font& uiFont) { this->uiFont = uiFont; }
	void dragFromInventory(sf::RenderWindow& window, Player& player, MouseDragCheck::DragState& dragState) const;
	void dragFromEquippedSlot(sf::RenderWindow& window, Player& player, MouseDragCheck::DragState& dragState) const;
	void dragFromMasterList(sf::RenderWindow& window, Player& player, MouseDragCheck::DragState& dragState, equipmentArray& gameEquipment) const;
	void dropOnPlayerSlot(const sf::Vector2f& dropPos, Player& player, MouseDragCheck::DragState& dragState, equipmentArray& gameEquipment, slotFloatRects& slotRects);
	void dropOnInventory(Player& player, MouseDragCheck::DragState& dragState, equipmentArray& gameEquipment);

	void drawBoxHelper(sf::RenderWindow& window, Player& player, MouseDragCheck::DragState& dragState, Equipment equipment) const;


private:
	std::string textBuffer;
	std::vector<Equipment> equipCandidates;

};


#endif // !INVENTORY_ACTIONS_H
