#ifndef MOUSE_H

#define MOUSE_H

#include"Common.h"

struct Mouse
{
	sf::Image image;
	sf::Cursor cursor;
	
};

void InitCursor(sf::RenderWindow& _window);

#endif // !MOUSE_H

