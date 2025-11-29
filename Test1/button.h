#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include "textures.h"

enum BUTTON_STATE
{
	IDLE = 0, HOVER = 1, PRESSED = 2
};

class Button
{
private:
	
	sf::Color colorIdle;
	sf::Color colorHover;
	sf::Color colorPressed;
	const sf::Texture* textureIdle;
	const sf::Texture* textureHover;
	const sf::Texture* texturePressed;
	std::unique_ptr<sf::Sprite> shape;
	int buttonState;

public:
	Button(sf::Vector2f& mousePosView, const sf::Texture& textureIdle, const sf::Texture& textureHover, const sf::Texture& texturePressed);
	~Button();

	void setButtonPosition(sf::Vector2f& mousePosView);
	void updateButton(const sf::RenderWindow& window);
	void render(sf::RenderTarget& target);

};

