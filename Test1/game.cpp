#include "game.h"
#include "gameInitialize.h"
#include "save_load.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>

void Game::Quit()
{
	std::cout << "Exiting game.\n";
	gameMode = GameMode::Quit;
}

void Game::startFight()
{
	gameMode = GameMode::Combat;
	enemy = combatActions.spawnEnemy(EnemyType::SLIME);
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
	// TODO for Player name input
}

void Game::handleMousePressed(const sf::Event::MouseButtonPressed& _mousePressed, const sf::RenderWindow& window)
{
	if (_mousePressed.button == sf::Mouse::Button::Left)
	{
		leftMouseButtonPressed = true;
		sf::Vector2f clickPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		if (showInventorySheet)
		{
			const auto& inventory = player.getPlayerInventory().getEquipmentInventory();
			for (std::size_t i = 0; i < inventory.size() && i < inventoryItemRects.size(); ++i)
			{
				if (inventoryItemRects[i].contains(clickPos))
				{
					mouseDragCheck.drag.offset = { inventoryItemRects[i].position.x - clickPos.x,  inventoryItemRects[i].position.y - clickPos.y };
					mouseDragCheck.drag.active = true;
					mouseDragCheck.drag.source = DragSource::Inventory;
					mouseDragCheck.drag.inventoryIndex = i;
					mouseDragCheck.drag.cursorPos = clickPos;
					break;
				}
			}
		}
		if (showCharacterSheet)
		{

			for (int i = 0; i < equipmentSlotToIndex(EquipmentSlot::COUNT); i++)
			{
				if (slotRects[i].contains(clickPos))
				{
					EquipmentSlot slot = equipmentSlotFromIndex(i);

					const auto& playerEquipment = player.getPlayerEquipment();
					if (!playerEquipment[i].getId().empty())
					{
						mouseDragCheck.drag.offset = { slotRects[i].position.x - clickPos.x, slotRects[i].position.y - clickPos.y };
						mouseDragCheck.drag.active = true;
						mouseDragCheck.drag.source = DragSource::EquippedSlot;
						mouseDragCheck.drag.slot = slot;
						mouseDragCheck.drag.inventoryIndex = i;
						mouseDragCheck.drag.cursorPos = clickPos;
					}
					break;
				}
			}

		}
		if (showMasterEquipmentSheet)
		{
			const auto& masterEquipmentList = gameEquipment;
			std::size_t index = -1;
			for (int i = 1; i < equipmentSlotToIndex(EquipmentSlot::COUNT); ++i)
			{
				for (std::size_t j = 0; j < masterEquipmentList[i].size(); j++)
				{
					index++;
					if (masterItemRects[index].contains(clickPos))
					{
						mouseDragCheck.drag.offset = { masterItemRects[index].position.x - clickPos.x,  masterItemRects[index].position.y - clickPos.y };
						mouseDragCheck.drag.active = true;
						mouseDragCheck.drag.source = DragSource::MasterList;
						mouseDragCheck.drag.slot = equipmentSlotFromIndex(i);
						mouseDragCheck.drag.inventoryIndex = j;
						mouseDragCheck.drag.cursorPos = clickPos;
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

void Game::handleMouseReleased(const sf::Event::MouseButtonReleased& _mouseReleased, const sf::RenderWindow& window)
{
	if (_mouseReleased.button == sf::Mouse::Button::Left)
	{
		leftMouseButtonPressed = false;

		if (mouseDragCheck.drag.active)
		{
			sf::Vector2f releasePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

			// try to drop on a slot
			handleDropOnCharacter(releasePos);
			handleDropOnInventory(releasePos);
			mouseDragCheck.drag.active = false;
			mouseDragCheck.drag.offset = { 0.f, 0.f };
			mouseDragCheck.drag.source = DragSource::None;
		}
	}
	if (_mouseReleased.button == sf::Mouse::Button::Right)
	{
		rightMouseButtonPressed = false;
	}
}

void Game::handleMouseMoved(const sf::Event::MouseMoved& _mouseMoved, const sf::RenderWindow& window)
{
	sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	mouseDragCheck.drag.cursorPos = pos;

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
		if (mouseDragCheck.drag.active)
		{
			if (mouseDragCheck.drag.source == DragSource::Inventory)
			{
				inventoryActions.dragFromInventory(window, player, mouseDragCheck.drag);
			}
			else if (mouseDragCheck.drag.source == DragSource::EquippedSlot)
			{
				inventoryActions.dragFromEquippedSlot(window, player, mouseDragCheck.drag);
			}
			else if (mouseDragCheck.drag.source == DragSource::MasterList)
			{
				inventoryActions.dragFromMasterList(window, player, mouseDragCheck.drag, gameEquipment);
			}
		}
	}
}

void Game::handleDropOnCharacter(const sf::Vector2f& dropPos)
{
	if (!showCharacterSheet)
		return;

	inventoryActions.dropOnPlayerSlot(dropPos, player, mouseDragCheck.drag, gameEquipment, slotRects);
}

void Game::handleDropOnInventory(const sf::Vector2f& dropPos)
{
	if (!showInventorySheet || !inventoryRect.getGlobalBounds().contains(dropPos))
		return;

	inventoryActions.dropOnInventory(player, mouseDragCheck.drag, gameEquipment);
}
