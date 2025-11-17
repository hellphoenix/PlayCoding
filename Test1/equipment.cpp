#include "equipment.h"
#include <iomanip>
#include <iostream>


// Maps EquipmentSlot enums to strings.
const std::map<Equipment::EquipmentSlot, std::string> Equipment::equipmentSlotToString =
{
	{EquipmentSlot::EMPTY, "Empty"}, {EquipmentSlot::HELMET, "Helmet"}, {EquipmentSlot::CHESTPIECE, "Chestpiece"}, 
	{EquipmentSlot::PANTS, "Pants"}, {EquipmentSlot::BOOTS, "Boots"}, {EquipmentSlot::SHIELD, "Shield"}, {EquipmentSlot::WEAPON, "Weapon"}
};


int Equipment::getEquipmentAttack() const
{
	return equipmentAttack;
}

int Equipment::getEquipmentDefense() const
{
	return equipmentDefense;
}

int Equipment::getEquipmentHealth() const
{
	return equipmentHealth;
}

Equipment::EquipmentSlot Equipment::getEquipmentSlot() const
{
	return equipmentSlot;
}


void Equipment::setEquipmentAttack(int _equipmentAttack)
{
	equipmentAttack = _equipmentAttack;
}

void Equipment::setEquipmentDefense(int _equipmentDefense)
{
	equipmentDefense = _equipmentDefense;
}

void Equipment::setEquipmentHealth(int _equipmentHealth)
{
	equipmentHealth = _equipmentHealth;
}

void Equipment::setEquipmentSlot(EquipmentSlot _equipmentSlot)
{	
	equipmentSlot = _equipmentSlot;
}

void Equipment::printEquipment() const
{
	if (equipmentSlot == EquipmentSlot::EMPTY)
		return;

	std::cout << "| " << std::setw(22) << this->getId() << " | " << std::setw(9) << itemTypeToString.at(this->getItemType()) << " | " << std::setw(9) << itemRarityToString.at(this->getItemRarity()) << " | " << std::setw(10) << equipmentSlotToString.at(equipmentSlot)
		<< " | " << std::setw(21) << this->getItemName() << " | " << std::setw(6) << equipmentAttack << " | " << std::setw(7) << equipmentDefense << " | " << std::setw(6) << equipmentHealth << " |" << std::endl;
}