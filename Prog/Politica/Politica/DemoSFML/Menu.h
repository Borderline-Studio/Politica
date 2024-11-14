#ifndef MENU_H

#define MENU_H

#include"Common.h"
#include "Animation.h"
#include "Audio.h"

enum ButtonType
{
	PLAY,
	SETTINGS_MENU,
	CREDITS_MENU,
	QUIT

};

struct MenuInfos
{
	sf::Texture textureBackground;
	sf::Sprite spriteBackground;

	sf::Texture textureGameName;
	sf::Sprite spriteGameName;
	sf::Vector2u titleSize;
	std::vector<Animation> animation;

	int buttonSelected;
	int menuMusic;
	int buttonPressSound;
	int buttonSelectSound;

	Fade fade;

	bool reload;

};





void LoadMenuSprites(void);

void InitMenu(GameData& _gameData);

void FadeMenu(int& _state, float& _dt, sf::RenderWindow& _window, float _maxVolume = 25.f, float _speedPerSec = 1.f);

void CheckMouseButtonCollision(sf::Event::MouseMoveEvent& _buttonEvt);

void UpdateButtons(float& _dt);

void UpdateButtonsSelection(void);

void UpdateMenu(GameData& _gameData);

void DrawButtons(sf::RenderWindow& _window);

void DisplayMenu(sf::RenderWindow& _window);

void KeypressedMenu(GameData& _gameData);

void MousePressedMenu(GameData& _gameData);

void MouseMovedMenu(sf::Event::MouseMoveEvent& _buttonEvt);

#endif


