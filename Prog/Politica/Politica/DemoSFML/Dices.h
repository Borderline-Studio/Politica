#ifndef DICES_H
#define DICES_H

#include "Common.h"
#include "Audio.h"


#define NB_ANIMS 6
#define MAX_TIME 0.4f

struct Dices
{
	sf::Sprite anim[NB_ANIMS];
	sf::Sprite sprite;
	int value = 0;
	int launchedDices = 0;
	float globalTime = 0.f;
	int currentFrame = 0;
	bool isDiceRolling = 0;
	bool isDiceHasRolling = 0;
	bool isDiceAvailable = 0;
	bool isOvered = 0;
	bool isSelected = 0;
	sf::Vector2f pos = {0,0};
	sf::Vector2f size = { 0,0 };
	float timerRoll= 0.f;
	float maxTimerRoll = 0.f;
	float timerAvailable = 0.f;
	float maxTimerAvailable = 0.f;
	int nbSelected = 0;
	bool hasChosen = 0;
	bool isReplaying = 0;
	int riggedValue = 0;
	bool isDelayingLaunchDices = 0;
	float delayLaunchDices = 0.f;

	unsigned char diceRollSound = 0;
};

struct TextureDices
{
	sf::Texture dice[NB_ANIMS];
};

// Moving dices
void InitMovingDices();

void ReloadMovingDices(void);

void LaunchMovingDices(GameData&);
void RiggedDices(GameData&);

void DisplayMovingDices(sf::RenderWindow& _window);

void MousePressedMovingDices(sf::Event);

void KeyPressedMovingDices(sf::Event& _event);

// Common functions
void InitDices();

void ReloadDices(void);

void UpdateDices(GameData&);

void DisplayDices(sf::RenderWindow& _window);

void MousePressedDices(sf::Event);

void KeyPressedDices(sf::Event& _event);

#endif
