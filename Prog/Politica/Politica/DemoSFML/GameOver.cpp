#include"GameOver.h"
#include "Menu.h"

GameOver gameOver;
std::vector<Button> buttonListGameOver;
GameOverPlayer player[NB_PLAYERS];

void InitGameOver(GameData& _gameData)
{
	SetLoadingScreenText("Loading GameOver/Background");
	DisplayLoadingScreen(_gameData);

	InitGameOverBackground();

	SetLoadingScreenText("Loading GameOver/Buttons");
	DisplayLoadingScreen(_gameData);

	InitGameOverButtons();

	SetLoadingScreenText("Loading GameOver/Podium");
	DisplayLoadingScreen(_gameData);

	InitGameOverPodium();

	SetLoadingScreenText("Loading GameOver/Player");
	DisplayLoadingScreen(_gameData);

	initGameOverPlayers();
	CreateFadeRect(gameOver.fade, true);
	gameOver.gameOverMusic = AddMusic("Assets/Musics/GameOverMusic.wav");

	InitFireWork();
}

void ReloadGameOver(void)
{
	CreateText(gameOver.textWin, GetSettingsFont(), GetPlayerPseudo(0) + " a remporté l'élection", 50, sf::Color::White);
	gameOver.textWin.setPosition(GetScreen().width / 2.f, PosToScreenY(50));

	initGameOverPlayers();
	CreateFadeRect(gameOver.fade, true);

	gameOver.buttonSelected = PLAY_AGAIN;
	buttonListGameOver[MAIN_MENU_GAME_OVER].isSelected = false;
	buttonListGameOver[MAIN_MENU_GAME_OVER].isPressed = false;
	buttonListGameOver[PLAY_AGAIN].isSelected = true;
	buttonListGameOver[PLAY_AGAIN].isPressed = false;

	gameOver.buttonClickedOn = PLAY_AGAIN;
}

void InitGameOverButtons(void)
{
	buttonListGameOver.push_back(CreateButton("Assets/Images/Menu/NewGameButton.png", PosToScreenY(950), true, ScaleToScreen(0.95f, 0.95f), PosToScreenX(250)));
	buttonListGameOver.push_back(CreateButton("Assets/Images/Pause/MainMenuButton.png", PosToScreenY(950), true, ScaleToScreen(0.95f, 0.95f), PosToScreenX(1670)));

	gameOver.buttonSelected = PLAY_AGAIN;
	buttonListGameOver[MAIN_MENU_GAME_OVER].isSelected = false;
	buttonListGameOver[MAIN_MENU_GAME_OVER].isPressed = false;
	buttonListGameOver[PLAY_AGAIN].isSelected = true;
	buttonListGameOver[PLAY_AGAIN].isPressed = false;

	gameOver.buttonClickedOn = PLAY_AGAIN;

	for (unsigned char i = 0; i < buttonListGameOver.size(); i++)
	{
		CreateAnimationLeftToRight(buttonListGameOver[i].animation[0], 3, 1, buttonListGameOver[i].texture->getSize());
	}
}

void InitGameOverBackground(void)
{
	gameOver.textureBackground.loadFromFile("Assets/Images/GameOver/Background.png");
	gameOver.spriteBackground.setTexture(gameOver.textureBackground);
	gameOver.spriteBackground.setScale(GetScreen().width / gameOver.textureBackground.getSize().x, GetScreen().height / gameOver.textureBackground.getSize().y);
}

void initGameOverPlayers()
{
	for (int i = 0; i < NB_PLAYERS; i++)
	{
		player[i].name = GetPlayerPseudo(i);
		player[i].voters = GetPlayersVoters(i);
		player[i].reputation = GetPlayersReputation(i);
		player[i].money = GetPlayerMoney(i);
		player[i].sprite = gameOver.avatarSpriteTab[i];
		player[i].playerNB = i;
	}
}

void InitGameOverPodium(void)
{

	CreateText(gameOver.textWin, GetSettingsFont(), GetPlayerPseudo(0) + " a remporté l'élection", 50, sf::Color::White);
	gameOver.textWin.setPosition(GetScreen().width / 2.f, PosToScreenY(50));

	gameOver.avatarSpriteTab[0] = LoadSprite("Assets/Images/CharacterSelection/MargaretTchatcheur.png", true);
	gameOver.avatarSpriteTab[1] = LoadSprite("Assets/Images/CharacterSelection/RonaldRayban.png", true);
	gameOver.avatarSpriteTab[2] = LoadSprite("Assets/Images/CharacterSelection/JVFranco.png", true);
	gameOver.avatarSpriteTab[3] = LoadSprite("Assets/Images/CharacterSelection/VladInput.png", true);
}



