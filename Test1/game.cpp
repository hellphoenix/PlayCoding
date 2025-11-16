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
    cout << "  [c]haracter   - show player stats and equipment\n";
    cout << "  [i]nventory   - show inventory\n";
    cout << "  [e]quip       - equip an item from inventory\n";
    cout << "  [u]nequip     - unequip an item back to inventory\n";
    cout << "  [d]ebug       - change base player variables, or add items from the master item table to your inventory\n";
    cout << "  [s]ave        - save player stats and items\n";
    cout << "  [l]oad        - load player stats and items\n";
    cout << "  [q]uit        - exit game\n";
    cout << "  [f]ight       - spawn a slime and fight it\n";
    cout << endl;
}

void Game::startEquip()
{
    mode = Mode::EquipSelectSlot;
    //selectedSlotIndex = -1;
    cout << "\nEnter a slot number to equip item: ";
    for (int i = 2; i < itemSlotToIndex(Item::ItemSlot::COUNT); i++)
    {
        cout << Item::itemSlotToString.at(itemSlotFromIndex(i)) << "[" << i - 1 << "], ";
    }
    cout << "or cancel[0]: \n" << std::endl;
}

void Game::handleEquipSlotInput(int _slotNumber)
{
    
    if (_slotNumber == 0)
    {
        cout << "Equip canceled." << endl;
        mode = Mode::Normal;
        return;
    }
    else if (_slotNumber >= itemSlotToIndex(Item::ItemSlot::COUNT))
    {
        std::cout << "Invalid choice.\n";
        return;
    }
    else
    {
        Item::ItemSlot slot = itemSlotFromIndex(_slotNumber + 1);

        equipCandidates = player.getPlayerInventory().filterInventoryBySlot(slot);

        cout << "Getting inverntory in the chosen slot." << endl;

        if (equipCandidates.empty())
        {
            cout << "No " << Item::itemSlotToString.at(slot) << " items found in inventory." << endl;
            cout << "Type 'h' to see available commands.\n";
            mode = Mode::Normal;
            return;
        }
        else if (slot == Item::ItemSlot::EMPTY || slot == Item::ItemSlot::CONSUMABLE)
        {
            cout << Item::itemSlotToString.at(slot) << " items are not equippable." << endl;
            cout << "Type 'h' to see available commands.\n";
            mode = Mode::Normal;
            return;
        }
        else
        {
            cout << "Choose an item from the list to equip: " << endl;
            int count = 0;
            for (Item item : equipCandidates)
            {
                count++;
                cout << item.itemRarityToString.at(item.getItemRarity()) << " " << item.getItemName() << "[" << count << "]  " << endl;
            }
            
            pendingEquipSelectItem = true;
        }
    }  
}

void Game::handleEquipItemInput(const sf::Event::TextEntered& _text)
{
    if (mode == Mode::EquipSelectItem)
    {
        if (_text.unicode == '\r' || _text.unicode == '\n')
        {
            if (!textBuffer.empty())
            {
                int newItem = stoi(textBuffer);

                if (newItem == 0)
                {
                    mode = Mode::Normal;
                    equipCandidates.clear();
                    std::cout << "\nEquip canceled.\n";
                    cout << "Type 'h' to see available commands.\n";
                    return;
                }
                else if (newItem > static_cast<int>(equipCandidates.size()))
                {
                    textBuffer.clear();
                    std::cout << "\nInvalid choice.\n";
                    return;
                }
                else
                {
                    const Item& chosen = equipCandidates[newItem - 1];
                    player.equipItemFromInventory(chosen.getId());
                    cout << "\nUpdated player:\n";
                    player.printPlayer();
                    
                }               
                std::cout << endl;
                cout << "Type 'h' to see available commands.\n";
            }
            textBuffer.clear();
            equipCandidates.clear();
            mode = Mode::Normal;
            return;
        }

        else if (_text.unicode == 27) // Escape
        {
            textBuffer.clear();
            equipCandidates.clear();
            mode = Mode::Normal;
            std::cout << "\nEquip canceled.\n";
            cout << "Type 'h' to see available commands.\n";
            return;
        }

        else if (_text.unicode == 8) // Backspace
        {
            if (!textBuffer.empty())
                textBuffer.pop_back();
            return;
        }

        else if (_text.unicode < 48 || _text.unicode > 57)
            return;

        textBuffer.push_back(static_cast<char>(_text.unicode));
        cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
        // You can draw this on screen instead of printing
    }
}

