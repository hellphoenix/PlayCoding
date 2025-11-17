#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <map>
#include <string>

struct Item
{
public:

	enum class ItemType
	{
		UNKNOWN = 0,
		EQUIPMENT,
		CONSUMABLE,
		QUEST_ITEM,
		COUNT
	};

	static const std::map<ItemType, std::string> itemTypeToString;

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
	
	static const std::map<ItemRarity, std::string> itemRarityToString;

	Item();

	Item(const std::string& _id, const std::string& _itemName, ItemType _itemType = ItemType::UNKNOWN, ItemRarity _itemRarity = ItemRarity::NONEXISTENT);
	std::string getId() const;
	std::string getItemName() const;
	ItemType getItemType() const;
	ItemRarity getItemRarity() const;

	void setId(const std::string& _id);
	void setItemName(const std::string& _itemName);
	void setItemType(ItemType _itemType);
	void setItemRarity(ItemRarity _itemRarity);

	void printItem() const;


private:
	std::string id;
	std::string itemName;
	ItemType itemType;
	ItemRarity itemRarity;

};

constexpr std::size_t itemTypeToIndex(Item::ItemType slot) // returns an int value from an item type
{
	return static_cast<std::size_t>(slot);
}

constexpr std::size_t itemRarityToIndex(Item::ItemRarity slot) // returns an int value from an item rarity
{
	return static_cast<std::size_t>(slot);
}

constexpr Item::ItemType itemTypeFromIndex(int _index) // Returns an item type, between UNKNOWN and COUNT, from an int
{
	if (_index > 0 && _index < itemTypeToIndex(Item::ItemType::COUNT))
		return static_cast<Item::ItemType>(_index);
	else
		return Item::ItemType::UNKNOWN;
}

constexpr Item::ItemRarity itemRarityFromIndex(int _index) // Returns an item rarity, between NONEXISTENT and COUNT, from an int
{
	if (_index > 0 && _index < itemRarityToIndex(Item::ItemRarity::COUNT))
		return static_cast<Item::ItemRarity>(_index);
	else
		return Item::ItemRarity::NONEXISTENT;
}

#endif // !ITEM_H
