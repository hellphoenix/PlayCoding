#include "item_library.h"
#include "json.hpp"
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

using json = nlohmann::json;

// Internal storage
static std::vector<Item> g_items;
static bool g_loaded = false;

static std::unordered_map<std::string, std::size_t> g_byId;

// Determines an ItemSlot based on a string. Input is a string name of the item slot. Returns an ItemSlot (EMPTY if not found).
static Item::ItemSlot itemSlotFromString(const std::string& slotStr)
{
    std::string slot = slotStr;
    std::transform(slot.begin(), slot.end(), slot.begin(),::toupper);
    for (int i = 0; i < itemSlotToIndex(Item::ItemSlot::COUNT); i++)
    {
        std::string upperSlot = Item::itemSlotToString.at(itemSlotFromIndex(i));
        std::transform(upperSlot.begin(), upperSlot.end(), upperSlot.begin(), ::toupper);
        if (slot.compare(upperSlot) == 0)
            return itemSlotFromIndex(i);
    }
    return Item::ItemSlot::EMPTY;
}

// Determines an ItemType based on a string. Input is a string name of the item type. Returns an ItemType (UNKNOWN if not found).
static Item::ItemType itemTypeFromString(const std::string& itemStr)
{
    std::string item = itemStr;
    std::transform(item.begin(), item.end(), item.begin(), ::toupper);
    for (int i = 0; i < itemTypeToIndex(Item::ItemType::COUNT); i++)
    {
        std::string upperItem = Item::itemTypeToString.at(itemTypeFromIndex(i));
        std::transform(upperItem.begin(), upperItem.end(), upperItem.begin(), ::toupper);
        if (item.compare(upperItem) == 0)
            return itemTypeFromIndex(i);
    }
    return Item::ItemType::UNKNOWN;
}

// Determines an ItemRarity based on a string. Input is a string name of the item rarity. Returns an ItemRarity (NONEXISTENT if not found).
static Item::ItemRarity itemRarityFromString(const std::string& rarityStr)
{
    std::string rarity = rarityStr;
    std::transform(rarity.begin(), rarity.end(), rarity.begin(), ::toupper);
    for (int i = 0; i < itemRarityToIndex(Item::ItemRarity::COUNT); i++)
    {
        std::string upperRarity = Item::itemRarityToString.at(itemRarityFromIndex(i));
        std::transform(upperRarity.begin(), upperRarity.end(), upperRarity.begin(), ::toupper);
        if (rarity.compare(upperRarity) == 0)
            return itemRarityFromIndex(i);
    }
    return Item::ItemRarity::NONEXISTENT;
}

// Loads items found in the items.json file by creating a base item, mutating it with the inputs found in the file, and stroing that item in the g_items vector. Also emplaced the item with it's item ID into the g_byId map.
static void loadIfNeeded()
{
    if (g_loaded) return;

    std::ifstream file("items.json");
    if (!file)
        throw std::runtime_error("Could not open items.json");

    json j;
    file >> j;
    for (const auto& jitem : j["items"])
    {
        
        std::string id = jitem["id"];
        std::string slot = jitem["slot"];
        std::string type = jitem["type"];
        std::string rarity = jitem["rarity"];
        std::string name = jitem["name"];
        int attack = jitem["attack"];
        int defense = jitem["defense"];
        int health = jitem["health"];

        Item::ItemSlot itemSlot = itemSlotFromString(slot);
        Item::ItemType itemType = itemTypeFromString(type);
        Item::ItemRarity itemRarity = itemRarityFromString(rarity);

        //Item item(id, name, attack, defense, health, itemSlot, itemType, itemRarity);

        //g_items.push_back(item);
        g_items.emplace_back(Item(id, name, attack, defense, health, itemSlot, itemType, itemRarity));

        // id registry
        
        g_byId.emplace(id, g_items.size() - 1);
    }

    g_loaded = true;
}

// Public API

const std::vector<Item>& ItemLibrary::items()
{
    loadIfNeeded();
    return g_items;
}

const Item& ItemLibrary::byId(const std::string& _id)
{
    loadIfNeeded();
    auto it = g_byId.find(_id);
    if (it != g_byId.end()) return g_items[it->second];
    else std::cout << _id << " not found in master inventory.\n";

    static Item EMPTY; // default-constructed EMPTY
    return EMPTY;
}

