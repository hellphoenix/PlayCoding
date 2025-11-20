#pragma once
#ifndef INVENTORY_ACTIONS_H
#define INVENTORY_ACTIONS_H
#include "equipment.h"
#include "player.h"
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
	InventoryActions() {}
	//void handleEquipSlotInput(int _slotNumber, Player& _player, bool& _pendingEquipSelectItem, bool& _normal);

	//void handleEquipItemInput(NumberInputKey key, char digit, Player& _player, bool& _normal);

	void handleUnequipSlotInput(int _slotNumber, Player& _player, bool& _normal);

	void debugAddToInventorySlotInput(int _slotNumber, std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)>& _gameEquipment, bool& _pendingDebugAddToInventoryItemInput, bool& _normal);

	void debugAddToInventoryItemInput(NumberInputKey key, char digit, Player& _player, bool& _normal);

	void debugRemoveFromInventory(NumberInputKey key, char digit, Player& _player, bool& _normal);

private:
	std::string textBuffer;
	std::vector<Equipment> equipCandidates;
	
};


#endif // !INVENTORY_ACTIONS_H
