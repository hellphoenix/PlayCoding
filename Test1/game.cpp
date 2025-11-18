#include "game.h"
#include "gameInitialize.h"
#include "save_load.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>


void Game::printHelp() const
{
    std::cout << "Commands:\n";
    std::cout << "  [h]elp        - show this help\n";
    std::cout << "  [c]haracter   - show player stats and equipment\n";
    std::cout << "  [i]nventory   - show inventory\n";
    std::cout << "  [e]quip       - equip an item from inventory\n";
    std::cout << "  [u]nequip     - unequip an item back to inventory\n";
    std::cout << "  [d]ebug       - change base player variables, or add items from the master item table to your inventory\n";
    std::cout << "  [s]ave        - save player stats and items\n";
    std::cout << "  [l]oad        - load player stats and items\n";
    std::cout << "  [q]uit        - exit game\n";
    std::cout << "  [f]ight       - spawn a slime and fight it\n";
    std::cout << std::endl;
}

void Game::startEquip()
{
    mode = Mode::EquipSelectSlot;
    std::cout << "\nEnter a slot number to equip item: ";
    for (int i = 1; i < equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT); i++)
    {
        //std::cout << Item::itemSlotToString.at(itemSlotFromIndex(i)) << "[" << i << "], ";
        std::cout << Equipment::equipmentSlotToString.at(equipmentSlotFromIndex(i)) << "[" << i << "], ";
    }
    std::cout << "or cancel[0]: \n" << std::endl;
}

//void Game::handleEquipSlotInput(int _slotNumber)
//{
//    
//    if (_slotNumber == 0)
//    {
//        std::cout << "Equip canceled." << std::endl;
//        std::cout << "Type 'h' to see available commands.\n";
//        mode = Mode::Normal;
//        return;
//    }
//    else if (_slotNumber >= equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT))
//    {
//        std::cout << "Invalid choice.\n";
//        return;
//    }
//    else
//    {
//        Equipment::EquipmentSlot slot = equipmentSlotFromIndex(_slotNumber);
//
//        equipCandidates = player.getPlayerInventory().filterEquipmentInventoryBySlot(slot);
//
//        if (equipCandidates.empty())
//        {
//            std::cout << "No " << Equipment::equipmentSlotToString.at(slot) << " items found in equipment inventory." << std::endl;
//            std::cout << "Type 'h' to see available commands.\n";
//            mode = Mode::Normal;
//            return;
//        }
//        else if (slot == Equipment::EquipmentSlot::EMPTY)
//        {
//            std::cout << Equipment::equipmentSlotToString.at(slot) << " items are not equippable." << std::endl;
//            std::cout << "Type 'h' to see available commands.\n";
//            mode = Mode::Normal;
//            return;
//        }
//        else
//        {
//            std::cout << "Choose an item from the list to equip: " << std::endl;
//            int count = 0;
//            for (Equipment equipment : equipCandidates)
//            {
//                count++;
//                std::cout << equipment.itemRarityToString.at(equipment.getItemRarity()) << " " << equipment.getItemName() << "[" << count << "]  " << std::endl;
//            }
//            
//            pendingEquipSelectItem = true;
//        }
//    }  
//}

