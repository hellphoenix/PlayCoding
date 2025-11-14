#pragma once
#include "item_library.h"
using std::vector;

#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory
{
private:
	vector<Item> inventoryItems;

public:
	const vector<Item>& getInventory() const { return inventoryItems; }
	void addToInventory(const Item& _item);
	void removeFromInventory(const string& _id);

	void sortInventory();
	vector<Item> filterInventoryBySlot(Item::ItemSlot _slot) const;
	vector<Item> filterInventoryByType(Item::ItemType _type) const;
	vector<Item> filterInventoryByRarity(Item::ItemRarity _rarity) const;
	const Item searchInventoryById(const string& _id) const;
	void printInventory();
};


#endif // !INVENTORY_H

