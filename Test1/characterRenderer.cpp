#include "characterRenderer.h"



void CharacterRenderer::drawPlayerCharacterSheet(sf::RenderWindow& window, Player& player, slotFloatRects& slotRects, float windowWidth, float windowHeight) const
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