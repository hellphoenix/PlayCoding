#include "hudRenderer.h"
#include "combatActions.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>


void HudRenderer::drawCombat(sf::RenderWindow& window, const Player& player, const Enemy& enemy, float windowWidth, float windowHeight)
{
	float panelHeight = 240.f;
	sf::RectangleShape panel({ windowWidth - 40.f, panelHeight });
	panel.setPosition(sf::Vector2f{ 20.f, 440.f });
	panel.setFillColor(sf::Color(25, 25, 25, 220));
	panel.setOutlineThickness(2.f);
	panel.setOutlineColor(sf::Color::Red);
	window.draw(panel);

	if (uiFont.getInfo().family.empty())
		return;

	sf::Text text(uiFont, "", 18);
	text.setFillColor(sf::Color::White);

	auto drawBar = [&](float x, float y, float width, float height, int current, int max, const std::string& label, const sf::Color& fill)
		{
			float pct = max > 0 ? static_cast<float>(current) / static_cast<float>(max) : 0.f;
			pct = std::clamp(pct, 0.f, 1.f);

			sf::RectangleShape back({ width, height });
			back.setPosition({ x, y });
			back.setFillColor(sf::Color(40, 40, 40, 200));
			back.setOutlineThickness(1.f);
			back.setOutlineColor(sf::Color::White);

			sf::RectangleShape front({ width * pct, height });
			front.setPosition({ x, y });
			front.setFillColor(fill);

			text.setString(label + " " + std::to_string(current) + "/" + std::to_string(max));
			text.setPosition({ x + 10.f, y - 24.f });

			window.draw(back);
			window.draw(front);
			window.draw(text);
		};

	float barWidth = panel.getSize().x - 80.f;
	drawBar(panel.getPosition().x + 30.f, panel.getPosition().y + 40.f, barWidth, 24.f, player.getCurrentHealth(), player.getMaxHealth(), "Player HP", sf::Color(70, 200, 90));
	drawBar(panel.getPosition().x + 30.f, panel.getPosition().y + 110.f, barWidth, 24.f, enemy.getCurrentHealth(), enemy.getMaxHealth(), enemy.getName() + " HP", sf::Color(200, 60, 60));

	// auto-attack timers
	float timerY = panel.getPosition().y + 170.f;
	float timerWidth = 220.f;
	auto drawTimer = [&](float x, const std::string& label, float timer, float interval)
		{
			float pct = std::clamp(1.f - (timer / interval), 0.f, 1.f);
			sf::RectangleShape back({ timerWidth, 16.f });
			back.setPosition({ x, timerY });
			back.setFillColor(sf::Color(30, 30, 30, 200));
			back.setOutlineThickness(1.f);
			back.setOutlineColor(sf::Color::White);

			sf::RectangleShape front({ timerWidth * pct, 16.f });
			front.setPosition({ x, timerY });
			front.setFillColor(sf::Color(120, 120, 220));

			text.setString(label);
			text.setPosition({ x, timerY - 22.f });

			window.draw(back);
			window.draw(front);
			window.draw(text);
		};

	drawTimer(panel.getPosition().x + 30.f, "Player auto", playerAutoAttackTimer, playerAutoAttackInterval);
	drawTimer(panel.getPosition().x + 300.f, "Enemy auto", enemyAutoAttackTimer, enemyAutoAttackInterval);

	// ability bar
	float abilityY = panel.getPosition().y + panelHeight - 50.f;
	float abilityWidth = 250.f;
	float abilityX = panel.getPosition().x + 30.f;

	for (std::size_t i = 0; i < abilitySlots.size(); ++i)
	{
		const auto& ability = abilitySlots[i];
		sf::RectangleShape slotBox({ abilityWidth, 26.f });
		slotBox.setPosition({ abilityX + static_cast<float>(i) * (abilityWidth + 10.f), abilityY });
		slotBox.setFillColor(sf::Color(50, 50, 50, 220));
		slotBox.setOutlineThickness(1.f);
		slotBox.setOutlineColor(sf::Color::White);

		std::string label = std::to_string(i + 1) + ") " + (ability.name.empty() ? "Empty" : ability.name);
		if (!ability.isReady() && ability.cooldown > 0.f)
		{
			float remaining = std::max(0.f, ability.timer);
			label += " (" + std::to_string(static_cast<int>(std::ceil(remaining))) + "s)";
		}

		text.setString(label);
		text.setPosition(slotBox.getPosition() + sf::Vector2f{ 6.f, 2.f });

		window.draw(slotBox);

		if (!ability.isReady())
		{
			float pct = ability.cooldown > 0.f ? std::clamp(ability.timer / ability.cooldown, 0.f, 1.f) : 0.f;
			sf::RectangleShape cooldownMask({ abilityWidth, 26.f * pct });
			cooldownMask.setPosition(slotBox.getPosition());
			cooldownMask.setFillColor(sf::Color(0, 0, 0, 120));
			window.draw(cooldownMask);
		}

		window.draw(text);
	}
}