void FadeGameOver(int& _state, float& _dt, float _maxVolume, float _speedPerSec)
{
	if (gameOver.fade.isFadingIn)
	{
		if (gameOver.fade.timer == gameOver.fade.timerMax)
		{
			CheckWinners();
		}

		gameOver.fade.timer = gameOver.fade.timer - _dt * _speedPerSec;

		gameOver.fade.alpha = fmaxf((gameOver.fade.timer / gameOver.fade.timerMax) * gameOver.fade.alphaMax, gameOver.fade.alphaMin);
		SetMusicVolume(gameOver.gameOverMusic, fminf(((gameOver.fade.timerMax - gameOver.fade.timer) / gameOver.fade.timerMax) * (_maxVolume * GetSoundMultiplier()), _maxVolume * GetSoundMultiplier()));

		gameOver.fade.color = sf::Color(0, 0, 0, (sf::Uint8)gameOver.fade.alpha);
		gameOver.fade.rect.setFillColor(gameOver.fade.color);

		if (gameOver.fade.timer <= gameOver.fade.timerMin)
		{
			gameOver.fade.isFadingIn = false;
		}
	}

	if (gameOver.fade.isFadingOut)
	{

		gameOver.fade.timer = gameOver.fade.timer + _dt * _speedPerSec;

		gameOver.fade.alpha = fminf((gameOver.fade.timer / gameOver.fade.timerMax) * gameOver.fade.alphaMax, gameOver.fade.alphaMax);
		SetMusicVolume(gameOver.gameOverMusic, fmaxf(((gameOver.fade.timerMax - gameOver.fade.timer) / gameOver.fade.timerMax) * (_maxVolume * GetSoundMultiplier()), 0.f));

		gameOver.fade.color = sf::Color(0, 0, 0, (sf::Uint8)gameOver.fade.alpha);
		gameOver.fade.rect.setFillColor(gameOver.fade.color);

		if (gameOver.fade.timer >= gameOver.fade.timerMax)
		{
			gameOver.fade.isFadingOut = false;

			if (gameOver.buttonClickedOn == PLAY_AGAIN)
			{
				ReloadNewGame();
				_state = GAME;
				StopMusic(gameOver.gameOverMusic);
			}
			else
			{
				Reload();
				_state = MENU;
				StopMusic(gameOver.gameOverMusic);
			}

		}
	}
}



