#include "game.h"
#include "gameInitialize.h"
#include "save_load.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>

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
	gameMode = GameMode::Quit;
}

void Game::startFight()
{
	gameMode = GameMode::Combat;
	enemy = combatActions.spawnEnemy(Enemy::EnemyType::SLIME);
	enemy.changeCurrentHealth(enemy.getMaxHealth() - enemy.getCurrentHealth());
	player.changeCurrentHealth(player.getMaxHealth()); // heal to full before combat

	hudRenderer.refreshAbilitySlotsFromEquipment(player);
	std::cout << "Engaged " << enemy.getName() << "!\n";
}

void Game::loop(const equipmentArray& _gameEquipment)
{
	
	gameEquipment = _gameEquipment;


	sf::Clock clock;
	giveStartingItems();
	hudRenderer.refreshAbilitySlotsFromEquipment(player);

	float windowWidth = 1920;
	float windowHeight = 1080;
	sf::RenderWindow window(sf::VideoMode({ (unsigned)windowWidth, (unsigned)windowHeight }), "Inferno");
	//window.setKeyRepeatEnabled(false);


	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>() || gameMode == GameMode::Quit)
			{
				window.close();
			}

			handleEvent(*event, window);
		}

		float dt = clock.restart().asSeconds();
		update(dt, window);

		window.clear();

		draw(window, windowWidth, windowHeight);
		window.display();
	}

	for (size_t i = 0; i < buttonVectors.size(); i++)
	{
		delete buttonVectors[i];
	}
}

void Game::handleEvent(const sf::Event& _event, const sf::RenderWindow& window)
{
	if (auto* key = _event.getIf<sf::Event::KeyPressed>())
	{
		handleKeyPressed(*key, window);
	}
	else if (auto* text = _event.getIf<sf::Event::TextEntered>())
	{
		handleTextEntered(*text);
	}
	else if (auto* mousePressed = _event.getIf<sf::Event::MouseButtonPressed>())
	{
		handleMousePressed(*mousePressed, window);
	}
	else if (auto* mouseReleased = _event.getIf<sf::Event::MouseButtonReleased>())
	{
		handleMouseReleased(*mouseReleased, window);
	}
	else if (auto* mouseMoved = _event.getIf<sf::Event::MouseMoved>())
	{
		handleMouseMoved(*mouseMoved, window);
	}
}

void Game::handleKeyPressed(const sf::Event::KeyPressed& _keyPressed, const sf::RenderWindow& window)
{
	sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	if (gameMode == GameMode::Normal)
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
		case sf::Keyboard::Scancode::F: { startFight(); break; }
		case sf::Keyboard::Scancode::S: { pendingSave = true; break; }
		case sf::Keyboard::Scancode::L: { pendingLoad = true; break; }
		case sf::Keyboard::Scancode::Escape: { Quit(); break; }
		case sf::Keyboard::Scancode::B: 
		{
			if (keyTime >= keyTimeMax)
			{
				buttonVectors.emplace_back(new Button(pos));
				buttonVectors[buttonVectors.size()-1]->setButtonPosition(pos);
				keyTime = 0.f;
			}
			break;
		}
		default:
		{
			break;
		}
		}
	}
	if (gameMode == GameMode::Combat)
	{
		switch (_keyPressed.scancode)
		{
		case sf::Keyboard::Scancode::Num1: { hudRenderer.useAbility(0, player, enemy, gameMode); break; }
		case sf::Keyboard::Scancode::Num2: { hudRenderer.useAbility(1, player, enemy, gameMode); break; }
		case sf::Keyboard::Scancode::Num3: { hudRenderer.useAbility(2, player, enemy, gameMode); break; }
		case sf::Keyboard::Scancode::Num4: { hudRenderer.useAbility(3, player, enemy, gameMode); break; }
		case sf::Keyboard::Scancode::Num5: { hudRenderer.useAbility(4, player, enemy, gameMode); break; }
		case sf::Keyboard::Scancode::Escape: { gameMode = GameMode::Normal; break; }
		default:
			break;
		}
	}
}

void Game::handleTextEntered(const sf::Event::TextEntered& _textEntered)
{

}

