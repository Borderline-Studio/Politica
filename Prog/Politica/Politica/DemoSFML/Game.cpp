#include "Game.h"

Background background;
Game game;

void InitBackgroundGame(void)
{
	background.texture.loadFromFile("Assets/Images/BackgroundGame.png");
	background.sprite.setTexture(background.texture);
	background.sprite.setOrigin(sf::Vector2f(background.texture.getSize().x / 2.f, background.texture.getSize().y / 2.f));
	//scale something bigger than screen width and height to the screen size
	background.sprite.setScale(GetScreen().width / background.texture.getSize().x, GetScreen().height / background.texture.getSize().y);
	background.sprite.setPosition(GetScreen().width * 0.5f, GetScreen().height * 0.5f);
}

void InitGameFade(void)
{
	CreateFadeRect(game.fade, true);
}

void ReloadGameFade(void)
{
	CreateFadeRect(game.fade, true);
}

void InitGame(GameData& _gameData)
{
	SetLoadingScreenText("Loading Game");
	DisplayLoadingScreen(_gameData);

	InitBackgroundGame();
	InitGameFade();

	SetLoadingScreenText("Loading Game/Grid");
	DisplayLoadingScreen(_gameData);

	InitGrid();
	InitTurnManager();

	SetLoadingScreenText("Loading Game/Players");
	DisplayLoadingScreen(_gameData);

	InitPlayersGestion();
	SetLoadingScreenText("Loading Game/Cards");
	DisplayLoadingScreen(_gameData);

	InitCards();
	SetLoadingScreenText("Loading Game/HUD");
	DisplayLoadingScreen(_gameData);

	InitHUD();
	InitHudPlayer();

	SetLoadingScreenText("Loading Game/Dices");
	DisplayLoadingScreen(_gameData);

	InitDices();

	game.gameMusic = AddMusic("Assets/Musics/GameMusic.wav");
}

void MouseMovedGame(sf::Event::MouseMoveEvent _buttonEvt)
{
	if (!GetPlayerIsAnAI(GetActivePlayer()) || (GetPlayerIsAnAI(GetActivePlayer()) && (GetIsBlackMailPlaying() || GetIsDenunciationPlaying())))
	{
		MouseMovedCards(_buttonEvt);
		MouseMovedHUD();
	}

}

void MousePressedGame(GameData& _gameData, sf::Event::MouseButtonEvent& _buttonEvt)
{
	if (!GetPlayerIsAnAI(GetActivePlayer()) || (GetPlayerIsAnAI(GetActivePlayer()) && (GetIsBlackMailPlaying() || GetIsDenunciationPlaying())))
	{
		MousePressedCards(_gameData, _buttonEvt);
		MousePressedHUD(_gameData.event, _gameData);
		MousePressedDices(_gameData.event);
		MousePressedPlayers(_gameData.event, GetActivePlayer());
	}
}

void MouseReleasedGame(GameData& _gameData, sf::Event::MouseButtonEvent& _buttonEvt)
{
	if (!GetPlayerIsAnAI(GetActivePlayer()) || (GetPlayerIsAnAI(GetActivePlayer()) && (GetIsBlackMailPlaying() || GetIsDenunciationPlaying())))
	{
		MouseReleasedCards(_gameData, _buttonEvt);
	}
}

