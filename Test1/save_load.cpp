#include "save_load.h"
#include <fstream>
using nlohmann::json;

json SaveLoad::toJson(Player& p)
{
    json j;
    j["name"] = p.getName();
    j["base"] = {
        {"base_health", p.getBaseHealth()},
        {"current_health", p.getCurrentHealth()},
        {"attack", p.getBaseAttack()},
        {"defense", p.getBaseDefense()}
    };

    // equipped as list of ids
    json equ = json::array();
    for (const auto& it : p.getPlayerEquipment())
    {
        if (it.getId() == "") continue;
        equ.push_back(it.getId());
    }
        
    j["equipped"] = equ;

    // inventory as list of ids
    json inv = json::array();
    for (const auto& it : p.getPlayerInventory().getEquipmentInventory())
    {
        if (it.getId() == "") continue;
        inv.push_back(it.getId());
    }
        
    j["equipment_inventory"] = inv;

    return j;
}

bool SaveLoad::saveToFile(Player& p, const std::string& path)
{
    std::ofstream f(path);
    if (!f) return false;
    f << toJson(p).dump(2);
    return true;
}

static Equipment resolveOrEmpty(const std::string& id)
{
    if (id.empty()) return Equipment();
    const Equipment& ref = ItemLibrary::equipmentById(id);
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
                Equipment it = resolveOrEmpty(id.get<std::string>());
                out.equipEquipment(it);
            }
        }

        // inventory
        if (j.contains("equipment_inventory") && j["equipment_inventory"].is_array()) {
            for (const auto& id : j["equipment_inventory"]) {
                Equipment it = resolveOrEmpty(id.get<std::string>());
                if (it.getEquipmentSlot() != EquipmentSlot::EMPTY)
                    out.getPlayerInventory().addEquipmentToInventory(it);
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