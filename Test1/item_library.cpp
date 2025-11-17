#include "item_library.h"
#include "json.hpp"
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

using json = nlohmann::json;

// Internal storage
static std::vector<Equipment> g_equipment;
static bool g_loaded = false;

static std::unordered_map<std::string, std::size_t> g_EquipmentById;

// Determines an ItemSlot based on a string. Input is a string name of the item slot. Returns an ItemSlot (EMPTY if not found).
static Equipment::EquipmentSlot equipmentSlotFromString(const std::string& slotStr)
{
    std::string slot = slotStr;
    std::transform(slot.begin(), slot.end(), slot.begin(),::toupper);
    for (int i = 0; i < equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT); i++)
    {
        std::string upperSlot = Equipment::equipmentSlotToString.at(equipmentSlotFromIndex(i));
        std::transform(upperSlot.begin(), upperSlot.end(), upperSlot.begin(), ::toupper);
        if (slot.compare(upperSlot) == 0)
            return equipmentSlotFromIndex(i);
    }
    return Equipment::EquipmentSlot::EMPTY;
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
    for (const auto& jitem : j["equipment"])
    {
        
        std::string id = jitem["id"];
        std::string slot = jitem["slot"];
        std::string type = jitem["type"];
        std::string rarity = jitem["rarity"];
        std::string name = jitem["name"];
        int attack = jitem["attack"];
        int defense = jitem["defense"];
        int health = jitem["health"];

        Equipment::EquipmentSlot itemSlot = equipmentSlotFromString(slot);
        Item::ItemType itemType = itemTypeFromString(type);
        Item::ItemRarity itemRarity = itemRarityFromString(rarity);

        if (itemType == Item::ItemType::EQUIPMENT)
        {
            g_equipment.emplace_back(Equipment(id, name, attack, defense, health, itemSlot, itemRarity));
            g_EquipmentById.emplace(id, g_equipment.size() - 1);
        }       
    }

    g_loaded = true;
}

// Public API

const std::vector<Equipment>& ItemLibrary::equipment()
{
    loadIfNeeded();
    return g_equipment;
}

const Equipment& ItemLibrary::equipmentById(const std::string& _id)
{
    loadIfNeeded();
    auto it = g_EquipmentById.find(_id);
    if (it != g_EquipmentById.end()) return g_equipment[it->second];
    else std::cout << _id << " not found in master equipment inventory.\n";

    static Equipment EMPTY; // default-constructed EMPTY
    return EMPTY;
}

