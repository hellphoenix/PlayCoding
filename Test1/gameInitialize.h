#pragma once
#include "enemy.h"
#include "item_library.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include <vector>

#ifndef GAME_INITIALIZE_H
#define GAME_INITIALIZE_H

class GameInitialize
{
public:

    void run();
    std::array < std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT )> gameEquipment{};
    const std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)>& getGameEquipment() const;

private:
    void loadEquipment(); // Loads all items from item slot libraries

    const std::vector<Equipment>* equipment = nullptr; // pointer for master items list.
};


#endif // !GAME_INITIALIZE_H


