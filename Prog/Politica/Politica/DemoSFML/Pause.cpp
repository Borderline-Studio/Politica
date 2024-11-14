#include"Pause.h"

Pause pause;
std::vector<Button> buttonListPause;



void InitPause(GameData& _gameData)
{
	SetLoadingScreenText("Loading Pause/Buttons");
	DisplayLoadingScreen(_gameData);

	buttonListPause.push_back(CreateButton("Assets/Images/Pause/ResumeButton.png", PosToScreenY(421), true, ScaleToScreen(.95f, 0.95f)));
	buttonListPause.push_back(CreateButton("Assets/Images/Menu/SettingsButton.png", PosToScreenY(508), true, ScaleToScreen(.95f, 0.95f)));
	buttonListPause.push_back(CreateButton("Assets/Images/Pause/MainMenuButton.png", PosToScreenY(594), true, ScaleToScreen(.95f, 0.95f)));
	buttonListPause.push_back(CreateButton("Assets/Images/Menu/QuitButton.png", PosToScreenY(680), true, ScaleToScreen(.95f, 0.95f)));

	for (unsigned char i = 0; i < buttonListPause.size(); i++)
	{
		CreateAnimationLeftToRight(buttonListPause[i].animation[0], 3, 1, buttonListPause[i].texture->getSize());
	}

	pause.buttonSelected = CONTINUE;
	buttonListPause[CONTINUE].isSelected = true;
	buttonListPause[SETTINGS_PAUSE].isSelected = false;
	buttonListPause[MAIN_MENU].isSelected = false;
	buttonListPause[QUIT_PAUSE].isSelected = false;
}

void ReloadPause(void)
{
	pause.buttonSelected = CONTINUE;
	buttonListPause[CONTINUE].isSelected = true;
	buttonListPause[SETTINGS_PAUSE].isSelected = false;
	buttonListPause[QUIT_PAUSE].isSelected = false;
	buttonListPause[MAIN_MENU].isSelected = false;
}

void UpdatePause(float _dt)
{
	for (unsigned char i = 0; i < buttonListPause.size(); i++)
	{
		if (pause.buttonSelected == i)
		{
			buttonListPause[i].isSelected = true;
		}
		else
		{
			buttonListPause[i].isSelected = false;
		}

	}

	for (unsigned char i = 0; i < buttonListPause.size(); i++)
	{
		UpdateAnimationButton(buttonListPause[i].animation[0], buttonListPause[i].sprite ,buttonListPause[i].isSelected, buttonListPause[i].isPressed, _dt);
	}

}

void DisplayPause(sf::RenderWindow& _window)
{
	for (unsigned char i = 0; i < buttonListPause.size(); i++)
	{
		_window.draw(buttonListPause[i].sprite);
	}
}

void CheckMouseButtonCollisionPause(sf::RenderWindow& _window, sf::Event::MouseMoveEvent& _buttonEvt)
{
	sf::Vector2f mouse = { (float)_buttonEvt.x, (float)_buttonEvt.y };
	for (unsigned char i = 0; i < buttonListPause.size(); i++)
	{
		if (RectContains(buttonListPause[i].sprite.getGlobalBounds(), mouse) && !buttonListPause[i].isSelected)
		{
			PlaySoundFromList(GetButtonSelectSound(), 5);
		}
		if (RectContains(buttonListPause[i].sprite.getGlobalBounds(), mouse))
		{
			for (unsigned char j = 0; j < buttonListPause.size(); j++)
			{

				buttonListPause[j].isSelected = false;

			}
			buttonListPause[i].isSelected = true;
			pause.buttonSelected = i;
		}
	}
}

void KeypressedPause(GameData& _gameData)
{
	if (_gameData.event.type == sf::Event::KeyPressed)
	{
		switch (_gameData.event.key.code)
		{
		case sf::Keyboard::Down:
			if (pause.buttonSelected != QUIT_PAUSE)
			{
				++pause.buttonSelected;
			}
			else
			{
				pause.buttonSelected = CONTINUE;
			}

			buttonListPause[pause.buttonSelected].isSelected = true;
			break;

		case sf::Keyboard::Up:
			if (pause.buttonSelected != CONTINUE)
			{
				--pause.buttonSelected;
			}
			else
			{
				pause.buttonSelected = QUIT_PAUSE;
			}

			buttonListPause[pause.buttonSelected].isSelected = true;
			break;

		case sf::Keyboard::Enter:
			switch (pause.buttonSelected)
			{
			case CONTINUE:
				//SetFadeShapeAlpha(0);
				SetLastState(_gameData);
				_gameData.gameState = GAME;
				break;

			case SETTINGS_PAUSE:
				SetLastState(_gameData);
				_gameData.gameState = SETTINGS;
				break;

			case MAIN_MENU:
				SetAlphaMenu();
				SetAlphaCharacterSelection();
				ReloadMenu();
				_gameData.gameState = MENU;
				StopAllMusics();
				break;

			case QUIT_PAUSE:
				_gameData.window.close();
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
	}
}

void MousePressedPause(GameData& _gameData)
{
	sf::Vector2i mouse = sf::Mouse::getPosition();

	if (_gameData.event.type == sf::Event::MouseButtonPressed && _gameData.event.mouseButton.button == sf::Mouse::Left)
	{
		if (buttonListPause[CONTINUE].isSelected && RectContains(buttonListPause[CONTINUE].sprite.getGlobalBounds(), (sf::Vector2f)mouse))
		{
			SetAlphaFadeGame(0.f);
			_gameData.gameState = GAME;
			PlaySoundFromList(GetButtonPressSound(), 50);
		}
		else if (buttonListPause[SETTINGS_PAUSE].isSelected && RectContains(buttonListPause[SETTINGS_PAUSE].sprite.getGlobalBounds(), (sf::Vector2f)mouse))
		{
			SetLastState(_gameData);
			_gameData.gameState = SETTINGS;
			PlaySoundFromList(GetButtonPressSound(), 50);
		}
		else if (buttonListPause[MAIN_MENU].isSelected && RectContains(buttonListPause[MAIN_MENU].sprite.getGlobalBounds(), (sf::Vector2f)mouse))
		{
			SetAlphaMenu();
			SetAlphaCharacterSelection();
			ReloadMenu();
			_gameData.gameState = MENU;
			PlaySoundFromList(GetButtonPressSound(), 50);
			StopAllMusics();
		}
		else if (buttonListPause[QUIT_PAUSE].isSelected && RectContains(buttonListPause[QUIT_PAUSE].sprite.getGlobalBounds(), (sf::Vector2f)mouse))
		{
			PlaySoundFromList(GetButtonPressSound(), 50);
			_gameData.window.close();
		}
	}
}

void MouseMovedPause(sf::RenderWindow& _window, sf::Event::MouseMoveEvent& _buttonEvt)
{
	CheckMouseButtonCollisionPause(_window, _buttonEvt);
}