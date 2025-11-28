#pragma once
#include "character.h"
#include "equipment.h"
#include "inventory.h"
#include <array>
#include <string>

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Character
{
private:
	Inventory inventory;
	typedef std::array<Equipment, equipmentSlotToIndex(EquipmentSlot::COUNT)> equippedArray;
	equippedArray equipped{};

	// Stats derived from base stats plus equipment stats
	int maxAttack;
	int maxDefense;
	int maxHealth;

public:
	//Default Player constructor
	Player() : Character("Player", 1, 1, 0, 0), maxHealth(1)
	{
		updateMaxStats();
	}
	// Initialized Player constructor
	Player(const std::string& _name, int _baseHealth, int _currentHealth, int _attack, int _defense) :
		Character(_name, _baseHealth, _currentHealth, _attack, _defense), maxHealth(_baseHealth)
	{
		updateMaxStats();
	}
	// Returns an inventory object attached to the Player
	Inventory& getPlayerInventory() { return Player::inventory; }
	// Returns an array of equipped items attached to the Player
	const equippedArray& getPlayerEquipment() { return Player::equipped; }
	// Returns the equipment in an equipment slot. Input is an equipment slot.
	const Equipment& getEquippedItem(EquipmentSlot _slot) const { return this->equipped[equipmentSlotToIndex(_slot)]; }
	// Returns the greater of Max attack and Base attack
	int getMaxAttack() const
	{
		if (this->maxAttack > this->baseAttack)
			return this->maxAttack;
		else return this->baseAttack;
	}
	// Returns the greater of Max defense and Base defense
	int getMaxDefense() const
	{
		if (this->maxDefense > this->baseDefense)
			return this->maxDefense;
		else return this->baseDefense;
	}
	// Returns the greater of Max health and Base health
	int getMaxHealth() const
	{
		if (this->maxHealth > this->baseHealth)
			return this->maxHealth;
		else return this->baseHealth;
	}

	void equipEquipment(const Equipment&);
	void equipFromInventory(const std::string&);
	void unequipEquipment(EquipmentSlot);

	// Sets base stats for Player. Used for debugging.
	void setBaseStats(int _baseHealth, int _currentHealth, int _attack, int _defense)
	{
		this->setBaseHealth(_baseHealth);
		this->setCurrentHealth(_currentHealth);
		this->setBaseAttack(_attack);
		this->setBaseDefense(_defense);

		updateMaxStats();
	}
	// Set Player current health. Used mainly for fighting. Input is integer for change in health. Can be positive for healing, or negative for taking damage.
	void changeCurrentHealth(int _healthChanged)
	{
		if (this->currentHealth + _healthChanged <= 0) this->setCurrentHealth(0); // Current health should not go below 0
		else if (this->currentHealth + _healthChanged > this->maxHealth) this->setCurrentHealth(this->maxHealth); // Current health should not go above max health
		else this->setCurrentHealth(this->currentHealth + _healthChanged); // Normal change of current health
	}
	void updateMaxStats();
};

#endif // !PLAYER_H
