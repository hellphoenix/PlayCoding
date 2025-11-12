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
	auto tempItem = std::remove_if(items.begin(), items.end(),[&](const Item& item) 
		{ 
			return item.getItemName() == _itemName; 
		});

	items.erase(tempItem, items.end());
	sortInventory();
}

Item Inventory::equipFromInventory(const string& _itemName, Item::ItemSlot _slot)
{
	auto tempItem = std::find_if(items.begin(), items.end(), [&](const Item& item)
		{
			return item.getItemName() == _itemName && item.getItemSlot() == _slot;
		});
	
	if (tempItem != items.end())
	{
		Item foundItem = *tempItem;               // copy the item to return
		items.erase(tempItem);                    // remove from inventory
		sortInventory();
		return foundItem;                   // return for equipping
	}

	// If not found, return a default EMPTY item
	return Item();
}

void Inventory::unequipToInventory(const Item& _item)
{
	if (_item.getItemSlot() != Item::ItemSlot::EMPTY)
	{
		items.push_back(_item);
		sortInventory();
	}
		
}

void Inventory::sortInventory()
{
	std::sort(items.begin(), items.end(),[](const Item& a, const Item& b)
		{
			return static_cast<int>(a.getItemRarity()) > static_cast<int>(b.getItemRarity());
		});
}

void Inventory::groupInventory() // Doesn't seem to actually group items within the inventory
{
	std::unordered_map<Item::ItemType, vector<Item>> grouped;

	for (const auto& item : items)
		grouped[item.getItemType()].push_back(item);

	for (const auto& [type, group] : grouped)
	{
		cout << "Group: " << Item::itemTypeToString.at(type) << endl;
		for (const auto& i : group)
			i.printItem();
		cout << std::endl;
	}
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