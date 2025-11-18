#include "inventoryActions.h"
#include <iostream>

InventoryActions::InventoryActions()
{

}

void InventoryActions::handleEquipSlotInput(int _slotNumber, Player& _player, bool& _pendingEquipSelectItem, bool& _normal)
{
    if (_slotNumber == 0)
    {
        std::cout << "Equip canceled." << std::endl;
        std::cout << "Type 'h' to see available commands.\n";
        //_mode = Mode::Normal;
        _normal = true;
        return;
    }
    else if (_slotNumber >= equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT))
    {
        std::cout << "Invalid choice.\n";
        return;
    }
    else
    {
        Equipment::EquipmentSlot slot = equipmentSlotFromIndex(_slotNumber);

        equipCandidates = _player.getPlayerInventory().filterEquipmentInventoryBySlot(slot);

        if (equipCandidates.empty())
        {
            std::cout << "No " << Equipment::equipmentSlotToString.at(slot) << " items found in equipment inventory." << std::endl;
            std::cout << "Type 'h' to see available commands.\n";
            //_mode = Mode::Normal;
            _normal = true;
            return;
        }
        else if (slot == Equipment::EquipmentSlot::EMPTY)
        {
            std::cout << Equipment::equipmentSlotToString.at(slot) << " items are not equippable." << std::endl;
            std::cout << "Type 'h' to see available commands.\n";
            //_mode = Mode::Normal;
            _normal = true;
            return;
        }
        else
        {
            std::cout << "Choose an item from the list to equip: " << std::endl;
            int count = 0;
            for (Equipment equipment : equipCandidates)
            {
                count++;
                std::cout << equipment.itemRarityToString.at(equipment.getItemRarity()) << " " << equipment.getItemName() << "[" << count << "]  " << std::endl;
            }

            _pendingEquipSelectItem = true;
        }
    }
}

void InventoryActions::handleEquipItemInput(const sf::Event::TextEntered& _text, Player& _player, bool& _normal)
{
    if (!_normal)
    {
        if (_text.unicode == '\r' || _text.unicode == '\n')
        {
            if (!textBuffer.empty())
            {
                int newEquipment = stoi(textBuffer);

                if (newEquipment == 0)
                {
                    //_mode = Mode::Normal;
                    _normal = true;
                    equipCandidates.clear();
                    std::cout << "\nEquip canceled.\n";
                    std::cout << "Type 'h' to see available commands.\n";
                    return;
                }
                else if (newEquipment > static_cast<int>(equipCandidates.size()))
                {
                    textBuffer.clear();
                    std::cout << "\nInvalid choice.\n";
                    return;
                }
                else
                {
                    const Equipment& chosen = equipCandidates[static_cast<std::vector<Equipment, std::allocator<Equipment>>::size_type>(newEquipment) - 1];
                    
                    _player.equipFromInventory(chosen.getId());
                    std::cout << "\nUpdated player:\n";
                    _player.printPlayer();
                }
                std::cout << std::endl;
                std::cout << "Type 'h' to see available commands.\n";
            }
            textBuffer.clear();
            equipCandidates.clear();
            //_mode = Mode::Normal;
            _normal = true;
            return;
        }

        else if (_text.unicode == 27) // Escape
        {
            textBuffer.clear();
            equipCandidates.clear();
            //_mode = Mode::Normal;
            _normal = true;
            std::cout << "\nEquip canceled.\n";
            std::cout << "Type 'h' to see available commands.\n";
            return;
        }

        else if (_text.unicode == 8) // Backspace
        {
            if (!textBuffer.empty())
                textBuffer.pop_back();
            std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
            return;
        }

        else if (_text.unicode < 48 || _text.unicode > 57)
            return;

        textBuffer.push_back(static_cast<char>(_text.unicode));
        std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
        // You can draw this on screen instead of printing
    }
}

void InventoryActions::handleUnequipSlotInput(int _slotNumber, Player& _player, bool& _normal)
{
    if (_slotNumber == 0)
    {
        std::cout << "\nUnequip canceled.\n" << std::endl;
        std::cout << "Type 'h' to see available commands.\n";
        //mode = Mode::Normal;
        _normal = true;
        return;
    }
    else if (_slotNumber >= equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT))
    {
        std::cout << "\nInvalid choice.\n";
        return;
    }
    else
    {
        Equipment::EquipmentSlot slot = equipmentSlotFromIndex(_slotNumber);
        Equipment equipment = _player.getPlayerEquipment()[_slotNumber];
        if (equipment.getId() == "")
        {
            std::cout << "\nNo item in slot.\n";
            std::cout << "Type 'h' to see available commands.\n";
            //mode = Mode::Normal;
            _normal = true;
            return;
        }
        _player.unequipItem(slot);
        std::cout << "\nUpdated player:\n";
        _player.printPlayer();
        std::cout << "Type 'h' to see available commands.\n";
        //mode = Mode::Normal;
        _normal = true;
    }
}