void Game::startUnequip()
{
    mode = Mode::UnequipSelectSlot;
    //selectedSlotIndex = -1;
    cout << "\nEnter a slot number to unequip an item from: ";
    for (int i = 2; i < itemSlotToIndex(Item::ItemSlot::COUNT); i++)
    {
        cout << Item::itemSlotToString.at(itemSlotFromIndex(i)) << "[" << i - 1 << "], ";
    }
    cout << "or cancel[0]: " << std::endl;
}

void Game::handleUnequipSlotInput(int _slotNumber)
{
    if (_slotNumber == 0)
    {
        cout << "\nUnequip canceled.\n" << endl;
        mode = Mode::Normal;
        return;
    }
    else if (_slotNumber >= itemSlotToIndex(Item::ItemSlot::COUNT))
    {
        std::cout << "\nInvalid choice.\n";
        return;
    }
    else
    {
        Item::ItemSlot slot = itemSlotFromIndex(_slotNumber + 1);
        player.unequipItem(slot);
        cout << "\nUpdated player:\n";
        player.printPlayer();
        mode = Mode::Normal;
    }  
}

void Game::startDebug()
{
    mode = Mode::DebugSelect;
    cout << "Select a variable to change name[1] " << player.getName() << ", base attack[2] " << player.getBaseAttack() << ", base defense[3] " << player.getBaseDefense() << ",or base health[4] " << player.getBaseHealth() << "." << endl;
    cout << "You can also add to[5], or remove from[6], your inventory, or cancel[0]:\n";
}

void Game::startDebugName()
{
    textBuffer.clear();
    cout << "Enter new name (Enter to confirm, Esc to cancel):\n";
    mode = Mode::DebugName;
}

void Game::debugName(const sf::Event::TextEntered& _text)
{

    if (mode == Mode::DebugName)
    {
        if (_text.unicode == '\r' || _text.unicode == '\n')
        {
            if (!textBuffer.empty())
            {
                player.setName(textBuffer);
                std::cout << "\nNew name: " << textBuffer << "\n";
                std::cout << endl;
                cout << "Type 'h' to see available commands.\n";
            }
            textBuffer.clear();
            mode = Mode::Normal;
            return;
        }

        else if (_text.unicode == 27) // Escape
        {
            textBuffer.clear();
            mode = Mode::Normal;
            std::cout << "\nName change canceled.\n";
            return;
        }

        else if (_text.unicode == 8) // Backspace
        {
            if (!textBuffer.empty())
                textBuffer.pop_back();
            return;
        }

        else if (_text.unicode < 32 || _text.unicode > 126)
            return;

        textBuffer.push_back(static_cast<char>(_text.unicode));
        cout << "\rNew name: " << textBuffer << " " << std::flush;
        // You can draw this on screen instead of printing
    }
}

void Game::startDebugAttack()
{
    textBuffer.clear();
    cout << "Enter new base attack value (Enter to confirm, Esc to cancel):\n";
    mode = Mode::DebugAttack;
}

void Game::debugAttack(const sf::Event::TextEntered& _text)
{
    if (mode == Mode::DebugAttack)
    {
        if (_text.unicode == '\r' || _text.unicode == '\n')
        {
            if (!textBuffer.empty())
            {
                int newAttack = stoi(textBuffer);
                player.setBaseAttack(newAttack);
                player.updateMaxStats();
                std::cout << "\nNew base attack set: " << newAttack << "\n";
                std::cout << endl;
                cout << "Type 'h' to see available commands.\n";
            }
            textBuffer.clear();
            mode = Mode::Normal;
            return;
        }

        else if (_text.unicode == 27) // Escape
        {
            textBuffer.clear();
            mode = Mode::Normal;
            std::cout << "\nBase Attack change canceled.\n";
            return;
        }

        else if (_text.unicode == 8) // Backspace
        {
            if (!textBuffer.empty())
                textBuffer.pop_back();
            return;
        }

        else if (_text.unicode < 48 || _text.unicode > 57)
            return;

        textBuffer.push_back(static_cast<char>(_text.unicode));
        cout << "\rNew base attack: " << textBuffer << " " << std::flush;
        // You can draw this on screen instead of printing
    }
}

void Game::startDebugDefense()
{
    textBuffer.clear();
    cout << "Enter new base defense value (Enter to confirm, Esc to cancel):\n";
    mode = Mode::DebugDefense;
}

