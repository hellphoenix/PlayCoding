#include "textures.h"

void Textures::loadTexture(std::string texturePath)
{
	if (!this->texture.loadFromFile(texturePath))
		std::cout << "Texture from " << texturePath << " could not load\n";
}

sf::Texture Textures::getTexture()
{
	return texture;
}