void Game::handleMousePressed(const sf::Event::MouseButtonPressed _mousePressed, const sf::RenderWindow& window)
{
	if (_mousePressed.button == sf::Mouse::Button::Left)
	{
		leftMouseButtonPressed = true;
		sf::Vector2f clickPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		// check for starting drag from inventory sheet
		if (showInventorySheet)
		{
			const auto& inventory = player.getPlayerInventory().getEquipmentInventory();
			for (std::size_t i = 0; i < inventory.size() && i < inventoryItemRects.size(); ++i)
			{
				if (inventoryItemRects[i].contains(clickPos))
				{
					dragState.offset = { inventoryItemRects[i].position.x - clickPos.x,  inventoryItemRects[i].position.y - clickPos.y };
					dragState.active = true;
					dragState.source = DragSource::Source::Inventory;
					dragState.inventoryIndex = i;
					dragState.cursorPos = clickPos;
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
						dragState.offset = { slotRects[i].position.x - clickPos.x, slotRects[i].position.y - clickPos.y };
						dragState.active = true;
						dragState.source = DragSource::Source::EquippedSlot;
						dragState.slot = slot;
						dragState.inventoryIndex = i;
						dragState.cursorPos = clickPos;
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


						dragState.offset = { masterItemRects[flatIndex].position.x - clickPos.x,  masterItemRects[flatIndex].position.y - clickPos.y };
						dragState.active = true;
						dragState.source = DragSource::Source::MasterList;
						dragState.slot = equipmentSlotFromIndex(static_cast<int>(i));
						dragState.inventoryIndex = j;
						dragState.cursorPos = clickPos;
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

void Game::handleMouseReleased(const sf::Event::MouseButtonReleased _mouseReleased, const sf::RenderWindow& window)
{
	if (_mouseReleased.button == sf::Mouse::Button::Left)
	{
		leftMouseButtonPressed = false;

		if (dragState.active)
		{
			sf::Vector2f releasePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

			// try to drop on a slot
			handleDropOnCharacter(releasePos);
			handleDropOnInventory(releasePos);
			dragState.active = false;
			dragState.offset = { 0.f, 0.f };
			dragState.source = DragSource::Source::None;
		}
	}
	if (_mouseReleased.button == sf::Mouse::Button::Right)
	{
		rightMouseButtonPressed = false;
	}
}

void Game::handleMouseMoved(const sf::Event::MouseMoved _mouseMoved, const sf::RenderWindow& window)
{
	sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	dragState.cursorPos = pos;

	if (leftMouseButtonPressed)
	{
		mouseMoving = true;
	}
	else
	{
		mouseMoving = false;
	}
}

void Game::update(float dt, const sf::RenderWindow& window)
{
	if (pendingSave)
	{
		pendingSave = false;
	}
	else if (pendingLoad)
	{
		pendingLoad = false;
	}
	else if (gameMode == GameMode::Combat)
	{
		hudRenderer.updateCombat(dt, player, enemy, gameMode);
	}

	for (size_t i = 0; i < buttonVectors.size(); i++)
	{
		buttonVectors[i]->updateButton(window);
	}

	if (keyTime < keyTimeMax)
	{
		keyTime += 100.f;
	}
}

void Game::draw(sf::RenderWindow& window, float windowWidth, float windowHeight)
{
	if (gameMode == GameMode::Combat)
	{
		hudRenderer.drawCombat(window, player, enemy, windowWidth, windowHeight);
	}
	else if (gameMode == GameMode::Normal)
	{
		if (showCharacterSheet)
		{
			characterRenderer.drawPlayerCharacterSheet(window, player, slotRects, windowWidth, windowHeight);
		}
		if (showInventorySheet)
		{
			inventoryRenderer.drawInventorySheet(window, player, inventoryItemRects, inventoryRect, windowWidth, windowHeight);
		}
		if (showMasterEquipmentSheet)
		{
			inventoryRenderer.drawMasterEquipmentSheet(window, masterItemRects, gameEquipment, windowWidth, windowHeight);
			for (size_t i = 0; i < buttonVectors.size(); i++)
			{
				buttonVectors[i]->render(window);
			}
		}
		if (dragState.active)
		{
			if (dragState.source == DragSource::Source::Inventory)
			{
				inventoryActions.dragFromInventory(window, player, dragState);
			}
			else if (dragState.source == DragSource::Source::EquippedSlot)
			{
				inventoryActions.dragFromEquippedSlot(window, player, dragState);
			}
			else if (dragState.source == DragSource::Source::MasterList)
			{
				inventoryActions.dragFromMasterList(window, player, dragState, gameEquipment);
			}
		}
	}
}

void Game::handleDropOnCharacter(const sf::Vector2f& dropPos)
{
	if (!showCharacterSheet)
		return;

	inventoryActions.dropOnPlayerSlot(dropPos, player, dragState, gameEquipment, slotRects);
}

void Game::handleDropOnInventory(const sf::Vector2f& dropPos)
{
	if (!showInventorySheet || !inventoryRect.getGlobalBounds().contains(dropPos))
		return;

	inventoryActions.dropOnInventory(player, dragState, gameEquipment);
}
