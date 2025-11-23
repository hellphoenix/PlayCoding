#include "game.h"
#include "gameInitialize.h"
#include "save_load.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

Game::Game()
{
	if (!uiFont.openFromFile("assets/Arial.ttf"))
	{
		std::cout << "Failed to load UI font. Check path.\n";
	}
}

//void Game::save(const sf::Event::TextEntered& _text)
//{
//	if (mode == Mode::Save)
//	{
//		if (_text.unicode == '\r' || _text.unicode == '\n')
//		{
//			if (!textBuffer.empty())
//			{
//				std::string saveName = textBuffer;
//				saveName.append(".json");
//				if (SaveLoad::saveToFile(player, saveName))
//					std::cout << "\nSaved to " << saveName << "\n";
//				else
//					std::cout << "Save failed.\n";
//
//				std::cout << "Type 'h' to see available commands.\n";
//			}
//			textBuffer.clear();
//			mode = Mode::Normal;
//			return;
//		}
//
//		else if (_text.unicode == 27) // Escape
//		{
//			textBuffer.clear();
//			mode = Mode::Normal;
//			std::cout << "\nSave canceled.\n";
//			std::cout << "\nType 'h' to see available commands.\n";
//			return;
//		}
//
//		else if (_text.unicode == 8) // Backspace
//		{
//			if (!textBuffer.empty())
//				textBuffer.pop_back();
//			std::cout << "\rSave file name(e.g. save1) : " << textBuffer << " " << std::flush;
//			return;
//		}
//
//		else if (_text.unicode < 32 || _text.unicode > 126)
//			return;
//
//		textBuffer.push_back(static_cast<char>(_text.unicode));
//		std::cout << "\rSave file name(e.g. save1) : " << textBuffer << " " << std::flush;
//	}
//}

//void Game::load(const sf::Event::TextEntered& _text)
//{
//	if (mode == Mode::Load)
//	{
//		if (_text.unicode == '\r' || _text.unicode == '\n')
//		{
//			if (!textBuffer.empty())
//			{
//				Player loaded;
//				std::string loadName = textBuffer;
//				loadName.append(".json");
//				if (SaveLoad::loadFromFile(loaded, loadName)) {
//					player = std::move(loaded);
//					std::cout << "Loaded from " << loadName << "\n";
//					player.updateMaxStats();
//					//player.printPlayer();
//					//player.getPlayerInventory().printEquipmentInventory();
//				}
//				else {
//					std::cout << "Load failed.\n";
//				}
//				std::cout << "\nType 'h' to see available commands.\n";
//			}
//			textBuffer.clear();
//			mode = Mode::Normal;
//			return;
//		}
//
//		else if (_text.unicode == 27) // Escape
//		{
//			textBuffer.clear();
//			mode = Mode::Normal;
//			std::cout << "\nLoad canceled.\n";
//			std::cout << "\nType 'h' to see available commands.\n";
//			return;
//		}
//
//		else if (_text.unicode == 8) // Backspace
//		{
//			if (!textBuffer.empty())
//				textBuffer.pop_back();
//			std::cout << "\rLoad file name (e.g. save1): " << textBuffer << " " << std::flush;
//			return;
//		}
//
//		else if (_text.unicode < 32 || _text.unicode > 126)
//			return;
//
//		textBuffer.push_back(static_cast<char>(_text.unicode));
//		std::cout << "\rLoad file name (e.g. save1): " << textBuffer << " " << std::flush;
//	}
//}

void Game::Quit()
{
	std::cout << "Exiting game.\n";
	mode = Mode::Quit;
}

void Game::startFight()
{
	//TODO
}

