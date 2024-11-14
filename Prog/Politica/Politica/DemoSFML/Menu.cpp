#include "Menu.h"

MenuInfos menuData;
std::vector<Button> buttonList;

//*2 dans le newSize est égal au nombre de frame en X
Button CreateButton(std::string _file, float _y, bool _isCentered, sf::Vector2f _scale, float _x, unsigned char _nbFramesX)
{
	Button temp;

	temp.texture = new sf::Texture;
	temp.texture->loadFromFile(_file);
	temp.texture->setSmooth(true);
	temp.sprite.setTexture(*temp.texture);

	sf::Vector2u size = temp.texture->getSize();
	temp.size.x = (unsigned int)(((float)size.x / (float)_nbFramesX) * _scale.x);
	temp.size.y = (unsigned int)(size.y * _scale.y);
	temp.animation.resize(1);

	if (_isCentered)
	{
		sf::Vector2f newSize(size.x / (2.0f * _nbFramesX), size.y / 2.0f);
		temp.sprite.setOrigin(newSize);
	}

	temp.sprite.setScale(_scale);
	temp.pos.x = _x;
	temp.pos.y = _y;
	temp.sprite.setPosition(temp.pos);
	temp.isPressed = false;

	return temp;
}

void LoadMenuSprites(void)
{
	//// Background
	menuData.textureBackground.loadFromFile("Assets/Images/Background.png");
	menuData.spriteBackground.setTexture(menuData.textureBackground);
	menuData.spriteBackground.setScale(GetScreen().width / menuData.textureBackground.getSize().x, GetScreen().height / menuData.textureBackground.getSize().y);


	//// Title
	menuData.textureGameName.loadFromFile("Assets/Images/Menu/Title.png");
	menuData.spriteGameName.setTexture(menuData.textureGameName);
	menuData.titleSize = menuData.textureGameName.getSize();
	menuData.spriteGameName.setOrigin((float)menuData.titleSize.x / 2.f, (float)menuData.titleSize.y / 2.f);
	menuData.spriteGameName.setScale(ScaleToScreen(1, 1));
	menuData.spriteGameName.setPosition(PosToScreen(sf::Vector2f(960, 200)));


	//// Buttons


	buttonList.push_back(CreateButton("Assets/Images/Menu/NewGameButton.png", PosToScreenY(421), true, ScaleToScreen(0.95f, 0.95f)));
	buttonList.push_back(CreateButton("Assets/Images/Menu/SettingsButton.png", PosToScreenY(508), true, ScaleToScreen(0.95f, 0.95f)));
	buttonList.push_back(CreateButton("Assets/Images/Menu/CreditsButton.png", PosToScreenY(594), true, ScaleToScreen(0.95f, 0.95f)));
	buttonList.push_back(CreateButton("Assets/Images/Menu/QuitButton.png", PosToScreenY(680), true, ScaleToScreen(0.95f, 0.95f)));



	for (unsigned char i = 0; i < buttonList.size(); i++)
	{
		CreateAnimationLeftToRight(buttonList[i].animation[0], 3, 1, buttonList[i].texture->getSize());
	}



	buttonList[PLAY].isSelected = true;
	buttonList[SETTINGS_MENU].isSelected = false;
	buttonList[CREDITS_MENU].isSelected = false;
	buttonList[QUIT].isSelected = false;
	menuData.buttonSelected = PLAY;
	menuData.reload = false;

}


void InitMenu(GameData& _gameData)
{
	SetLoadingScreenText("Loading Menu/Sprites");
	DisplayLoadingScreen(_gameData);
	LoadMenuSprites();
	CreateFadeRect(menuData.fade, true);
	menuData.menuMusic = AddMusic("Assets/Musics/MenuMusic.wav");
	menuData.buttonPressSound = AddSound("Assets/Sounds/ButtonPress.ogg");
	menuData.buttonSelectSound = AddSound("Assets/Sounds/ButtonSelect.ogg");
}

void ReloadMenu(void)
{
	buttonList[PLAY].isSelected = true;
	buttonList[SETTINGS_MENU].isSelected = false;
	buttonList[CREDITS_MENU].isSelected = false;
	buttonList[QUIT].isSelected = false;
	menuData.buttonSelected = PLAY;

	CreateFadeRect(menuData.fade, true);
}

