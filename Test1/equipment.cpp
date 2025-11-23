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
	return this->equipmentAttack;
}

int Equipment::getEquipmentDefense() const
{
	return this->equipmentDefense;
}

int Equipment::getEquipmentHealth() const
{
	return this->equipmentHealth;
}

Equipment::EquipmentSlot Equipment::getEquipmentSlot() const
{
	return this->equipmentSlot;
}


void Equipment::setEquipmentAttack(int _equipmentAttack)
{
	this->equipmentAttack = _equipmentAttack;
}

void Equipment::setEquipmentDefense(int _equipmentDefense)
{
	this->equipmentDefense = _equipmentDefense;
}

void Equipment::setEquipmentHealth(int _equipmentHealth)
{
	this->equipmentHealth = _equipmentHealth;
}

void Equipment::setEquipmentSlot(EquipmentSlot _equipmentSlot)
{	
	for (int i = 0; i < equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT); i++)
	{
		if (_equipmentSlot == equipmentSlotFromIndex(i))
		{
			this->equipmentSlot = _equipmentSlot;
			return;
		}
	}
	this->equipmentSlot = Equipment::EquipmentSlot::EMPTY;
}