void FadeGame(GameData& _gameData, float _maxVolume, float _speedPerSec)
{
	if (game.fade.isFadingIn)
	{

		game.fade.timer = game.fade.timer - _gameData.dt;
		game.fade.alpha = fmaxf((game.fade.timer / game.fade.timerMax) * game.fade.alphaMax, game.fade.alphaMin);
		SetMusicVolume(game.gameMusic, fminf(((game.fade.timerMax - game.fade.timer) / game.fade.timerMax) * (_maxVolume * GetSoundMultiplier()), _maxVolume * GetSoundMultiplier()));

		game.fade.color = sf::Color(0, 0, 0, (sf::Uint8)game.fade.alpha);
		game.fade.rect.setFillColor(game.fade.color);

		if (game.fade.timer <= game.fade.timerMin)
		{
			game.fade.isFadingIn = false;
		}
	}
	else if (game.fade.isFadingOut)
	{


		game.fade.timer = game.fade.timer + _gameData.dt;
		game.fade.alpha = fminf((game.fade.timer / game.fade.timerMax) * game.fade.alphaMax, game.fade.alphaMax);
		SetMusicVolume(game.gameMusic, fmaxf(((game.fade.timerMax - game.fade.timer) / game.fade.timerMax) * (_maxVolume * GetSoundMultiplier()), 0.f));

		game.fade.color = sf::Color(0, 0, 0, (sf::Uint8)game.fade.alpha);
		game.fade.rect.setFillColor(game.fade.color);

		if (game.fade.timer >= game.fade.timerMax)
		{
			game.fade.isFadingOut = false;
			_gameData.gameState = GAMEOVER;
			StopMusic(game.gameMusic);
		}
	}
}

void UpdateGame(GameData& _gameData)
{
	PlayMusic(game.gameMusic, true, 0.f);
	FadeGame(_gameData, 25.f, 2.f);
	UpdateTurnManager(_gameData.dt, _gameData.gameState);
	UpdateHUD(_gameData.dt);
	UpdatePlayers(_gameData);
	UpdateDices(_gameData);
	UpdateCards(_gameData);
	UpdateHudPlayer(_gameData);
}

void DisplayBackgroundGame(sf::RenderWindow& _window)
{
	_window.draw(background.sprite);
}

void DisplayGame(sf::RenderWindow& _window)
{
	DisplayBackgroundGame(_window);
	DisplayGrid(_window);
	DisplayDecosBeforePlayer(_window);
	DisplayPlayers(_window);
	DisplayDecosAfterPlayer(_window);
	DrawParticleHudPlayer(_window);
	DisplayCards(_window);
	DisplayHudPlayer(_window);
	DisplayHUD(_window);
	DisplayDices(_window);
	DisplayPlayerCards(_window);
	_window.draw(game.fade.rect);

}

void KeyPressedGame(GameData& _gameData)
{
	if (!GetPlayerIsAnAI(GetActivePlayer()) || (GetPlayerIsAnAI(GetActivePlayer()) && (GetIsBlackMailPlaying() || GetIsDenunciationPlaying())))
	{
		KeyPressedDices(_gameData.event);
		KeyPressedPlayers(_gameData.event);

		if (_gameData.event.type == sf::Event::KeyPressed && _gameData.event.key.code == GetKey(KB_ENDTURN) && GetDiceHasRolling() && !GetPlayerIsMoving(GetActivePlayer()) && !GetDiceisAvailable() && GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()) && !GetIsAnyCardDisplaying() && !GetActionStackCanBeSelected() && !GetChanceStackCanBeSelected() && !GetIsInParliamentaryCouncil() && !GetIsDebateIsPlaying() && !GetInsertIsDisplay())
		{
			if (GetPlayerMoney(GetActivePlayer()) < 0)
			{
				AddPlayerVoters(GetActivePlayer(), -50);
			}

			SetPlayerHasAlreadyMoved(GetActivePlayer(), false);
			SetPlayerHasFinishedTurn(GetActivePlayer(), true);
			setDiceHasRolling(false);
		}
	}

	if (_gameData.event.type == sf::Event::KeyPressed && _gameData.event.key.code == sf::Keyboard::Escape && !GetHudAreRulesDisplaying())
	{
		_gameData.gameState = PAUSE;
		SetLastState(_gameData);
	}


}

void LostFocusGame(GameData& _gameData)
{
	if (_gameData.event.type == sf::Event::LostFocus)
	{
		_gameData.gameState = PAUSE;
		SetLastState(_gameData);
	}
}

void SetAlphaFadeGame(float _alpha)
{
	game.fade.rect.setFillColor(sf::Color(0, 0, 0, (sf::Uint8)_alpha));
}

void SetGameFadeOut(bool _fadeOut)
{
	game.fade.isFadingIn = !_fadeOut;
	game.fade.isFadingOut = _fadeOut;
}

bool GetGameFadeOut(void)
{
	return game.fade.isFadingOut;
}