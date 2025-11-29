#pragma once
#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "item.h"
#include <map>
#include <string>

enum class EquipmentSlot
{
	EMPTY = 0,
	HELMET,
	TRINKET,
	CHESTPIECE,
	PANTS,
	BOOTS,
	SHIELD,
	WEAPON,
	COUNT
};

// Update this map when adding or removing an equipment slot if you want it to be seen on the character sheet.
static const std::map<EquipmentSlot, std::string> equipmentSlotToString =
{
	{EquipmentSlot::EMPTY, "Empty"},{EquipmentSlot::TRINKET, "Trinket"} , {EquipmentSlot::HELMET, "Helmet"}, {EquipmentSlot::CHESTPIECE, "Chestpiece"},
	{EquipmentSlot::PANTS, "Pants"}, {EquipmentSlot::BOOTS, "Boots"}, {EquipmentSlot::SHIELD, "Shield"}, {EquipmentSlot::WEAPON, "Weapon"}
};

constexpr size_t equipmentSlotToIndex(EquipmentSlot slot)
{
	return static_cast<size_t>(slot);
}

// Returns an equipment slot, between EMPTY and COUNT, from an int
constexpr EquipmentSlot equipmentSlotFromIndex(std::size_t _index)
{
	if (_index > 0 && _index < equipmentSlotToIndex(EquipmentSlot::COUNT))
		return static_cast<EquipmentSlot>(_index);
	else
		return EquipmentSlot::EMPTY;
}

class Equipment : public Item
{
private:

	EquipmentSlot equipmentSlot;
	int equipmentAttack;
	int equipmentDefense;
	int equipmentHealth;

public:

	Equipment() : Item("", "", ItemType::EQUIPMENT, ItemRarity::NONEXISTENT), equipmentAttack(0), equipmentDefense(0),
		equipmentHealth(0), equipmentSlot(EquipmentSlot::EMPTY) {
	}

	Equipment(const std::string& _id, const std::string& _equipmentName, int _equipmentAttack, int _equipmentDefense, int _equipmentHealth,
		EquipmentSlot _equipmentSlot = EquipmentSlot::EMPTY, ItemRarity _equipmentRarity = ItemRarity::POOR) :
		Item(_id, _equipmentName, ItemType::EQUIPMENT, _equipmentRarity),
		equipmentAttack(_equipmentAttack), equipmentDefense(_equipmentDefense),
		equipmentHealth(_equipmentHealth), equipmentSlot(_equipmentSlot) {
	}

	int getEquipmentAttack() const { return this->equipmentAttack; }
	int getEquipmentDefense() const { return this->equipmentDefense; }
	int getEquipmentHealth() const { return this->equipmentHealth; }
	EquipmentSlot getEquipmentSlot() const { return this->equipmentSlot; }

	void setEquipmentAttack(int _equipmentAttack) { this->equipmentAttack = _equipmentAttack; }
	void setEquipmentDefense(int _equipmentDefense) { this->equipmentDefense = _equipmentDefense; }
	void setEquipmentHealth(int _equipmentHealth) { this->equipmentHealth = _equipmentHealth; }
	void setEquipmentSlot(EquipmentSlot _equipmentSlot)
	{
		for (int i = 0; i < equipmentSlotToIndex(EquipmentSlot::COUNT); i++)
		{
			if (_equipmentSlot == equipmentSlotFromIndex(i))
			{
				this->equipmentSlot = _equipmentSlot;
				return;
			}
		}
		this->equipmentSlot = EquipmentSlot::EMPTY;
	}
};


#endif // !EQUIPMENT_H