//void Game::handleEquipItemInput(const sf::Event::TextEntered& _text)
//{
//    if (mode == Mode::EquipSelectItem)
//    {
//        if (_text.unicode == '\r' || _text.unicode == '\n')
//        {
//            if (!textBuffer.empty())
//            {
//                int newEquipment = stoi(textBuffer);
//
//                if (newEquipment == 0)
//                {
//                    mode = Mode::Normal;
//                    equipCandidates.clear();
//                    std::cout << "\nEquip canceled.\n";
//                    std::cout << "Type 'h' to see available commands.\n";
//                    return;
//                }
//                else if (newEquipment > static_cast<int>(equipCandidates.size()))
//                {
//                    textBuffer.clear();
//                    std::cout << "\nInvalid choice.\n";
//                    return;
//                }
//                else
//                {
//                    const Equipment& chosen = equipCandidates[static_cast<std::vector<Equipment, std::allocator<Equipment>>::size_type>(newEquipment) - 1];
//                    player.equipFromInventory(chosen.getId());
//                    std::cout << "\nUpdated player:\n";
//                    player.printPlayer();
//                }               
//                std::cout << std::endl;
//                std::cout << "Type 'h' to see available commands.\n";
//            }
//            textBuffer.clear();
//            equipCandidates.clear();
//            mode = Mode::Normal;
//            return;
//        }
//
//        else if (_text.unicode == 27) // Escape
//        {
//            textBuffer.clear();
//            equipCandidates.clear();
//            mode = Mode::Normal;
//            std::cout << "\nEquip canceled.\n";
//            std::cout << "Type 'h' to see available commands.\n";
//            return;
//        }
//
//        else if (_text.unicode == 8) // Backspace
//        {
//            if (!textBuffer.empty())
//                textBuffer.pop_back();
//            std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
//            return;
//        }
//
//        else if (_text.unicode < 48 || _text.unicode > 57)
//            return;
//
//        textBuffer.push_back(static_cast<char>(_text.unicode));
//        std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
//        // You can draw this on screen instead of printing
//    }
//}

void Game::startUnequip()
{
    mode = Mode::UnequipSelectSlot;
    //selectedSlotIndex = -1;
    std::cout << "\nEnter a slot number to unequip an item from: ";
    for (int i = 1; i < equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT); i++)
    {
        std::cout << Equipment::equipmentSlotToString.at(equipmentSlotFromIndex(i)) << "[" << i << "], ";
    }
    std::cout << "or cancel[0]: " << std::endl;
}

//void Game::handleUnequipSlotInput(int _slotNumber)
//{
//    if (_slotNumber == 0)
//    {
//        std::cout << "\nUnequip canceled.\n" << std::endl;
//        std::cout << "Type 'h' to see available commands.\n";
//        mode = Mode::Normal;
//        return;
//    }
//    else if (_slotNumber >= equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT))
//    {
//        std::cout << "\nInvalid choice.\n";
//        return;
//    }
//    else
//    {
//        Equipment::EquipmentSlot slot = equipmentSlotFromIndex(_slotNumber);
//        Equipment equipment = player.getPlayerEquipment()[_slotNumber];
//        if (equipment.getId() == "")
//        {
//            std::cout << "\nNo item in slot.\n";
//            std::cout << "Type 'h' to see available commands.\n";
//            mode = Mode::Normal;
//            return;
//        }
//        player.unequipItem(slot);
//        std::cout << "\nUpdated player:\n";
//        player.printPlayer();
//        std::cout << "Type 'h' to see available commands.\n";
//        mode = Mode::Normal;
//    }  
//}

void Game::startDebug()
{
    mode = Mode::DebugSelect;
    std::cout << "Select a variable to change name[1] " << player.getName() << ", base attack[2] " << player.getBaseAttack()
        << ", base defense[3] " << player.getBaseDefense() << ",or base health[4] " << player.getBaseHealth() << "." << std::endl;
    std::cout << "You can also add to[5], or remove from[6], your inventory, or cancel[0]:\n";
}

void Game::startDebugName()
{
    textBuffer.clear();
    std::cout << "Enter new name (Enter to confirm, Esc to cancel):\n";
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
                std::cout << std::endl;
                std::cout << "Type 'h' to see available commands.\n";
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
            std::cout << "Type 'h' to see available commands.\n";
            return;
        }

        else if (_text.unicode == 8) // Backspace
        {
            if (!textBuffer.empty())
                textBuffer.pop_back();
            std::cout << "\rNew name: " << textBuffer << " " << std::flush;
            return;
        }

        else if (_text.unicode < 32 || _text.unicode > 126)
            return;

        textBuffer.push_back(static_cast<char>(_text.unicode));
        std::cout << "\rNew name: " << textBuffer << " " << std::flush;
        // You can draw this on screen instead of printing
    }
}

