#include "player.h"
#include <iostream>
using std::cout, std::endl;

Player::Player() : Character("Player", 1, 0, 0), maxHealth(1)
{
	updateMaxStats();
}

Player::Player(const string& _name, int _health, int _attack, int _defense) : Character(_name, _health, _attack, _defense), maxHealth(_health)

{
	updateMaxStats();
}

Player::Player(const string& _name, int _health, int _currenHealth, int _attack, int _defense) : Character(_name, _health, _attack, _defense), maxHealth(_health)
{
	Player::setCurrentHealth(_currenHealth);
	updateMaxStats();
}

const Item& Player::getEquippedItem(Item::ItemSlot _slot) const
{
	return equipped[itemSlotToIndex(_slot)];
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

void Player::equipItem(const Item& _item) // Used to equip from save files
{ 
	if (_item.getItemSlot() == Item::ItemSlot::EMPTY) return;

	inventory.addToInventory(getEquippedItem(_item.getItemSlot()));
	equipped[itemSlotToIndex(_item.getItemSlot())] = _item;

	updateMaxStats();
}

void Player::equipItemFromInventory(const string& _id)
{
	if (inventory.searchInventoryById(_id).getId() != _id) return; // If the search does not return the item, then we don't equip an item

	inventory.addToInventory(getEquippedItem(inventory.searchInventoryById(_id).getItemSlot()));
	equipped[itemSlotToIndex(inventory.searchInventoryById(_id).getItemSlot())] = inventory.searchInventoryById(_id);

	inventory.removeFromInventory(_id);
	updateMaxStats();
}

void Player::unequipItem(Item::ItemSlot _itemSlot) //used when you do know the item slot
{
	auto& current = equipped[itemSlotToIndex(_itemSlot)];

	if (current.getItemSlot() == Item::ItemSlot::EMPTY) return;

	inventory.addToInventory(current);
	current = Item{};

	updateMaxStats();
}


void Player::printPlayer() const
{
	cout << "Player Name: " << Player::getName() << ", HP: " << Player::getCurrentHealth() << "/" << Player::getMaxHealth() << ", Attack: " << Player::getMaxAttack() << ", Defense: " << Player::getMaxDefense()  << endl;
	cout << "Player equipment: "<< endl;
	cout << "|                   Id |      Type |    Rarity |       Slot |                  Name | Attack | Defense | Health |" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	for (const auto& item : equipped)
		item.printItem();

	cout << endl;
}

void Player::quickPrintPlayer() const
{
	cout << "Player Name: " << Player::getName() << ", HP: " << Player::getCurrentHealth() << "/" << Player::getMaxHealth() << ", Attack: " << Player::getMaxAttack() << ", Defense: " << Player::getMaxDefense() << endl;
}

void Player::setBaseStats(int _baseHealth, int _currentHealth, int _attack, int _defense)
{
	Player::setBaseHealth(_baseHealth);
	Player::setCurrentHealth(_currentHealth);
	Player::setBaseAttack(_attack);
	Player::setBaseDefense(_defense);
	
	updateMaxStats();
}

void Player::changeCurrentHealth(int _healthChanged)
{
	if (Player::getCurrentHealth() + _healthChanged <= 0) Player::setCurrentHealth(0); // Current health should nopt go below 0
		
	else if (Player::getCurrentHealth() + _healthChanged > Player::maxHealth) Player::setCurrentHealth(Player::maxHealth); // Current health should not go above max health
		
	else Player::setCurrentHealth(Player::getCurrentHealth() + _healthChanged); // Normal change of current health
}

void Player::updateMaxStats()
{
	bool fullHealth = false;
	if (Player::getCurrentHealth() >= Player::maxHealth) fullHealth = true; // If the player currently has full health, we want them to keep their health full after updating max stats
	
	// We start by resetting max values to the base values before recalculating
	Player::maxAttack = Player::getBaseAttack();
	Player::maxDefense = Player::getBaseDefense();
	Player::maxHealth = Player::getBaseHealth();

	// For each item, we add their stats to the player max stats
	for (const auto& item : equipped)
	{
		if (item.getItemSlot() == Item::ItemSlot::EMPTY)
			continue;

		maxAttack += item.getItemAttack();
		maxDefense += item.getItemDefense();
		maxHealth += item.getItemHealth();
	}

	// If the player's health was full before this recalculation, set their current health to their new max health. This can be exploited by the player to heal themselves by unequipping and re-equipping items. Bug or feature?
	if (Player::getCurrentHealth() > maxHealth || fullHealth) Player::setCurrentHealth(maxHealth);
}