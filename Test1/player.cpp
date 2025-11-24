#include "player.h"
#include <iostream>
using std::cout, std::endl;

Player::Player() : Character("Player", 1, 1, 0, 0), maxHealth(1)
{
	updateMaxStats();
}

Player::Player(const std::string& _name, int _baseHealth, int _currentHealth, int _attack, int _defense) : 
	Character(_name, _baseHealth, _currentHealth, _attack, _defense), maxHealth(_baseHealth)
{
	updateMaxStats();
}

const Equipment& Player::getEquippedItem(Equipment::EquipmentSlot _slot) const
{
	return this->equipped[equipmentSlotToIndex(_slot)];
}

int Player::getMaxAttack() const
{
	if (this->maxAttack > this->baseAttack)
		return this->maxAttack;
	else return this->baseAttack;
}

int Player::getMaxDefense() const
{
	if (this->maxDefense > this->baseDefense)
		return this->maxDefense;
	else return this->baseDefense;
}

int Player::getMaxHealth() const
{
	if (this->maxHealth > this->baseHealth)
		return this->maxHealth;
	else return this->baseHealth;
}

// Used to equip items. Input is an Equipment object.
void Player::equipEquipment(const Equipment& _equipment)
{ 
	Equipment::EquipmentSlot is = _equipment.getEquipmentSlot();
	if (is == Equipment::EquipmentSlot::EMPTY) return;

	const Equipment& old = this->getEquippedItem(is);
	if (old.getEquipmentSlot() != Equipment::EquipmentSlot::EMPTY || old.getId() != "" || old.getItemName() != "")
		this->inventory.addEquipmentToInventory(old);

	this->equipped[equipmentSlotToIndex(is)] = _equipment;

	updateMaxStats();
}

// Used to equip items from the player's inventory. Input is item ID.
void Player::equipFromInventory(const std::string& _id)
{
	Equipment found = this->inventory.findEquipmentById(_id);
	if (found.getId() != _id)
		return; // If the search does not return the item, then we don't equip an item

	this->equipEquipment(found); // Equip the found equipment
	this->inventory.removeEquipmentFromInventory(_id); // Remove found equipment from inventory
}

// Used to unequip item and store it in the Player's inventory. Input is ItemSlot.
void Player::unequipEquipment(Equipment::EquipmentSlot _itemSlot)
{
	auto& current = this->equipped[equipmentSlotToIndex(_itemSlot)];
	if (current.getEquipmentSlot() == Equipment::EquipmentSlot::EMPTY || current.getId() == "") return;

	this->inventory.addEquipmentToInventory(current);
	current = Equipment{};

	updateMaxStats();
}

void Player::setBaseStats(int _baseHealth, int _currentHealth, int _attack, int _defense) // Set Player base stats. Used for debugging. Input is an integer for each stat.
{
	this->setBaseHealth(_baseHealth);
	this->setCurrentHealth(_currentHealth);
	this->setBaseAttack(_attack);
	this->setBaseDefense(_defense);
	
	updateMaxStats();
}

// Set Player current health. Used mainly for fighting. Input is integer for change in health. Can be positive for healing, or negative for taking damage.
void Player::changeCurrentHealth(int _healthChanged) 
{
	if (this->currentHealth + _healthChanged <= 0) this->setCurrentHealth(0); // Current health should not go below 0
		
	else if (this->currentHealth + _healthChanged > this->maxHealth) this->setCurrentHealth(this->maxHealth); // Current health should not go above max health
		
	else this->setCurrentHealth(this->currentHealth + _healthChanged); // Normal change of current health
}

// Updates Player max stats. Used when creating a new player, setting Player base stats, or Equipping and unequipping items.
void Player::updateMaxStats() 
{
	bool fullHealth = false;
	if (this->currentHealth >= this->maxHealth) fullHealth = true; // If the player currently has full health, we want them to keep their health full after updating max stats
	
	// We start by resetting max values to the base values before recalculating
	this->maxAttack = this->baseAttack;
	this->maxDefense = this->baseDefense;
	this->maxHealth = this->baseHealth;

	// For each piece of equipment, we add their stats to the player max stats
	for (const auto& equipment : equipped)
	{
		if (equipment.getEquipmentSlot() == Equipment::EquipmentSlot::EMPTY)
			continue;

		maxAttack += equipment.getEquipmentAttack();
		maxDefense += equipment.getEquipmentDefense();
		maxHealth += equipment.getEquipmentHealth();
	}

	// If the player's health was full before this recalculation, set their current health to their new max health. This can be exploited by the player to heal themselves by unequipping and re-equipping items. Bug or feature?
	if (this->currentHealth > maxHealth || fullHealth) this->setCurrentHealth(maxHealth);
}