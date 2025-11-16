#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H
#include "item_library.h"
#include <vector>

class Inventory
{
private:
	std::vector<Item> inventoryItems;

public:
	const std::vector<Item>& getInventory() const { return inventoryItems; }
	void addToInventory(const Item& _item);
	void removeFromInventory(const std::string& _id);

	void sortInventory();
	std::vector<Item> filterInventoryBySlot(Item::ItemSlot _slot) const;
	std::vector<Item> filterInventoryByType(Item::ItemType _type) const;
	std::vector<Item> filterInventoryByRarity(Item::ItemRarity _rarity) const;
	Item findById(const std::string& _id) const;
	void printInventory();
};


#endif // !INVENTORY_H

