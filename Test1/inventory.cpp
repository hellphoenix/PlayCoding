#include "inventory.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>

// Adds item to inventory if it has a proper item ID. Input is Item object. 
void Inventory::addEquipmentToInventory(const Equipment& _equipment)
{
	if (_equipment.getId() != "")
		equipmentInventory.push_back(_equipment);
}

// Removes item from inventory if it exists. Input is item ID.
void Inventory::removeEquipmentFromInventory(const std::string& _id)
{
	auto tempItem = std::remove_if(equipmentInventory.begin(), equipmentInventory.end(),[&](const Equipment& _equipment)
		{ 
			return _equipment.getId() == _id;
		});

	equipmentInventory.erase(tempItem, equipmentInventory.end());
}

// Sorts inventory by slot type, then rarity, then name.
void Inventory::sortEquipmentInventory()
{
	std::sort(equipmentInventory.begin(), equipmentInventory.end(),[](const Equipment& a, const Equipment& b)
		{
			if (a.getEquipmentSlot() != b.getEquipmentSlot())
				return a.getEquipmentSlot() < b.getEquipmentSlot();
			if (a.getItemRarity() != b.getItemRarity())
				return a.getItemRarity() > b.getItemRarity();
			return a.getItemName() < b.getItemName();
		});
}

// Filters inventory by ItemSlot. Input is ItemSlot. Returns a vector of Items.
std::vector<Equipment> Inventory::filterEquipmentInventoryBySlot(Equipment::EquipmentSlot _slot) const
{
	std::vector<Equipment> filteredList;
	filteredList.reserve(equipmentInventory.size());

	for (const auto& item : equipmentInventory)
	{
		if (item.getEquipmentSlot() == _slot)
		{
			filteredList.push_back(item);
		}
	}
	filteredList.shrink_to_fit();

	return filteredList;
}

std::vector<Equipment> Inventory::filterEquipmentInventoryByRarity(Item::ItemRarity _rarity) const
{
	std::vector<Equipment> filteredList;
	filteredList.reserve(equipmentInventory.size());

	for (const auto& equipment : equipmentInventory)
	{
		if (equipment.getItemRarity() == _rarity)
		{
			filteredList.push_back(equipment);
		}
	}
	filteredList.shrink_to_fit();

	return filteredList;
}

Equipment Inventory::findEquipmentById(const std::string& _id) const
{
	for (const auto& equipment : equipmentInventory)
	{
		if (equipment.getId() == _id) return equipment; // if we find the item ID in our inventory, we return that item
	}
	return Equipment{}; // If the item id is found in our inventory, we return an empty item
}

void Inventory::printEquipmentInventory()
{
	sortEquipmentInventory();
	std::cout << "=== Player Equipment Inventory ===" << std::endl;
	std::cout << "|                   Id |      Type |    Rarity |       Slot |                  Name | Attack | Defense | Health |" << std::endl;
	std::cout << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
	for (const auto& equipment : equipmentInventory)
		equipment.printEquipment();
	std::cout << "========================" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}