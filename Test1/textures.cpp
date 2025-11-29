#include "textures.h"
#include <iostream>

const sf::Texture& Textures::loadTexture(const std::string& texturePath)
{
	if (textures.find(texturePath) == textures.end())
	{
		sf::Texture texture;
		if (!texture.loadFromFile(texturePath))
		{
			std::cout << "Texture from " << texturePath << " could not load\n";
		}
		textures.emplace(texturePath, std::move(texture));
	}
	return textures.at(texturePath);
}