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
    cout << "  [h]elp        - show this help\n";
    cout << "  [s]tats       - show player stats and equipment\n";
    cout << "  [i]nventory   - show inventory\n";
    cout << "  [e]quip       - equip an item from inventory\n";
    cout << "  [u]nequip     - unequip an item back to inventory\n";
    cout << "  [d]ebug       - change base player variables\n";
    cout << "  s[a]ve        - save player stats and items\n";
    cout << "  [l]oad        - load player stats and items\n";
    cout << "  [q]uit        - exit game\n";
    cout << "  [f]ight       - spawn a slime and fight it\n";
}

void Game::handleEquipCommand()
{
    std::string slot;
    int slotInput;
    std::string itemName;
    int itemNameInput;
    bool slotFound = false;
    vector<Item> filteredList;

    while (!slotFound)
    {
        cout << "Enter slot number: helmet[1], chestpiece[2], pants[3], boots[4], shield[5], sword[6], or cancel[0]: ";
        std::getline(std::cin, slot);
        slot = toLowerCopy(slot);
        try
        {
            slotInput = std::stoi(slot);
            if (slotInput > 0 && slotInput < 7)
            {
                filteredList.clear();
                switch (slotInput)
                {
                case 1: filteredList = player.getInventory().filterInventoryBySlot(Item::ItemSlot::HELMET); break;
                case 2: filteredList = player.getInventory().filterInventoryBySlot(Item::ItemSlot::CHESTPIECE); break;
                case 3: filteredList = player.getInventory().filterInventoryBySlot(Item::ItemSlot::PANTS); break;
                case 4: filteredList = player.getInventory().filterInventoryBySlot(Item::ItemSlot::BOOTS); break;
                case 5: filteredList = player.getInventory().filterInventoryBySlot(Item::ItemSlot::SHIELD); break;
                case 6: filteredList = player.getInventory().filterInventoryBySlot(Item::ItemSlot::SWORD); break;
                default:;
                }

                
                cout << "Choose an item from the list to equip: " << endl;
                int count = 0;
                if (!filteredList.empty())
                {
                    for (Item item : filteredList)
                    {
                        count++;
                        cout << item.itemRarityToString.at(item.getItemRarity()) << " " << item.getItemName() << "[" << count << "]  " << endl;
                    }
                }
                else return;

                std::getline(std::cin, itemName);
                itemName = toLowerCopy(itemName);

                try
                {
                    itemNameInput = std::stoi(itemName);

                    if (itemNameInput < 1 || itemNameInput > filteredList.size())
                    {
                        std::cout << "Invalid number. Please try again.\n";
                    }
                    else
                    {
                        player.equipFromInventory(filteredList[itemNameInput - 1]);
                        cout << "Updated player:\n";
                        player.printPlayer();
                        slotFound = true;
                    }
                    
                }
                catch (...)
                {
                    std::cout << "Invalid number. Please try again.\n";
                }
                
            }
            else if (slotInput == 0)
            {
                slotFound = true;
            }
            else
                cout << "Unknown slot. Please try again.\n";
        }
        catch (...)
        {
            cout << "Unknown slot. Please try again.\n";
        }
    } 
    filteredList.clear();
}

void Game::handleUnequipCommand()
{
    std::string slot;
    int slotInput;
    bool slotFound = false;

    while (!slotFound)
    {
        cout << "Enter slot number to unequip: helmet[1], chestpiece[2], pants[3], boots[4], shield[5], sword[6], or cancel[0]: ";
        std::getline(std::cin, slot);
        slot = toLowerCopy(slot);

        try
        {
            slotInput = std::stoi(slot);
            if (slotInput > 0 && slotInput < 7)
            {
                switch (slotInput)
                {
                case 1: player.setItem(Item(), Item::ItemSlot::HELMET); break;
                case 2: player.setItem(Item(), Item::ItemSlot::CHESTPIECE); break;
                case 3: player.setItem(Item(), Item::ItemSlot::PANTS); break;
                case 4: player.setItem(Item(), Item::ItemSlot::BOOTS); break;
                case 5: player.setItem(Item(), Item::ItemSlot::SHIELD); break;
                case 6: player.setItem(Item(), Item::ItemSlot::SWORD); break;
                default:;
                }
                cout << "Updated player:\n";
                player.printPlayer();
                slotFound = true;
            }
            else if (slotInput == 0)
            {
                slotFound = true;
            }
            else
                cout << "Unknown slot. Please try again.\n";
        }
        catch (...)
        {
            cout << "Unknown slot. Please try again.\n";
        } 
    }
}

