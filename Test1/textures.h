#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

struct Textures
{
	sf::Texture texture;

	void loadTexture(std::string texturePath);
	sf::Texture getTexture();
};