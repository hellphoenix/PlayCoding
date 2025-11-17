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
	return equipped[equipmentSlotToIndex(_slot)];
}

int Player::getMaxAttack() const
{
	if (maxAttack > 0)
		return maxAttack;
	else return 0;
}

int Player::getMaxDefense() const
{
	if (maxDefense > 0)
		return maxDefense;
	else return 0;
}

int Player::getMaxHealth() const
{
	if (maxHealth > 0)
		return maxHealth;
	else return 0;
}

// Used to equip items. Input is an Equipment object.
void Player::equipItem(const Equipment& _equipment)
{ 
	Equipment::EquipmentSlot is = _equipment.getEquipmentSlot();
	if (is == Equipment::EquipmentSlot::EMPTY) return;

	const Equipment& old = getEquippedItem(is);
	if (old.getEquipmentSlot() != Equipment::EquipmentSlot::EMPTY && old.getId() != "")
		inventory.addEquipmentToInventory(old);

	equipped[equipmentSlotToIndex(is)] = _equipment;

	updateMaxStats();
}

// Used to equip items from the player's inventory. Input is item ID.
void Player::equipFromInventory(const std::string& _id)
{
	Equipment found = inventory.findEquipmentById(_id);
	if (found.getId() != _id)
		return; // If the search does not return the item, then we don't equip an item

	Equipment::EquipmentSlot slot = found.getEquipmentSlot();
	if (slot == Equipment::EquipmentSlot::EMPTY) return;

	const Equipment& old = getEquippedItem(slot);
	if (old.getEquipmentSlot() != Equipment::EquipmentSlot::EMPTY && old.getId() != "")
		inventory.addEquipmentToInventory(old);

	equipped[equipmentSlotToIndex(slot)] = found;
	inventory.removeEquipmentFromInventory(_id);
		
	updateMaxStats();
}

// Used to unequip item and store it in the Player's inventory. Input is ItemSlot.
void Player::unequipItem(Equipment::EquipmentSlot _itemSlot)
{
	auto& current = equipped[equipmentSlotToIndex(_itemSlot)];

	if (current.getEquipmentSlot() == Equipment::EquipmentSlot::EMPTY || current.getId() == "") return;

	inventory.addEquipmentToInventory(current);
	current = Equipment{};

	updateMaxStats();
}

// Prints the complete Player character sheet, not including inventory
void Player::printPlayer() const 
{
	cout << "Player Name: " << Player::getName() << ", HP: " << Player::getCurrentHealth() << "/" << Player::getMaxHealth() << ", Attack: " << Player::getMaxAttack() << ", Defense: " << Player::getMaxDefense()  << endl;
	cout << "Player equipment: "<< endl;
	cout << "|                     Id |      Type |    Rarity |       Slot |                  Name | Attack | Defense | Health |" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
	for (const auto& equipment : equipped)
		equipment.printEquipment();

	cout << endl;
}

// Prints Player stats only
void Player::quickPrintPlayer() const 
{
	cout << "Player Name: " << Player::getName() << ", HP: " << Player::getCurrentHealth() << "/" << Player::getMaxHealth() << ", Attack: " << Player::getMaxAttack() << ", Defense: " << Player::getMaxDefense() << endl;
}

void Player::setBaseStats(int _baseHealth, int _currentHealth, int _attack, int _defense) // Set Player base stats. Used for debugging. Input is an integer for each stat.
{
	Player::setBaseHealth(_baseHealth);
	Player::setCurrentHealth(_currentHealth);
	Player::setBaseAttack(_attack);
	Player::setBaseDefense(_defense);
	
	updateMaxStats();
}

// Set Player current health. Used mainly for fighting. Input is integer for change in health. Can be positive for healing, or negative for taking damage.
void Player::changeCurrentHealth(int _healthChanged) 
{
	if (Player::getCurrentHealth() + _healthChanged <= 0) Player::setCurrentHealth(0); // Current health should nopt go below 0
		
	else if (Player::getCurrentHealth() + _healthChanged > Player::maxHealth) Player::setCurrentHealth(Player::maxHealth); // Current health should not go above max health
		
	else Player::setCurrentHealth(Player::getCurrentHealth() + _healthChanged); // Normal change of current health
}

// Updates Player max stats. Used when creating a new player, setting Player base stats, or Equipping and unequipping items.
void Player::updateMaxStats() 
{
	bool fullHealth = false;
	if (Player::getCurrentHealth() >= Player::maxHealth) fullHealth = true; // If the player currently has full health, we want them to keep their health full after updating max stats
	
	// We start by resetting max values to the base values before recalculating
	Player::maxAttack = Player::getBaseAttack();
	Player::maxDefense = Player::getBaseDefense();
	Player::maxHealth = Player::getBaseHealth();

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
	if (Player::getCurrentHealth() > maxHealth || fullHealth) Player::setCurrentHealth(maxHealth);
}