void Game::handleDebugCommand()
{
    std::string command;
    int commandInput = 0;
    cout << "Select a variable to change: name[1]: " << player.getName() << ", base attack[2]: "<< player.getBaseAttack() << ", base defense[3]: "<< player.getBaseDefense() << ", base health[4]: " << player.getBaseHealth() << ", or cancel[0]: ";
    std::getline(std::cin, command);
    command = toLowerCopy(command);

    try
    {
        commandInput = std::stoi(command);

        //Setting new name
        if (commandInput == 1)
        {
            std::string newName;
            cout << "Set New Name: ";
            std::getline(std::cin, newName);
            player.setName(newName);

            cout << "Updated player:\n";
            player.printPlayer();
        }
        //Setting new base attack
        else if (commandInput == 2)
        {
            int newBaseAttack = player.getBaseAttack();
            string input;
            while (true)
            {
                cout << "Set new base attack, or type c to cancel: ";
                std::getline(std::cin, input);
                input = toLowerCopy(input);
                if (input == "c") break;

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
                    std::cout << "Invalid number. Please try again.\n";
                }
            }

        }
        //Setting new base defense
        else if (commandInput == 3)
        {
            int newBaseDefense = player.getBaseDefense();
            string input;
            while (true)
            {
                cout << "Set new base defense, or type c to cancel: ";
                std::getline(std::cin, input);
                input = toLowerCopy(input);
                if (input == "c") break;
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
                    std::cout << "Invalid number. Please try again.\n";
                }
            }
        }
        //Setting new base health
        else if (commandInput == 4)
        {
            int newBaseHealth = player.getBaseHealth();
            string input;
            while (true)
            {
                cout << "Set new base health, or type c to cancel: ";
                std::getline(std::cin, input);
                input = toLowerCopy(input);
                if (input == "c") break;
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
                    std::cout << "Invalid number. Please try again.\n";
                }
            }
        }
        else if (commandInput == 0) return;
        else
        {
            cout << "Unknown command. Type 'h' for a list of available commands.\n";
        }
    }
    catch (...)
    {
        cout << "Unknown command. Type 'h' for a list of available commands.\n";
    }
}

void Game::loop(Player _player)
{
    Game::player = _player;
    Game::slimeEnemy = createSlimeEnemy();
    cout << "---- Game loop started ----" << endl;
    cout << "Type 'h' to see available commands.\n";

    std::string command;

    while (player.isAlive())
    {
        cout << "\n> ";
        if (!std::getline(std::cin, command))
            break; // EOF or input error

        command = toLowerCopy(command);

        if (command == "quit" || command == "q")
        {
            cout << "Exiting game.\n";
            break;
        }
        else if (command == "help" || command == "h")
        {
            printHelp();
        }
        else if (command == "stats" || command == "s")
        {
            player.printPlayer();
        }
        else if (command == "inventory" || command == "i")
        {
            player.getInventory().printInventory();
        }
        else if (command == "equip" || command == "e")
        {
            handleEquipCommand();
        }
        else if (command == "unequip" || command == "u")
        {
            handleUnequipCommand();
        }
        else if (command == "debug" || command == "d")
        {
            handleDebugCommand();
        }
        else if (command == "save" || command == "a")
        { 
            handleSaveCommand(); 
        }
        else if (command == "load" || command == "l")
        { 
            handleLoadCommand(); 
        }
        else if (command == "fight" || command == "f")
        {
            handleFightCommand();
        }
        else if (command.empty())
        {
            // ignore blank line
        }
        else
        {
            cout << "Unknown command. Type 'h' for a list of available commands.\n";
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

Enemy Game::createSlimeEnemy()
{
    Enemy enemyOne("King Slime", 1000, 50, 40);
    return enemyOne;
}

void Game::handleFightCommand()
{
    string command;
    int commandInput;
    if (!slimeEnemy.isAlive())
    {
        slimeEnemy = createSlimeEnemy();
        cout << "A slime has been created. ";
    }
    while (slimeEnemy.isAlive() && player.isAlive())
    {
        slimeEnemy.printEnemy();
        cout << "Attack ? Yes[1] No[2] \n";
        std::getline(std::cin, command);
        command = toLowerCopy(command);
        try
        {
            commandInput = std::stoi(command);
            if (commandInput == 1)
            {
                cout << "You attack the slime for " << attacking(slimeEnemy, player) << " damage! \n";
                slimeEnemy.setBaseHealth(slimeEnemy.getBaseHealth() - attacking(slimeEnemy, player));
                if (slimeEnemy.getBaseHealth() > 0)
                {
                    cout << "The slime attacks you for " << defending(slimeEnemy, player) << " damage! \n";
                    player.setBaseStats(player.getBaseHealth() - defending(slimeEnemy, player), player.getBaseAttack(), player.getBaseDefense());
                    player.quickPrintPlayer();
                }
                else
                {
                    slimeEnemy.setBaseHealth(0);
                    slimeEnemy.setAlive(false);
                    cout << "You killed the slime!\n";
                    //slimeEnemy.~Enemy();
                    return;
                }
            }
            else if (commandInput == 2)
            {
                return;
            }
            else
            {
                std::cout << "Invalid number. Please try again.\n";
            }
        }
        catch (...)
        {
            std::cout << "unknown command. Please try again.\n";
        }
        if (player.getTotalHealth() <= 0)
        {
            cout << "You died. So sad.\n";
            player.setAlive(false);
        }
    }  
}

int Game::attacking(const Enemy& _enemy, const Player& _player)
{
    if (_enemy.getBaseDefense() >= _player.getTotalAttack()) return 0;
    else return _player.getTotalAttack() - _enemy.getBaseDefense();
}

int Game::defending(const Enemy& _enemy, const Player& _player)
{
    if (_player.getTotalDefense() >= _enemy.getBaseAttack()) return 0;
    else return _enemy.getBaseAttack() - _player.getTotalDefense();
}