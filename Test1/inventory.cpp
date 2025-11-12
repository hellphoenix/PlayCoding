#include "inventory.h"
#include <algorithm>
#include <unordered_map>
#include <iostream>

using std::cout, std::endl;


void Inventory::addToInventory(const Item& _item)
{
	
	items.push_back(_item);
	sortInventory();
}

void Inventory::removeFromInventory(const string& _itemName)
{
	auto tempItem = std::remove_if(items.begin(), items.end(),[&](const Item& _item) 
		{ 
			return _item.getItemName() == _itemName; 
		});

	items.erase(tempItem, items.end());
	sortInventory();
}

Item Inventory::equipFromInventory(const string& _itemName, Item::ItemSlot _slot)
{
	auto tempItem = std::find_if(items.begin(), items.end(), [&](const Item& _item)
		{
			return _item.getItemName() == _itemName && _item.getItemSlot() == _slot;
		});
	
	if (tempItem != items.end())
	{
		Item foundItem = std::move(*tempItem);               // copy the item to return
		items.erase(tempItem);                    // remove from inventory
		sortInventory();
		return foundItem;                   // return for equipping
	}

	// If not found, return a default EMPTY item
	return Item();
}


void Inventory::sortInventory()
{
	std::sort(items.begin(), items.end(),[](const Item& a, const Item& b)
		{
			if (a.getItemRarity() != b.getItemRarity())
				return a.getItemRarity() > b.getItemRarity();
			if (a.getItemSlot() != b.getItemSlot())
				return a.getItemSlot() < b.getItemSlot();
			return a.getItemName() < b.getItemName();
		});
}

void Inventory::printInventory() const
{
	std::cout << "=== Player Inventory ===" << endl;
	for (const auto& item : items)
		item.printItem();
	cout << "========================" << endl;
	cout << endl;
	cout << endl;
}