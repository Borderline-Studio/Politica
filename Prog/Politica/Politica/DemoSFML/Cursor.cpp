#include"Cursor.h"

Mouse mouse;

void InitCursor(sf::RenderWindow& _window)
{
	
	sf::Texture texture;
	texture.loadFromFile("Assets/Images/Cursor/DefaultCursor.png");
	texture.setSmooth(true);
	mouse.image = texture.copyToImage();
	mouse.cursor.loadFromPixels(mouse.image.getPixelsPtr(), mouse.image.getSize(), sf::Vector2u(0, 0));

	_window.setMouseCursor(mouse.cursor);
	_window.setMouseCursorVisible(false);

}