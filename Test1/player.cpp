#include "player.h"

// Used to equip gear. Input is an Equipment object.
void Player::equipEquipment(const Equipment& _equipment)
{
	EquipmentSlot is = _equipment.getEquipmentSlot();
	if (is == EquipmentSlot::EMPTY) return;

	const Equipment& old = this->getEquippedItem(is);
	if (old.getEquipmentSlot() != EquipmentSlot::EMPTY || old.getId() != "" || old.getItemName() != "")
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
void Player::unequipEquipment(EquipmentSlot _slot)
{
	auto& current = this->equipped[equipmentSlotToIndex(_slot)];
	if (current.getEquipmentSlot() == EquipmentSlot::EMPTY || current.getId() == "") return;

	this->inventory.addEquipmentToInventory(current);
	current = Equipment{};

	updateMaxStats();
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
		if (equipment.getEquipmentSlot() == EquipmentSlot::EMPTY)
			continue;

		maxAttack += equipment.getEquipmentAttack();
		maxDefense += equipment.getEquipmentDefense();
		maxHealth += equipment.getEquipmentHealth();
	}

	// If the player's health was full before this recalculation, set their current health to their new max health. This can be exploited by the player to heal themselves by unequipping and re-equipping items. Bug or feature?
	if (this->currentHealth > maxHealth || fullHealth) this->setCurrentHealth(maxHealth);
}