void Game::debugDefense(const sf::Event::TextEntered& _text)
{
    if (mode == Mode::DebugDefense)
    {
        if (_text.unicode == '\r' || _text.unicode == '\n')
        {
            if (!textBuffer.empty())
            {
                int newDefense = stoi(textBuffer);
                player.setBaseDefense(newDefense);
                player.updateMaxStats();
                std::cout << "\nNew base defense set: " << newDefense << "\n";
                std::cout << endl;
                cout << "Type 'h' to see available commands.\n";
            }
            textBuffer.clear();
            mode = Mode::Normal;
            return;
        }

        else if (_text.unicode == 27) // Escape
        {
            textBuffer.clear();
            mode = Mode::Normal;
            std::cout << "\nBase Defense change canceled.\n";
            return;
        }

        else if (_text.unicode == 8) // Backspace
        {
            if (!textBuffer.empty())
                textBuffer.pop_back();
            return;
        }

        else if (_text.unicode < 48 || _text.unicode > 57)
            return;

        textBuffer.push_back(static_cast<char>(_text.unicode));
        cout << "\rNew base defense: " << textBuffer << " " << std::flush;
        // You can draw this on screen instead of printing
    }
}

void Game::startDebugHealth()
{
    textBuffer.clear();
    cout << "Enter new base health value (Enter to confirm, Esc to cancel):\n";
    mode = Mode::DebugHealth;
}

void Game::debugHealth(const sf::Event::TextEntered& _text)
{
    if (mode == Mode::DebugHealth)
    {
        if (_text.unicode == '\r' || _text.unicode == '\n')
        {
            if (!textBuffer.empty())
            {
                int newHealth = stoi(textBuffer);
                player.setBaseHealth(newHealth);
                player.updateMaxStats();
                std::cout << "\nNew base health set: " << newHealth << "\n";
                std::cout << endl;
                cout << "Type 'h' to see available commands.\n";
            }
            textBuffer.clear();
            mode = Mode::Normal;
            return;
        }

        else if (_text.unicode == 27) // Escape
        {
            textBuffer.clear();
            mode = Mode::Normal;
            std::cout << "\nBase Health change canceled.\n";
            return;
        }

        else if (_text.unicode == 8) // Backspace
        {
            if (!textBuffer.empty())
                textBuffer.pop_back();
            return;
        }

        else if (_text.unicode < 48 || _text.unicode > 57)
            return;

        textBuffer.push_back(static_cast<char>(_text.unicode));
        cout << "\rNew base health: " << textBuffer << " " << std::flush;
        // You can draw this on screen instead of printing
    }
}

void Game::startDebugAddToInventory()
{
    mode = Mode::DebugAddToInventorySlot;
    cout << "Enter a slot number to search master item list for: ";
    for (int i = 2; i < itemSlotToIndex(Item::ItemSlot::COUNT); i++)
    {
        cout << Item::itemSlotToString.at(itemSlotFromIndex(i)) << "[" << i - 1 << "], ";
    }
    cout << "or cancel[0]: \n" << std::endl;
}

void Game::debugEquipmentSlotInput(int _slotNumber)
{
    if (_slotNumber == 0)
    {
        cout << "Debug canceled." << endl;
        mode = Mode::Normal;
        return;
    }
    else if (_slotNumber >= itemSlotToIndex(Item::ItemSlot::COUNT))
    {
        std::cout << "Invalid choice.\n";
        return;
    }
    else
    {
        Item::ItemSlot slot = itemSlotFromIndex(_slotNumber + 1);

        equipCandidates = gameItems[_slotNumber];

        cout << "Getting inverntory in the chosen slot." << endl;

        if (equipCandidates.empty())
        {
            cout << "No " << Item::itemSlotToString.at(slot) << " items found in master item list." << endl;
            cout << "Type 'h' to see available commands.\n";
            mode = Mode::Normal;
            return;
        }
        else if (slot == Item::ItemSlot::EMPTY || slot == Item::ItemSlot::CONSUMABLE)
        {
            cout << Item::itemSlotToString.at(slot) << " items are not equippable." << endl;
            cout << "Type 'h' to see available commands.\n";
            mode = Mode::Normal;
            return;
        }
        else
        {
            cout << "Choose an item from the filtered list to add to inventory: " << endl;
            int count = 0;
            for (Item item : equipCandidates)
            {
                count++;
                cout << item.itemRarityToString.at(item.getItemRarity()) << " " << item.getItemName() << "[" << count << "]  " << endl;
            }

            pendingDebugEquipmentSelection = true;
        }
    }
}

