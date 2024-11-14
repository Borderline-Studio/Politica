#ifndef CREDITS_H
#define CREDITS_H

#include "Common.h"
#include"Animation.h"
#include"Audio.h"

struct CreditsData
{
	sf::Texture texture;
	sf::Sprite sprite;
	float posY;
	short int speed;
	Button quitButton;
};

void InitCredits(GameData& _gameData);

void UpdateCredits(float _dt);

void DisplayCredits(sf::RenderWindow& _window);

void KeyPressedCredits(int& _state, sf::Event& _event);

void MousePressedCredits(int& _state, sf::Event& _event);

void MouseMovedCredits(sf::Event& _event);

#endif