void Game::startDebugAttack()
{
    textBuffer.clear();
    std::cout << "Enter new base attack value (Enter to confirm, Esc to cancel):\n";
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
                player.setBaseStats(player.getBaseHealth(), player.getCurrentHealth(), newAttack, player.getBaseDefense());
                //player.setBaseAttack(newAttack);
                //player.updateMaxStats();
                std::cout << "\nNew base attack set: " << newAttack << "\n";
                std::cout << std::endl;
                std::cout << "Type 'h' to see available commands.\n";
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
            std::cout << "Type 'h' to see available commands.\n";
            return;
        }

        else if (_text.unicode == 8) // Backspace
        {
            if (!textBuffer.empty())
                textBuffer.pop_back();
            std::cout << "\rNew base attack: " << textBuffer << " " << std::flush;
            return;
        }

        else if (_text.unicode < 48 || _text.unicode > 57)
            return;

        textBuffer.push_back(static_cast<char>(_text.unicode));
        std::cout << "\rNew base attack: " << textBuffer << " " << std::flush;
        // You can draw this on screen instead of printing
    }
}

void Game::startDebugDefense()
{
    textBuffer.clear();
    std::cout << "Enter new base defense value (Enter to confirm, Esc to cancel):\n";
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
                player.setBaseStats(player.getBaseHealth(), player.getCurrentHealth(), player.getBaseAttack(), newDefense);
                //player.setBaseDefense(newDefense);
                //player.updateMaxStats();
                std::cout << "\nNew base defense set: " << newDefense << "\n";
                std::cout << std::endl;
                std::cout << "Type 'h' to see available commands.\n";
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
            std::cout << "Type 'h' to see available commands.\n";
            return;
        }

        else if (_text.unicode == 8) // Backspace
        {
            if (!textBuffer.empty())
                textBuffer.pop_back();
            std::cout << "\rNew base defense: " << textBuffer << " " << std::flush;
            return;
        }

        else if (_text.unicode < 48 || _text.unicode > 57)
            return;

        textBuffer.push_back(static_cast<char>(_text.unicode));
        std::cout << "\rNew base defense: " << textBuffer << " " << std::flush;
        // You can draw this on screen instead of printing
    }
}

void Game::startDebugHealth()
{
    textBuffer.clear();
    std::cout << "Enter new base health value (Enter to confirm, Esc to cancel):\n";
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
                player.setBaseStats(newHealth, player.getCurrentHealth(), player.getBaseAttack(), player.getBaseDefense());
                //player.setBaseHealth(newHealth);
                //player.updateMaxStats();
                std::cout << "\nNew base health set: " << newHealth << "\n";
                std::cout << std::endl;
                std::cout << "Type 'h' to see available commands.\n";
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
            std::cout << "Type 'h' to see available commands.\n";
            return;
        }

        else if (_text.unicode == 8) // Backspace
        {
            if (!textBuffer.empty())
                textBuffer.pop_back();
            std::cout << "\rNew base health: " << textBuffer << " " << std::flush;
            return;
        }

        else if (_text.unicode < 48 || _text.unicode > 57)
            return;

        textBuffer.push_back(static_cast<char>(_text.unicode));
        std::cout << "\rNew base health: " << textBuffer << " " << std::flush;
        // You can draw this on screen instead of printing
    }
}

void Game::startDebugAddToInventory()
{
    mode = Mode::DebugAddToInventorySlot;
    std::cout << "Enter a slot number to search master item list for: ";
    for (int i = 1; i < equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT); i++)
    {
        std::cout << Equipment::equipmentSlotToString.at(equipmentSlotFromIndex(i)) << "[" << i << "], ";
    }
    std::cout << "or cancel[0]: \n" << std::endl;
}

