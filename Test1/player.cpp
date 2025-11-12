#include "player.h"
#include <iostream>
using std::cout, std::endl;

Player::Player() : Character("Player", 1, 0, 0), totalHealth(1), totalAttack(0), totalDefense(0),  helmet(), chestPiece(), pants(), boots(), shield(), sword()
{
	updateTotalStats();
}

Player::Player(const string& _name, int _health, int _attack, int _defense) : Character(_name, _health, _attack, _defense), totalHealth(_health), totalAttack(_attack), totalDefense(_defense),  helmet(), chestPiece(), pants(), boots(), shield(), sword()

{
	updateTotalStats();
}

Player::Player(const string& _name, int _health, int _attack, int _defense, const Item& _helmet, const Item& _chestPiece, const Item& _pants, const Item& _boots, const Item& _shield, const Item& _sword) : Character(_name, _health, _attack, _defense),
helmet(_helmet), chestPiece(_chestPiece), pants(_pants), boots(_boots), shield(_shield), sword(_sword)
{
	updateTotalStats();
}

//Getters for each item
const Item& Player::getHelmet() const
{
	return Player::helmet;
}

const Item& Player::getChestPiece() const
{
	return Player::chestPiece;
}

const Item& Player::getPants() const
{
	return Player::pants;
}

const Item& Player::getBoots() const
{
	return Player::boots;
}

const Item& Player::getShield() const
{
	return Player::shield;
}

const Item& Player::getSword() const
{
	return Player::sword;
}

int Player::getTotalAttack() const
{
	return Player::totalAttack;
}

int Player::getTotalDefense() const
{
	return Player::totalDefense;
}

int Player::getTotalHealth() const
{
	return Player::totalHealth;
}

//Setters for each item
void Player::setHelmet(const Item& _helmet)
{
	inventory.addToInventory(std::move(helmet));
	Player::helmet = _helmet;
	updateTotalStats();
}

void Player::setChestPiece(const Item& _chestPiece)
{
	inventory.addToInventory(std::move(chestPiece));
	Player::chestPiece = _chestPiece;
	updateTotalStats();
}

void Player::setPants(const Item& _pants)
{
	inventory.addToInventory(std::move(pants));
	Player::pants = _pants;
	updateTotalStats();
}

void Player::setBoots(const Item& _boots)
{
	inventory.addToInventory(std::move(boots));
	Player::boots = _boots;
	updateTotalStats();
}

void Player::setShield(const Item& _shield)
{
	inventory.addToInventory(std::move(shield));
	Player::shield = _shield;
	updateTotalStats();
}

void Player::setSword(const Item& _sword)
{
	inventory.addToInventory(std::move(sword));
	Player::sword = _sword;
	updateTotalStats();
}


void Player::printPlayer() const
{
	cout << "Player Name: " << Player::getName() << ", Health: " << Player::getTotalHealth() << ", Attack: " << Player::getTotalAttack() << ", Defense: " << Player::getTotalDefense()  << endl;
	cout << "Player equipment: "<< endl;
	getHelmet().printItem();
	getChestPiece().printItem();
	getPants().printItem();
	getBoots().printItem();
	getShield().printItem();
	getSword().printItem();
	cout << endl;
}

void Player::setBaseStats(int _health, int _attack, int _defense)
{
	Character::setBaseHealth(_health);
	Character::setBaseAttack(_attack);
	Character::setBaseDefense(_defense);
	updateTotalStats();
}

void Player::updateTotalStats()
{
	Player::totalAttack = Player::getBaseAttack();
	Player::totalDefense = Player::getBaseDefense();
	Player::totalHealth = Player::getBaseHealth();

	const Item* equipment[] = { &helmet, &chestPiece, &pants, &boots, &shield, &sword };

	for (auto& item : equipment)
	{
		totalAttack += item->getItemAttack();
		totalDefense += item->getItemDefense();
		totalHealth += item->getItemHealth();
	}
}


//Equipping Items
void Player::equipHelmetFromInventory(const std::string& _itemName)
{
	// Ask inventory for a helmet with this name
	Item newItem = inventory.equipFromInventory(_itemName, Item::ItemSlot::HELMET);

	// If not found, equipFromInventory returns an EMPTY item
	if (newItem.getItemSlot() != Item::ItemSlot::HELMET)
		return;

	// Put current helmet back into inventory if it is not empty
	inventory.addToInventory(std::move(helmet));

	// Equip the new one
	helmet = std::move(newItem);
	updateTotalStats();
}

void Player::equipChestFromInventory(const std::string& _itemName)
{
	Item newItem = inventory.equipFromInventory(_itemName, Item::ItemSlot::CHESTPIECE);
	if (newItem.getItemSlot() != Item::ItemSlot::CHESTPIECE)
		return;

	inventory.addToInventory(std::move(chestPiece));
	chestPiece = std::move(newItem);
	updateTotalStats();
}

void Player::equipPantsFromInventory(const std::string& _itemName)
{
	Item newItem = inventory.equipFromInventory(_itemName, Item::ItemSlot::PANTS);
	if (newItem.getItemSlot() != Item::ItemSlot::PANTS)
		return;

	inventory.addToInventory(std::move(pants));
	pants = std::move(newItem);
	updateTotalStats();
}

void Player::equipBootsFromInventory(const std::string& _itemName)
{
	Item newItem = inventory.equipFromInventory(_itemName, Item::ItemSlot::BOOTS);
	if (newItem.getItemSlot() != Item::ItemSlot::BOOTS)
		return;

	inventory.addToInventory(std::move(boots));
	boots = std::move(newItem);
	updateTotalStats();
}

void Player::equipShieldFromInventory(const std::string& _itemName)
{
	Item newItem = inventory.equipFromInventory(_itemName, Item::ItemSlot::SHIELD);
	if (newItem.getItemSlot() != Item::ItemSlot::SHIELD)
		return;

	inventory.addToInventory(std::move(shield));
	shield = std::move(newItem);
	updateTotalStats();
}

void Player::equipSwordFromInventory(const std::string& _itemName)
{
	Item newItem = inventory.equipFromInventory(_itemName, Item::ItemSlot::SWORD);
	if (newItem.getItemSlot() != Item::ItemSlot::SWORD)
		return;

	inventory.addToInventory(std::move(sword));
	sword = std::move(newItem);
	updateTotalStats();
}