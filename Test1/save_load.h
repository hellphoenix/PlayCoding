#pragma once
#include "player.h"
#include "item_library.h"
#include "json.hpp"

#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

namespace SaveLoad {
    nlohmann::json toJson(const Player& p);
    bool saveToFile(const Player& p, const std::string& path);

    bool fromJson(const nlohmann::json& j, Player& out);
    bool loadFromFile(Player& out, const std::string& path);
}

#endif // !SAVE_LOAD_H