//void Game::debugAddToInventorySlotInput(int _slotNumber)
//{
//    if (_slotNumber == 0)
//    {
//        std::cout << "Debug canceled." << std::endl;
//        mode = Mode::Normal;
//        return;
//    }
//    else if (_slotNumber >= equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT))
//    {
//        std::cout << "Invalid choice.\n";
//        return;
//    }
//    else
//    {
//        Equipment::EquipmentSlot slot = equipmentSlotFromIndex(_slotNumber);
//
//        equipCandidates = gameEquipment[_slotNumber];
//
//        std::cout << "Getting inventory in the chosen slot." << std::endl;
//
//        if (equipCandidates.empty())
//        {
//            std::cout << "No " << Equipment::equipmentSlotToString.at(slot) << " items found in master equipment list." << std::endl;
//            std::cout << "Type 'h' to see available commands.\n";
//            mode = Mode::Normal;
//            return;
//        }
//        else if (slot == Equipment::EquipmentSlot::EMPTY)
//        {
//            std::cout << Equipment::equipmentSlotToString.at(slot) << " items are not equippable." << std::endl;
//            std::cout << "Type 'h' to see available commands.\n";
//            mode = Mode::Normal;
//            return;
//        }
//        else
//        {
//            std::cout << "Choose an item from the filtered list to add to inventory: " << std::endl;
//            int count = 0;
//            for (Equipment equipment : equipCandidates)
//            {
//                count++;
//                std::cout << equipment.itemRarityToString.at(equipment.getItemRarity()) << " " << equipment.getItemName() << "[" << count << "]  " << std::endl;
//            }
//
//            pendingDebugAddToInventoryItemInput = true;
//        }
//    }
//}

//void Game::debugAddToInventoryItemInput(const sf::Event::TextEntered& _text)
//{
//    if (mode == Mode::DebugAddToInventoryItem)
//    {
//        if (_text.unicode == '\r' || _text.unicode == '\n')
//        {
//            if (!textBuffer.empty())
//            {
//                int newItem = stoi(textBuffer);
//
//                if (newItem == 0)
//                {
//                    mode = Mode::Normal;
//                    equipCandidates.clear();
//                    std::cout << "\nDebug canceled.\n";
//                    std::cout << "Type 'h' to see available commands.\n";
//                    return;
//                }
//                else if (newItem > static_cast<int>(equipCandidates.size()))
//                {
//                    textBuffer.clear();
//                    std::cout << "\nInvalid choice.\n";
//                    return;
//                }
//                else
//                {
//                    const Equipment& chosen = equipCandidates[static_cast<std::vector<Equipment, std::allocator<Equipment>>::size_type>(newItem) - 1];
//                    player.getPlayerInventory().addEquipmentToInventory(chosen);
//                    std::cout << "\nUpdated inventory:\n";
//                    player.getPlayerInventory().printEquipmentInventory();
//
//                }
//                std::cout << std::endl;
//                std::cout << "Type 'h' to see available commands.\n";
//            }
//            textBuffer.clear();
//            equipCandidates.clear();
//            mode = Mode::Normal;
//            return;
//        }
//
//        else if (_text.unicode == 27) // Escape
//        {
//            textBuffer.clear();
//            equipCandidates.clear();
//            mode = Mode::Normal;
//            std::cout << "\nDebug canceled.\n";
//            std::cout << "Type 'h' to see available commands.\n";
//            return;
//        }
//
//        else if (_text.unicode == 8) // Backspace
//        {
//            if (!textBuffer.empty())
//                textBuffer.pop_back();
//            std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
//            return;
//        }
//
//        else if (_text.unicode < 48 || _text.unicode > 57)
//            return;
//
//        textBuffer.push_back(static_cast<char>(_text.unicode));
//        std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
//        // You can draw this on screen instead of printing
//    }
//}

void Game::startDebugRemoveFromInventory()
{
    mode = Mode::DebugRemoveFromInventoryItem;
    
    if (player.getPlayerInventory().getEquipmentInventory().empty())
    {
        mode = Mode::Normal;
        std::cout << "\nNo items in equipment inventory.\n";
        std::cout << "Type 'h' to see available commands.\n";
        return;
    }
    player.getPlayerInventory().sortEquipmentInventory();
    std::cout << "Choose an item to remove from your inventory: ";
    int count = 0;
    for (Equipment equipment : player.getPlayerInventory().getEquipmentInventory())
    {
        count++;
        std::cout << "\n" << equipment.getItemName() << "[" << count << "]";
    }
    std::cout << "\nor cancel[0]: " << std::endl;
}

