#include "Screen.h"

Screen screen;

void InitScreen(sf::RenderWindow& _window)
{
	screen.width = (float)_window.getSize().x;
	screen.height = (float)_window.getSize().y;
}

Screen GetScreen(void)
{
	return screen;
}