void Game::loop(std::array<std::vector<Equipment>, equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT)>& _gameEquipment)
{

	sf::Clock clock;
	enemy = combatActions.spawnEnemy(Enemy::EnemyType::SLIME);

	gameEquipment = _gameEquipment;
	giveStartingItems();

	float windowWidth = 1920;
	float windowHeight = 1080;
	sf::RenderWindow window(sf::VideoMode({ (unsigned)windowWidth, (unsigned)windowHeight }), "Play Coding");
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
		draw(window, windowWidth, windowHeight);
		window.display();
	}
}

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
		handleMousePressed(*mousePressed);
	}
	else if (auto* mouseReleased = _event.getIf<sf::Event::MouseButtonReleased>())
	{
		handleMouseReleased(*mouseReleased);
	}
	else if (auto* mouseMoved = _event.getIf<sf::Event::MouseMoved>())
	{
		handleMouseMoved(*mouseMoved);
	}
}

void Game::handleKeyPressed(const sf::Event::KeyPressed& _keyPressed)
{
	if (mode == Mode::Normal)
	{
		switch (_keyPressed.scancode)
		{
		case sf::Keyboard::Scancode::C: {
			showCharacterSheet = !showCharacterSheet;
			break;
		}
		case sf::Keyboard::Scancode::I: {
			showInventorySheet = !showInventorySheet;
			break;
		}
		case sf::Keyboard::Scancode::M: {
			showMasterEquipmentSheet = !showMasterEquipmentSheet;
			break;
		}
		case sf::Keyboard::Scancode::S: { pendingSave = true; break; }
		case sf::Keyboard::Scancode::L: { pendingLoad = true; break; }
		case sf::Keyboard::Scancode::Escape: { Quit(); break; }
		default:
		{
			break;
		}
		}
	}
}

void Game::handleTextEntered(const sf::Event::TextEntered& _textEntered)
{

	//if (mode == Mode::DebugAddToInventoryItem || mode == Mode::DebugRemoveFromInventoryItem)
	//{
	//	NumberInputKey key;
	//	char digit = 0;
	//	if (_textEntered.unicode == '\r' || _textEntered.unicode == '\n')
	//	{
	//		key = NumberInputKey::Confirm;
	//	}
	//	else if (_textEntered.unicode == 27)   // Escape
	//	{
	//		key = NumberInputKey::Cancel;
	//	}
	//	else if (_textEntered.unicode == 8)    // Backspace
	//	{
	//		key = NumberInputKey::Backspace;
	//	}
	//	else if (_textEntered.unicode >= '0' && _textEntered.unicode <= '9')
	//	{
	//		key = NumberInputKey::Digit;
	//		digit = static_cast<char>(_textEntered.unicode);
	//	}
	//	else
	//	{
	//		return; // ignore other input
	//	}
	//	switch (mode)
	//	{
	//		//case Mode::EquipSelectItem: { inventoryActions.handleEquipItemInput(key, digit, player, normal); break; }
	//	case Mode::DebugAddToInventoryItem: { inventoryActions.debugAddToInventoryItemInput(key, digit, player, normal); break; }
	//	case Mode::DebugRemoveFromInventoryItem: { inventoryActions.debugRemoveFromInventory(key, digit, player, normal); break; }
	//	}
	//}
	//else
	//{
	//	switch (mode)
	//	{
	//	/*case Mode::DebugName: { debugName(_textEntered); break; }
	//	case Mode::DebugAttack: { debugAttack(_textEntered); break; }
	//	case Mode::DebugDefense: { debugDefense(_textEntered); break; }
	//	case Mode::DebugHealth: { debugHealth(_textEntered); break; }*/
	//	case Mode::Save: { save(_textEntered); break; }
	//	case Mode::Load: { load(_textEntered); break; }
	//	default: break;
	//	}
	//}
}

