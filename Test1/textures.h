#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


struct Textures
{
	sf::Texture texture;

	const sf::Texture& loadTexture(std::string texturePath);
	//const sf::Texture& getTexture() const;
};