//void Game::debugRemoveFromInventory(const sf::Event::TextEntered& _text)
//{
//    
//    if (mode == Mode::DebugRemoveFromInventoryItem)
//    {
//        std::vector<Equipment> playerEquipmentInventory = player.getPlayerInventory().getEquipmentInventory();
//
//        if (_text.unicode == '\r' || _text.unicode == '\n')
//        {
//            if (!textBuffer.empty())
//            {
//                int equipmentToRemove = stoi(textBuffer);
//
//                if (equipmentToRemove == 0)
//                {
//                    mode = Mode::Normal;
//                    std::cout << "\nDebug canceled.\n";
//                    std::cout << "Type 'h' to see available commands.\n";
//                    return;
//                }
//                else if (equipmentToRemove > playerEquipmentInventory.size())
//                {
//                    textBuffer.clear();
//                    std::cout << "\nInvalid choice.\n";
//                    return;
//                }
//                else
//                {
//                    //const Item& chosen = equipCandidates[itemToRemove - 1];
//                    const Equipment& chosen = playerEquipmentInventory[static_cast<std::vector<Equipment, std::allocator<Equipment>>::size_type>(equipmentToRemove) - 1];
//                    player.getPlayerInventory().removeEquipmentFromInventory(chosen.getId());
//                    std::cout << "\nUpdated inventory:\n";
//                    player.getPlayerInventory().printEquipmentInventory();
//
//                }
//                std::cout << std::endl;
//                std::cout << "Type 'h' to see available commands.\n";
//            }
//            textBuffer.clear();
//            mode = Mode::Normal;
//            return;
//        }
//
//        else if (_text.unicode == 27) // Escape
//        {
//            textBuffer.clear();
//            mode = Mode::Normal;
//            std::cout << "\nDebug canceled.\n";
//            std::cout << "Type 'h' to see available commands.\n";
//            return;
//        }
//
//        else if (_text.unicode == 8) // Backspace
//        {
//            if (!textBuffer.empty())
//                textBuffer.pop_back();
//            std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
//            return;
//        }
//
//        else if (_text.unicode < 48 || _text.unicode > 57)
//            return;
//
//        textBuffer.push_back(static_cast<char>(_text.unicode));
//        std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
//        // You can draw this on screen instead of printing
//    }
//}

void Game::startSave()
{
    textBuffer.clear();
    std::cout << "Save file name (e.g. save1): ";
    mode = Mode::Save;
}

void Game::save(const sf::Event::TextEntered& _text)
{
    if (mode == Mode::Save)
    {
        if (_text.unicode == '\r' || _text.unicode == '\n')
        {
            if (!textBuffer.empty())
            {
                std::string saveName = textBuffer;
                saveName.append(".json");
                if (SaveLoad::saveToFile(player, saveName))
                    std::cout << "\nSaved to " << saveName << "\n";
                else
                    std::cout << "Save failed.\n";

                std::cout << "Type 'h' to see available commands.\n";
            }
            textBuffer.clear();
            mode = Mode::Normal;
            return;
        }

        else if (_text.unicode == 27) // Escape
        {
            textBuffer.clear();
            mode = Mode::Normal;
            std::cout << "\nSave canceled.\n";
            std::cout << "\nType 'h' to see available commands.\n";
            return;
        }

        else if (_text.unicode == 8) // Backspace
        {
            if (!textBuffer.empty())
                textBuffer.pop_back();
            std::cout << "\rSave file name(e.g. save1) : " << textBuffer << " " << std::flush;
            return;
        }

        else if (_text.unicode < 32 || _text.unicode > 126)
            return;

        textBuffer.push_back(static_cast<char>(_text.unicode));
        std::cout << "\rSave file name(e.g. save1) : " << textBuffer << " " << std::flush;
        // You can draw this on screen instead of printing
    }
}