void Game::handleMousePressed(const sf::Event::MouseButtonPressed _mousePressed)
{
	if (_mousePressed.button == sf::Mouse::Button::Left)
	{
		leftMouseButtonPressed = true;
		sf::Vector2f clickPos{
				static_cast<float>(_mousePressed.position.x),
				static_cast<float>(_mousePressed.position.y)
		};
		// check for starting drag from inventory sheet
		if (showInventorySheet)
		{
			const auto& inventory = player.getPlayerInventory().getEquipmentInventory();
			for (std::size_t i = 0; i < inventory.size() && i < inventoryItemRects.size(); ++i)
			{
				if (inventoryItemRects[i].contains(clickPos))
				{
					drag.offset = { inventoryItemRects[i].position.x - clickPos.x,  inventoryItemRects[i].position.y - clickPos.y };
					drag.active = true;
					drag.source = DragSource::Inventory;
					drag.inventoryIndex = i;
					drag.cursorPos = clickPos;
					break;
				}
			}
		}
		if (showCharacterSheet)
		{

			for (std::size_t i = 0; i < equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT); i++)
			{
				if (slotRects[i].contains(clickPos))
				{
					Equipment::EquipmentSlot slot = equipmentSlotFromIndex(i);

					const auto& playerEquipment = player.getPlayerEquipment();
					if (!playerEquipment[i].getId().empty())
					{
						drag.offset = { slotRects[i].position.x - clickPos.x, slotRects[i].position.y - clickPos.y };
						drag.active = true;
						drag.source = DragSource::EquippedSlot;
						drag.slot = slot;
						drag.inventoryIndex = i;
						drag.cursorPos = clickPos;
					}
					break;
				}
			}

		}
		if (showMasterEquipmentSheet)
		{
			const auto& masterEquipmentList = gameEquipment;
			int index = 0;
			for (std::size_t i = 1; i < equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT); ++i)
			{
				for (std::size_t j = 0; j < masterEquipmentList[i].size(); j++)
				{
					const std::size_t flatIndex = index;/* however you built masterItemRects, same order */;
					index++;
					if (masterItemRects[flatIndex].contains(clickPos))
					{


						drag.offset = { masterItemRects[flatIndex].position.x - clickPos.x,  masterItemRects[flatIndex].position.y - clickPos.y };
						drag.active = true;
						drag.source = DragSource::MasterList;
						drag.slot = equipmentSlotFromIndex(static_cast<int>(i));
						drag.inventoryIndex = j;
						drag.cursorPos = clickPos;
						break;
					}
				}
			}
		}
	}
	if (_mousePressed.button == sf::Mouse::Button::Right)
	{
		rightMouseButtonPressed = true;
	}
}

void Game::handleMouseReleased(const sf::Event::MouseButtonReleased _mouseReleased)
{
	if (_mouseReleased.button == sf::Mouse::Button::Left)
	{
		leftMouseButtonPressed = false;

		if (drag.active)
		{
			sf::Vector2f releasePos{
				static_cast<float>(_mouseReleased.position.x),
				static_cast<float>(_mouseReleased.position.y)
			};

			// try to drop on a slot
			handleDropOnCharacter(releasePos);
			handleDropOnInventory(releasePos);
			drag.active = false;
			drag.offset = { 0.f, 0.f };
			drag.source = DragSource::None;
		}
	}
	if (_mouseReleased.button == sf::Mouse::Button::Right)
	{
		rightMouseButtonPressed = false;
	}
}

void Game::handleMouseMoved(const sf::Event::MouseMoved _mouseMoved)
{
	sf::Vector2f pos{ static_cast<float>(_mouseMoved.position.x), static_cast<float>(_mouseMoved.position.y) };
	drag.cursorPos = pos;

	if (leftMouseButtonPressed)
	{
		mouseMoving = true;
		//std::cout << "The mouse is moving!\n";
	}
	else
	{
		mouseMoving = false;
	}
}

void Game::update(float dt)
{
	if (pendingSave)
	{
		pendingSave = false;
	}
	else if (pendingLoad)
	{
		pendingLoad = false;
	}
	else if (normal)
	{
		normal = false;
		mode = Mode::Normal;
	}
}

