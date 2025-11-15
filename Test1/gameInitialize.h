#pragma once
#include "player.h"
#include "enemy.h"
#include "item_library.h"

#ifndef GAME_INITIALIZE_H
#define GAME_INITIALIZE_H

class GameInitialize
{
public:
    void run();
    const Player& getPlayer() const;
    std::array<vector<Item>, itemSlotToIndex(Item::ItemSlot::COUNT)> gameItems{};

private:
    void loadItems(); // Loads all items from item slot libraries
    void createPlayer(); // Creates a player with defined stats
    void giveStartingItems(); // Gives player some items at the start of the game. Will change when inventory testing is complete.

    const std::vector<Item>* items = nullptr; // pointer for master items list.


    Player playerOne{};
};


#endif // !GAME_INITIALIZE_H


