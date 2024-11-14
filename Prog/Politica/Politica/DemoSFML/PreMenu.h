#ifndef PREMENU_H
#define PREMENU_H

#include "Common.h"

 struct PreMenu
{
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Texture textureLogo;

	Fade fade;

	bool isOnLogo;

};

 void InitPreMenu(GameData& _gameData);

 void FadePreMenu(int& _state, float& _dt);

 void DisplayPreMenu(sf::RenderWindow& _window);

 void KeypressedPreMenu(sf::Event::KeyEvent& _keyEvt, int& _state);

 void MousePressedPreMenu(int& _state, sf::Event::MouseButtonEvent& _buttonEvt);

#endif


