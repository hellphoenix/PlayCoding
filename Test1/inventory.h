#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H
#include "item_library.h"
#include "equipment.h"
#include <vector>

class Inventory
{
private:
	std::vector<Equipment> equipmentInventory;

public:
	const std::vector<Equipment>& getEquipmentInventory() const { return this->equipmentInventory; }
	void addEquipmentToInventory(const Equipment& _equipment);
	void removeEquipmentFromInventory(const std::string& _id);

	void sortEquipmentInventory();
	std::vector<Equipment> filterEquipmentInventoryBySlot(EquipmentSlot _slot) const;
	std::vector<Equipment> filterEquipmentInventoryByRarity(ItemRarity _rarity) const;
	Equipment findEquipmentById(const std::string& _id) const;
};


#endif // !INVENTORY_H

