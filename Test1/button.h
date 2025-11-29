#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
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
	sf::Texture textureIdle;
	sf::Texture textureHover;
	sf::Texture texturePressed;
	std::optional<sf::Sprite> shape;
	Textures loadedTexture;
	//sf::Sprite shape = sf::Sprite(textureIdle);
	int buttonState;

public:
	Button(sf::Vector2f& mousePosView);
	Button(sf::Vector2f& mousePosView, std::string& textureSingle);
	Button(sf::Vector2f& mousePosView, std::string& textureIdle, std::string& textureHover, std::string& texturePressed);
	~Button();

	void setButtonIdleTexture(std::string& textureIdle);
	void setButtonHoverTexture(std::string& textureHover);
	void setButtonPressedTexture(std::string& textureHover);

	void setButtonPosition(sf::Vector2f& mousePosView);
	void updateButton(const sf::RenderWindow& window);
	void render(sf::RenderTarget& target);

};

