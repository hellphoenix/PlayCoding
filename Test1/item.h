#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <map>
#include <string>

enum class ItemType
{
	UNKNOWN = 0,
	EQUIPMENT,
	CONSUMABLE,
	QUEST_ITEM,
	COUNT
};

static const std::map<ItemType, std::string> itemTypeToString =
{
	{ItemType::UNKNOWN, "Unknown"}, {ItemType::EQUIPMENT, "Equipment"}, {ItemType::CONSUMABLE, "Consumable"}, {ItemType::QUEST_ITEM, "Quest Item"}
};

constexpr std::size_t itemTypeToIndex(ItemType slot) // returns an int value from an item type
{
	return static_cast<std::size_t>(slot);
}

constexpr ItemType itemTypeFromIndex(int _index) // Returns an item type, between UNKNOWN and COUNT, from an int
{
	if (_index > 0 && _index < itemTypeToIndex(ItemType::COUNT))
		return static_cast<ItemType>(_index);
	else
		return ItemType::UNKNOWN;
}

enum class ItemRarity
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

static const std::map<ItemRarity, std::string> itemRarityToString =
{
	{ItemRarity::NONEXISTENT, "Non-Existent"}, {ItemRarity::POOR, "Poor"}, {ItemRarity::COMMON, "Common"}, {ItemRarity::UNCOMMON, "Uncommon"},
	{ItemRarity::RARE, "Rare"}, {ItemRarity::EPIC, "Epic"}, {ItemRarity::LEGENDARY, "Legendary"}
};

constexpr std::size_t itemRarityToIndex(ItemRarity slot) // returns an int value from an item rarity
{
	return static_cast<std::size_t>(slot);
}

constexpr ItemRarity itemRarityFromIndex(int _index) // Returns an item rarity, between NONEXISTENT and COUNT, from an int
{
	if (_index > 0 && _index < itemRarityToIndex(ItemRarity::COUNT))
		return static_cast<ItemRarity>(_index);
	else
		return ItemRarity::NONEXISTENT;
}

struct Item
{
public:

	Item() : id(), itemName(), itemType(ItemType::UNKNOWN), itemRarity(ItemRarity::NONEXISTENT)
	{

	}

	Item(const std::string& _id, const std::string& _itemName, ItemType _itemType = ItemType::UNKNOWN, ItemRarity _itemRarity = ItemRarity::NONEXISTENT) :
		id(_id), itemName(_itemName), itemType(_itemType), itemRarity(_itemRarity)
	{

	}

	std::string getId() const { return this->id; }
	std::string getItemName() const { return this->itemName; }
	ItemType getItemType() const { return this->itemType; }
	ItemRarity getItemRarity() const { return this->itemRarity; }

	void setId(const std::string& _id) { this->id = _id; }
	void setItemName(const std::string& _itemName) { this->itemName = _itemName; }
	void setItemType(ItemType _itemType) { this->itemType = _itemType; }
	void setItemRarity(ItemRarity _itemRarity) { this->itemRarity = _itemRarity; }

protected:
	std::string id;
	std::string itemName;
	ItemType itemType;
	ItemRarity itemRarity;

};

#endif // !ITEM_H
