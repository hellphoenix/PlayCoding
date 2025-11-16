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

    //Will probably alter significantly

    void run();
    std::array<std::vector<Item>, itemSlotToIndex(Item::ItemSlot::COUNT)> gameItems{};
    const std::array<std::vector<Item>, itemSlotToIndex(Item::ItemSlot::COUNT)>& getGameItems() const;

private:
    void loadItems(); // Loads all items from item slot libraries

    const std::vector<Item>* items = nullptr; // pointer for master items list.


    //Player playerOne;
};


#endif // !GAME_INITIALIZE_H


