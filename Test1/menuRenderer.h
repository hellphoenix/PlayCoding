#pragma once
#ifndef MENU_RENDERER_H
#define MENU_RENDERER_H
#include "SFML/Graphics.hpp"

class MenuRenderer
{
public:
	MenuRenderer();
	MenuRenderer(const sf::Font& uiFont);

	void drawInGameMenu();
	void drawMainMenu();
	void drawWinScreen();
	void drawLoseScreen();
};
#endif // !MENU_RENDERER_H

