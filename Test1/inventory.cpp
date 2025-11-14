#include "inventory.h"
#include <algorithm>
#include <unordered_map>
#include <iostream>

using std::cout, std::endl;


void Inventory::addToInventory(const Item& _item)
{
	if (_item.getId() != "")
		inventoryItems.push_back(_item);
}

void Inventory::removeFromInventory(const string& _id)
{
	auto tempItem = std::remove_if(inventoryItems.begin(), inventoryItems.end(),[&](const Item& _item) 
		{ 
			return _item.getId() == _id;
		});

	inventoryItems.erase(tempItem, inventoryItems.end());
}

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

vector<Item> Inventory::filterInventoryBySlot(Item::ItemSlot _slot) const
{
	vector<Item> filteredList;
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

vector<Item> Inventory::filterInventoryByType(Item::ItemType _type) const
{
	vector<Item> filteredList;
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

vector<Item> Inventory::filterInventoryByRarity(Item::ItemRarity _rarity) const
{
	vector<Item> filteredList;
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

const Item Inventory::searchInventoryById(const string& _id) const
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
	std::cout << "=== Player Inventory ===" << endl;
	cout << "|                   Id |      Type |    Rarity |       Slot |                  Name | Attack | Defense | Health |" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	for (const auto& item : inventoryItems)
		item.printItem();
	cout << "========================" << endl;
	cout << endl;
	cout << endl;
}