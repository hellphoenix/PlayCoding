#include "player.h"
#include <iostream>
using std::cout, std::endl;

Player::Player() : Character("Player", 1, 0, 0), currentHealth(1), helmet(), chestPiece(), pants(), boots(), shield(), sword()
{
	updateMaxStats();
}

Player::Player(const string& _name, int _baseHealth, int _currentHealth, int _attack, int _defense) : Character(_name, _baseHealth, _attack, _defense), currentHealth(_currentHealth), helmet(), chestPiece(), pants(), boots(), shield(), sword()

{
	updateMaxStats();
}

Player::Player(const string& _name, int _baseHealth, int _currentHealth, int _attack, int _defense, const Item& _helmet, const Item& _chestPiece, const Item& _pants, const Item& _boots, const Item& _shield, const Item& _sword) : 
	Character(_name, _baseHealth, _attack, _defense), currentHealth(_currentHealth), helmet(_helmet), chestPiece(_chestPiece), pants(_pants), boots(_boots), shield(_shield), sword(_sword)
{
	updateMaxStats();
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

int Player::getMaxAttack() const
{
	if (maxAttack > 0)
		return Player::maxAttack;
	else return 0;
}

int Player::getMaxDefense() const
{
	if (maxDefense > 0)
		return Player::maxDefense;
	else return 0;
}

int Player::getMaxHealth() const
{
	if (maxHealth > 0)
		return Player::maxHealth;
	else return 0;
}

int Player::getCurrentHealth() const
{
	if (currentHealth > 0)
		return Player::currentHealth;
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
	updateMaxStats();
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
	updateMaxStats();
}


void Player::printPlayer() const
{
	cout << "Player Name: " << Player::getName() << ", HP: " << Player::getCurrentHealth() << "/" << Player::getMaxHealth() << ", Attack: " << Player::getMaxAttack() << ", Defense: " << Player::getMaxDefense()  << endl;
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
	cout << "Player Name: " << Player::getName() << ", HP: " << Player::getCurrentHealth() << "/" << Player::getMaxHealth() << ", Attack: " << Player::getMaxAttack() << ", Defense: " << Player::getMaxDefense() << endl;
}

void Player::setBaseStats(int _baseHealth, int _currentHealth, int _attack, int _defense)
{
	Character::setBaseHealth(_baseHealth);
	Character::setBaseAttack(_attack);
	Character::setBaseDefense(_defense);
	updateMaxStats();
	Player::currentHealth = _currentHealth;
}

void Player::changeCurrentHealth(int _healthChanged)
{
	if (Player::currentHealth + _healthChanged <= 0) //Sending negative values can lower health to zero or less (also called dying)
		Player::currentHealth = 0;
	else if (Player::currentHealth + _healthChanged > Player::maxHealth) //Sending positive values can cause the current health to go above max health (also called overhealing)
		Player::currentHealth = Player::maxHealth;
	else Player::currentHealth += _healthChanged; //Normal gain or loss of current health
}

void Player::updateMaxStats()
{
	Player::maxAttack = Player::getBaseAttack();
	Player::maxDefense = Player::getBaseDefense();
	Player::maxHealth = Player::getBaseHealth();

	const Item* equipment[] = { &helmet, &chestPiece, &pants, &boots, &shield, &sword };

	for (auto& item : equipment)
	{
		Player::maxAttack += item->getItemAttack();
		Player::maxDefense += item->getItemDefense();
		Player::maxHealth += item->getItemHealth();
	}
	if (Player::maxHealth < Player::currentHealth) Player::currentHealth = Player::maxHealth;
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
	updateMaxStats();
}