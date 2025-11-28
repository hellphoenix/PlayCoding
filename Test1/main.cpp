#include "gameInitialize.h"
#include <iostream>
#include <stdexcept>

int main()
{
	GameInitialize game;
	try
	{
		game.run();
	}
	catch (const std::exception& ex)
	{
		std::cout << "Fatal Error: " << ex.what() << "\n";
		return 1;
	}
}