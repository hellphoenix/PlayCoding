#pragma once
#ifndef MOUSE_DRAG_CHECK_H
#define MOUSE_DRAG_CHECK_H
#include "equipment.h"
#include "SFML/Graphics.hpp"

enum class DragSource
{
	None,
	Inventory,
	EquippedSlot,
	MasterList
};

struct MouseDragCheck
{
	struct DragState
	{
		bool active = false;
		DragSource source = DragSource::None;
		std::size_t inventoryIndex = 0;           // which item in inventory
		EquipmentSlot slot{};
		sf::Vector2f cursorPos{ 0.f, 0.f };         // current mouse position
		sf::Vector2f offset{ 0.f, 0.f };
	} drag;

	// Open for future use
};

#endif // !MOUSE_DRAG_CHECK_H


