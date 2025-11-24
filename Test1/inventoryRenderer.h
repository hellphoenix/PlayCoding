#pragma once
#ifndef INVENTORY_RENDERER_H
#define INVENTORY_RENDERER_H
#include "player.h"
#include "SFML/Graphics.hpp"
#include <vector>

class InventoryRenderer
{
public:
	typedef std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)> equipmentArray;

	InventoryRenderer() {}
	InventoryRenderer(const sf::Font& uiFont) { this->uiFont = uiFont; }

	sf::Font uiFont;

	//Shows player inventory
	void drawInventorySheet(sf::RenderWindow& window, Player& player, std::vector<sf::FloatRect>& inventoryItemRects,
		sf::RectangleShape& inventoryRect, float windowWidth, float windowHeight) const;

	//Shows master equipment list. Used for debugging.
	void drawMasterEquipmentSheet(sf::RenderWindow& window, std::vector<sf::FloatRect>& masterItemRects,
		equipmentArray& gameEquipment, float windowWidth, float windowHeight) const;

	//Shows shop inventory. Can use for main shop and mini-shops, or can make separate one for mini-shop later.
	//void drawShopInventorySheet(sf::RenderWindow& window, float windowWidth, float windowHeight);
};
#endif // !INVENTORY_RENDERER_H
