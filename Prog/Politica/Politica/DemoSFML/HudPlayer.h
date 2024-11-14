#ifndef HUD_PLAYER_H
#define HUD_PLAYER_H

#include "Common.h"

#define MAX_HEIGHT GetScreen().height * 0.4629f
#define MIN_HEIGHT GetScreen().height *  0.898148f 
#define SPEED 500
#define MAX_TIMER 3.f

struct Text
{
	sf::Text changeStat;
	float timerChangeStat;
	sf::Vector2f posChangeStat;
	float changingStatSpeed;
	int changeStatValue;
	float changeStatMaxHeight;
	sf::RectangleShape changeStatRect;

	sf::Text textChangeStat;

	Stats typeStat;
};

struct HudPlayer
{
	sf::Sprite sprite;
	sf::Vector2f pos;
	float speed;
	bool isMoving;
	bool down;
	sf::Text money;
	sf::Text reputation;
	sf::Text voters;
	sf::Text unpaidTax;

	sf::Sprite spriteCaricature;
	sf::Vector2f posCaricature;
	sf::Text nameCaricature;

	std::vector <Text> vectorText;

	float timer;
};



void InitHudPlayer();

void ReloadHudPlayer(void);

void UpdateTextChangeStat(GameData& _gameData);
void UpdateParlemtaryScale(float& _dt);
void UpdateMysteryScale(float& _dt);
void UpdateHudPlayer(GameData& _gameData);

void DisplayHudPlayer(sf::RenderWindow& _window);



#endif