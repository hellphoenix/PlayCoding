#include "inventoryActions.h"
#include <iostream>


//void InventoryActions::handleEquipSlotInput(int _slotNumber, Player& _player, bool& _pendingEquipSelectItem, bool& _normal)
//{
//	if (_slotNumber == 0)
//	{
//		std::cout << "Equip canceled." << std::endl;
//		std::cout << "Type 'h' to see available commands.\n";
//		//_mode = Mode::Normal;
//		_normal = true;
//		return;
//	}
//	else if (_slotNumber >= equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT))
//	{
//		std::cout << "Invalid choice.\n";
//		return;
//	}
//	else
//	{
//		Equipment::EquipmentSlot slot = equipmentSlotFromIndex(_slotNumber);
//
//		equipCandidates = _player.getPlayerInventory().filterEquipmentInventoryBySlot(slot);
//
//		if (equipCandidates.empty())
//		{
//			std::cout << "No " << Equipment::equipmentSlotToString.at(slot) << " items found in equipment inventory." << std::endl;
//			std::cout << "Type 'h' to see available commands.\n";
//			//_mode = Mode::Normal;
//			_normal = true;
//			return;
//		}
//		else if (slot == Equipment::EquipmentSlot::EMPTY)
//		{
//			std::cout << Equipment::equipmentSlotToString.at(slot) << " items are not equippable." << std::endl;
//			std::cout << "Type 'h' to see available commands.\n";
//			//_mode = Mode::Normal;
//			_normal = true;
//			return;
//		}
//		else
//		{
//			std::cout << "Choose an item from the list to equip: " << std::endl;
//			int count = 0;
//			for (Equipment equipment : equipCandidates)
//			{
//				count++;
//				std::cout << equipment.itemRarityToString.at(equipment.getItemRarity()) << " " << equipment.getItemName() << "[" << count << "]  " << std::endl;
//			}
//
//			_pendingEquipSelectItem = true;
//		}
//	}
//}

//void InventoryActions::handleEquipItemInput(NumberInputKey key, char digit, Player& _player, bool& _normal)
//{
//	switch (key)
//	{
//	case NumberInputKey::Confirm:
//		if (!textBuffer.empty())
//		{
//			int newEquipment = std::stoi(textBuffer);
//
//			if (newEquipment == 0)
//			{
//				_normal = true;
//				equipCandidates.clear();
//				std::cout << "\nEquip canceled.\n";
//				std::cout << "Type 'h' to see available commands.\n";
//				break;
//			}
//			else if (newEquipment > static_cast<int>(equipCandidates.size()))
//			{
//				textBuffer.clear();
//				std::cout << "\nInvalid choice.\n";
//				break;
//			}
//			else
//			{
//				const Equipment& chosen =
//					equipCandidates[static_cast<std::size_t>(newEquipment) - 1];
//
//				_player.equipFromInventory(chosen.getId());
//				std::cout << "\nUpdated player:\n";
//				_player.printPlayer();
//				std::cout << std::endl;
//				std::cout << "Type 'h' to see available commands.\n";
//			}
//		}
//
//		textBuffer.clear();
//		equipCandidates.clear();
//		_normal = true;
//		break;
//
//	case NumberInputKey::Cancel:
//		textBuffer.clear();
//		equipCandidates.clear();
//		_normal = true;
//		std::cout << "\nEquip canceled.\n";
//		std::cout << "Type 'h' to see available commands.\n";
//		break;
//
//	case NumberInputKey::Backspace:
//		if (!textBuffer.empty())
//			textBuffer.pop_back();
//		std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
//		break;
//
//	case NumberInputKey::Digit:
//		textBuffer.push_back(digit);
//		std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
//		break;
//	}
//}

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
		std::cout << "Add To Inventory canceled." << std::endl;
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

void InventoryActions::debugAddToInventoryItemInput(NumberInputKey key, char digit, Player& _player, bool& _normal)
{
	switch (key)
	{
	case NumberInputKey::Confirm:
		if (!textBuffer.empty())
		{
			int newEquipment = std::stoi(textBuffer);

			if (newEquipment == 0)
			{
				_normal = true;
				equipCandidates.clear();
				std::cout << "\nAdd To Inventory canceled.\n";
				std::cout << "Type 'h' to see available commands.\n";
				break;
			}
			else if (newEquipment > static_cast<int>(equipCandidates.size()))
			{
				textBuffer.clear();
				std::cout << "\nInvalid choice.\n";
				break;
			}
			else
			{
				const Equipment& chosen = equipCandidates[static_cast<std::vector<Equipment, std::allocator<Equipment>>::size_type>(newEquipment) - 1];
				_player.getPlayerInventory().addEquipmentToInventory(chosen);
				std::cout << "\nUpdated inventory:\n";
				_player.getPlayerInventory().printEquipmentInventory();
				std::cout << std::endl;
				std::cout << "Type 'h' to see available commands.\n";
			}
		}

		textBuffer.clear();
		equipCandidates.clear();
		_normal = true;
		break;

	case NumberInputKey::Cancel:
		textBuffer.clear();
		equipCandidates.clear();
		_normal = true;
		std::cout << "\nAdd To Inventory canceled.\n";
		std::cout << "Type 'h' to see available commands.\n";
		break;

	case NumberInputKey::Backspace:
		if (!textBuffer.empty())
			textBuffer.pop_back();
		std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
		break;

	case NumberInputKey::Digit:
		textBuffer.push_back(digit);
		std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
		break;
	}
}

void InventoryActions::debugRemoveFromInventory(NumberInputKey key, char digit, Player& _player, bool& _normal)
{
	const auto& playerEquipmentInventory = _player.getPlayerInventory().getEquipmentInventory();

	switch (key)
	{
	case NumberInputKey::Confirm:
		if (!textBuffer.empty())
		{
			int equipmentToRemove = std::stoi(textBuffer);

			if (equipmentToRemove == 0)
			{
				_normal = true;
				std::cout << "\nDebug canceled.\n";
				std::cout << "Type 'h' to see available commands.\n";
				break;
			}
			else if (equipmentToRemove > playerEquipmentInventory.size())
			{
				textBuffer.clear();
				std::cout << "\nInvalid choice.\n";
				break;
			}
			else
			{
				const Equipment& chosen = playerEquipmentInventory[static_cast<std::vector<Equipment, std::allocator<Equipment>>::size_type>(equipmentToRemove) - 1];
				_player.getPlayerInventory().removeEquipmentFromInventory(chosen.getId());
				std::cout << "\nUpdated inventory:\n";
				_player.getPlayerInventory().printEquipmentInventory();
				std::cout << std::endl;
				std::cout << "Type 'h' to see available commands.\n";
			}
		}

		textBuffer.clear();
		_normal = true;
		break;

	case NumberInputKey::Cancel:
		textBuffer.clear();
		_normal = true;
		std::cout << "\nDebug canceled.\n";
		std::cout << "Type 'h' to see available commands.\n";
		break;

	case NumberInputKey::Backspace:
		if (!textBuffer.empty())
			textBuffer.pop_back();
		std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
		break;

	case NumberInputKey::Digit:
		textBuffer.push_back(digit);
		std::cout << "\rEquipment selection: " << textBuffer << " " << std::flush;
		break;
	}
}