void Game::draw(sf::RenderWindow& window, float windowWidth, float windowHeight)
{
	if (showCharacterSheet)
	{
		drawCharacterSheet(window, windowWidth, windowHeight);
	}
	if (showInventorySheet)
	{
		drawInventorySheet(window, windowWidth, windowHeight);
	}
	if (showMasterEquipmentSheet)
	{
		drawMasterEquipmentSheet(window, windowWidth, windowHeight);
	}


	if (drag.active)
	{
		if (drag.source == DragSource::Inventory)
		{
			const auto& inventory = player.getPlayerInventory().getEquipmentInventory();
			if (drag.inventoryIndex < inventory.size())
			{
				const auto& equipment = inventory[drag.inventoryIndex];

				sf::RectangleShape box({ 240.f, 20.f });
				box.setPosition(drag.cursorPos + drag.offset);
				box.setFillColor(sf::Color(0, 0, 0, 200));
				box.setOutlineThickness(2.f);
				box.setOutlineColor(sf::Color::Yellow);

				sf::Text text(uiFont, "", 16);
				text.setFillColor(sf::Color::White);
				text.setString(Equipment::itemRarityToString.at(equipment.getItemRarity()) + " " + equipment.getItemName());
				text.setPosition(drag.cursorPos + drag.offset);

				window.draw(box);
				window.draw(text);
			}
		}
		else if (drag.source == DragSource::EquippedSlot)
		{
			const auto& equipment = player.getEquippedItem(equipmentSlotFromIndex(drag.inventoryIndex));

			sf::RectangleShape box({ 260.f, 20.f });
			box.setPosition(drag.cursorPos + drag.offset);
			box.setFillColor(sf::Color(0, 0, 0, 200));
			box.setOutlineThickness(2.f);
			box.setOutlineColor(sf::Color::Yellow);

			sf::Text text(uiFont, "", 16);
			text.setFillColor(sf::Color::White);
			text.setString(Equipment::itemRarityToString.at(equipment.getItemRarity()) + " " + equipment.getItemName());
			text.setPosition(drag.cursorPos + drag.offset);

			window.draw(box);
			window.draw(text);
		}
		else if (drag.source == DragSource::MasterList)
		{

			const auto& masterEquipmentList = gameEquipment;
			const auto slotIndex = equipmentSlotToIndex(drag.slot);

			if (slotIndex >= masterEquipmentList.size())
				return;
			if (drag.inventoryIndex >= masterEquipmentList[slotIndex].size())
				return;

			Equipment draggedItem = masterEquipmentList[slotIndex][drag.inventoryIndex];

				sf::RectangleShape box({ 240.f, 20.f });
				box.setPosition(drag.cursorPos + drag.offset);
				box.setFillColor(sf::Color(0, 0, 0, 200));
				box.setOutlineThickness(2.f);
				box.setOutlineColor(sf::Color::Yellow);

				sf::Text text(uiFont, "", 16);
				text.setFillColor(sf::Color::White);
				text.setString(Equipment::itemRarityToString.at(draggedItem.getItemRarity()) + " " + draggedItem.getItemName());
				text.setPosition(drag.cursorPos + drag.offset);

				window.draw(box);
				window.draw(text);
			
		}

	}

}

