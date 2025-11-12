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
	enum class ItemSlot
	{
		EMPTY = 0,
		HELMET = 1,
		CHESTPIECE = 2,
		PANTS = 3,
		BOOTS = 4,
		SHIELD = 5,
		SWORD = 6
		
	};

	enum class ItemType
	{
		UNKNOWN = 0,
		EQUIPMENT = 1,
		CONSUMABLE = 2,
		QUEST_ITEM = 3
	};

	enum class ItemRarity
	{
		NONEXISTENT = 0,
		POOR = 1,
		COMMON = 2,
		UNCOMMON = 3,
		RARE = 4,
		EPIC = 5,
		LEGENDARY = 6
	};

	static const map<ItemSlot, string> itemSlotToString;
	static const map<ItemType, string> itemTypeToString;
	static const map<ItemRarity, string> itemRarityToString;


	Item();
	Item(string _itemName, int _itemAttack, int _itemDefense, int _itemHealth, ItemSlot _itemSlot, ItemType _itemType = ItemType::EQUIPMENT, ItemRarity _itemRarity = ItemRarity::POOR);
	string getItemName() const;
	int getItemAttack() const;
	int getItemDefense() const;
	int getItemHealth() const;
	ItemSlot getItemSlot() const;
	ItemType getItemType() const;
	ItemRarity getItemRarity() const;


	void setItemName(const string& _itemName);
	void setItemAttack(int _itemAttack);
	void setItemDefense(int _itemDefense);
	void setItemHealth(int _itemHealth);
	void setItemSlot(ItemSlot _itemSlot);
	void setItemType(ItemType _itemType);
	void setItemRarity(ItemRarity _itemRarity);

	void printItem() const;

private:
	string itemName;
	int itemAttack;
	int itemDefense;
	int itemHealth;
	ItemSlot itemSlot;
	ItemType itemType;
	ItemRarity itemRarity;

};

#endif // !ITEM_H
