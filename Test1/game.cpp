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
        cout << "Enter a slot number to equip item: ";
        for (int i = 1; i < itemSlotToIndex(Item::ItemSlot::COUNT); i++) cout << Item::itemSlotToString.at(itemSlotFromIndex(i)) << "[" << i << "], ";
        cout << "or cancel[0]: ";

        std::getline(std::cin, slot);
        slot = toLowerCopy(slot);
        try
        {
            slotInput = std::stoi(slot);
            if (slotInput > 0 && slotInput < itemSlotToIndex(Item::ItemSlot::COUNT))
            {
                filteredList.clear();
                filteredList = player.getPlayerInventory().filterInventoryBySlot(itemSlotFromIndex(slotInput));

                if (!filteredList.empty())
                {
                cout << "Choose an item from the list to equip: " << endl;
                int count = 0;
                    for (Item item : filteredList)
                    {
                        count++;
                        cout << item.itemRarityToString.at(item.getItemRarity()) << " " << item.getItemName() << "[" << count << "]  " << endl;
                    }
                }
                else
                {
                    cout << "No " << Item::itemSlotToString.at(itemSlotFromIndex(slotInput)) << " items found in inventory." << endl;
                    return;
                }

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
                        player.equipItemFromInventory(filteredList[itemNameInput - 1].getId());
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
        cout << "Enter a slot number to unequip item: ";
        for (int i = 1; i < itemSlotToIndex(Item::ItemSlot::COUNT); i++) cout << Item::itemSlotToString.at(itemSlotFromIndex(i)) << "[" << i << "], ";
        cout << "or cancel[0]: ";
        std::getline(std::cin, slot);
        slot = toLowerCopy(slot);

        try
        {
            slotInput = std::stoi(slot);
            
            if (slotInput > 0 && slotInput < itemSlotToIndex(Item::ItemSlot::COUNT))
            {
                player.unequipItem(itemSlotFromIndex(slotInput));
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
                    player.setBaseStats(player.getBaseHealth(), player.getCurrentHealth(), newBaseAttack, player.getBaseDefense());
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
                    player.setBaseStats(player.getBaseHealth(), player.getCurrentHealth(), player.getBaseAttack(), newBaseDefense);
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
                    player.setBaseStats(newBaseHealth, player.getCurrentHealth(), player.getBaseAttack(), player.getBaseDefense());
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
    Game::enemy = gameActions.spawnEnemy(Enemy::EnemyType::SLIME);
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
            player.getPlayerInventory().printInventory();
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
        player.updateMaxStats();
        player.printPlayer();
        player.getPlayerInventory().printInventory();
    }
    else {
        std::cout << "Load failed.\n";
    }
}

void Game::handleFightCommand()
{
    string command;
    int commandInput;
    if (!enemy.isAlive())
    {
        enemy = gameActions.spawnEnemy(Enemy::EnemyType::SLIME);
        cout << "An enemy has been created. ";
    }
    while (enemy.isAlive() && player.isAlive())
    {
        enemy.printEnemy();
        cout << "Attack ? Yes[1] No[2] \n";
        std::getline(std::cin, command);
        command = toLowerCopy(command);
        try
        {
            commandInput = std::stoi(command);
            if (commandInput == 1)
            {
                int playerDamage = gameActions.playerAttack(enemy, player);
                cout << "You attack the enemy for " << playerDamage << " damage! \n";
                enemy.setCurrentHealth(enemy.getCurrentHealth() - playerDamage);
                if (enemy.getCurrentHealth() > 0)
                {
                    int enemyDamage = gameActions.enemyAttack(enemy, player);
                    cout << "The enemy attacks you for " << enemyDamage << " damage! \n";
                    player.changeCurrentHealth(0 - enemyDamage);
                    player.quickPrintPlayer();
                }
                else
                {
                    enemy.setCurrentHealth(0);
                    enemy.setAlive(false);
                    cout << "You killed the enemy!\n";
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

        if (player.getCurrentHealth() <= 0)
        {
            cout << "You died. So sad.\n";
            player.setAlive(false);
        }
    }  
}