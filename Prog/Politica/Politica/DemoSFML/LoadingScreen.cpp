#include "LoadingScreen.h"

LoadingScreenData loadingScreenData;

sf::Font tempFont;

void InitLoadingScreen(GameData& _gameData)
{
	_gameData.loadingScreenCompteur = 0;
	
	tempFont.loadFromFile("Assets/Fonts/HudFont.ttf");
	CreateText(loadingScreenData.text, tempFont, "", 35, sf::Color::White, false);
	CreateRectangleShape(loadingScreenData.backChargingBar, PosToScreen(sf::Vector2f( 1920.f / 4.f, 1080.f / 10.f * 9.f)), PosToScreen(sf::Vector2f( 1920 - (2*(1920.f / 4.f)), 10 )), sf::Color::White, false);
	CreateRectangleShape(loadingScreenData.frontChargingBar, PosToScreen(sf::Vector2f( 1920.f / 4.f, 1080.f / 10.f * 9.f )), PosToScreen(sf::Vector2f(0, 10 )), sf::Color::Green, false);
	loadingScreenData.text.setPosition(PosToScreen(sf::Vector2f(1920 / 4, 1080 / 10 * 8.6f)));
	loadingScreenData.timer = 0;
	loadingScreenData.background = LoadSprite("Assets/Images/BackgroundLoadingScreen.png", false);
	//loadingScreenData.icon2.setScale(PosToScreen({ 1.5f,1.5f }));
}

void DisplayLoadingScreen(GameData& _gameData)
{
	_gameData.window.clear(sf::Color(0, 0, 0)); // 45, 46, 63

	BlitSprite(loadingScreenData.background, PosToScreen(sf::Vector2f(0, 0)), _gameData.window, 0);

	_gameData.window.draw(loadingScreenData.backChargingBar);
	loadingScreenData.frontChargingBar.setSize({ (_gameData.loadingScreenCompteur * loadingScreenData.backChargingBar.getSize().x), loadingScreenData.backChargingBar.getSize().y });
	_gameData.window.draw(loadingScreenData.frontChargingBar);
	_gameData.window.draw(loadingScreenData.text);

	if (_gameData.loadingScreenCompteur >= 1)
	{
		loadingScreenData.timer++;
		if (loadingScreenData.timer >= 200)
		{
			_gameData.loadingScreenFinish = true;
		}
	}

	_gameData.window.display();
}

void SetLoadingScreenText(const sf::String& _string)
{
	loadingScreenData.text.setString(_string);
}
