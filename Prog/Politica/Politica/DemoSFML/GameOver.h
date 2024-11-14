#ifndef GAMEOVER_H

#define GAMEOVER_H

#include "Common.h"
#include "Animation.h"
#include "Audio.h"


#define PODIUM_NB 3

enum ButtonTypeGameOver
{
	PLAY_AGAIN,
	MAIN_MENU_GAME_OVER

};

enum Podium
{
	FIRST,
	SECOND,
	THIRD
};

struct GameOver
{
	sf::Texture textureBackground;
	sf::Sprite spriteBackground;
	int buttonSelected;
	Fade fade;
	int buttonClickedOn;

	sf::Text textWin;

	sf::Texture avatarTexture;
	
	sf::Sprite avatarSpriteTab[4];

	unsigned char gameOverMusic;
};

struct GameOverPlayer
{
	int voters;
	int reputation;
	int money;
	int putsch;
	std::string name;
	sf::Sprite sprite;
	unsigned char playerNB;
};
void InitGameOver(GameData& _gameData);

void InitGameOverButtons(void);

void InitGameOverBackground(void);

void initGameOverPlayers(void);

void InitGameOverPodium(void);

void FadeGameOver(int& _state, float& _dt,float _maxVolume = 25.f, float _speedPerSec = 1.f);

void CheckWinners(void);

void UpdateButtonsGameOver(float& _dt);

void UpdateGameOver(int& _state, float& _dt);

void DisplayGameOverPodium(sf::RenderWindow& _window);

void DisplayGameOver(sf::RenderWindow& _window);

void KeypressedGameOver(GameData& _gameData);

void MousePressedGameOver(GameData& _gameData);

void CheckMouseButtonCollisionGameOver(sf::Event::MouseMoveEvent& _buttonEvt);

void MouseMovedGameOver(sf::Event::MouseMoveEvent& _buttonEvt);

#endif // !GAMEOVER_H
