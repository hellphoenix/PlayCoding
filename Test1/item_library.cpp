#include "item_library.h"
#include "include/json.hpp"
#include <fstream>
#include <stdexcept>
#include <unordered_map>

using json = nlohmann::json;

// Internal storage
static std::vector<Item> g_helmets;
static std::vector<Item> g_chestPieces;
static std::vector<Item> g_pants;
static std::vector<Item> g_boots;
static std::vector<Item> g_shields;
static std::vector<Item> g_swords;
static bool g_loaded = false;

static std::unordered_map<std::string, Item> g_byId; // copy-based registry

static Item::ItemSlot itemSlotFromString(const string& slotStr)
{
	if (slotStr == "HELMET")      return Item::ItemSlot::HELMET;
	if (slotStr == "CHESTPIECE")  return Item::ItemSlot::CHESTPIECE;
	if (slotStr == "PANTS")       return Item::ItemSlot::PANTS;
	if (slotStr == "BOOTS")       return Item::ItemSlot::BOOTS;
	if (slotStr == "SHIELD")      return Item::ItemSlot::SHIELD;
	if (slotStr == "SWORD")       return Item::ItemSlot::SWORD;
	return Item::ItemSlot::EMPTY;
}

static Item::ItemType itemTypeFromString(const string& itemStr)
{
    if (itemStr == "EQUIPMENT") return Item::ItemType::EQUIPMENT;
    if (itemStr == "CONSUMABLE")return Item::ItemType::CONSUMABLE;
    if (itemStr == "QUEST_ITEM")return Item::ItemType::QUEST_ITEM;
    return Item::ItemType::UNKNOWN;
}

static Item::ItemRarity itemRarityFromString(const string& rarityStr)
{
    if (rarityStr == "POOR")    return Item::ItemRarity::POOR;
    if (rarityStr == "COMMON")    return Item::ItemRarity::COMMON;
    if (rarityStr == "UNCOMMON")    return Item::ItemRarity::UNCOMMON;
    if (rarityStr == "RARE")    return Item::ItemRarity::RARE;
    if (rarityStr == "EPIC")    return Item::ItemRarity::EPIC;
    if (rarityStr == "LEGENDARY")    return Item::ItemRarity::LEGENDARY;
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
        std::transform(slot.begin(), slot.end(), slot.begin(), ::toupper);
        std::string type = jitem["type"];
        std::transform(type.begin(), type.end(), type.begin(), ::toupper);
        std::string rarity = jitem["rarity"];
        std::transform(rarity.begin(), rarity.end(), rarity.begin(), ::toupper);
        std::string name = jitem["name"];
        int attack = jitem["attack"];
        int defense = jitem["defense"];
        int health = jitem["health"];

        Item::ItemSlot itemSlot = itemSlotFromString(slot);
        Item::ItemType itemType = itemTypeFromString(type);
        Item::ItemRarity itemRarity = itemRarityFromString(rarity);

        Item item(id, name, attack, defense, health, itemSlot, itemType, itemRarity);

        switch (itemSlot)
        {
        case Item::ItemSlot::HELMET:      g_helmets.push_back(item);      break;
        case Item::ItemSlot::CHESTPIECE:  g_chestPieces.push_back(item);  break;
        case Item::ItemSlot::PANTS:       g_pants.push_back(item);        break;
        case Item::ItemSlot::BOOTS:       g_boots.push_back(item);        break;
        case Item::ItemSlot::SHIELD:      g_shields.push_back(item);      break;
        case Item::ItemSlot::SWORD:       g_swords.push_back(item);       break;
        default:
            // You might log or ignore EMPTY or unknown
            break;
        }

        // id registry
        g_byId.emplace(item.getId(), item);
    }

    g_loaded = true;
}

// Public API

const std::vector<Item>& ItemLibrary::helmets()
{
    loadIfNeeded();
    return g_helmets;
}

const std::vector<Item>& ItemLibrary::chestPieces()
{
    loadIfNeeded();
    return g_chestPieces;
}

const std::vector<Item>& ItemLibrary::pants()
{
    loadIfNeeded();
    return g_pants;
}

const std::vector<Item>& ItemLibrary::boots()
{
    loadIfNeeded();
    return g_boots;
}

const std::vector<Item>& ItemLibrary::shields()
{
    loadIfNeeded();
    return g_shields;
}

const std::vector<Item>& ItemLibrary::swords()
{
    loadIfNeeded();
    return g_swords;
}

const Item& ItemLibrary::byId(const string& _id)
{
    loadIfNeeded();
    auto it = g_byId.find(_id);
    if (it != g_byId.end()) return it->second;

    static Item EMPTY; // default-constructed EMPTY
    return EMPTY;
}