#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include "Common.h"

struct LoadingScreenData
{
	sf::RectangleShape backChargingBar;
	sf::RectangleShape frontChargingBar;

	sf::Sprite background;
	sf::Text text;

	float timer = 0;
};

void InitLoadingScreen(GameData& _gameData);

#endif // !LOADINGSCREEN_H