void Game::drawCharacterSheet(sf::RenderWindow& window, float windowWidth, float windowHeight)
{
	sf::RectangleShape panel({ 300.f, 400.f });
	panel.setPosition(sf::Vector2f{ 20.f, 20.f });
	panel.setFillColor(sf::Color(0, 0, 0, 180));
	panel.setOutlineThickness(2.f);
	panel.setOutlineColor(sf::Color::White);

	window.draw(panel);

	slotRects.fill(sf::FloatRect{}); // reset each frame

	if (uiFont.getInfo().family.empty())
	{
		// font failed to load, do not try to draw text
		return;
	}

	sf::Text text(uiFont, "", 16);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);

	float x = panel.getPosition().x + 10.f;
	float y = panel.getPosition().y + 10.f;

	auto writeLine = [&](const std::string& line)
		{
			text.setString(line);
			text.setPosition(sf::Vector2f{ x, y });
			window.draw(text);
			y += 20.f;
		};

	writeLine("Name: " + player.getName());
	//writeLine("Level: " + std::to_string(player.getLevel()));   // if you add one
	writeLine("");

	writeLine("Base HP: " + std::to_string(player.getBaseHealth()));
	writeLine("Max HP:  " + std::to_string(player.getMaxHealth()));
	writeLine("ATK:     " + std::to_string(player.getMaxAttack()));
	writeLine("DEF:     " + std::to_string(player.getMaxDefense()));
	writeLine("");

	// equipped items
	const auto& equipped = player.getPlayerEquipment();

	auto printSlot = [&](Equipment::EquipmentSlot slot, const std::string& label)
		{
			std::size_t index = equipmentSlotToIndex(slot);
			const auto& item = equipped[index];
			std::string rarity = item.getId().empty() ? " " : item.itemRarityToString.at(item.getItemRarity());
			std::string name = item.getId().empty() ? "(none)" : item.getItemName();

			// compute position but do not move y yet
			sf::Vector2f textPos{ x, y };
			text.setString(label + ": " + rarity + " " + name);
			text.setPosition(textPos);
			// define a drop zone for this slot
			sf::FloatRect rect({ textPos.x, textPos.y }, { 260.f, 20.f });
			slotRects[index] = rect;
			window.draw(text);
			y += 20.f;
		};

	for (int i = 1; i < equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT); i++)
	{
		auto slot = equipmentSlotFromIndex(i);
		printSlot(slot, Equipment::equipmentSlotToString.at(slot));
	}
}

void Game::drawInventorySheet(sf::RenderWindow& window, float windowWidth, float windowHeight)
{
	inventoryItemRects.clear();  // rebuild each frame
	sf::RectangleShape inventoryPanel({ 300.f, 400.f });
	inventoryPanel.setPosition(sf::Vector2f{ (windowWidth - 320.f), 20.f });
	inventoryPanel.setFillColor(sf::Color(0, 0, 0, 180));
	inventoryPanel.setOutlineThickness(2.f);
	inventoryPanel.setOutlineColor(sf::Color::White);

	window.draw(inventoryPanel);
	inventoryRect = inventoryPanel;

	if (uiFont.getInfo().family.empty())
	{
		// font failed to load, do not try to draw text
		return;
	}

	sf::Text text(uiFont, "", 16);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);

	float x = inventoryPanel.getPosition().x + 10.f;
	float y = inventoryPanel.getPosition().y + 10.f;

	auto writeLine = [&](const std::string& line)
		{
			sf::RectangleShape linePanel({ 240.f, 20.f });
			linePanel.setPosition(sf::Vector2f{ x, y });
			linePanel.setFillColor(sf::Color(0, 0, 0, 180));
			linePanel.setOutlineThickness(2.f);
			linePanel.setOutlineColor(sf::Color::White);
			float lx = linePanel.getPosition().x;
			float ly = linePanel.getPosition().y;
			inventoryItemRects.push_back(linePanel.getGlobalBounds());
			text.setString(line);
			text.setPosition(sf::Vector2f{ lx, ly });
			window.draw(linePanel);
			window.draw(text);
			y += 30.f;
		};
	auto writeHeadLine = [&](const std::string& line)
		{
			text.setString(line);
			text.setPosition(sf::Vector2f{ x, y });
			window.draw(text);
			y += 30.f;
		};

	writeHeadLine("Inventory:");
	//writeLine("Level: " + std::to_string(player.getLevel()));   // if you add one
	writeHeadLine("");

	// equipped items
	const auto& inventory = player.getPlayerInventory().getEquipmentInventory();

	auto printEquipment = [&](const Equipment equipment)
		{
			std::string rarity = equipment.itemRarityToString.at(equipment.getItemRarity());
			std::string name = equipment.getItemName();
			writeLine(rarity + " " + name);
		};

	for (const auto& eq : inventory)
	{

		printEquipment(eq);
	}
}

