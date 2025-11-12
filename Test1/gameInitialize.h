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

private:
    void loadItems();
    void createPlayer();
    
    void giveStartingItems();

    // data used across phases
    const std::vector<Item>* helmets = nullptr;
    const std::vector<Item>* chestPieces = nullptr;
    const std::vector<Item>* pants = nullptr;
    const std::vector<Item>* boots = nullptr;
    const std::vector<Item>* shields = nullptr;
    const std::vector<Item>* swords = nullptr;

    Player playerOne{};
};


#endif // !GAME_INITIALIZE_H


