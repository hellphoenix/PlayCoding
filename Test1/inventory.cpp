#include "inventory.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>

// Adds item to inventory if it has a proper item ID. Input is Item object. 
void Inventory::addToInventory(const Item& _item)
{
	if (_item.getId() != "")
		inventoryItems.push_back(_item);
}

// Removes item from inventory if it exists. Input is item ID.
void Inventory::removeFromInventory(const std::string& _id)
{
	auto tempItem = std::remove_if(inventoryItems.begin(), inventoryItems.end(),[&](const Item& _item) 
		{ 
			return _item.getId() == _id;
		});

	inventoryItems.erase(tempItem, inventoryItems.end());
}

// Sorts inventory by slot type, then rarity, then name.
void Inventory::sortInventory()
{
	std::sort(inventoryItems.begin(), inventoryItems.end(),[](const Item& a, const Item& b)
		{
			if (a.getItemSlot() != b.getItemSlot())
				return a.getItemSlot() < b.getItemSlot();
			if (a.getItemRarity() != b.getItemRarity())
				return a.getItemRarity() > b.getItemRarity();
			return a.getItemName() < b.getItemName();
		});
}

// Filters inventory by ItemSlot. Input is ItemSlot. Returns a vector of Items.
std::vector<Item> Inventory::filterInventoryBySlot(Item::ItemSlot _slot) const
{
	std::vector<Item> filteredList;
	filteredList.reserve(inventoryItems.size());

	for (const auto& item : inventoryItems)
	{
		if (item.getItemSlot() == _slot)
		{
			filteredList.push_back(item);
		}
	}
	filteredList.shrink_to_fit();

	return filteredList;
}

std::vector<Item> Inventory::filterInventoryByType(Item::ItemType _type) const
{
	std::vector<Item> filteredList;
	filteredList.reserve(inventoryItems.size());

	for (const auto& item : inventoryItems)
	{
		if (item.getItemType() == _type)
		{
			filteredList.push_back(item);
		}
	}
	filteredList.shrink_to_fit();

	return filteredList;

}

std::vector<Item> Inventory::filterInventoryByRarity(Item::ItemRarity _rarity) const
{
	std::vector<Item> filteredList;
	filteredList.reserve(inventoryItems.size());

	for (const auto& item : inventoryItems)
	{
		if (item.getItemRarity() == _rarity)
		{
			filteredList.push_back(item);
		}
	}
	filteredList.shrink_to_fit();

	return filteredList;
}

Item Inventory::findById(const std::string& _id) const
{
	for (const auto& item : inventoryItems)
	{
		if (item.getId() == _id) return item; // if we find the item ID in our inventory, we return that item
	}
	return Item{}; // If the item id is found in our inventory, we return an empty item
}

void Inventory::printInventory()
{
	sortInventory();
	std::cout << "=== Player Inventory ===" << std::endl;
	std::cout << "|                   Id |      Type |    Rarity |       Slot |                  Name | Attack | Defense | Health |" << std::endl;
	std::cout << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
	for (const auto& item : inventoryItems)
		item.printItem();
	std::cout << "========================" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}