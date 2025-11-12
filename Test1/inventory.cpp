#include "inventory.h"
#include <algorithm>
#include <unordered_map>
#include <iostream>

using std::cout, std::endl;


void Inventory::addToInventory(const Item& _item)
{
	
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

void Inventory::filterInventoryBySlot(Item::ItemSlot _slot, vector<Item>& _filterList)
{
	for (Item item : Inventory::inventoryItems)
	{	
		if (item.getItemSlot() == _slot)
		{
			_filterList.push_back(item);
		}
	}
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