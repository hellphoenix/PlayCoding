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



private:
	std::string textBuffer;
	std::vector<Equipment> equipCandidates;
	
};


#endif // !INVENTORY_ACTIONS_H
