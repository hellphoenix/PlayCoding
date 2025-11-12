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
	if (totalAttack > 0)
		return Player::totalAttack;
	else return 0;
}

int Player::getTotalDefense() const
{
	if (totalDefense > 0)
		return Player::totalDefense;
	else return 0;
}

int Player::getTotalHealth() const
{
	if (totalHealth > 0)
		return Player::totalHealth;
	else return 0;
}

void Player::setItem(const Item& _item) //used when you don't know the item slot
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
	updateTotalStats();
}
void Player::setItem(const Item& _item, Item::ItemSlot _itemSlot) //used when you do know the item slot
{
	switch (_itemSlot)
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
	updateTotalStats();
}


void Player::printPlayer() const
{
	cout << "Player Name: " << Player::getName() << ", Health: " << Player::getTotalHealth() << ", Attack: " << Player::getTotalAttack() << ", Defense: " << Player::getTotalDefense()  << endl;
	cout << "Player equipment: "<< endl;
	cout << "|                   Id |      Type |    Rarity |       Slot |                  Name | Attack | Defense | Health |" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	getHelmet().printItem();
	getChestPiece().printItem();
	getPants().printItem();
	getBoots().printItem();
	getShield().printItem();
	getSword().printItem();
	cout << endl;
}

void Player::quickPrintPlayer() const
{
	cout << "Player Name: " << Player::getName() << ", Health: " << Player::getTotalHealth() << ", Attack: " << Player::getTotalAttack() << ", Defense: " << Player::getTotalDefense() << endl;
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

void Player::equipFromInventory(const Item& _item)
{
	if (_item.getItemSlot() == Item::ItemSlot::HELMET)
	{
		inventory.addToInventory(std::move(helmet));
		helmet = _item;
	}
	else if (_item.getItemSlot() == Item::ItemSlot::CHESTPIECE)
	{
		inventory.addToInventory(std::move(chestPiece));
		chestPiece = _item;
	}
	else if (_item.getItemSlot() == Item::ItemSlot::PANTS)
	{
		inventory.addToInventory(std::move(pants));
		pants = _item;
	}
	else if (_item.getItemSlot() == Item::ItemSlot::BOOTS)
	{
		inventory.addToInventory(std::move(boots));
		boots = _item;
	}
	else if (_item.getItemSlot() == Item::ItemSlot::SHIELD)
	{
		inventory.addToInventory(std::move(shield));
		shield = _item;
	}
	else if (_item.getItemSlot() == Item::ItemSlot::SWORD)
	{
		inventory.addToInventory(std::move(sword));
		sword = _item;
	}
	else
	{
		cout << "No item of that type is in your inventory." << endl;
		return;
	}
	inventory.removeFromInventory(_item.getId());
	updateTotalStats();
}