void Game::debugEquipmentItemInput(const sf::Event::TextEntered& _text)
{
    if (mode == Mode::DebugAddToInventoryItem)
    {
        if (_text.unicode == '\r' || _text.unicode == '\n')
        {
            if (!textBuffer.empty())
            {
                int newItem = stoi(textBuffer);

                if (newItem == 0)
                {
                    mode = Mode::Normal;
                    equipCandidates.clear();
                    std::cout << "\nDebug canceled.\n";
                    cout << "Type 'h' to see available commands.\n";
                    return;
                }
                else if (newItem > static_cast<int>(equipCandidates.size()))
                {
                    textBuffer.clear();
                    std::cout << "\nInvalid choice.\n";
                    return;
                }
                else
                {
                    const Item& chosen = equipCandidates[newItem - 1];
                    player.getPlayerInventory().addToInventory(chosen);
                    cout << "\nUpdated inventory:\n";
                    player.getPlayerInventory().printInventory();

                }
                std::cout << endl;
                cout << "Type 'h' to see available commands.\n";
            }
            textBuffer.clear();
            equipCandidates.clear();
            mode = Mode::Normal;
            return;
        }

        else if (_text.unicode == 27) // Escape
        {
            textBuffer.clear();
            equipCandidates.clear();
            mode = Mode::Normal;
            std::cout << "\nDebug canceled.\n";
            cout << "Type 'h' to see available commands.\n";
            return;
        }

        else if (_text.unicode == 8) // Backspace
        {
            if (!textBuffer.empty())
                textBuffer.pop_back();
            return;
        }

        else if (_text.unicode < 48 || _text.unicode > 57)
            return;

        textBuffer.push_back(static_cast<char>(_text.unicode));
        cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
        // You can draw this on screen instead of printing
    }
}

void Game::startSave()
{

}

void Game::startLoad()
{

}

void Game::Quit()
{
    cout << "Exiting game.\n";
    cout << "Game ended. Final player state:\n";
    player.printPlayer();
    mode = Mode::Quit;
}

void Game::startFight()
{

}

//void Game::handleEquipCommand()
//{
//    /*std::string slot;
//    int slotInput;
//    std::string itemName;
//    int itemNameInput;
//    bool slotFound = false;
//    vector<Item> filteredList;
//
//    cout << "Enter a slot number to equip item: ";
//    for (int i = 2; i < itemSlotToIndex(Item::ItemSlot::COUNT); i++)
//    {
//        cout << Item::itemSlotToString.at(itemSlotFromIndex(i)) << "[" << i - 1 << "], ";
//
//    }
//    cout << "or cancel[0]: ";
//    
//
//    while (!slotFound)
//    {
//        std::getline(std::cin, slot);
//        slot = toLowerCopy(slot);
//        try
//        {
//            slotInput = std::stoi(slot);
//            if (slotInput > 0 && slotInput < itemSlotToIndex(Item::ItemSlot::COUNT))
//            {
//                filteredList.clear();
//                filteredList = player.getPlayerInventory().filterInventoryBySlot(itemSlotFromIndex(slotInput + 1));
//
//                if (!filteredList.empty())
//                {
//                cout << "Choose an item from the list to equip: " << endl;
//                int count = 0;
//                    for (Item item : filteredList)
//                    {
//                        count++;
//                        cout << item.itemRarityToString.at(item.getItemRarity()) << " " << item.getItemName() << "[" << count << "]  " << endl;
//                    }
//                }
//                else
//                {
//                    cout << "No " << Item::itemSlotToString.at(itemSlotFromIndex(slotInput)) << " items found in inventory." << endl;
//                    return;
//                }
//
//                std::getline(std::cin, itemName);
//                itemName = toLowerCopy(itemName);
//
//                try
//                {
//                    itemNameInput = std::stoi(itemName);
//
//                    if (itemNameInput < 1 || itemNameInput > filteredList.size())
//                    {
//                        std::cout << "Invalid number. Please try again.\n";
//                    }
//                    else
//                    {
//                        player.equipItemFromInventory(filteredList[itemNameInput - 1].getId());
//                        cout << "Updated player:\n";
//                        player.printPlayer();
//                        slotFound = true;
//                    }  
//                }
//                catch (...)
//                {
//                    std::cout << "Invalid number. Please try again.\n";
//                } 
//            }
//            else if (slotInput == 0)
//            {
//                slotFound = true;
//            }
//            else
//                cout << "Unknown slot. Please try again.\n";
//        }
//        catch (...)
//        {
//            cout << "Unknown slot. Please try again.\n";
//        }
//    } 
//    filteredList.clear();*/
//}

