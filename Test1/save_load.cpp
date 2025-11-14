#include "save_load.h"
#include <fstream>
using nlohmann::json;

namespace {
    // helper to get id or empty for EMPTY item
    std::string idOrEmpty(const Item& it) {
        return it.getItemSlot() == Item::ItemSlot::EMPTY ? "" : it.getId();
    }
}

json SaveLoad::toJson(const Player& p)
{
    Player tp = p;
    json j;
    j["name"] = tp.getName();
    j["base"] = {
        {"base_health", tp.getBaseHealth()},
        {"current_health", tp.getCurrentHealth()},
        {"attack", tp.getBaseAttack()},
        {"defense", tp.getBaseDefense()}
    };

    // equipped as list of ids
    json equ = json::array();
    for (const auto& it : tp.getPlayerEquipment())
    {
        if (it.getId() == "") continue;
        equ.push_back(it.getId());
    }
        
    j["equipped"] = equ;

    // inventory as list of ids
    json inv = json::array();
    for (const auto& it : tp.getPlayerInventory().getInventory())
    {
        if (it.getId() == "") continue;
        inv.push_back(it.getId());
    }
        
    j["inventory"] = inv;

    return j;
}

bool SaveLoad::saveToFile(const Player& p, const std::string& path)
{
    std::ofstream f(path);
    if (!f) return false;
    f << toJson(p).dump(2);
    return true;
}

static Item resolveOrEmpty(const std::string& id)
{
    if (id.empty()) return Item();
    const Item& ref = ItemLibrary::byId(id);
    return ref; // copy into Player or Inventory
}

bool SaveLoad::fromJson(const json& j, Player& out)
{
    try {
        // base
        std::string name = j.at("name").get<std::string>();
        int bh = j.at("base").at("base_health").get<int>();
        int ch = j.at("base").at("current_health").get<int>();
        int ba = j.at("base").at("attack").get<int>();
        int bd = j.at("base").at("defense").get<int>();

        // start with no gear
        out = Player{ name, bh, ch, ba, bd };

        // equip
        if (j.contains("equipped") && j["equipped"].is_array())
        {
            for (const auto& id : j["equipped"])
            {
                Item it = resolveOrEmpty(id.get<std::string>());
                out.equipItem(it);
            }
        }

        // inventory
        if (j.contains("inventory") && j["inventory"].is_array()) {
            for (const auto& id : j["inventory"]) {
                Item it = resolveOrEmpty(id.get<std::string>());
                if (it.getItemSlot() != Item::ItemSlot::EMPTY)
                    out.getPlayerInventory().addToInventory(it);
            }
        }

        // totals refresh
        out.updateMaxStats();
        return true;
    }
    catch (...) {
        return false;
    }
}

bool SaveLoad::loadFromFile(Player& out, const std::string& path)
{
    std::ifstream f(path);
    if (!f) return false;
    json j; f >> j;
    return fromJson(j, out);
}