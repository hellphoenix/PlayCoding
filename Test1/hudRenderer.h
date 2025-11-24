#pragma once
#ifndef HUD_RENDERER_H
#define HUD_RENDERER_H
#include "combatActions.h"
#include "enemy.h"
#include "player.h"
#include "gameMode.h"
#include "SFML/Graphics.hpp"

class HudRenderer
{
public:
	sf::Font uiFont;
	CombatActions combatActions;
	HudRenderer() {}
	HudRenderer(const sf::Font& uiFont) { this->uiFont = uiFont; }

	//void drawCombat(sf::RenderWindow&, const CombatContext&, const Player&);
	void drawCombat(sf::RenderWindow& window, const Player& player, const Enemy& enemy, float windowWidth, float windowHeight);
	void updateCombat(float dt, Player& player, Enemy& enemy, GameMode& mode);

	void refreshAbilitySlotsFromEquipment(const Player& player);
	void useAbility(std::size_t slotIndex, Player& player, Enemy& enemy, GameMode& mode);

	//void drawExplore(sf::RenderWindow& window, const Player& player);

private:
	struct AbilitySlot
	{
		std::string name;
		float cooldown = 0.f;
		float timer = 0.f;

		bool isReady() const { return timer <= 0.f && !name.empty(); }
		void reset(float _cooldown)
		{
			cooldown = _cooldown;
			timer = 0.f;
		}
		void trigger()
		{
			timer = cooldown;
		}
		void update(float dt)
		{
			if (timer > 0.f)
			{
				timer -= dt;
				if (timer < 0.f)
					timer = 0.f;
			}
		}
	};

	std::array<AbilitySlot, 5> abilitySlots{};
	float playerAutoAttackTimer = 0.f;
	float enemyAutoAttackTimer = 0.f;
	float playerAutoAttackInterval = 1.0f;
	float enemyAutoAttackInterval = 1.4f;

	void drawHealthBar(sf::RenderWindow& window, float x, float y, float width, float height, float currentHP, float maxHP);
	void drawAbilitySlot(sf::RenderWindow& window, const AbilitySlot& slot, float x, float y);
	//void drawEnemySlot();
	//void drawTopBar();
};
#endif // !HUD_RENDERER_H

