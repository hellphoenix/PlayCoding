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

void Player::setItem(const Item& _item, const string& _itemSlot)
{
	if (_item.getItemSlot() != Item::ItemSlot::EMPTY)
	{
		switch (_item.getItemSlot())
		{
		case Item::ItemSlot::HELMET:
		{
			inventory.addToInventory(std::move(helmet));
			Player::helmet = _item;
			break;
		}
		case Item::ItemSlot::CHESTPIECE:
		{
			inventory.addToInventory(std::move(chestPiece));
			Player::chestPiece = _item;
			break;
		}
		case Item::ItemSlot::PANTS:
		{
			inventory.addToInventory(std::move(pants));
			Player::pants = _item;
			break;
		}
		case Item::ItemSlot::BOOTS:
		{
			inventory.addToInventory(std::move(boots));
			Player::boots = _item;
			break;
		}
		case Item::ItemSlot::SHIELD:
		{
			inventory.addToInventory(std::move(shield));
			Player::shield = _item;
			break;
		}
		case Item::ItemSlot::SWORD:
		{
			inventory.addToInventory(std::move(sword));
			Player::sword = _item;
			break;
		}
		default:
			return;
		}
	}
	else if (_itemSlot == "helmet")
	{
		inventory.addToInventory(std::move(helmet));
		Player::helmet = _item;
	}
	else if (_itemSlot == "chest" || _itemSlot == "chestpiece")
	{
		inventory.addToInventory(std::move(chestPiece));
		Player::chestPiece = _item;
	}
	else if (_itemSlot == "pants")
	{
		inventory.addToInventory(std::move(pants));
		Player::pants = _item;
	}
	else if (_itemSlot == "boots")
	{
		inventory.addToInventory(std::move(boots));
		Player::boots = _item;
	}
	else if (_itemSlot == "shield")
	{
		inventory.addToInventory(std::move(shield));
		Player::shield = _item;
	}
	else if (_itemSlot == "sword")
	{
		inventory.addToInventory(std::move(sword));
		Player::sword = _item;
	}
	else return;

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

void Player::equipEquipmentFromInventory(const std::string& _itemName)
{
	Item newItem = inventory.equipFromInventory(_itemName);
	if (newItem.getItemSlot() == Item::ItemSlot::HELMET)
	{
		inventory.addToInventory(std::move(helmet));
		helmet = std::move(newItem);
	}
	else if (newItem.getItemSlot() == Item::ItemSlot::CHESTPIECE)
	{
		inventory.addToInventory(std::move(chestPiece));
		chestPiece = std::move(newItem);
	}
	else if (newItem.getItemSlot() == Item::ItemSlot::PANTS)
	{
		inventory.addToInventory(std::move(pants));
		pants = std::move(newItem);
	}
	else if (newItem.getItemSlot() == Item::ItemSlot::BOOTS)
	{
		inventory.addToInventory(std::move(boots));
		boots = std::move(newItem);
	}
	else if (newItem.getItemSlot() == Item::ItemSlot::SHIELD)
	{
		inventory.addToInventory(std::move(shield));
		shield = std::move(newItem);
	}
	else if (newItem.getItemSlot() == Item::ItemSlot::SWORD)
	{
		inventory.addToInventory(std::move(sword));
		sword = std::move(newItem);
	}
	else
	{
		cout << "No item of that name is in your inventory." << endl;
		return;
	}
	updateTotalStats();
}