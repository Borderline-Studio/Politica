#ifndef SETTINGS_H
#define SETTINGS_H

#include "Common.h"
#include"Animation.h"
#include "Audio.h"

enum SettingsButton
{
	MINUS,
	PLUS,
	QUIT_S
	
};

struct Settings
{
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::RectangleShape volumeRect;
	sf::Sprite volumeBar;
	sf::Vector2f originalRectSize;
	bool volumeRectSelected;

	sf::Font textFont;
	sf::Text volumeText;

	float soundMultiplier;

	std::vector<Button> buttonList;
};

void InitSettingsSprites(void);

void InitSettingsTexts(void);

void InitSettingsVolumeRect(void);

void InitSettings(GameData &_gameData);

void UpdateSettingsButtons(float& _dt);

void UpdateSettings(float& _dt);

void SoundMultiplierSecurity(void);

void UpdateVolumeRectSize(void);

void DisplaySettings(sf::RenderWindow& _window);

void MousePressedSettings(sf::Event& _event, int& _lastState, int& _gameState);

void MouseReleasedSettings(sf::Event& _event);

void MouseMovedSettings(sf::Event& _event);

void KeyPressedSettings(GameData& _gameData);

#endif


