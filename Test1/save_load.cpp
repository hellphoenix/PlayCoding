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

    j["equipped"] = {
        {"helmet",     idOrEmpty(tp.getHelmet())},
        {"chest",      idOrEmpty(tp.getChestPiece())},
        {"pants",      idOrEmpty(tp.getPants())},
        {"boots",      idOrEmpty(tp.getBoots())},
        {"shield",     idOrEmpty(tp.getShield())},
        {"sword",      idOrEmpty(tp.getSword())}
    };

    // inventory as list of ids
    json inv = json::array();
    for (const auto& it : tp.getInventory().getItems())
        inv.push_back(it.getId());
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
        const auto& eq = j.at("equipped");
        out.setItem(resolveOrEmpty(eq.value("helmet", "")));
        out.setItem(resolveOrEmpty(eq.value("chest", "")));
        out.setItem(resolveOrEmpty(eq.value("pants", "")));
        out.setItem(resolveOrEmpty(eq.value("boots", "")));
        out.setItem(resolveOrEmpty(eq.value("shield", "")));
        out.setItem(resolveOrEmpty(eq.value("sword", "")));

        // inventory
        if (j.contains("inventory") && j["inventory"].is_array()) {
            for (const auto& id : j["inventory"]) {
                Item it = resolveOrEmpty(id.get<std::string>());
                if (it.getItemSlot() != Item::ItemSlot::EMPTY)
                    out.getInventory().addToInventory(it);
            }
        }

        // totals refresh
        out.setBaseStats(bh,ch,ba,bd);
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