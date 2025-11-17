#pragma once
#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include <map>
#include <string>
#include "item.h"

struct Equipment : public Item
{
	enum class EquipmentSlot // change me when adding item slots
	{
		EMPTY = 0,
		HELMET,
		CHESTPIECE,
		PANTS,
		BOOTS,
		SHIELD,
		WEAPON,
		COUNT
	};

	static const std::map<EquipmentSlot, std::string> equipmentSlotToString;

	Equipment() : Item("", "", Item::ItemType::EQUIPMENT, Item::ItemRarity::NONEXISTENT), equipmentAttack(0), equipmentDefense(0),
		equipmentHealth(0), equipmentSlot(EquipmentSlot::EMPTY){}

	Equipment(const std::string& _id, const std::string& _equipmentName, int _equipmentAttack, int _equipmentDefense, int _equipmentHealth,
		EquipmentSlot _equipmentSlot = EquipmentSlot::EMPTY, Item::ItemRarity _equipmentRarity = Item::ItemRarity::POOR) :
		Item(_id, _equipmentName, Item::ItemType::EQUIPMENT, _equipmentRarity),
		equipmentAttack(_equipmentAttack), equipmentDefense(_equipmentDefense),
		equipmentHealth(_equipmentHealth), equipmentSlot(_equipmentSlot){}

	int getEquipmentAttack() const;
	int getEquipmentDefense() const;
	int getEquipmentHealth() const;
	EquipmentSlot getEquipmentSlot() const;

	void setEquipmentAttack(int _equipmentAttack);
	void setEquipmentDefense(int _equipmentDefense);
	void setEquipmentHealth(int _equipmentHealth);
	void setEquipmentSlot(EquipmentSlot _itemSlot);

	void printEquipment() const;

private:

	EquipmentSlot equipmentSlot;
	int equipmentAttack;
	int equipmentDefense;
	int equipmentHealth;
};

// returns an int value from an equipment slot
constexpr std::size_t equipmentSlotToIndex(Equipment::EquipmentSlot slot) 
{
	return static_cast<std::size_t>(slot);
}

// Returns an equipment slot, between EMPTY and COUNT, from an int
constexpr Equipment::EquipmentSlot equipmentSlotFromIndex(int _index) 
{
	if (_index > 0 && _index < equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT))
		return static_cast<Equipment::EquipmentSlot>(_index);
	else
		return Equipment::EquipmentSlot::EMPTY;
}

#endif // !EQUIPMENT_H
