#include "item.h"
#include <iostream>
using std::cout, std::endl;

Item::Item() : itemName(), itemAttack(0), itemDefense(0), itemHealth(0), itemSlot(ItemSlot::EMPTY), itemType(ItemType::UNKNOWN), itemRarity(ItemRarity::NONEXISTENT)
{

}

Item::Item(string _itemName, int _itemAttack, int _itemDefense, int _itemHealth, ItemSlot _itemSlot, ItemType _itemType, ItemRarity _itemRarity) : 
	itemName(_itemName), itemAttack(_itemAttack), itemDefense(_itemDefense), itemHealth(_itemHealth), itemSlot(_itemSlot), itemType(_itemType), itemRarity(_itemRarity)
{

}

const map<Item::ItemSlot, string> Item::itemSlotToString = 
{ 
	{ItemSlot::EMPTY, "Empty"}, {ItemSlot::HELMET, "Helmet"}, {ItemSlot::CHESTPIECE, "Chestpiece"}, {ItemSlot::PANTS, "Pants"}, {ItemSlot::BOOTS, "Boots"}, {ItemSlot::SHIELD, "Shield"}, {ItemSlot::SWORD, "Sword"} 
};

const map<Item::ItemType, string> Item::itemTypeToString =
{
	{ItemType::UNKNOWN, "Unknown"}, {ItemType::EQUIPMENT, "Equipment"}, {ItemType::CONSUMABLE, "Consumable"}, {ItemType::QUEST_ITEM, "Quest Item"}
};

const map<Item::ItemRarity, string> Item::itemRarityToString =
{
	{ItemRarity::NONEXISTENT, "Non-Existent"}, {ItemRarity::POOR, "Poor"}, {ItemRarity::COMMON, "Common"}, {ItemRarity::UNCOMMON, "Uncommon"}, {ItemRarity::RARE, "Rare"}, {ItemRarity::EPIC, "Epic"}, {ItemRarity::LEGENDARY, "Legendary"}
};

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

void Item::setItemName(string _itemName)
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

	cout << "Item Slot: " << itemSlotToString.at(itemSlot) << ", Item Name: " << itemName << ", Item Type: " << itemTypeToString.at(itemType) << ", Item Rarity: " << itemRarityToString.at(itemRarity) << endl;
		cout << "Health: " << itemHealth << ", Attack: " << itemAttack << ", Defense: " << itemDefense << endl;
}