void Game::startLoad()
{
    textBuffer.clear();
    std::cout << "Load file name (e.g. save1): ";
    mode = Mode::Load;
}

void Game::load(const sf::Event::TextEntered& _text)
{
    if (mode == Mode::Load)
    {
        if (_text.unicode == '\r' || _text.unicode == '\n')
        {
            if (!textBuffer.empty())
            {
                Player loaded;
                std::string loadName = textBuffer;
                loadName.append(".json");
                    if (SaveLoad::loadFromFile(loaded, loadName)) {
                        player = std::move(loaded);
                        std::cout << "Loaded from " << loadName << "\n";
                        player.updateMaxStats();
                        player.printPlayer();
                        player.getPlayerInventory().printEquipmentInventory();
                    }
                    else {
                        std::cout << "Load failed.\n";
                    }
                    std::cout << "\nType 'h' to see available commands.\n";
            }
            textBuffer.clear();
            mode = Mode::Normal;
            return;
        }

        else if (_text.unicode == 27) // Escape
        {
            textBuffer.clear();
            mode = Mode::Normal;
            std::cout << "\nLoad canceled.\n";
            std::cout << "\nType 'h' to see available commands.\n";
            return;
        }

        else if (_text.unicode == 8) // Backspace
        {
            if (!textBuffer.empty())
                textBuffer.pop_back();
            std::cout << "\rLoad file name (e.g. save1): " << textBuffer << " " << std::flush;
            return;
        }

        else if (_text.unicode < 32 || _text.unicode > 126)
            return;

        textBuffer.push_back(static_cast<char>(_text.unicode));
        std::cout << "\rLoad file name (e.g. save1): " << textBuffer << " " << std::flush;
        // You can draw this on screen instead of printing
    }
}

void Game::Quit()
{
    std::cout << "Exiting game.\n";
    std::cout << "Game ended. Final player state:\n";
    player.printPlayer();
    mode = Mode::Quit;
}

void Game::startFight()
{

}

