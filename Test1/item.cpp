#include "item.h"
#include <iostream>
#include <iomanip>
using std::cout, std::endl;

Item::Item() : id(), itemName(), itemAttack(0), itemDefense(0), itemHealth(0), itemSlot(ItemSlot::EMPTY), itemType(ItemType::UNKNOWN), itemRarity(ItemRarity::NONEXISTENT)
{

}

Item::Item( const string& _id, const string& _itemName, int _itemAttack, int _itemDefense, int _itemHealth, ItemSlot _itemSlot, ItemType _itemType, ItemRarity _itemRarity) : 
	id(_id), itemName(_itemName), itemAttack(_itemAttack), itemDefense(_itemDefense), itemHealth(_itemHealth), itemSlot(_itemSlot), itemType(_itemType), itemRarity(_itemRarity)
{

}

// change me when adding item slots
const map<Item::ItemSlot, string> Item::itemSlotToString =
{
	{ItemSlot::EMPTY, "Empty"}, {ItemSlot::HELMET, "Helmet"}, {ItemSlot::CHESTPIECE, "Chestpiece"}, {ItemSlot::PANTS, "Pants"}, {ItemSlot::BOOTS, "Boots"}, {ItemSlot::SHIELD, "Shield"}, {ItemSlot::WEAPON, "Weapon"}
};

// change me when adding item types
const map<Item::ItemType, string> Item::itemTypeToString =
{
	{ItemType::UNKNOWN, "Unknown"}, {ItemType::EQUIPMENT, "Equipment"}, {ItemType::CONSUMABLE, "Consumable"}, {ItemType::QUEST_ITEM, "Quest Item"}
};

// change me when adding item rarities
const map<Item::ItemRarity, string> Item::itemRarityToString =
{
	{ItemRarity::NONEXISTENT, "Non-Existent"}, {ItemRarity::POOR, "Poor"}, {ItemRarity::COMMON, "Common"}, {ItemRarity::UNCOMMON, "Uncommon"}, {ItemRarity::RARE, "Rare"}, {ItemRarity::EPIC, "Epic"}, {ItemRarity::LEGENDARY, "Legendary"}
};

string Item::getId() const
{
	return id;
}

string Item::getItemName() const
{
	return itemName;
}

int Item::getItemAttack() const
{
	return itemAttack;
}

int Item::getItemDefense() const
{
	return itemDefense;
}

int Item::getItemHealth() const
{
	return itemHealth;
}

Item::ItemSlot Item::getItemSlot() const
{
	return itemSlot;
}

Item::ItemType Item::getItemType() const
{
	return itemType;
}

Item::ItemRarity Item::getItemRarity() const
{
	return itemRarity;
}

void Item::setId(const string& _id)
{
	id = _id;
}

void Item::setItemName(const string& _itemName)
{
	itemName = _itemName;
}

void Item::setItemAttack(int _itemAttack)
{
	itemAttack = _itemAttack;
}

void Item::setItemDefense(int _itemDefense)
{
	itemDefense = _itemDefense;
}

void Item::setItemHealth(int _itemHealth)
{
	itemHealth = _itemHealth;
}

void Item::setItemSlot(ItemSlot _itemSlot)
{
	itemSlot = _itemSlot;
}

void Item::setItemType(ItemType _itemType)
{
	itemType = _itemType;
}

void Item::setItemRarity(ItemRarity _itemRarity)
{
	itemRarity = _itemRarity;
}

void Item::printItem() const
{
	if (itemSlot == ItemSlot::EMPTY)
		return;

	cout << "| "  << std::setw(20) << id << " | " << std::setw(9) << itemTypeToString.at(itemType) << " | " << std::setw(9) << itemRarityToString.at(itemRarity) << " | " << std::setw(10) << itemSlotToString.at(itemSlot) 
		<< " | " << std::setw(21) << itemName << " | " << std::setw(6) << itemAttack << " | " << std::setw(7) << itemDefense << " | " << std::setw(6) << itemHealth << " |" << endl;
}