#pragma once
#include "character.h"
#include "item.h"
#include "inventory.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Character
{
private:
	Inventory inventory;
	Item helmet;
	Item chestPiece;
	Item pants;
	Item boots;
	Item shield;
	Item sword;
	int totalAttack;
	int totalDefense;
	int totalHealth;

public:
	Player();
	Player(const string& _name, int _health, int _attack, int _defense);
	Player(const string& _name, int _health, int _attack, int _defense, const Item& _helmet, const Item& _chestPiece, const Item& _pants, const Item& _boots, const Item& _shield, const Item& _sword);

	Inventory& getInventory() { return Player::inventory; }
	const Item& getHelmet() const;
	const Item& getChestPiece() const;
	const Item& getPants() const;
	const Item& getBoots() const;
	const Item& getShield() const;
	const Item& getSword() const;
	int getTotalAttack() const;
	int getTotalDefense() const;
	int getTotalHealth() const;

	void setHelmet(const Item& _helmet);
	void setChestPiece(const Item& _chestPiece);
	void setPants(const Item& _pants);
	void setBoots(const Item& _boots);
	void setShield(const Item& _shield);
	void setSword(const Item& _sword);
	void setBaseStats(int _health, int _attack, int _defense);

	void equipHelmetFromInventory(const std::string& itemName);
	void equipChestFromInventory(const std::string& itemName);
	void equipPantsFromInventory(const std::string& itemName);
	void equipBootsFromInventory(const std::string& itemName);
	void equipShieldFromInventory(const std::string& itemName);
	void equipSwordFromInventory(const std::string& itemName);


	void printPlayer() const;

	void updateTotalStats();
};

#endif // !PLAYER_H