void InventoryActions::debugAddToInventorySlotInput(int _slotNumber, std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)>& _gameEquipment, bool& _pendingDebugAddToInventoryItemInput, bool& _normal)
{
    if (_slotNumber == 0)
    {
        std::cout << "Debug canceled." << std::endl;
        //mode = Mode::Normal;
        _normal = true;
        return;
    }
    else if (_slotNumber >= equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT))
    {
        std::cout << "Invalid choice.\n";
        return;
    }
    else
    {
        Equipment::EquipmentSlot slot = equipmentSlotFromIndex(_slotNumber);

        equipCandidates = _gameEquipment[_slotNumber];

        std::cout << "Getting inventory in the chosen slot." << std::endl;

        if (equipCandidates.empty())
        {
            std::cout << "No " << Equipment::equipmentSlotToString.at(slot) << " items found in master equipment list." << std::endl;
            std::cout << "Type 'h' to see available commands.\n";
            //mode = Mode::Normal;
            _normal = true;
            return;
        }
        else if (slot == Equipment::EquipmentSlot::EMPTY)
        {
            std::cout << Equipment::equipmentSlotToString.at(slot) << " items are not equippable." << std::endl;
            std::cout << "Type 'h' to see available commands.\n";
            //mode = Mode::Normal;
            _normal = true;
            return;
        }
        else
        {
            std::cout << "Choose an item from the filtered list to add to inventory: " << std::endl;
            int count = 0;
            for (Equipment equipment : equipCandidates)
            {
                count++;
                std::cout << equipment.itemRarityToString.at(equipment.getItemRarity()) << " " << equipment.getItemName() << "[" << count << "]  " << std::endl;
            }

            _pendingDebugAddToInventoryItemInput = true;
        }
    }
}

void InventoryActions::debugAddToInventoryItemInput(const sf::Event::TextEntered& _text, Player& _player, bool& _normal)
{
    if (!_normal)
    {
        if (_text.unicode == '\r' || _text.unicode == '\n')
        {
            if (!textBuffer.empty())
            {
                int newItem = stoi(textBuffer);

                if (newItem == 0)
                {
                    //mode = Mode::Normal;
                    _normal = true;
                    equipCandidates.clear();
                    std::cout << "\nDebug canceled.\n";
                    std::cout << "Type 'h' to see available commands.\n";
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
                    const Equipment& chosen = equipCandidates[static_cast<std::vector<Equipment, std::allocator<Equipment>>::size_type>(newItem) - 1];
                    _player.getPlayerInventory().addEquipmentToInventory(chosen);
                    std::cout << "\nUpdated inventory:\n";
                    _player.getPlayerInventory().printEquipmentInventory();

                }
                std::cout << std::endl;
                std::cout << "Type 'h' to see available commands.\n";
            }
            textBuffer.clear();
            equipCandidates.clear();
            //mode = Mode::Normal;
            _normal = true;
            return;
        }

        else if (_text.unicode == 27) // Escape
        {
            textBuffer.clear();
            equipCandidates.clear();
            //mode = Mode::Normal;
            _normal = true;
            std::cout << "\nDebug canceled.\n";
            std::cout << "Type 'h' to see available commands.\n";
            return;
        }

        else if (_text.unicode == 8) // Backspace
        {
            if (!textBuffer.empty())
                textBuffer.pop_back();
            std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
            return;
        }

        else if (_text.unicode < 48 || _text.unicode > 57)
            return;

        textBuffer.push_back(static_cast<char>(_text.unicode));
        std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
        // You can draw this on screen instead of printing
    }
}

void InventoryActions::debugRemoveFromInventory(const sf::Event::TextEntered& _text, Player& _player, bool& _normal)
{

    if (!_normal)
    {
        std::vector<Equipment> playerEquipmentInventory = _player.getPlayerInventory().getEquipmentInventory();

        if (_text.unicode == '\r' || _text.unicode == '\n')
        {
            if (!textBuffer.empty())
            {
                int equipmentToRemove = stoi(textBuffer);

                if (equipmentToRemove == 0)
                {
                    //mode = Mode::Normal;
                    _normal = true;
                    std::cout << "\nDebug canceled.\n";
                    std::cout << "Type 'h' to see available commands.\n";
                    return;
                }
                else if (equipmentToRemove > playerEquipmentInventory.size())
                {
                    textBuffer.clear();
                    std::cout << "\nInvalid choice.\n";
                    return;
                }
                else
                {
                    //const Item& chosen = equipCandidates[itemToRemove - 1];
                    const Equipment& chosen = playerEquipmentInventory[static_cast<std::vector<Equipment, std::allocator<Equipment>>::size_type>(equipmentToRemove) - 1];
                    _player.getPlayerInventory().removeEquipmentFromInventory(chosen.getId());
                    std::cout << "\nUpdated inventory:\n";
                    _player.getPlayerInventory().printEquipmentInventory();

                }
                std::cout << std::endl;
                std::cout << "Type 'h' to see available commands.\n";
            }
            textBuffer.clear();
            //mode = Mode::Normal;
            _normal = true;
            return;
        }

        else if (_text.unicode == 27) // Escape
        {
            textBuffer.clear();
            //mode = Mode::Normal;
            _normal = true;
            std::cout << "\nDebug canceled.\n";
            std::cout << "Type 'h' to see available commands.\n";
            return;
        }

        else if (_text.unicode == 8) // Backspace
        {
            if (!textBuffer.empty())
                textBuffer.pop_back();
            std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
            return;
        }

        else if (_text.unicode < 48 || _text.unicode > 57)
            return;

        textBuffer.push_back(static_cast<char>(_text.unicode));
        std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
        // You can draw this on screen instead of printing
    }
}