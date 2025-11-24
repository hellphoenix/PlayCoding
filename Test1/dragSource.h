#pragma once
#ifndef DRAG_SOURCE_H
#define DRAG_SOURCE_H
#include "equipment.h"
#include "SFML/Graphics.hpp"

class DragSource
{
public:
	enum class Source
	{
		None,
		Inventory,
		EquippedSlot,
		MasterList
	};

	struct DragState
	{
		bool active = false;
		DragSource::Source source = DragSource::Source::None;
		std::size_t inventoryIndex = 0;           // which item in inventory
		Equipment::EquipmentSlot slot{};
		sf::Vector2f cursorPos{ 0.f, 0.f };         // current mouse position
		sf::Vector2f offset{ 0.f, 0.f };
	} drag;
};



#endif // !DRAG_SOURCE_H


