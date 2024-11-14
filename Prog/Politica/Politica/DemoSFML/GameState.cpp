#include "GameState.h"


void Init(GameData& _gameData)
{
	_gameData.window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Politica", sf::Style::Fullscreen);
	_gameData.window.setFramerateLimit(144);

	InitScreen(_gameData.window);
	InitCursor(_gameData.window);
	InitLoadingScreen(_gameData);

	_gameData.loadingScreenCompteur = 0.f / NB_INIT;
	SetLoadingScreenText("Loading Window Completed!");
	DisplayLoadingScreen(_gameData);

	InitSettings(_gameData);

	_gameData.loadingScreenCompteur = 1.f / NB_INIT;
	SetLoadingScreenText("Loading Settings Completed!");
	DisplayLoadingScreen(_gameData);

	InitPreMenu(_gameData);

	_gameData.loadingScreenCompteur = 2.f / NB_INIT;
	SetLoadingScreenText("Loading PreMenu Completed");
	DisplayLoadingScreen(_gameData);

	InitMenu(_gameData);

	_gameData.loadingScreenCompteur = 3.f / NB_INIT;
	SetLoadingScreenText("Loading Menu Completed");
	DisplayLoadingScreen(_gameData);

	InitCredits(_gameData);

	_gameData.loadingScreenCompteur = 4.f / NB_INIT;
	SetLoadingScreenText("Loading Credits Completed");
	DisplayLoadingScreen(_gameData);

	InitKeyBindings(_gameData);

	_gameData.loadingScreenCompteur = 5.f / NB_INIT;
	SetLoadingScreenText("Loading Key Bindings Completed");
	DisplayLoadingScreen(_gameData);

	InitCharacterSelection(_gameData);

	_gameData.loadingScreenCompteur = 6.f / NB_INIT;
	SetLoadingScreenText("Loading Character Selection Completed");
	DisplayLoadingScreen(_gameData);

	_gameData.gameState = PREMENU;
	InitGame(_gameData);

	_gameData.loadingScreenCompteur = 7.f / NB_INIT;
	SetLoadingScreenText("Loading Game Completed");
	DisplayLoadingScreen(_gameData);

	InitGameOver(_gameData);

	_gameData.loadingScreenCompteur = 8.f / NB_INIT;
	SetLoadingScreenText("Loading GameOver Completed");
	DisplayLoadingScreen(_gameData);

	InitPause(_gameData);

	_gameData.loadingScreenCompteur = 9.f / NB_INIT;
	SetLoadingScreenText("Loading Complete!");
	DisplayLoadingScreen(_gameData);

	while (_gameData.loadingScreenFinish != true)
	{
		DisplayLoadingScreen(_gameData);
	}

	_gameData.dtClock.restart();
}

void Reload(void)
{
	InitTurnManager();
	ReloadCharacterSelection();
	InitPlayers();
	ReloadDices();
	ReloadCards();
	ReloadCredits();
	ReloadGameFade();
	ReloadMenu();
	ReloadPause();
	ReloadSettings();
	ReloadHud();
	ReloadHudPlayer();
	ReloadKeyBindings();
	ReloadGameOver();
}

void ReloadNewGame(void)
{
	InitTurnManager();
	ReloadPlayersNewGame();
	ReloadDices();
	ReloadCards();
	ReloadCredits();
	ReloadGameFade();
	ReloadHud();
	ReloadHudPlayer();
	ReloadMenu();
	ReloadPause();
	ReloadSettings();
	ReloadKeyBindings();
	ReloadGameOver();
}

void Update(GameData& _gameData)
{
	if (_gameData.loadingScreenFinish)
	{
		_gameData.dt = _gameData.dtClock.restart().asSeconds();

		switch (_gameData.gameState)
		{
		case PREMENU:
			FadePreMenu(_gameData.gameState, _gameData.dt);
			break;
		case MENU:
			UpdateMenu(_gameData);
			break;
		case CHARACTER_SELECTION:
			UpdateCharacterSelection(_gameData);
			break;
		case GAME:
			UpdateGame(_gameData);
			break;
		case PAUSE:
			UpdatePause(_gameData.dt);
			break;
		case GAMEOVER:
			UpdateGameOver(_gameData.gameState, _gameData.dt);
			break;
		case SETTINGS:
			UpdateSettings(_gameData.dt);
			UpdateKeyBindings(_gameData.dt);
			break;
		case CREDITS:
			UpdateCredits(_gameData.dt);
			break;
		case RULES:
			UpdateRules(_gameData.dt);
			break;

		default:
			break;
		}
	}
}

