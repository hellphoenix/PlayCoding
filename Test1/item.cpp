#include "item.h"
#include <iomanip>
#include <iostream>


Item::Item() : id(), itemName(), itemType(ItemType::UNKNOWN), itemRarity(ItemRarity::NONEXISTENT)
{

}

Item::Item(const std::string& _id, const std::string& _itemName, ItemType _itemType, ItemRarity _itemRarity) :
	id(_id), itemName(_itemName), itemType(_itemType), itemRarity(_itemRarity)
{

}

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

void Item::setItemType(ItemType _itemType)
{
	itemType = _itemType;
}

void Item::setItemRarity(ItemRarity _itemRarity)
{
	itemRarity = _itemRarity;
}

// Prints the ID, ItemType, ItemRarity, item name, in that order
void Item::printItem() const
{

	std::cout << "| "  << std::setw(22) << id << " | " << std::setw(9) << itemTypeToString.at(itemType) << " | " << std::setw(9) << 
		itemRarityToString.at(itemRarity) << " | " << std::setw(10) << " | " << std::setw(21) << itemName << " |" << std::endl;
}