void Game::loop(std::array<vector<Item>, itemSlotToIndex(Item::ItemSlot::COUNT)>& _gameItems)
{

    sf::Clock clock;
   
    enemy = gameActions.spawnEnemy(Enemy::EnemyType::SLIME);

    gameItems = _gameItems;
    giveStartingItems();

    float windowWidth = 800;
    float windowHeight = 800;
    sf::RenderWindow window(sf::VideoMode({ (unsigned)windowWidth, (unsigned)windowHeight }), "Play Coding");
    cout << "---- Game loop started ----" << endl;
    cout << "Type 'h' to see available commands.\n";
    cout << endl;
    //window.setKeyRepeatEnabled(false);


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>() || mode == Mode::Quit)
            {
                window.close();
            }

            handleEvent(*event);        
        }

        float dt = clock.restart().asSeconds();
        update(dt);

        window.clear();
        //draw(window);
        window.display();
    }  
}

//void Game::handleSaveCommand()
//{
//    std::string path;
//    std::cout << "Save file name (e.g. save1): ";
//    std::getline(std::cin, path);
//    if (path.empty()) { std::cout << "Canceled.\n"; return; }
//    path.append(".json");
//
//    if (SaveLoad::saveToFile(player, path))
//        std::cout << "Saved to " << path << "\n";
//    else
//        std::cout << "Save failed.\n";
//}
//
//void Game::handleLoadCommand()
//{
//    std::string path;
//    std::cout << "Load file name (e.g. save1): ";
//    std::getline(std::cin, path);
//    if (path.empty()) { std::cout << "Canceled.\n"; return; }
//    path.append(".json");
//
//    Player loaded;
//    if (SaveLoad::loadFromFile(loaded, path)) {
//        player = std::move(loaded);
//        std::cout << "Loaded from " << path << "\n";
//        player.updateMaxStats();
//        player.printPlayer();
//        player.getPlayerInventory().printInventory();
//    }
//    else {
//        std::cout << "Load failed.\n";
//    }
//}
//
//void Game::handleFightCommand()
//{
//    string command;
//    int commandInput;
//    if (!enemy.isAlive())
//    {
//        enemy = gameActions.spawnEnemy(Enemy::EnemyType::SLIME);
//        cout << "An enemy has been created. ";
//    }
//    while (enemy.isAlive() && player.isAlive())
//    {
//        enemy.printEnemy();
//        cout << "Attack ? Yes[1] No[2] \n";
//        std::getline(std::cin, command);
//        command = toLowerCopy(command);
//        try
//        {
//            commandInput = std::stoi(command);
//            if (commandInput == 1)
//            {
//                int playerDamage = gameActions.playerAttack(enemy, player);
//                cout << "You attack the enemy for " << playerDamage << " damage! \n";
//                enemy.setCurrentHealth(enemy.getCurrentHealth() - playerDamage);
//                if (enemy.getCurrentHealth() > 0)
//                {
//                    int enemyDamage = gameActions.enemyAttack(enemy, player);
//                    cout << "The enemy attacks you for " << enemyDamage << " damage! \n";
//                    player.changeCurrentHealth(0 - enemyDamage);
//                    player.quickPrintPlayer();
//                }
//                else
//                {
//                    enemy.setCurrentHealth(0);
//                    enemy.setAlive(false);
//                    cout << "You killed the enemy!\n";
//                    return;
//                }
//            }
//            else if (commandInput == 2)
//            {
//                return;
//            }
//            else
//            {
//                std::cout << "Invalid number. Please try again.\n";
//            }
//        }
//        catch (...)
//        {
//            std::cout << "unknown command. Please try again.\n";
//        }
//
//        if (player.getCurrentHealth() <= 0)
//        {
//            cout << "You died. So sad.\n";
//            player.setAlive(false);
//        }
//    }  
//}

