#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>


struct Textures
{
	const sf::Texture& loadTexture(const std::string& texturePath);
private:
	std::unordered_map<std::string, sf::Texture> textures;
};