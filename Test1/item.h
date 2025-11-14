#pragma once
#include <string>
#include <map>
using std::string;
using std::map;

#ifndef ITEM_H
#define ITEM_H

class Item
{
public:
	enum class ItemSlot // change me when adding item slots
	{
		EMPTY = 0,
		HELMET,
		CHESTPIECE,
		PANTS,
		BOOTS,
		SHIELD,
		WEAPON,
		COUNT
	};

	static const map<ItemSlot, string> itemSlotToString; 
	


	enum class ItemType // change me when adding item types
	{
		UNKNOWN = 0,
		EQUIPMENT,
		CONSUMABLE,
		QUEST_ITEM,
		COUNT
	};

	static const map<ItemType, string> itemTypeToString; 

	enum class ItemRarity // change me when adding item rarities
	{
		NONEXISTENT = 0,
		POOR,
		COMMON,
		UNCOMMON,
		RARE,
		EPIC,
		LEGENDARY,
		COUNT
	};
	
	static const map<ItemRarity, string> itemRarityToString; 

	Item();
	Item(const string& _id, const string& _itemName, int _itemAttack, int _itemDefense, int _itemHealth, ItemSlot _itemSlot = ItemSlot::EMPTY, ItemType _itemType = ItemType::UNKNOWN, ItemRarity _itemRarity = ItemRarity::NONEXISTENT);
	string getId() const;
	string getItemName() const;
	int getItemAttack() const;
	int getItemDefense() const;
	int getItemHealth() const;
	ItemSlot getItemSlot() const;
	ItemType getItemType() const;
	ItemRarity getItemRarity() const;

	void setId(const string& _id);
	void setItemName(const string& _itemName);
	void setItemAttack(int _itemAttack);
	void setItemDefense(int _itemDefense);
	void setItemHealth(int _itemHealth);
	void setItemSlot(ItemSlot _itemSlot);
	void setItemType(ItemType _itemType);
	void setItemRarity(ItemRarity _itemRarity);

	void printItem() const;


private:
	string id;
	string itemName;
	int itemAttack;
	int itemDefense;
	int itemHealth;
	ItemSlot itemSlot;
	ItemType itemType;
	ItemRarity itemRarity;

};

constexpr std::size_t itemSlotToIndex(Item::ItemSlot slot) // returns an int value from an item slot
{
	return static_cast<std::size_t>(slot);
}

constexpr std::size_t itemTypeToIndex(Item::ItemType slot) // returns an int value from an item type
{
	return static_cast<std::size_t>(slot);
}

constexpr std::size_t itemRarityToIndex(Item::ItemRarity slot) // returns an int value from an item rarity
{
	return static_cast<std::size_t>(slot);
}

constexpr Item::ItemSlot itemSlotFromIndex(int _index) // Returns an item slot, between EMPTY and COUNT, from an int
{
	if (_index >= itemSlotToIndex(Item::ItemSlot::EMPTY) && _index < itemSlotToIndex(Item::ItemSlot::COUNT))
		return static_cast<Item::ItemSlot>(_index);
	else
		return Item::ItemSlot::EMPTY;
}

constexpr Item::ItemType itemTypeFromIndex(int _index) // Returns an item type, between UNKNOWN and COUNT, from an int
{
	if (_index >= itemTypeToIndex(Item::ItemType::UNKNOWN) && _index < itemTypeToIndex(Item::ItemType::COUNT))
		return static_cast<Item::ItemType>(_index);
	else
		return Item::ItemType::UNKNOWN;
}

constexpr Item::ItemRarity itemRarityFromIndex(int _index) // Returns an item rarity, between NONEXISTENT and COUNT, from an int
{
	if (_index >= itemRarityToIndex(Item::ItemRarity::NONEXISTENT) && _index < itemRarityToIndex(Item::ItemRarity::COUNT))
		return static_cast<Item::ItemRarity>(_index);
	else
		return Item::ItemRarity::NONEXISTENT;
}

#endif // !ITEM_H
