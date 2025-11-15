#pragma once
#include "character.h"
#include "item.h"
#include "inventory.h"
#include <array>

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Character
{
private:
	Inventory inventory;

	std::array<Item, itemSlotToIndex(Item::ItemSlot::COUNT)> equipped{};

	// Stats derived from base stats plus equipment stats
	int maxAttack;
	int maxDefense;
	int maxHealth;
	
public:
	Player(); // default constructor
	Player(const string& _name, int _health, int _attack, int _defense); // fresh player with no equipment
	Player(const string& _name, int _health, int _currentHealth, int _attack, int _defense); // loading saved players

	Inventory& getPlayerInventory() { return Player::inventory; }
	std::array<Item, itemSlotToIndex(Item::ItemSlot::COUNT)>& getPlayerEquipment() { return Player::equipped; }
	const Item& getEquippedItem(Item::ItemSlot _slot) const;

	int getMaxAttack() const;
	int getMaxDefense() const;
	int getMaxHealth() const;

	void equipItem(const Item& _item); // Equips items using Items object.
	void equipItemFromInventory(const string& _id); // Equips items from inventory using equipment id
	void unequipItem(Item::ItemSlot _itemSlot); // Unequips item using item slot

	void setBaseStats(int _baseHealth, int _currentHealth, int _attack, int _defense); // for debugging
	void changeCurrentHealth(int _health); // Adds input health to change current health between 0 and max health

	

	void printPlayer() const; // Player stats and equipment
	void quickPrintPlayer() const; // Player stats only 
	void updateMaxStats(); // Recalculate max stats when equipping items, unequipping items, or creating a new player

	
};

#endif // !PLAYER_H
