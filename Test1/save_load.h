#pragma once
#include "item_library.h"
#include "json.hpp"
#include "player.h"
#include "equipment.h"

#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

namespace SaveLoad {
    nlohmann::json toJson(Player& p);
    bool saveToFile(Player& p, const std::string& path);

    bool fromJson(const nlohmann::json& j, Player& out);
    bool loadFromFile(Player& out, const std::string& path);
}

#endif // !SAVE_LOAD_H