void HudRenderer::updateCombat(float dt, Player& player, Enemy& enemy, GameMode& mode)
{
	playerAutoAttackTimer += dt;
	enemyAutoAttackTimer += dt;

	for (auto& slot : abilitySlots)
	{
		slot.update(dt);
	}

	if (mode != GameMode::Combat)
		return;

	if (playerAutoAttackTimer >= playerAutoAttackInterval && enemy.isAlive())
	{
		playerAutoAttackTimer = 0.f;
		int damage = combatActions.playerAttack(enemy, player);
		enemy.changeCurrentHealth(-damage);
		std::cout << "Auto attack deals " << damage << " damage. Enemy HP: " << enemy.getCurrentHealth() << "/" << enemy.getMaxHealth() << "\n";
	}

	if (enemyAutoAttackTimer >= enemyAutoAttackInterval && enemy.isAlive())
	{
		enemyAutoAttackTimer = 0.f;
		int damage = combatActions.enemyAttack(enemy, player);
		player.changeCurrentHealth(-damage);
		std::cout << enemy.getName() << " hits for " << damage << " damage. Player HP: " << player.getCurrentHealth() << "/" << player.getMaxHealth() << "\n";
	}

	if (!enemy.isAlive())
	{
		mode = GameMode::Normal;
		std::cout << "Enemy defeated!\n";
		return;
	}

	if (player.getCurrentHealth() <= 0)
	{
		mode = GameMode::Normal;
		std::cout << "You were defeated.\n";
		player.changeCurrentHealth(player.getMaxHealth());
		//return;
	}
}

void HudRenderer::refreshAbilitySlotsFromEquipment(const Player& player)
{
	auto setSlot = [&](std::size_t index, const std::string& name, float cooldown)
		{
			if (index >= abilitySlots.size())
				return;
			abilitySlots[index].name = name;
			abilitySlots[index].reset(cooldown);
		};

	auto clearSlot = [&](std::size_t index)
		{
			if (index >= abilitySlots.size())
				return;
			abilitySlots[index].name.clear();
			abilitySlots[index].reset(0.f);
		};

	const Equipment& mainHand = player.getEquippedItem(Equipment::EquipmentSlot::WEAPON);
	if (mainHand.getId().empty())
	{
		setSlot(0, "Jab", 1.2f);
		setSlot(1, "Guard", 3.0f);
		setSlot(2, "Heavy Punch", 4.0f);
	}
	else
	{
		std::string base = mainHand.getItemName();
		setSlot(0, base + " Slash", 1.0f);
		setSlot(1, base + " Parry", 2.5f);
		setSlot(2, base + " Finisher", 4.0f);
	}

	const Equipment& offHand = player.getEquippedItem(Equipment::EquipmentSlot::SHIELD);
	if (offHand.getId().empty())
	{
		clearSlot(3);
		clearSlot(4);
	}
	else
	{
		std::string base = offHand.getItemName();
		setSlot(3, base + " Bash", 3.0f);
		setSlot(4, base + " Surge", 5.0f);
	}
}

void HudRenderer::useAbility(std::size_t slotIndex, Player& player, Enemy& enemy, GameMode& mode)
{
	if (mode != GameMode::Combat || slotIndex >= abilitySlots.size())
		return;

	auto& slot = abilitySlots[slotIndex];
	if (!slot.isReady() || slot.name.empty() || !enemy.isAlive())
		return;

	int baseDamage = combatActions.playerAttack(enemy, player);
	float modifier = 1.0f;
	if (slotIndex == 1)
		modifier = 0.7f; // guard-style move
	else if (slotIndex == 2)
		modifier = 1.5f;
	else if (slotIndex >= 3)
		modifier = 1.1f;

	int damage = static_cast<int>(std::max(1.f, std::round(baseDamage * modifier)));
	enemy.changeCurrentHealth(-damage);
	slot.trigger();

	std::cout << "Used " << slot.name << " for " << damage << " damage. Enemy HP: " << enemy.getCurrentHealth() << "/" << enemy.getMaxHealth() << "\n";

	if (!enemy.isAlive())
	{
		mode = GameMode::Normal;
		std::cout << "Enemy defeated!\n";
	}
}

void HudRenderer::drawHealthBar(sf::RenderWindow& window, float x, float y, float width, float height, float currentHP, float maxHP)
{

}

void HudRenderer::drawAbilitySlot(sf::RenderWindow& window, const AbilitySlot& slot, float x, float y)
{

}