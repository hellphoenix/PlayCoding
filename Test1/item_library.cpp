#include "item_library.h"
#include "json.hpp"
#include <fstream>
#include <cctype>
#include <stdexcept>
#include <unordered_map>

using json = nlohmann::json;

// Internal storage
static std::vector<Item> g_items;
static bool g_loaded = false;

static std::unordered_map<std::string, Item> g_byId; // copy-based registry

static Item::ItemSlot itemSlotFromString(const string& slotStr)
{
    string slot = slotStr;
    transform(slot.begin(), slot.end(), slot.begin(),::toupper);
    for (int i = 0; i < itemSlotToIndex(Item::ItemSlot::COUNT); i++)
    {
        string upperSlot = Item::itemSlotToString.at(itemSlotFromIndex(i));
        transform(upperSlot.begin(), upperSlot.end(), upperSlot.begin(), ::toupper);
        if (slot.compare(upperSlot) == 0)
            return itemSlotFromIndex(i);
    }
    return Item::ItemSlot::EMPTY;
}

static Item::ItemType itemTypeFromString(const string& itemStr)
{
    string item = itemStr;
    transform(item.begin(), item.end(), item.begin(), ::toupper);
    for (int i = 0; i < itemTypeToIndex(Item::ItemType::COUNT); i++)
    {
        string upperItem = Item::itemTypeToString.at(itemTypeFromIndex(i));
        transform(upperItem.begin(), upperItem.end(), upperItem.begin(), ::toupper);
        if (item.compare(upperItem) == 0)
            return itemTypeFromIndex(i);
    }
    return Item::ItemType::UNKNOWN;
}

static Item::ItemRarity itemRarityFromString(const string& rarityStr)
{
    string rarity = rarityStr;
    transform(rarity.begin(), rarity.end(), rarity.begin(), ::toupper);
    for (int i = 0; i < itemRarityToIndex(Item::ItemRarity::COUNT); i++)
    {
        string upperRarity = Item::itemRarityToString.at(itemRarityFromIndex(i));
        transform(upperRarity.begin(), upperRarity.end(), upperRarity.begin(), ::toupper);
        if (rarity.compare(upperRarity) == 0)
            return itemRarityFromIndex(i);
    }
    return Item::ItemRarity::NONEXISTENT;
}

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

        Item item(id, name, attack, defense, health, itemSlot, itemType, itemRarity);

        g_items.push_back(item);

        // id registry
        g_byId.emplace(item.getId(), item);
    }

    g_loaded = true;
}

// Public API

const std::vector<Item>& ItemLibrary::items()
{
    loadIfNeeded();
    return g_items;
}

const Item& ItemLibrary::byId(const string& _id)
{
    loadIfNeeded();
    auto it = g_byId.find(_id);
    if (it != g_byId.end()) return it->second;

    static Item EMPTY; // default-constructed EMPTY
    return EMPTY;
}

