#include "game.h"
#include "gameInitialize.h"
#include "save_load.h"
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>


using std::cout;
using std::endl;



// helper to lower case a string
static std::string toLowerCopy(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
}

void Game::printHelp() const
{
    cout << "Commands:\n";
    cout << "  help        - show this help\n";
    cout << "  stats       - show player stats and equipment\n";
    cout << "  inventory   - show inventory\n";
    cout << "  equip       - equip an item from inventory\n";
    cout << "  unequip     - unequip an item back to inventory\n";
    cout << "  debug       - change base player variables\n";
    cout << "  save        - save player stats and items\n";
    cout << "  load        - load player stats and items\n";
    cout << "  quit        - exit game\n";
}

void Game::handleEquipCommand()
{
    std::string slot;
    std::string itemName;
    bool slotFound = false;

    while (!slotFound)
    {
        cout << "Enter slot (helmet, chestpiece, pants, boots, shield, sword) or type cancel: ";
        std::getline(std::cin, slot);
        slot = toLowerCopy(slot);
      
        if (slot == "helmet" || slot == "chest" || slot == "chestpiece" || slot == "pants" || slot == "boots" || slot == "shield" || slot == "sword")
        {
            cout << "Enter item name exactly as shown in inventory: ";
            std::getline(std::cin, itemName);
            player.equipEquipmentFromInventory(itemName);
            cout << "Updated player:\n";
            player.printPlayer();
            slotFound = true;
        }
        else if (slot == "cancel")
        {
            slotFound = true;
        }
        else
            cout << "Unknown slot. Please try again or type cancel to not equip item.\n";
    }   
}

void Game::handleUnequipCommand()
{
    std::string slot;
    bool slotFound = false;

    while (!slotFound)
    {
        cout << "Enter slot to unequip (helmet, chest, pants, boots, shield, sword), or type cancel: ";
        std::getline(std::cin, slot);
        slot = toLowerCopy(slot);

        if (slot == "helmet" || slot == "chest" || slot == "chestpiece" || slot == "pants" || slot == "boots" || slot == "shield" || slot == "sword")
        {
            player.setItem(Item(), slot);
            cout << "Updated player:\n";
            player.printPlayer();
            slotFound = true;
        }
        else if (slot == "cancel")
        {
            slotFound = true;
        }
        else
            cout << "Unknown slot. Please try again or type cancel to not unequip item.\n";
    }
}

void Game::handleDebugCommand()
{
    std::string command;

    cout << "Enter a variable to change (name: " << player.getName() << ", base attack: "<< player.getBaseAttack() << ", base defense: "<< player.getBaseDefense() << ", base health: " << player.getBaseHealth() << "): ";
    std::getline(std::cin, command);
    command = toLowerCopy(command);

    //Setting new name
    if (command == "name")
    {
        std::string newName;
        cout << "Set New Name: ";
        std::getline(std::cin, newName);
        player.setName(newName);

        cout << "Updated player:\n";
        player.printPlayer();
    }
    //Setting new base attack
    else if (command == "base attack")
    {
        int newBaseAttack = player.getBaseAttack();
        string input;
        while (true)
        {
            cout << "Set new base attack: ";
            std::getline(std::cin, input);
            input = toLowerCopy(input);
            if (input == "cancel") break;

            try
            {
                newBaseAttack = std::stoi(input);
                player.setBaseStats(player.getBaseHealth(), newBaseAttack, player.getBaseDefense());
                cout << "Updated player:\n";
                player.printPlayer();
                break;
            }
            catch (...)
            {
                std::cout << "Invalid number. Try again, or type cancel to keep the base attack.\n";
            }
        }
        
    }
    //Setting new base defense
    else if (command == "base defense")
    {
        int newBaseDefense = player.getBaseDefense();
        string input;
        while (true)
        {
            cout << "Set new base defense: ";
            std::getline(std::cin, input);
            input = toLowerCopy(input);
            if (input == "cancel") break;
            try
            {
                newBaseDefense = std::stoi(input);
                player.setBaseStats(player.getBaseHealth(), player.getBaseAttack(), newBaseDefense);
                cout << "Updated player:\n";
                player.printPlayer();
                break;
            }
            catch (...)
            {
                std::cout << "Invalid number. Try again, or type cancel to keep the base defense.\n";
            }
        }
    }
    //Setting new base health
    else if (command == "base health")
    {
        int newBaseHealth = player.getBaseHealth();
        string input;
        while (true)
        {
            cout << "Set new base health: ";
            std::getline(std::cin, input);
            input = toLowerCopy(input);
            if (input == "cancel") break;
            try
            {
                newBaseHealth = std::stoi(input);
                player.setBaseStats(newBaseHealth, player.getBaseAttack(), player.getBaseDefense());
                cout << "Updated player:\n";
                player.printPlayer();
                break;
            }
            catch (...)
            {
                std::cout << "Invalid number. Try again, or type cancel to keep the base health.\n";
            }
        }    
    }
    else
    {
        cout << "Unknown command. Type 'help' for a list.\n";
    }
}

void Game::loop(const Player& _player)
{
    Game::player = _player;
    cout << "---- Game loop started ----" << endl;
    cout << "Type 'help' to see available commands.\n";

    std::string command;

    while (true)
    {
        cout << "\n> ";
        if (!std::getline(std::cin, command))
            break; // EOF or input error

        command = toLowerCopy(command);

        if (command == "quit" || command == "exit")
        {
            cout << "Exiting game.\n";
            break;
        }
        else if (command == "help")
        {
            printHelp();
        }
        else if (command == "stats")
        {
            player.printPlayer();
        }
        else if (command == "inventory")
        {
            player.getInventory().printInventory();
        }
        else if (command == "equip")
        {
            handleEquipCommand();
        }
        else if (command == "unequip")
        {
            handleUnequipCommand();
        }
        else if (command == "debug")
        {
            handleDebugCommand();
        }
        else if (command == "save") 
        { 
            handleSaveCommand(); 
        }
        else if (command == "load") 
        { 
            handleLoadCommand(); 
        }
        else if (command.empty())
        {
            // ignore blank line
        }
        else
        {
            cout << "Unknown command. Type 'help' for a list.\n";
        }
    }
    cout << "Game ended. Final player state:\n";
    player.printPlayer();
}

void Game::handleSaveCommand()
{
    std::string path;
    std::cout << "Save file name (e.g. save1): ";
    std::getline(std::cin, path);
    if (path.empty()) { std::cout << "Canceled.\n"; return; }
    path.append(".json");

    if (SaveLoad::saveToFile(player, path))
        std::cout << "Saved to " << path << "\n";
    else
        std::cout << "Save failed.\n";
}

void Game::handleLoadCommand()
{
    std::string path;
    std::cout << "Load file name (e.g. save1): ";
    std::getline(std::cin, path);
    if (path.empty()) { std::cout << "Canceled.\n"; return; }
    path.append(".json");

    Player loaded;
    if (SaveLoad::loadFromFile(loaded, path)) {
        player = std::move(loaded);
        std::cout << "Loaded from " << path << "\n";
        player.printPlayer();
        player.getInventory().printInventory();
    }
    else {
        std::cout << "Load failed.\n";
    }
}