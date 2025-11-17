#pragma once
#include "character.h"
#include "inventory.h"
#include "equipment.h"
#include <array>
#include <string>

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Character
{
private:
	Inventory inventory;

	std::array<Equipment, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)> equipped{};

	// Stats derived from base stats plus equipment stats
	int maxAttack;
	int maxDefense;
	int maxHealth;
	
public:
	Player(); // default player constructor
	Player(const std::string& _name, int _baseHealth, int _currentHealth, int _attack, int _defense); // player constructor with values for name and stats

	Inventory& getPlayerInventory() { return Player::inventory; } // Returns an inventory object attached to the Player
	std::array<Equipment, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)>& getPlayerEquipment() { return Player::equipped; } // Returns an array of equipped items attached to the Player
	const Equipment& getEquippedItem(Equipment::EquipmentSlot _slot) const;

	int getMaxAttack() const;
	int getMaxDefense() const;
	int getMaxHealth() const;

	void equipItem(const Equipment& _equipment); // Equips items using Items object.
	void equipFromInventory(const std::string& _id); // Equips items from inventory using equipment id
	void unequipItem(Equipment::EquipmentSlot _equipmentSlot); // Unequips item using item slot

	void setBaseStats(int _baseHealth, int _currentHealth, int _attack, int _defense); // for debugging
	void changeCurrentHealth(int _health); // Adds input health to change current health between 0 and max health

	

	void printPlayer() const; // Prints player stats and equipment
	void quickPrintPlayer() const; // Prints player stats only 
	void updateMaxStats(); // Recalculate max stats when equipping items, unequipping items, or creating a new player

	
};

#endif // !PLAYER_H
