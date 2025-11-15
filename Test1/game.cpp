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
    cout << "Enter a slot number to equip item: ";
    for (int i = 2; i < itemSlotToIndex(Item::ItemSlot::COUNT); i++)
    {
        cout << Item::itemSlotToString.at(itemSlotFromIndex(i)) << "[" << i - 1 << "], ";
    }
    cout << "or cancel[0]: " << std::endl;
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

        if (equipCandidates.empty() || slot == Item::ItemSlot::EMPTY || slot == Item::ItemSlot::CONSUMABLE)
        {
            cout << "No " << Item::itemSlotToString.at(itemSlotFromIndex(_slotNumber)) << " items found in inventory." << endl;
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
            mode = Mode::EquipSelectItem;
        }

        //selectedSlotIndex = _slotNumber; // what do?
        
    }  
}

void Game::handleEquipItemInput(int _itemNumber)
{
    if (_itemNumber == 0)
    {
        mode = Mode::Normal;
        equipCandidates.clear();
        return;
    }
    else if (_itemNumber > static_cast<int>(equipCandidates.size()))
    {
        std::cout << "Invalid choice.\n";
        return;
    }
    else
    {
        const Item& chosen = equipCandidates[_itemNumber - 1];
        player.equipItemFromInventory(chosen.getId());
        cout << "Updated player:\n";
        player.printPlayer();
        equipCandidates.clear();
        mode = Mode::Normal;
    } 
}

void Game::startUnequip()
{
    mode = Mode::UnequipSelectSlot;
    //selectedSlotIndex = -1;
    cout << "Enter a slot number to unequip an item from: ";
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
        cout << "Unequip canceled." << endl;
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
        player.unequipItem(slot);
        cout << "Updated player:\n";
        player.printPlayer();
        mode = Mode::Normal;
    }  
}

void Game::startDebug()
{

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

//void Game::handleDebugCommand()
//{
//    std::string command;
//    int commandInput = 0;
//    cout << "Select a variable to change name[1] " << player.getName() << ", base attack[2] " << player.getBaseAttack() << ", base defense[3] " << player.getBaseDefense() << ",or base health[4] " << player.getBaseHealth() << "." << endl;
//     cout <<"You can also add to[5], or remove from[6], your inventory, or cancel[0]: ";
//    std::getline(std::cin, command);
//    command = toLowerCopy(command);
//
//    try
//    {
//        commandInput = std::stoi(command);
//
//        //Setting new name
//        if (commandInput == 1)
//        {
//            changeName();
//        }
//        //Setting new base attack
//        else if (commandInput == 2)
//        {
//            changeBaseAttack();
//        }
//        //Setting new base defense
//        else if (commandInput == 3)
//        {
//            changeBaseDefense();
//        }
//        //Setting new base health
//        else if (commandInput == 4)
//        {
//            changeBaseHealth();
//        }
//        else if (commandInput == 5)
//        {
//            addToInventory();
//        }
//        else if (commandInput == 6)
//        {
//            removeFromInventory();
//        }
//        else if (commandInput == 0) return;
//        else
//        {
//            cout << "Unknown command. Type 'h' for a list of available commands.\n";
//        }
//    }
//    catch (...)
//    {
//        cout << "Unknown command. Type 'h' for a list of available commands.\n";
//    }
//}

void Game::loop(Player _player,const std::array<vector<Item>, itemSlotToIndex(Item::ItemSlot::COUNT)>& _gameItems)
{
    Game game;

    sf::Clock clock;

    game.player = _player;
    game.gameItems = _gameItems;
    game.enemy = gameActions.spawnEnemy(Enemy::EnemyType::SLIME);

    float windowWidth = 800;
    float windowHeight = 800;
    sf::RenderWindow window(sf::VideoMode({ (unsigned)windowWidth, (unsigned)windowHeight }), "Play Coding");
    cout << "---- Game loop started ----" << endl;
    cout << "Type 'h' to see available commands.\n";
    cout << endl;
    window.setKeyRepeatEnabled(false);


    while (window.isOpen() && mode != Mode::Quit)
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            game.handleEvent(*event);
            /*else if (auto* key = event->getIf<sf::Event::KeyPressed>())
            { 
                    if (key->scancode == sf::Keyboard::Scancode::Q)
                    {
                        cout << "Exiting game.\n";
                        cout << "Game ended. Final player state:\n";
                        player.printPlayer();
                        window.close();
                        break;
                    }
                    else if (key->scancode == sf::Keyboard::Scancode::H)
                    {
                        printHelp();
                    }
                    else if (key->scancode == sf::Keyboard::Scancode::C)
                    {
                        player.printPlayer();
                    }
                    else if (key->scancode == sf::Keyboard::Scancode::I)
                    {
                        player.getPlayerInventory().printInventory();
                    }
                    else if (key->scancode == sf::Keyboard::Scancode::E)
                    {
                        startEquip();
                    }
                    else if (key->scancode == sf::Keyboard::Scancode::U)
                    {
                        handleUnequipCommand();
                    }
                    else if (key->scancode == sf::Keyboard::Scancode::D)
                    {
                        handleDebugCommand();
                    }
                    else if (key->scancode == sf::Keyboard::Scancode::S)
                    {
                        handleSaveCommand();
                    }
                    else if (key->scancode == sf::Keyboard::Scancode::L)
                    {
                        handleLoadCommand();
                    }
                    else if (key->scancode == sf::Keyboard::Scancode::F)
                    {
                        handleFightCommand();
                    }       
            }*/
            
        }
        /*if (mode == Mode::EquipSelectSlot)
        {
            std::string slot;
            if (std::getline(std::cin, slot))
            {
                handleEquipSlotInput(slot);
            }
        }
        else if (mode == Mode::EquipSelectItem)
        {
            std::string choice;
            if (std::getline(std::cin, choice))
            {
                handleEquipItemInput(choice);
            }
        }*/
        //float dt = clock.restart().asSeconds();
        //game.update(dt);

        window.clear();
        //game.draw(window);
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
        if (mode == Mode::Normal)
        {
            switch (key->scancode)
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
            switch (key->scancode)
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
            default: {  break; } 
            }
        }
        else if (mode == Mode::EquipSelectItem)
        {
            switch (key->scancode)
            {
            case sf::Keyboard::Scancode::Num0: { handleEquipItemInput(0); break; }
            case sf::Keyboard::Scancode::Num1: { handleEquipItemInput(1); break; }
            case sf::Keyboard::Scancode::Num2: { handleEquipItemInput(2); break; }
            case sf::Keyboard::Scancode::Num3: { handleEquipItemInput(3); break; }
            case sf::Keyboard::Scancode::Num4: { handleEquipItemInput(4); break; }
            case sf::Keyboard::Scancode::Num5: { handleEquipItemInput(5); break; }
            case sf::Keyboard::Scancode::Num6: { handleEquipItemInput(6); break; }
            case sf::Keyboard::Scancode::Num7: { handleEquipItemInput(7); break; }
            case sf::Keyboard::Scancode::Num8: { handleEquipItemInput(8); break; }
            case sf::Keyboard::Scancode::Num9: { handleEquipItemInput(9); break; }
            default: { break; }
            }
        }
        else if (mode == Mode::UnequipSelectSlot)
        {
            switch (key->scancode)
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
    }

    if (auto* mousePressed = _event.getIf<sf::Event::MouseButtonPressed>())
    {
        // handle clicking on on-screen buttons here
        //handleMouseClick(event.mouseButton);
    }
}