void Game::loop(std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)>& _gameEquipment)
{

    sf::Clock clock;
    enemy = combatActions.spawnEnemy(Enemy::EnemyType::SLIME);

    //gameItems = gameInitialize.getGameItems();
    gameEquipment = _gameEquipment;
    giveStartingItems();

    float windowWidth = 800;
    float windowHeight = 800;
    sf::RenderWindow window(sf::VideoMode({ (unsigned)windowWidth, (unsigned)windowHeight }), "Play Coding");
    std::cout << "---- Game loop started ----" << std::endl;
    std::cout << "Type 'h' to see available commands.\n";
    std::cout << std::endl;
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

void Game::handleEvent(const sf::Event& _event)
{
    if (auto* key = _event.getIf<sf::Event::KeyPressed>())
    {
        handleKeyPressed(*key);
    }
    else if (auto* text = _event.getIf<sf::Event::TextEntered>())
    {
        handleTextEntered(*text);
        
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
            case sf::Keyboard::Scancode::C: { player.printPlayer(); std::cout << "\nType 'h' to see available commands.\n"; break; }
            case sf::Keyboard::Scancode::I: { player.getPlayerInventory().printEquipmentInventory(); std::cout << "\nType 'h' to see available commands.\n"; break; }
            case sf::Keyboard::Scancode::E: { startEquip(); break; }
            case sf::Keyboard::Scancode::U: { startUnequip(); break; }
            case sf::Keyboard::Scancode::D: { startDebug(); break; }
            case sf::Keyboard::Scancode::S: { pendingSave = true; break; }
            case sf::Keyboard::Scancode::L: { pendingLoad = true; break; }
            case sf::Keyboard::Scancode::Q: { Quit(); break; }
            case sf::Keyboard::Scancode::F: { startFight(); break; }
            default: 
            { 
                std::cout << "Not an option. Please try again.\n" << std::endl;
                break; 
            }
        }
    }
    else if (mode == Mode::EquipSelectSlot)
    {
        switch (_keyPressed.scancode)
        {
        case sf::Keyboard::Scancode::Num0: { inventoryActions.handleEquipSlotInput(0, player, pendingEquipSelectItem, normal); break; }
        case sf::Keyboard::Scancode::Num1: { inventoryActions.handleEquipSlotInput(1, player, pendingEquipSelectItem, normal); break; }
        case sf::Keyboard::Scancode::Num2: { inventoryActions.handleEquipSlotInput(2, player, pendingEquipSelectItem, normal); break; }
        case sf::Keyboard::Scancode::Num3: { inventoryActions.handleEquipSlotInput(3, player, pendingEquipSelectItem, normal); break; }
        case sf::Keyboard::Scancode::Num4: { inventoryActions.handleEquipSlotInput(4, player, pendingEquipSelectItem, normal); break; }
        case sf::Keyboard::Scancode::Num5: { inventoryActions.handleEquipSlotInput(5, player, pendingEquipSelectItem, normal); break; }
        case sf::Keyboard::Scancode::Num6: { inventoryActions.handleEquipSlotInput(6, player, pendingEquipSelectItem, normal); break; }
        case sf::Keyboard::Scancode::Num7: { inventoryActions.handleEquipSlotInput(7, player, pendingEquipSelectItem, normal); break; }
        case sf::Keyboard::Scancode::Num8: { inventoryActions.handleEquipSlotInput(8, player, pendingEquipSelectItem, normal); break; }
        case sf::Keyboard::Scancode::Num9: { inventoryActions.handleEquipSlotInput(9, player, pendingEquipSelectItem, normal); break; }
        default: { break; }
        }
    }
    else if (mode == Mode::UnequipSelectSlot)
    {
        switch (_keyPressed.scancode)
        {
        case sf::Keyboard::Scancode::Num0: { inventoryActions.handleUnequipSlotInput(0, player, normal); break; }
        case sf::Keyboard::Scancode::Num1: { inventoryActions.handleUnequipSlotInput(1, player, normal); break; }
        case sf::Keyboard::Scancode::Num2: { inventoryActions.handleUnequipSlotInput(2, player, normal); break; }
        case sf::Keyboard::Scancode::Num3: { inventoryActions.handleUnequipSlotInput(3, player, normal); break; }
        case sf::Keyboard::Scancode::Num4: { inventoryActions.handleUnequipSlotInput(4, player, normal); break; }
        case sf::Keyboard::Scancode::Num5: { inventoryActions.handleUnequipSlotInput(5, player, normal); break; }
        case sf::Keyboard::Scancode::Num6: { inventoryActions.handleUnequipSlotInput(6, player, normal); break; }
        case sf::Keyboard::Scancode::Num7: { inventoryActions.handleUnequipSlotInput(7, player, normal); break; }
        case sf::Keyboard::Scancode::Num8: { inventoryActions.handleUnequipSlotInput(8, player, normal); break; }
        case sf::Keyboard::Scancode::Num9: { inventoryActions.handleUnequipSlotInput(9, player, normal); break; }
        default: { break; }
        }
    }
    else if (mode == Mode::DebugSelect)
    {
        switch (_keyPressed.scancode)
        {
            case sf::Keyboard::Scancode::Num0: {
                std::cout << "Canceled debug mode.\n" << std::endl;
                mode = Mode::Normal;
                break;
            }
            case sf::Keyboard::Scancode::Num1: { pendingDebugName = true; break; }
            case sf::Keyboard::Scancode::Num2: { pendingDebugAttack = true; break; }
            case sf::Keyboard::Scancode::Num3: { pendingDebugDefense = true; break; }
            case sf::Keyboard::Scancode::Num4: { pendingDebugHealth = true; break; }
            case sf::Keyboard::Scancode::Num5: { startDebugAddToInventory(); break; }
            case sf::Keyboard::Scancode::Num6: { pendingDebugRemoveFromInventory = true; break; }
            default: 
            { 
                std::cout << "Not a debug mode option.\n" << std::endl;
                mode = Mode::Normal;
                break; 
            }
        }
    }
    else if (mode == Mode::DebugAddToInventorySlot)
    {
        switch (_keyPressed.scancode)
        {
        case sf::Keyboard::Scancode::Num0: { inventoryActions.debugAddToInventorySlotInput(0, gameEquipment, pendingDebugAddToInventoryItemInput, normal); break; }
        case sf::Keyboard::Scancode::Num1: { inventoryActions.debugAddToInventorySlotInput(1, gameEquipment, pendingDebugAddToInventoryItemInput, normal); break; }
        case sf::Keyboard::Scancode::Num2: { inventoryActions.debugAddToInventorySlotInput(2, gameEquipment, pendingDebugAddToInventoryItemInput, normal); break; }
        case sf::Keyboard::Scancode::Num3: { inventoryActions.debugAddToInventorySlotInput(3, gameEquipment, pendingDebugAddToInventoryItemInput, normal); break; }
        case sf::Keyboard::Scancode::Num4: { inventoryActions.debugAddToInventorySlotInput(4, gameEquipment, pendingDebugAddToInventoryItemInput, normal); break; }
        case sf::Keyboard::Scancode::Num5: { inventoryActions.debugAddToInventorySlotInput(5, gameEquipment, pendingDebugAddToInventoryItemInput, normal); break; }
        case sf::Keyboard::Scancode::Num6: { inventoryActions.debugAddToInventorySlotInput(6, gameEquipment, pendingDebugAddToInventoryItemInput, normal); break; }
        case sf::Keyboard::Scancode::Num7: { inventoryActions.debugAddToInventorySlotInput(7, gameEquipment, pendingDebugAddToInventoryItemInput, normal); break; }
        case sf::Keyboard::Scancode::Num8: { inventoryActions.debugAddToInventorySlotInput(8, gameEquipment, pendingDebugAddToInventoryItemInput, normal); break; }
        case sf::Keyboard::Scancode::Num9: { inventoryActions.debugAddToInventorySlotInput(9, gameEquipment, pendingDebugAddToInventoryItemInput, normal); break; }
        default: { break; }
        }
    }
}