void FadeMenu(int& _state, float& _dt, sf::RenderWindow& _window, float _maxVolume, float _speedPerSec)
{
	if (menuData.fade.isFadingIn)
	{
		if (menuData.fade.timer == menuData.fade.timerMax && _window.hasFocus())
		{
			sf::Mouse::setPosition((sf::Vector2i)PosToScreen(sf::Vector2f(1920 / 2, 1080 / 2)));
		}

		menuData.fade.timer = menuData.fade.timer - _dt * _speedPerSec;

		menuData.fade.alpha = fmaxf((menuData.fade.timer / menuData.fade.timerMax) * menuData.fade.alphaMax, menuData.fade.alphaMin);
		SetMusicVolume(menuData.menuMusic, fminf(((menuData.fade.timerMax - menuData.fade.timer) / menuData.fade.timerMax) * (_maxVolume * GetSoundMultiplier()), _maxVolume * GetSoundMultiplier()));

		menuData.fade.color = sf::Color(0, 0, 0, (sf::Uint8)menuData.fade.alpha);
		menuData.fade.rect.setFillColor(menuData.fade.color);


		if (menuData.fade.timer <= menuData.fade.timerMin)
		{
			menuData.fade.isFadingIn = false;
		}
	}

	if (menuData.fade.isFadingOut)
	{
		menuData.fade.timer = menuData.fade.timer + _dt * _speedPerSec;

		menuData.fade.alpha = fminf((menuData.fade.timer / menuData.fade.timerMax) * menuData.fade.alphaMax, menuData.fade.alphaMax);
		SetMusicVolume(menuData.menuMusic, fmaxf(((menuData.fade.timerMax - menuData.fade.timer) / menuData.fade.timerMax) * (_maxVolume * GetSoundMultiplier()), 0.f));

		menuData.fade.color = sf::Color(0, 0, 0, (sf::Uint8)menuData.fade.alpha);
		menuData.fade.rect.setFillColor(menuData.fade.color);

		if (menuData.fade.timer >= menuData.fade.timerMax)
		{
			menuData.fade.isFadingOut = false;
			if (menuData.reload)
			{
				Reload();
			}
			else
			{
				menuData.reload = true;
			}
			_state = CHARACTER_SELECTION;
			StopMusic(menuData.menuMusic);
		}
	}
}

void CheckMouseButtonCollision(sf::Event::MouseMoveEvent& _buttonEvt)
{
	sf::Vector2f mouse = { (float)_buttonEvt.x , (float)_buttonEvt.y };

	for (unsigned char i = 0; i < buttonList.size(); i++)
	{
		if (RectContains(buttonList[i].sprite.getGlobalBounds(), mouse) && !buttonList[i].isSelected && !menuData.fade.isFadingIn && !menuData.fade.isFadingOut)
		{
			PlaySoundFromList(menuData.buttonSelectSound, 5);
		}
		if (RectContains(buttonList[i].sprite.getGlobalBounds(), mouse))
		{
			for (unsigned char j = 0; j < buttonList.size(); j++)
			{

				buttonList[j].isSelected = false;
				

			}
			buttonList[i].isSelected = true;
			menuData.buttonSelected = i;
		}
	}
}


void UpdateButtons(float& _dt)
{
	for (unsigned char i = 0; i < buttonList.size(); i++)
	{
		UpdateAnimationButton(buttonList[i].animation[0], buttonList[i].sprite, buttonList[i].isSelected, buttonList[i].isPressed, _dt);

	}
}

void UpdateButtonsSelection(void)
{
	for (unsigned char i = 0; i < buttonList.size(); i++)
	{
		if (menuData.buttonSelected == i)
		{
			buttonList[i].isSelected = true;
		}
		else
		{
			buttonList[i].isSelected = false;
		}
	}
}

void UpdateMenu(GameData& _gameData)
{
	PlayMusic(menuData.menuMusic, true, 0.f);
	FadeMenu(_gameData.gameState, _gameData.dt, _gameData.window, 25.f, 2.f);
	UpdateButtonsSelection();
	UpdateButtons(_gameData.dt);
}

void DrawButtons(sf::RenderWindow& _window)
{
	for (unsigned char i = 0; i < buttonList.size(); i++)
	{
		_window.draw(buttonList[i].sprite);

	}

}

void DisplayMenu(sf::RenderWindow& _window)
{
	_window.draw(menuData.spriteBackground);
	DrawButtons(_window);

	_window.draw(menuData.spriteGameName);

	_window.draw(menuData.fade.rect);
}

