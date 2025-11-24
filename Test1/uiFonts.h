#pragma once
#ifndef UI_FONTS_H
#define UI_FONTS_H
#include "SFML/Graphics.hpp"
#include <iostream>

struct UiFonts
{
	sf::Font uiFont;

	UiFonts()
	{
		if (!uiFont.openFromFile("assets/Arial.ttf"))
		{
			std::cout << "Failed to load UI font. Check path.\n";
		}
	}
};

#endif // !UI_FONTS_H

