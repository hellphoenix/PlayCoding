#include "item.h"
#include <iomanip>
#include <iostream>


Item::Item() : id(), itemName(), itemAttack(0), itemDefense(0), itemHealth(0), itemSlot(ItemSlot::EMPTY), itemType(ItemType::UNKNOWN), itemRarity(ItemRarity::NONEXISTENT)
{

}

Item::Item( const std::string& _id, const std::string& _itemName, int _itemAttack, int _itemDefense, int _itemHealth, ItemSlot _itemSlot, ItemType _itemType, ItemRarity _itemRarity) :
	id(_id), itemName(_itemName), itemAttack(_itemAttack), itemDefense(_itemDefense), itemHealth(_itemHealth), itemSlot(_itemSlot), itemType(_itemType), itemRarity(_itemRarity)
{

}

// Maps ItemSlot enums to strings.
const std::map<Item::ItemSlot, std::string> Item::itemSlotToString =
{
	{ItemSlot::EMPTY, "Empty"}, {ItemSlot::HELMET, "Helmet"}, {ItemSlot::CHESTPIECE, "Chestpiece"}, {ItemSlot::PANTS, "Pants"}, {ItemSlot::BOOTS, "Boots"}, {ItemSlot::SHIELD, "Shield"}, {ItemSlot::WEAPON, "Weapon"}
};

// Maps ItemType enums to strings
const std::map<Item::ItemType, std::string> Item::itemTypeToString =
{
	{ItemType::UNKNOWN, "Unknown"}, {ItemType::EQUIPMENT, "Equipment"}, {ItemType::CONSUMABLE, "Consumable"}, {ItemType::QUEST_ITEM, "Quest Item"}
};

// Maps ItemRarity enums to strings
const std::map<Item::ItemRarity, std::string> Item::itemRarityToString =
{
	{ItemRarity::NONEXISTENT, "Non-Existent"}, {ItemRarity::POOR, "Poor"}, {ItemRarity::COMMON, "Common"}, {ItemRarity::UNCOMMON, "Uncommon"}, {ItemRarity::RARE, "Rare"}, {ItemRarity::EPIC, "Epic"}, {ItemRarity::LEGENDARY, "Legendary"}
};

std::string Item::getId() const
{
	return id;
}

std::string Item::getItemName() const
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

void Item::setId(const std::string& _id)
{
	id = _id;
}

void Item::setItemName(const std::string& _itemName)
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

// Prints the ID, ItemType, ItemRarity, ItemSLot, item name, item attack, item defense, and item health, in that order
void Item::printItem() const
{
	if (itemSlot == ItemSlot::EMPTY)
		return;

	std::cout << "| "  << std::setw(22) << id << " | " << std::setw(9) << itemTypeToString.at(itemType) << " | " << std::setw(9) << itemRarityToString.at(itemRarity) << " | " << std::setw(10) << itemSlotToString.at(itemSlot)
		<< " | " << std::setw(21) << itemName << " | " << std::setw(6) << itemAttack << " | " << std::setw(7) << itemDefense << " | " << std::setw(6) << itemHealth << " |" << std::endl;
}