#include "inventoryRenderer.h"

void InventoryRenderer::drawInventorySheet(sf::RenderWindow& window, Player& player, std::vector<sf::FloatRect>& inventoryItemRects,
	sf::RectangleShape& inventoryRect, float windowWidth, float windowHeight) const
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
			std::string rarity = itemRarityToString.at(equipment.getItemRarity());
			std::string name = equipment.getItemName();
			writeLine(rarity + " " + name);
		};

	for (const auto& eq : inventory)
	{

		printEquipment(eq);
	}
}

void InventoryRenderer::drawMasterEquipmentSheet(sf::RenderWindow& window, std::vector<sf::FloatRect>& masterItemRects,
	equipmentArray& gameEquipment, float windowWidth, float windowHeight) const
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
			std::string rarity = itemRarityToString.at(equipment.getItemRarity());
			std::string name = equipment.getItemName();
			writeLine(rarity + " " + name);
		};

	for (const auto& eqs : masterEquipmentList)
	{
		for (const auto& eq : eqs)
		{
			count++;
			printEquipment(eq);
		}
	}
}