//void Game::changeName()
//{
//    std::string newName;
//    cout << "Set New Name: ";
//    std::getline(std::cin, newName);
//    player.setName(newName);
//    
//
//    cout << "Updated player:\n";
//    player.printPlayer();
//}
//
//void Game::changeBaseAttack()
//{
//    int newBaseAttack = player.getBaseAttack();
//    string input;
//    while (true)
//    {
//        cout << "Set new base attack, or type c to cancel: ";
//        std::getline(std::cin, input);
//        input = toLowerCopy(input);
//        if (input == "c") break;
//
//        try
//        {
//            newBaseAttack = std::stoi(input);
//            player.setBaseStats(player.getBaseHealth(), player.getCurrentHealth(), newBaseAttack, player.getBaseDefense());
//            cout << "Updated player:\n";
//            player.printPlayer();
//            break;
//        }
//        catch (...)
//        {
//            std::cout << "Invalid number. Please try again.\n";
//        }
//    }
//}
//
//void Game::changeBaseDefense()
//{
//    int newBaseDefense = player.getBaseDefense();
//    string input;
//    while (true)
//    {
//        cout << "Set new base defense, or type c to cancel: ";
//        std::getline(std::cin, input);
//        input = toLowerCopy(input);
//        if (input == "c") break;
//        try
//        {
//            newBaseDefense = std::stoi(input);
//            player.setBaseStats(player.getBaseHealth(), player.getCurrentHealth(), player.getBaseAttack(), newBaseDefense);
//            cout << "Updated player:\n";
//            player.printPlayer();
//            break;
//        }
//        catch (...)
//        {
//            std::cout << "Invalid number. Please try again.\n";
//        }
//    }
//}
//
//void Game::changeBaseHealth()
//{
//    int newBaseHealth = player.getBaseHealth();
//    string input;
//    while (true)
//    {
//        cout << "Set new base health, or type c to cancel: ";
//        std::getline(std::cin, input);
//        input = toLowerCopy(input);
//        if (input == "c") break;
//        try
//        {
//            newBaseHealth = std::stoi(input);
//            player.setBaseStats(newBaseHealth, player.getCurrentHealth(), player.getBaseAttack(), player.getBaseDefense());
//            cout << "Updated player:\n";
//            player.printPlayer();
//            break;
//        }
//        catch (...)
//        {
//            std::cout << "Invalid number. Please try again.\n";
//        }
//    }
//}

//void Game::addToInventory()
//{
//    std::string slot;
//    int slotInput;
//    std::string itemName;
//    int itemNameInput;
//    bool slotFound = false;
//    vector<Item> filteredList;
//
//    while (!slotFound)
//    {
//        cout << "Enter a slot number to search for items: ";
//        for (int i = 2; i < itemSlotToIndex(Item::ItemSlot::COUNT); i++) cout << Item::itemSlotToString.at(itemSlotFromIndex(i)) << "[" << i - 1 << "], ";
//        cout << "or cancel[0]: ";
//
//        std::getline(std::cin, slot);
//        slot = toLowerCopy(slot);
//        try
//        {
//            slotInput = std::stoi(slot);
//            if (slotInput > 0 && slotInput < itemSlotToIndex(Item::ItemSlot::COUNT))
//            {
//                filteredList.clear();
//                filteredList = gameItems[slotInput];
//
//                if (!filteredList.empty())
//                {
//                    cout << "Choose an item from the list to add to inventory: " << endl;
//                    int count = 0;
//                    for (Item item : filteredList)
//                    {
//                        count++;
//                        cout << item.itemRarityToString.at(item.getItemRarity()) << " " << item.getItemName() << "[" << count << "]  " << endl;
//                    }
//                }
//                else
//                {
//                    cout << "No " << Item::itemSlotToString.at(itemSlotFromIndex(slotInput)) << " items found in inventory." << endl;
//                    return;
//                }
//
//                std::getline(std::cin, itemName);
//                itemName = toLowerCopy(itemName);
//
//                try
//                {
//                    itemNameInput = std::stoi(itemName);
//
//                    if (itemNameInput < 1 || itemNameInput > filteredList.size())
//                    {
//                        std::cout << "Invalid number. Please try again.\n";
//                    }
//                    else
//                    {
//                        player.getPlayerInventory().addToInventory(filteredList[itemNameInput - 1]);
//                        cout << "Updated inventory:\n";
//                        player.getPlayerInventory().printInventory();
//                        slotFound = true;
//                    }
//                }
//                catch (...)
//                {
//                    std::cout << "Invalid number. Please try again.\n";
//                }
//            }
//            else if (slotInput == 0)
//            {
//                slotFound = true;
//            }
//            else
//                cout << "Unknown slot. Please try again.\n";
//        }
//        catch (...)
//        {
//            cout << "Unknown slot. Please try again.\n";
//        }
//    }
//    filteredList.clear();
//}
//
//void Game::removeFromInventory()
//{
//    std::string itemName;
//    int itemNameInput;
//    vector<Item> playerInventory = player.getPlayerInventory().getInventory();
//    bool itemFound = false;
//
//    while (!itemFound)
//    {
//
//        cout << "Choose an item to remove from your inventory: ";
//        for (int i = 0; i < playerInventory.size(); i++) cout << playerInventory[i].getItemName() << "[" << i + 1 << "], ";
//        cout << "or cancel[0]: ";
//
//        std::getline(std::cin, itemName);
//        itemName = toLowerCopy(itemName);
//
//        try
//        {
//            itemNameInput = std::stoi(itemName);
//
//            if (itemNameInput > 0 && itemNameInput <= playerInventory.size())
//            {
//
//                player.getPlayerInventory().removeFromInventory(playerInventory[itemNameInput - 1].getId());
//                cout << "Updated inventory:\n";
//                player.getPlayerInventory().printInventory();
//                itemFound = true;
//            }
//            else if (itemNameInput == 0)
//            {
//
//            }
//            else
//                cout << "Unknown item. Please try again.\n";
//        }
//        catch (...)
//        {
//            cout << "Unknown item. Please try again.\n";
//        }
//    }
//}


