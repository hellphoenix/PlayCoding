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
	const vector<Item>& getItems() const { return inventoryItems; }
	void addToInventory(const Item& _item);
	void removeFromInventory(const string& _id);

	void sortInventory();
	void filterInventoryBySlot(Item::ItemSlot _slot, vector<Item>& _filterList);
	void printInventory();
};


#endif // !INVENTORY_H

