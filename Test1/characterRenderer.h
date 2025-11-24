#pragma once
#ifndef CHARACTER_RENDERER_H
#define	CHARACTER_RENDERER_H
#include "equipment.h"
#include "player.h"
#include "SFML/Graphics.hpp"

class CharacterRenderer
{


public:
	typedef std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)> equipmentArray;
	typedef std::array<sf::FloatRect, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)> slotFloatRects;
	sf::Font uiFont;

	CharacterRenderer() {}
	CharacterRenderer(const sf::Font& uiFont) { this->uiFont = uiFont; }

	//Shows Complete character sheet, including equipped items and detailed stats
	void drawPlayerCharacterSheet(sf::RenderWindow& window, Player& player, slotFloatRects& slotRects, float windowWidth, float windowHeight) const;

	//Shows enemy abilities and stats
	//void drawEnemyCharacterSheet(sf::RenderWindow& window, float windowWidth, float windowHeight);
};

#endif // !CHARACTER_RENDERER_H