void Game::handleEvent(const sf::Event& _event)
{
    if (auto* key = _event.getIf<sf::Event::KeyPressed>())
    {
        handleKeyPressed(*key);
    }
    else if (auto* text = _event.getIf<sf::Event::TextEntered>())
    {
        // Temporary debug: log every TextEntered event
        //std::cout << "TextEntered unicode: " << static_cast<int>(text->unicode) << "\n";
        switch (mode)
        {
            case Mode::EquipSelectItem:
            {
                handleEquipItemInput(*text);
                break;
            }
            case Mode::DebugName:
            {
                debugName(*text);
                break;
            }
            case Mode::DebugAttack:
            {
                debugAttack(*text);
                break;
            }
            case Mode::DebugDefense:
            {
                debugDefense(*text);
                break;
            }
            case Mode::DebugHealth:
            {
                debugHealth(*text);
                break;
            }
            case Mode::DebugAddToInventoryItem:
            {
                debugEquipmentItemInput(*text);
                break;
            }
        }
    }
    else if (auto* mousePressed = _event.getIf<sf::Event::MouseButtonPressed>())
    {
        // handle clicking on on-screen buttons here
        //handleMouseClick(event.mouseButton);
    }
}

void Game::handleKeyPressed(const sf::Event::KeyPressed& _keyPressed)
{
    if (mode == Mode::Normal)
    {
        switch (_keyPressed.scancode)
        {
        case sf::Keyboard::Scancode::H: { printHelp(); break; }
        case sf::Keyboard::Scancode::C: { player.printPlayer(); break; }
        case sf::Keyboard::Scancode::I: { player.getPlayerInventory().printInventory();; break; }
        case sf::Keyboard::Scancode::E: { startEquip(); break; }
        case sf::Keyboard::Scancode::U: { startUnequip(); break; }
        case sf::Keyboard::Scancode::D: { startDebug(); break; }
        case sf::Keyboard::Scancode::S: { startSave(); break; }
        case sf::Keyboard::Scancode::L: { startLoad(); break; }
        case sf::Keyboard::Scancode::Q: { Quit(); break; }
        case sf::Keyboard::Scancode::F: { startFight(); break; }
        default: { break; }
        }
    }
    else if (mode == Mode::EquipSelectSlot)
    {
        switch (_keyPressed.scancode)
        {
        case sf::Keyboard::Scancode::Num0: { handleEquipSlotInput(0); break; }
        case sf::Keyboard::Scancode::Num1: { handleEquipSlotInput(1); break; }
        case sf::Keyboard::Scancode::Num2: { handleEquipSlotInput(2); break; }
        case sf::Keyboard::Scancode::Num3: { handleEquipSlotInput(3); break; }
        case sf::Keyboard::Scancode::Num4: { handleEquipSlotInput(4); break; }
        case sf::Keyboard::Scancode::Num5: { handleEquipSlotInput(5); break; }
        case sf::Keyboard::Scancode::Num6: { handleEquipSlotInput(6); break; }
        case sf::Keyboard::Scancode::Num7: { handleEquipSlotInput(7); break; }
        case sf::Keyboard::Scancode::Num8: { handleEquipSlotInput(8); break; }
        case sf::Keyboard::Scancode::Num9: { handleEquipSlotInput(9); break; }
        default: { break; }
        }
    }
    else if (mode == Mode::UnequipSelectSlot)
    {
        switch (_keyPressed.scancode)
        {
        case sf::Keyboard::Scancode::Num0: { handleUnequipSlotInput(0); break; }
        case sf::Keyboard::Scancode::Num1: { handleUnequipSlotInput(1); break; }
        case sf::Keyboard::Scancode::Num2: { handleUnequipSlotInput(2); break; }
        case sf::Keyboard::Scancode::Num3: { handleUnequipSlotInput(3); break; }
        case sf::Keyboard::Scancode::Num4: { handleUnequipSlotInput(4); break; }
        case sf::Keyboard::Scancode::Num5: { handleUnequipSlotInput(5); break; }
        case sf::Keyboard::Scancode::Num6: { handleUnequipSlotInput(6); break; }
        case sf::Keyboard::Scancode::Num7: { handleUnequipSlotInput(7); break; }
        case sf::Keyboard::Scancode::Num8: { handleUnequipSlotInput(8); break; }
        case sf::Keyboard::Scancode::Num9: { handleUnequipSlotInput(9); break; }
        default: { break; }
        }
    }
    else if (mode == Mode::DebugSelect)
    {
        switch (_keyPressed.scancode)
        {
        case sf::Keyboard::Scancode::Num0: {
            cout << "Canceled debug mode" << endl;
            mode = Mode::Normal;
            break;
        }
        case sf::Keyboard::Scancode::Num1: { pendingDebugName = true; break; }
        case sf::Keyboard::Scancode::Num2: { pendingDebugAttack = true; break; }
        case sf::Keyboard::Scancode::Num3: { pendingDebugDefense = true; break; }
        case sf::Keyboard::Scancode::Num4: { pendingDebugHealth = true; break; }
        case sf::Keyboard::Scancode::Num5: { startDebugAddToInventory(); break; }
        case sf::Keyboard::Scancode::Num6: {  break; }
        default: { break; }
        }
    }
    else if (mode == Mode::DebugAddToInventorySlot)
    {
        switch (_keyPressed.scancode)
        {
        case sf::Keyboard::Scancode::Num0: { debugEquipmentSlotInput(0); break; }
        case sf::Keyboard::Scancode::Num1: { debugEquipmentSlotInput(1); break; }
        case sf::Keyboard::Scancode::Num2: { debugEquipmentSlotInput(2); break; }
        case sf::Keyboard::Scancode::Num3: { debugEquipmentSlotInput(3); break; }
        case sf::Keyboard::Scancode::Num4: { debugEquipmentSlotInput(4); break; }
        case sf::Keyboard::Scancode::Num5: { debugEquipmentSlotInput(5); break; }
        case sf::Keyboard::Scancode::Num6: { debugEquipmentSlotInput(6); break; }
        case sf::Keyboard::Scancode::Num7: { debugEquipmentSlotInput(7); break; }
        case sf::Keyboard::Scancode::Num8: { debugEquipmentSlotInput(8); break; }
        case sf::Keyboard::Scancode::Num9: { debugEquipmentSlotInput(9); break; }
        default: { break; }
        }
    }
}

void Game::update(float dt)
{
    if (pendingDebugName)
    {
        pendingDebugName = false;
        startDebugName();
    }
    else if (pendingDebugAttack)
    {
        pendingDebugAttack = false;
        startDebugAttack();
    }
    else if (pendingDebugDefense)
    {
        pendingDebugDefense = false;
        startDebugDefense();
    }
    else if (pendingDebugHealth)
    {
        pendingDebugHealth = false;
        startDebugHealth();
    }
    else if (pendingDebugEquipmentSelection)
    {
        pendingDebugEquipmentSelection = false;
        mode = Mode::DebugAddToInventoryItem;
    }
    else if (pendingEquipSelectItem)
    {
        pendingEquipSelectItem = false;
        mode = Mode::EquipSelectItem;
    }
}