void Game::drawMasterEquipmentSheet(sf::RenderWindow& window, float windowWidth, float windowHeight)
{
	masterItemRects.clear();
	float newWindowHeight = windowHeight * 0.3f;
	sf::RectangleShape panel({ windowWidth - 40.f, newWindowHeight });
	panel.setPosition(sf::Vector2f{ 20.f, (windowHeight - newWindowHeight) - 20.f });
	panel.setFillColor(sf::Color(0, 0, 0, 180));
	panel.setOutlineThickness(2.f);
	panel.setOutlineColor(sf::Color::White);

	window.draw(panel);

	if (uiFont.getInfo().family.empty())
	{
		// font failed to load, do not try to draw text
		return;
	}

	sf::Text text(uiFont, "", 16);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);

	float x = panel.getPosition().x + 10.f;
	float y = panel.getPosition().y + 10.f;
	int count = 0;

	auto writeLine = [&](const std::string& line)
		{
			sf::RectangleShape linePanel({ 240.f, 20.f });
			linePanel.setPosition(sf::Vector2f{ x, y });
			linePanel.setFillColor(sf::Color(0, 0, 0, 180));
			linePanel.setOutlineThickness(2.f);
			linePanel.setOutlineColor(sf::Color::White);
			float lx = linePanel.getPosition().x;
			float ly = linePanel.getPosition().y;
			masterItemRects.push_back(linePanel.getGlobalBounds());
			text.setString(line);
			text.setPosition(sf::Vector2f{ lx, ly });
			window.draw(linePanel);
			window.draw(text);
			y += 30.f;
			if (count >= 10)
			{
				y = panel.getPosition().y + 10.f;
				x += 250.f;
				count = 0;
			}
		};

	// equipped items
	const auto& masterEquipmentList = gameEquipment;

	auto printEquipment = [&](const Equipment equipment)
		{
			std::string rarity = equipment.itemRarityToString.at(equipment.getItemRarity());
			std::string name = equipment.getItemName();
			writeLine(rarity + " " + name);
		};

	for (int i = 1; i < equipmentSlotToIndex(Equipment::EquipmentSlot::COUNT); i++)
	{
		for (const auto& eq : masterEquipmentList[i])
		{
			count++;
			printEquipment(eq);
		}
	}
}

void Game::handleDropOnCharacter(const sf::Vector2f& dropPos)
{
	if (!showCharacterSheet)
		return;

	if (drag.source == DragSource::Inventory)
	{
		const auto& inventory = player.getPlayerInventory().getEquipmentInventory();
		if (drag.inventoryIndex >= inventory.size())
			return;

		const auto& draggedItem = inventory[drag.inventoryIndex];
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
				return;
			}
		}
	}
	else if (drag.source == DragSource::MasterList)
	{

		const auto& masterEquipmentList = gameEquipment;
		const auto slotIndex = equipmentSlotToIndex(drag.slot);

		if (slotIndex >= masterEquipmentList.size() || drag.inventoryIndex >= masterEquipmentList[slotIndex].size())
			return;

		Equipment draggedItem = masterEquipmentList[slotIndex][drag.inventoryIndex];
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
				return;
			}
		}

	}
}

void Game::handleDropOnInventory(const sf::Vector2f& dropPos)
{
	if (!showInventorySheet || !inventoryRect.getGlobalBounds().contains(dropPos))
		return;

	if (drag.source == DragSource::EquippedSlot)
	{
		const auto& playerEquipment = player.getPlayerEquipment();
		const auto& old = player.getEquippedItem(equipmentSlotFromIndex(drag.inventoryIndex));

		player.unequipEquipment(old.getEquipmentSlot());
		
	}
	else if (drag.source == DragSource::MasterList)
	{
		const auto& masterEquipmentList = gameEquipment;
		const auto slotIndex = equipmentSlotToIndex(drag.slot);

		if (slotIndex >= masterEquipmentList.size() || drag.inventoryIndex >= masterEquipmentList[slotIndex].size())
			return;

		Equipment draggedItem = masterEquipmentList[slotIndex][drag.inventoryIndex];

		player.getPlayerInventory().addEquipmentToInventory(draggedItem);
	}

}
