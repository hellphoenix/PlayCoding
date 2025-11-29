#include "inventory.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>

// Adds item to inventory if it has a proper item ID. Input is Item object. 
void Inventory::addEquipmentToInventory(const Equipment& _equipment)
{
	if (_equipment.getId() != "")
	{
		equipmentInventory.push_back(_equipment);
		sortEquipmentInventory();
	}

}

// Removes item from inventory if it exists. Input is item ID.
void Inventory::removeEquipmentFromInventory(const std::string& _id)
{
	const auto tempItem = std::find_if(equipmentInventory.begin(), equipmentInventory.end(), [&](const Equipment& _equipment)
		{
			return _equipment.getId() == _id;
		});

	if (tempItem == equipmentInventory.end())
	{
		return; // Nothing to remove
	}

	equipmentInventory.erase(tempItem);
	equipmentInventory.shrink_to_fit();
	sortEquipmentInventory();
}

// Sorts inventory by slot type, then rarity, then name.
void Inventory::sortEquipmentInventory()
{
	std::sort(equipmentInventory.begin(), equipmentInventory.end(), [](const Equipment& a, const Equipment& b)
		{
			if (a.getEquipmentSlot() != b.getEquipmentSlot())
				return a.getEquipmentSlot() < b.getEquipmentSlot();
			if (a.getItemRarity() != b.getItemRarity())
				return a.getItemRarity() > b.getItemRarity();
			return a.getItemName() < b.getItemName();
		});
}

// Filters equipment inventory by EquipmentSlot. Input is EquipmentSlot. Returns a vector of Equipment.
std::vector<Equipment> Inventory::filterEquipmentInventoryBySlot(EquipmentSlot _slot) const
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

// Filters equipment inventory by ItemRarity. Input is ItemRarity. Returns a vector of Equipment.
std::vector<Equipment> Inventory::filterEquipmentInventoryByRarity(ItemRarity _rarity) const
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

// Finds equipment by ID string. Input is ID. Returns either the found Equipment object or an empty Equipment object.
Equipment Inventory::findEquipmentById(const std::string& _id) const
{
	for (const auto& equipment : equipmentInventory)
	{
		if (equipment.getId() == _id) return equipment; // if we find the item ID in our inventory, we return that item
	}
	return Equipment{}; // If the item id is not found in our inventory, we return an empty item
}