#include "inventoryActions.h"
#include <iostream>

void InventoryActions::dragFromInventory(sf::RenderWindow& window, Player& player, DragSource::DragState& dragState) const
{
	const auto& inventory = player.getPlayerInventory().getEquipmentInventory();
	if (dragState.inventoryIndex < inventory.size())
	{
		const auto& equipment = inventory[dragState.inventoryIndex];

		drawBoxHelper(window, player, dragState, equipment);
	}
}

void InventoryActions::dragFromEquippedSlot(sf::RenderWindow& window, Player& player, DragSource::DragState& dragState) const
{
	const auto& equipment = player.getEquippedItem(equipmentSlotFromIndex(dragState.inventoryIndex));

	drawBoxHelper(window, player, dragState, equipment);
}

void InventoryActions::dragFromMasterList(sf::RenderWindow& window, Player& player, DragSource::DragState& dragState, equipmentArray& gameEquipment) const
{
	const auto& masterEquipmentList = gameEquipment;
	const auto slotIndex = equipmentSlotToIndex(dragState.slot);

	if (slotIndex >= masterEquipmentList.size())
		return;
	if (dragState.inventoryIndex >= masterEquipmentList[slotIndex].size())
		return;

	const auto& equipment = masterEquipmentList[slotIndex][dragState.inventoryIndex];

	drawBoxHelper(window, player, dragState, equipment);
}

void InventoryActions::dropOnPlayerSlot(const sf::Vector2f& dropPos, Player& player, DragSource::DragState& dragState, equipmentArray& gameEquipment, slotFloatRects& slotRects)
{
	if (dragState.source == DragSource::Source::Inventory)
	{
		const auto& inventory = player.getPlayerInventory().getEquipmentInventory();
		if (dragState.inventoryIndex >= inventory.size())
			return;

		const auto& draggedItem = inventory[dragState.inventoryIndex];
		if (draggedItem.getId() == "" || draggedItem.getItemName() == "")
		{
			player.getPlayerInventory().removeEquipmentFromInventory(draggedItem.getId());
			return;
		}

		// find which slot rect, if any, we dropped on
		for (int i = 1; i < equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT); ++i)
		{
			Equipment::EquipmentSlot slot = equipmentSlotFromIndex(i);
			const auto& rect = slotRects[i];

			if (rect.size.x <= 0.f || rect.size.y <= 0.f)
				continue; // unused

			if (rect.contains(dropPos))
			{
				if (draggedItem.getEquipmentSlot() != slot)
				{
					std::cout << "Item does not fit that slot.\n";
					return;
				}

				player.equipFromInventory(draggedItem.getId());

				const Equipment& equipped = player.getEquippedItem(slot);

				std::cout << "Equipped " << Equipment::itemRarityToString.at(equipped.getItemRarity()) << " " << equipped.getItemName() << "\n";
				hudRenderer.refreshAbilitySlotsFromEquipment(player);
				return;
			}
		}
	}
	else if (dragState.source == DragSource::Source::MasterList)
	{

		const auto& masterEquipmentList = gameEquipment;
		const auto slotIndex = equipmentSlotToIndex(dragState.slot);

		if (slotIndex >= masterEquipmentList.size() || dragState.inventoryIndex >= masterEquipmentList[slotIndex].size())
			return;

		Equipment draggedItem = masterEquipmentList[slotIndex][dragState.inventoryIndex];
		if (draggedItem.getId() == "" || draggedItem.getItemName() == "")
		{
			return;
		}

		// find which slot rect, if any, we dropped on
		for (int i = 1; i < equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT); ++i)
		{

			Equipment::EquipmentSlot slot = equipmentSlotFromIndex(i);
			const auto& rect = slotRects[i];

			if (rect.size.x <= 0.f || rect.size.y <= 0.f)
				continue; // unused

			if (rect.contains(dropPos))
			{
				if (draggedItem.getEquipmentSlot() != slot)
				{
					std::cout << "Item does not fit that slot.\n";
					return;
				}

				player.equipEquipment(draggedItem);


				const Equipment& equipped = player.getEquippedItem(slot);

				std::cout << "Equipped " << Equipment::itemRarityToString.at(equipped.getItemRarity()) << " " << equipped.getItemName() << "\n";
				hudRenderer.refreshAbilitySlotsFromEquipment(player);
				return;
			}
		}
	}
}

void InventoryActions::dropOnInventory(Player& player, DragSource::DragState& dragState, equipmentArray& gameEquipment)
{
	if (dragState.source == DragSource::Source::EquippedSlot)
	{
		const auto& playerEquipment = player.getPlayerEquipment();
		const auto& old = player.getEquippedItem(equipmentSlotFromIndex(dragState.inventoryIndex));

		player.unequipEquipment(old.getEquipmentSlot());
		hudRenderer.refreshAbilitySlotsFromEquipment(player);

	}
	else if (dragState.source == DragSource::Source::MasterList)
	{
		const auto& masterEquipmentList = gameEquipment;
		const auto slotIndex = equipmentSlotToIndex(dragState.slot);

		if (slotIndex >= masterEquipmentList.size() || dragState.inventoryIndex >= masterEquipmentList[slotIndex].size())
			return;

		Equipment draggedItem = masterEquipmentList[slotIndex][dragState.inventoryIndex];

		player.getPlayerInventory().addEquipmentToInventory(draggedItem);
	}
}

void InventoryActions::drawBoxHelper(sf::RenderWindow& window, Player& player, DragSource::DragState& dragState, Equipment equipment) const
{
	sf::RectangleShape box({ 240.f, 20.f });
	box.setPosition(dragState.cursorPos + dragState.offset);
	box.setFillColor(sf::Color(0, 0, 0, 200));
	box.setOutlineThickness(2.f);
	box.setOutlineColor(sf::Color::Yellow);

	sf::Text text(uiFont, "", 16);
	text.setFillColor(sf::Color::White);
	text.setString(Equipment::itemRarityToString.at(equipment.getItemRarity()) + " " + equipment.getItemName());
	text.setPosition(dragState.cursorPos + dragState.offset);

	window.draw(box);
	window.draw(text);
}