#pragma once
#ifndef INVENTORY_ACTIONS_H
#define INVENTORY_ACTIONS_H
#include "equipment.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class InventoryActions
{
public:
	InventoryActions();
	void handleEquipSlotInput(int _slotNumber, Player& _player, bool& _pendingEquipSelectItem, bool& _normal);
	void handleEquipItemInput(const sf::Event::TextEntered& _text, Player& _player, bool& _normal);

	void handleUnequipSlotInput(int _slotNumber, Player& _player, bool& _normal);

	void debugAddToInventorySlotInput(int _slotNumber, std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)>& _gameEquipment, bool& _pendingDebugAddToInventoryItemInput, bool& _normal);
	void debugAddToInventoryItemInput(const sf::Event::TextEntered& _text, Player& _player, bool& _normal);

	void debugRemoveFromInventory(const sf::Event::TextEntered& _text, Player& _player, bool& _normal);

private:
	std::string textBuffer;
	std::vector<Equipment> equipCandidates;
	
};


#endif // !INVENTORY_ACTIONS_H
