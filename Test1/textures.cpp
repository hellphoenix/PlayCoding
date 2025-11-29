#include "textures.h"
#include <iostream>

const sf::Texture& Textures::loadTexture(std::string texturePath)
{
	if (!this->texture.loadFromFile(texturePath))
	{
		std::cout << "Texture from " << texturePath << " could not load\n";
	}
	else return this->texture;
}

//const sf::Texture& Textures::getTexture() const
//{
//	return texture;
//}