void Game::handleTextEntered(const sf::Event::TextEntered& _textEntered)
{
    switch (mode)
    {
    case Mode::EquipSelectItem: { inventoryActions.handleEquipItemInput(_textEntered, player, normal); break; }
    case Mode::DebugName: { debugName(_textEntered); break; }
    case Mode::DebugAttack: { debugAttack(_textEntered); break; }
    case Mode::DebugDefense: { debugDefense(_textEntered); break; }
    case Mode::DebugHealth: { debugHealth(_textEntered); break; }
    case Mode::DebugAddToInventoryItem: { inventoryActions.debugAddToInventoryItemInput(_textEntered, player, normal); break; }
    case Mode::DebugRemoveFromInventoryItem: { inventoryActions.debugRemoveFromInventory(_textEntered, player, normal); break; }
    case Mode::Save: { save(_textEntered); break; }
    case Mode::Load: { load(_textEntered); break; }
    default: break;
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
    else if (pendingDebugAddToInventoryItemInput)
    {
        pendingDebugAddToInventoryItemInput = false;
        mode = Mode::DebugAddToInventoryItem;
    }
    else if (pendingDebugRemoveFromInventory)
    {
        pendingDebugRemoveFromInventory = false;
        startDebugRemoveFromInventory();
    }
    else if (pendingEquipSelectItem)
    {
        pendingEquipSelectItem = false;
        mode = Mode::EquipSelectItem;
    }
    else if (pendingSave)
    {
        pendingSave = false;
        startSave();
    }
    else if (pendingLoad)
    {
        pendingLoad = false;
        startLoad();
    }
    else if (normal)
    {
        normal = false;
        mode = Mode::Normal;
    }
}
