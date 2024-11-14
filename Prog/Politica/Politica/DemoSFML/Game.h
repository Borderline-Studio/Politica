#ifndef  GAME_H

#define GAME_H

#include "Common.h"
#include "Grid.h"
#include "Cards.h"
#include "PlayersManager.h"
#include "TurnManager.h"
#include "HUD.h"
#include "HudPlayer.h"
#include "Dices.h"
#include "Audio.h"

struct Background
{
	sf::Sprite sprite;
	sf::Texture texture;

};

struct Game
{
	Fade fade;
	int gameMusic;
};

void InitBackgroundGame(void);

void InitGameFade(void);

void DisplayBackgroundGame(sf::RenderWindow& _window);

void InitGame(GameData& _gameData);
void MouseMovedGame(sf::Event::MouseMoveEvent _buttonEvt);
void MousePressedGame(GameData& _gameData, sf::Event::MouseButtonEvent& _buttonEvt);
void MouseReleasedGame(GameData& _gameData, sf::Event::MouseButtonEvent& _buttonEvt);
void FadeGame(GameData& _gameData,float _maxVolume = 25.f, float _speedPerSec = 1.f);
void UpdateGame(GameData& _gameData);
void KeyPressedGame(GameData& _gameData);

void LostFocusGame(GameData& _gameData);

void DisplayGame(sf::RenderWindow& _window);

#endif // ! GAMESTATE_H


