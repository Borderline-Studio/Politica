#ifndef PAUSE_H

#define PAUSE_H
#include "Common.h"
#include "Animation.h"
#include "Audio.h"

enum ButtonTypePause
{
	CONTINUE,
	SETTINGS_PAUSE,
	MAIN_MENU,
	QUIT_PAUSE

};

struct Pause
{
	sf::Texture texture;
	sf::Sprite sprite;
	int buttonSelected;
};

void InitPause(GameData& _gameData);

void UpdatePause(float _dt);

void DisplayPause(sf::RenderWindow& _window);

void CheckMouseButtonCollisionPause(sf::RenderWindow& _window, sf::Event::MouseMoveEvent& _buttonEvt);

void KeypressedPause(GameData& _gameData);

void MousePressedPause(GameData& _gameData);

void MouseMovedPause(sf::RenderWindow& _window, sf::Event::MouseMoveEvent& _buttonEvt);

#endif // !PAUSE_H