void PollEvent(GameData& _gameData)
{
	if (_gameData.loadingScreenFinish)
	{
		while (_gameData.window.pollEvent(_gameData.event))
		{
			if (_gameData.event.type == sf::Event::Closed)
			{
				_gameData.window.close();
			}

			switch (_gameData.gameState)
			{
			case PREMENU:
				KeypressedPreMenu(_gameData.event.key, _gameData.gameState);
				MousePressedPreMenu(_gameData.gameState, _gameData.event.mouseButton);
				break;
			case MENU:
				KeypressedMenu(_gameData);
				MousePressedMenu(_gameData);
				MouseMovedMenu(_gameData.event.mouseMove);
				break;
			case CHARACTER_SELECTION:
				KeyPressedCharacterSelection(_gameData);
				MousePressedCharacterSelection(_gameData);
				MouseMovedCharacterSelection(_gameData.event.mouseMove);
				break;
			case GAME:
				MouseMovedGame(_gameData.event.mouseMove);
				MousePressedGame(_gameData, _gameData.event.mouseButton);
				MouseReleasedGame(_gameData, _gameData.event.mouseButton);
				KeyPressedGame(_gameData);
				LostFocusGame(_gameData);
				break;
			case PAUSE:
				KeypressedPause(_gameData);
				MousePressedPause(_gameData);
				MouseMovedPause(_gameData.window, _gameData.event.mouseMove);
				break;
			case GAMEOVER:
				KeypressedGameOver(_gameData);
				MousePressedGameOver(_gameData);
				MouseMovedGameOver(_gameData.event.mouseMove);
				break;
			case SETTINGS:
				MouseReleasedSettings(_gameData.event);
				MousePressedSettings(_gameData.event, _gameData.lastState, _gameData.gameState);
				MousePressedKeyBindings(_gameData.event);
				KeyPressedKeyBindings(_gameData.event);
				MouseMovedSettings(_gameData.event);
				MouseMovedKB(_gameData.event);
				KeyPressedSettings(_gameData);
				break;
			case CREDITS:
				KeyPressedCredits(_gameData.gameState, _gameData.event);
				MousePressedCredits(_gameData.gameState, _gameData.event);
				MouseMovedCredits(_gameData.event);
				break;
			case RULES:
				MousePressedRules(_gameData.event, _gameData);
				KeyPressedRules(_gameData.event, _gameData);
				break;
			default:
				break;
			}

		}
	}
}


void Display(GameData& _gameData)
{
	if (_gameData.loadingScreenFinish)
	{
		_gameData.window.clear(sf::Color::Black);

		switch (_gameData.gameState)
		{
		case PREMENU:
			DisplayPreMenu(_gameData.window);
			break;
		case MENU:
			_gameData.window.setMouseCursorVisible(true);
			DisplayMenu(_gameData.window);
			break;
		case CHARACTER_SELECTION:
			DisplayCharacterSelection(_gameData.window);
			break;
		case GAME:
			DisplayGame(_gameData.window);
			break;
		case PAUSE:
			DisplayGame(_gameData.window);
			DisplayPause(_gameData.window);
			break;
		case GAMEOVER:
			DisplayGameOver(_gameData.window);
			break;
		case SETTINGS:
			DisplaySettings(_gameData.window);
			DisplayKeyBindings(_gameData.window);
			break;
		case CREDITS:
			DisplayCredits(_gameData.window);
			break;
		case RULES:
			DisplayRules(_gameData.window);
			break;
		default:
			break;
		}

		_gameData.window.display();
	}
}

void SetLastState(GameData& _gameData)
{
	_gameData.lastState = _gameData.gameState;
}