void KeypressedMenu(GameData& _gameData)
{
	if (_gameData.event.type == sf::Event::KeyPressed)
	{
		switch (_gameData.event.key.code)
		{

		case sf::Keyboard::Down:

			if (menuData.buttonSelected != QUIT)
			{
				++menuData.buttonSelected;
			}
			else
			{
				menuData.buttonSelected = PLAY;
			}

			buttonList[menuData.buttonSelected].isSelected = true;

			break;

		case sf::Keyboard::Up:

			if (menuData.buttonSelected != PLAY)
			{
				--menuData.buttonSelected;
			}
			else
			{
				menuData.buttonSelected = QUIT;
			}

			buttonList[menuData.buttonSelected].isSelected = true;

			break;

		case sf::Keyboard::Enter:

			if (buttonList[PLAY].isSelected && !menuData.fade.isFadingIn && !menuData.fade.isFadingOut)
			{

				menuData.fade.isFadingIn = false;
				menuData.fade.isFadingOut = true;
				buttonList[PLAY].isPressed = true;
			}
			else if (buttonList[SETTINGS_MENU].isSelected && !menuData.fade.isFadingIn && !menuData.fade.isFadingOut)
			{
				SetLastState(_gameData);
				_gameData.gameState = SETTINGS;
				SetAlphaMenu();
			}
			else if (buttonList[CREDITS_MENU].isSelected && !menuData.fade.isFadingIn && !menuData.fade.isFadingOut)
			{
				SetLastState(_gameData);
				_gameData.gameState = CREDITS;
				SetAlphaMenu();
			}
			else if (buttonList[QUIT].isSelected && !menuData.fade.isFadingIn && !menuData.fade.isFadingOut)
			{
				_gameData.window.close();
			}

			break;

		default:
			break;
		}
	}

}

void MousePressedMenu(GameData& _gameData)
{
	sf::Vector2i mouse = sf::Mouse::getPosition();
	if (_gameData.event.type == sf::Event::MouseButtonPressed && _gameData.event.mouseButton.button == sf::Mouse::Left && !menuData.fade.isFadingIn && !menuData.fade.isFadingOut)
	{
		if (buttonList[PLAY].isSelected && RectContains(buttonList[PLAY].sprite.getGlobalBounds(), (sf::Vector2f)mouse))
		{
			menuData.fade.isFadingIn = false;
			menuData.fade.isFadingOut = true;
			buttonList[PLAY].isPressed = true;
			PlaySoundFromList(menuData.buttonPressSound, 50);
		}
		else if (buttonList[SETTINGS_MENU].isSelected && RectContains(buttonList[SETTINGS_MENU].sprite.getGlobalBounds(), (sf::Vector2f)mouse))
		{
			SetLastState(_gameData);
			_gameData.gameState = SETTINGS;
			SetAlphaMenu();
			PlaySoundFromList(menuData.buttonPressSound, 50);
		}
		else if (buttonList[CREDITS_MENU].isSelected && RectContains(buttonList[CREDITS_MENU].sprite.getGlobalBounds(), (sf::Vector2f)mouse))
		{
			SetLastState(_gameData);
			_gameData.gameState = CREDITS;
			SetAlphaMenu();
			PlaySoundFromList(menuData.buttonPressSound, 50);
		}
		else if (buttonList[QUIT].isSelected && RectContains(buttonList[QUIT].sprite.getGlobalBounds(), (sf::Vector2f)mouse))
		{
			PlaySoundFromList(menuData.buttonPressSound, 50);
			_gameData.window.close();
		}
	}

}

void MouseMovedMenu(sf::Event::MouseMoveEvent& _buttonEvt)
{
	CheckMouseButtonCollision(_buttonEvt);
}

void SetAlphaMenu(float _alpha)
{
	menuData.fade.alpha = _alpha;
	menuData.fade.color = sf::Color(0, 0, 0, _alpha);
	menuData.fade.rect.setFillColor(menuData.fade.color);
}

void SetFadeMenuOn(void)
{
	menuData.fade.timer = menuData.fade.timerMin;
	menuData.fade.isFadingIn = true;
	menuData.fade.isFadingOut = false;
}

int GetMenuMusic()
{
	return menuData.menuMusic;
}

int GetButtonPressSound()
{
	return menuData.buttonPressSound;
}

int GetButtonSelectSound()
{
	return menuData.buttonSelectSound;
}