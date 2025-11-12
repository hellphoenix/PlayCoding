#pragma once
#include "item_library.h"
using std::vector;

#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory
{
private:
	vector<Item> items;

public:
	const vector<Item>& getItems() const { return items; }
	void addToInventory(const Item& _item);
	void removeFromInventory(const string& _itemName);
	Item equipFromInventory(const string& _itemName, Item::ItemSlot _slot);
	void unequipToInventory(const Item& _item);

	void sortInventory();
	void groupInventory();

	void printInventory() const;
};


#endif // !INVENTORY_H