void CheckWinners(void)
{
	for (unsigned char i = 0; i < NB_PLAYERS; i++)
	{
		switch (player[i].playerNB)
		{
		case PLAYER_1:
			player[i].name = GetPlayerPseudo(PLAYER_1);
			player[i].voters = GetPlayersVoters(PLAYER_1);
			player[i].reputation = GetPlayersReputation(PLAYER_1);
			player[i].money = GetPlayerMoney(PLAYER_1);
			player[i].putsch = GetPlayerHasSucceededPutsch(PLAYER_1);
			player[i].sprite = gameOver.avatarSpriteTab[GetPlayerCharacterChosen(PLAYER_1)];

			break;
		case PLAYER_2:
			player[i].name = GetPlayerPseudo(PLAYER_2);
			player[i].voters = GetPlayersVoters(PLAYER_2);
			player[i].reputation = GetPlayersReputation(PLAYER_2);
			player[i].money = GetPlayerMoney(PLAYER_2);
			player[i].putsch = GetPlayerHasSucceededPutsch(PLAYER_2);
			player[i].sprite = gameOver.avatarSpriteTab[GetPlayerCharacterChosen(PLAYER_2)];
			break;
		case PLAYER_3:
			player[i].name = GetPlayerPseudo(PLAYER_3);
			player[i].voters = GetPlayersVoters(PLAYER_3);
			player[i].reputation = GetPlayersReputation(PLAYER_3);
			player[i].money = GetPlayerMoney(PLAYER_3);
			player[i].putsch = GetPlayerHasSucceededPutsch(PLAYER_3);
			player[i].sprite = gameOver.avatarSpriteTab[GetPlayerCharacterChosen(PLAYER_3)];
			break;
		case PLAYER_4:
			player[i].name = GetPlayerPseudo(PLAYER_4);
			player[i].voters = GetPlayersVoters(PLAYER_4);
			player[i].reputation = GetPlayersReputation(PLAYER_4);
			player[i].money = GetPlayerMoney(PLAYER_4);
			player[i].putsch = GetPlayerHasSucceededPutsch(PLAYER_4);
			player[i].sprite = gameOver.avatarSpriteTab[GetPlayerCharacterChosen(PLAYER_4)];
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < NB_PLAYERS; i++)
	{
		for (int j = 0; j < NB_PLAYERS - 1; j++)
		{
			if (player[j].putsch != 1 && player[j + 1].putsch == 1)
			{
				GameOverPlayer tempPlayer = player[j];
				player[j] = player[j + 1];
				player[j + 1] = tempPlayer;
			}
			else if (player[j].putsch == 2 && player[j + 1].putsch != 2)
			{
				GameOverPlayer tempPlayer = player[j];
				player[j] = player[j + 1];
				player[j + 1] = tempPlayer;
			}
			else if (player[j].voters < player[j + 1].voters) //Si mauvais ordre
			{
				GameOverPlayer tempPlayer = player[j];
				player[j] = player[j + 1];
				player[j + 1] = tempPlayer;
			}
			else if (player[j].voters == player[j + 1].voters && player[j].reputation < player[j + 1].reputation)
			{
				GameOverPlayer tempPlayer = player[j];
				player[j] = player[j + 1];
				player[j + 1] = tempPlayer;
			}
			else if (player[j].voters == player[j + 1].voters && player[j].reputation == player[j + 1].reputation && player[j].money < player[j + 1].money)
			{
				GameOverPlayer tempPlayer = player[j];
				player[j] = player[j + 1];
				player[j + 1] = tempPlayer;
			}
			else if (player[j].voters == player[j + 1].voters && player[j].reputation == player[j + 1].reputation && player[j].money == player[j + 1].money)
			{
				bool random = rand() % 2;
				if (random == 0)
				{
					GameOverPlayer tempPlayer = player[j];
					player[j] = player[j + 1];
					player[j + 1] = tempPlayer;
				}
			}
		}
	}

	CreateText(gameOver.textWin, GetSettingsFont(), player[FIRST].name + " a remporté l'élection", 50, sf::Color::White);
	gameOver.textWin.setPosition(GetScreen().width / 2.f, PosToScreenY(50));

	player[FIRST].sprite.setPosition(sf::Vector2f(PosToScreenX(987), PosToScreenY(361)));
	player[SECOND].sprite.setPosition(sf::Vector2f(PosToScreenX(617), PosToScreenY(463)));
	player[THIRD].sprite.setPosition(sf::Vector2f(PosToScreenX(1920 - 560), PosToScreenY(528)));

}

void UpdateButtonsGameOver(float& _dt)
{
	UpdateFireWork(_dt);

	UpdateParticleGameOver(_dt);
	for (unsigned char i = 0; i < buttonListGameOver.size(); i++)
	{
		if (gameOver.buttonSelected == i)
		{
			buttonListGameOver[i].isSelected = true;
		}
		else
		{
			buttonListGameOver[i].isSelected = false;
		}
	}

	for (unsigned char i = 0; i < buttonListGameOver.size(); i++)
	{
		UpdateAnimationButton(buttonListGameOver[i].animation[0], buttonListGameOver[i].sprite, buttonListGameOver[i].isSelected, buttonListGameOver[i].isPressed, _dt);
	}
}

void UpdateGameOver(int& _state, float& _dt)
{
	PlayMusic(gameOver.gameOverMusic, true, 0.f);
	FadeGameOver(_state, _dt, 70.f);
	UpdateButtonsGameOver(_dt);
	StopSound(GetParliamentaryCouncilSound());
}

void DisplayGameOverPodium(sf::RenderWindow& _window)
{
	for (unsigned char i = 0; i < PODIUM_NB; i++)
	{
		//_window.draw(gameOver.podiumSpriteTab[i]);
		_window.draw(player[i].sprite);
	}
	_window.draw(gameOver.textWin);
}

void DisplayGameOver(sf::RenderWindow& _window)
{
	_window.draw(gameOver.spriteBackground);
	
	for (unsigned char i = 0; i < buttonListGameOver.size(); i++)
	{
		_window.draw(buttonListGameOver[i].sprite);
	}

	DisplayGameOverPodium(_window);
	DrawParticleGameOver(_window);
	_window.draw(gameOver.fade.rect);
	
}

void KeypressedGameOver(GameData& _gameData)
{
	if (_gameData.event.type == sf::Event::KeyPressed)
	{
		switch (_gameData.event.key.code)
		{

		case sf::Keyboard::Right:

			if (gameOver.buttonSelected != MAIN_MENU_GAME_OVER)
			{
				++gameOver.buttonSelected;
			}
			else
			{
				gameOver.buttonSelected = PLAY_AGAIN;
			}

			buttonListGameOver[gameOver.buttonSelected].isSelected = true;

			break;

		case sf::Keyboard::Left:

			if (gameOver.buttonSelected != PLAY_AGAIN)
			{
				--gameOver.buttonSelected;
			}
			else
			{
				gameOver.buttonSelected = MAIN_MENU_GAME_OVER;
			}

			buttonListGameOver[gameOver.buttonSelected].isSelected = true;

			break;

		case sf::Keyboard::Enter:

			if (!gameOver.fade.isFadingIn && !gameOver.fade.isFadingOut)
			{
				if (gameOver.buttonSelected == PLAY_AGAIN)
				{
					gameOver.buttonClickedOn = PLAY_AGAIN;
					buttonListGameOver[PLAY_AGAIN].isPressed = true;
				}
				else
				{
					gameOver.buttonClickedOn = MAIN_MENU_GAME_OVER;
					buttonListGameOver[MAIN_MENU_GAME_OVER].isPressed = true;
				}
				gameOver.fade.isFadingIn = false;
				gameOver.fade.isFadingOut = true;

			}
			break;

		default:
			break;
		}
	}

}

void MousePressedGameOver(GameData& _gameData)
{
	sf::Vector2i mouse = sf::Mouse::getPosition();
	if (_gameData.event.type == sf::Event::MouseButtonPressed && _gameData.event.mouseButton.button == sf::Mouse::Left && !gameOver.fade.isFadingIn && !gameOver.fade.isFadingOut)
	{
		if (buttonListGameOver[PLAY_AGAIN].isSelected && RectContains(buttonListGameOver[PLAY].sprite.getGlobalBounds(), (sf::Vector2f)mouse))
		{
			gameOver.buttonClickedOn = PLAY_AGAIN;
			buttonListGameOver[PLAY_AGAIN].isPressed = true;
			gameOver.fade.isFadingIn = false;
			gameOver.fade.isFadingOut = true;
			PlaySoundFromList(GetButtonPressSound(), 50);
		}
		else if (buttonListGameOver[MAIN_MENU_GAME_OVER].isSelected && RectContains(buttonListGameOver[MAIN_MENU_GAME_OVER].sprite.getGlobalBounds(), (sf::Vector2f)mouse))
		{
			gameOver.buttonClickedOn = MAIN_MENU_GAME_OVER;
			buttonListGameOver[MAIN_MENU_GAME_OVER].isPressed = true;
			gameOver.fade.isFadingIn = false;
			gameOver.fade.isFadingOut = true;
			PlaySoundFromList(GetButtonPressSound(), 50);
		}
	}
}

void CheckMouseButtonCollisionGameOver(sf::Event::MouseMoveEvent& _buttonEvt)
{
	sf::Vector2f mouse = { (float)_buttonEvt.x , (float)_buttonEvt.y };

	for (unsigned char i = 0; i < buttonListGameOver.size(); i++)
	{
		if (RectContains(buttonListGameOver[i].sprite.getGlobalBounds(), mouse) && !buttonListGameOver[i].isSelected && !gameOver.fade.isFadingOut)
		{
			PlaySoundFromList(GetButtonSelectSound(), 5);
		}
		if (RectContains(buttonListGameOver[i].sprite.getGlobalBounds(), mouse))
		{

			for (unsigned char j = 0; j < buttonListGameOver.size(); j++)
			{

				buttonListGameOver[j].isSelected = false;

			}
			buttonListGameOver[i].isSelected = true;
			gameOver.buttonSelected = i;
		}
	}
}

void MouseMovedGameOver(sf::Event::MouseMoveEvent& _buttonEvt)
{
	CheckMouseButtonCollisionGameOver(_buttonEvt);
}
