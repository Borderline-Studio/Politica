#include"Settings.h"
#include "Menu.h"

Settings settings;

void InitSettings(GameData& _gameData)
{
	SetLoadingScreenText("Loading Settings");
	DisplayLoadingScreen(_gameData);

	settings.soundMultiplier = 0.5f;

	SetLoadingScreenText("Loading Settings/Sprites");
	DisplayLoadingScreen(_gameData);

	InitSettingsSprites();
	InitSettingsVolumeRect();

	SetLoadingScreenText("Loading Settings/Texts");
	DisplayLoadingScreen(_gameData);

	InitSettingsTexts();
}

void ReloadSettings(void)
{
	//settings.soundMultiplier = 0.5f;
	//settings.volumeRect.setSize(sf::Vector2f(settings.soundMultiplier * settings.originalRectSize.x, settings.originalRectSize.y));
}

void InitSettingsSprites(void)
{
	settings.backgroundTexture.loadFromFile("Assets/Images/Settings/Background.png");

	settings.backgroundSprite.setTexture(settings.backgroundTexture, true);
	settings.backgroundSprite.setScale(sf::Vector2f(GetScreen().width / settings.backgroundTexture.getSize().x, GetScreen().height / settings.backgroundTexture.getSize().y));

	settings.buttonList.push_back(CreateButton("Assets/Images/Settings/MinusButton.png", PosToScreenY(108), true, ScaleToScreen(1.f, 1.f), PosToScreenX(634)));
	settings.buttonList.push_back(CreateButton("Assets/Images/Settings/PlusButton.png", PosToScreenY(108), true, ScaleToScreen(1.f, 1.f), PosToScreenX(1267)));
	settings.buttonList.push_back(CreateButton("Assets/Images/Hud/Cross.png", PosToScreenY(35), true, ScaleToScreen(1.f, 1.f), GetScreen().width - PosToScreenX(35)));

	for (unsigned char i = 0; i < settings.buttonList.size(); i++)
	{
		CreateAnimationLeftToRight(settings.buttonList[i].animation[0], 3, 1, settings.buttonList[i].texture->getSize());
	}
}

void InitSettingsTexts(void)
{
	settings.textFont.loadFromFile("Assets/Fonts/HudFont.ttf");
	CreateText(settings.volumeText, settings.textFont, "50", 42, sf::Color::White, true);
	settings.volumeText.setPosition(settings.volumeRect.getPosition().x + settings.originalRectSize.x / 2.f, settings.volumeRect.getPosition().y + settings.originalRectSize.y / 3.f);
}

void InitSettingsVolumeRect(void)
{
	settings.volumeBar = LoadSprite("Assets/Images/Settings/VolumeBar.png");
	settings.volumeBar.setPosition(PosToScreenX(718), PosToScreenY(76));

	CreateRectangleShape(settings.volumeRect, sf::Vector2f(PosToScreenX(725), PosToScreenY(83)), PosToScreen(sf::Vector2f(450, 54)), sf::Color(43, 58, 103), false);
	settings.originalRectSize = PosToScreen(sf::Vector2f(450, 54));
	settings.volumeRect.setSize(sf::Vector2f(settings.soundMultiplier * settings.originalRectSize.x, settings.originalRectSize.y));
}


void UpdateSettings(float& _dt)
{
	UpdateSettingsButtons(_dt);
	UpdateVolumeRectSize();
}

void UpdateSettingsButtons(float& _dt)
{
	for (auto it = settings.buttonList.begin(); it < settings.buttonList.end(); it++)
	{
		UpdateAnimationButton(it->animation[0], it->sprite, it->isSelected, it->isPressed, _dt);
	}
}

void UpdateVolumeRectSize(void)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();

	if (settings.volumeRectSelected)
	{
		settings.volumeRect.setSize(sf::Vector2f(fmaxf(fminf(mousePos.x - settings.volumeRect.getPosition().x, settings.originalRectSize.x), 0.f), settings.volumeRect.getSize().y));
		settings.soundMultiplier = settings.volumeRect.getSize().x / settings.originalRectSize.x;

		SoundMultiplierSecurity();
		SetAllMusicVolume();
		SetAllSoundVolume();

		SetCenteredString(settings.volumeText, ToString(settings.soundMultiplier * 100.f));
	}
}


void DisplaySettings(sf::RenderWindow& _window)
{
	_window.draw(settings.backgroundSprite);
	_window.draw(settings.volumeBar);

	for (auto it = settings.buttonList.begin(); it < settings.buttonList.end(); it++)
	{
		_window.draw(it->sprite);
	}

	_window.draw(settings.volumeRect);
	_window.draw(settings.volumeText);
}


void MousePressedSettings(sf::Event& _event, int& _lastState, int& _gameState)
{
	sf::Vector2i mousePos = { _event.mouseButton.x,  _event.mouseButton.y };
	sf::FloatRect rect = { settings.volumeRect.getPosition().x ,settings.volumeRect.getPosition().y ,settings.originalRectSize.x ,settings.originalRectSize.y };

	if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left && RectContains(settings.buttonList[MINUS].sprite.getGlobalBounds(), (sf::Vector2f)mousePos))
	{
		settings.soundMultiplier -= 0.05f;
		settings.buttonList[MINUS].isPressed = true;
		SoundMultiplierSecurity();
		SetAllMusicVolume();
		SetAllSoundVolume();
		PlaySoundFromList(GetButtonPressSound(), 50);
		SetCenteredString(settings.volumeText, ToString(settings.soundMultiplier * 100.f));
		settings.volumeRect.setSize(sf::Vector2f(settings.soundMultiplier * settings.originalRectSize.x, settings.volumeRect.getSize().y));
	}

	if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left && RectContains(settings.buttonList[PLUS].sprite.getGlobalBounds(), (sf::Vector2f)mousePos))
	{

		settings.soundMultiplier += 0.05f;
		settings.buttonList[PLUS].isPressed = true;
		SoundMultiplierSecurity();
		SetAllMusicVolume();
		SetAllSoundVolume();
		PlaySoundFromList(GetButtonPressSound(), 50);
		SetCenteredString(settings.volumeText, ToString(settings.soundMultiplier * 100.f));
		settings.volumeRect.setSize(sf::Vector2f(settings.soundMultiplier * settings.originalRectSize.x, settings.volumeRect.getSize().y));
	}

	if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left && RectContains(rect, (sf::Vector2f)mousePos) && !settings.volumeRectSelected)
	{
		settings.volumeRectSelected = true;
	}

	if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left && RectContains(settings.buttonList[QUIT_S].sprite.getGlobalBounds(), (sf::Vector2f)mousePos))
	{
		PlaySoundFromList(GetButtonPressSound(), 50);
		if (_lastState == MENU)
		{
			_gameState = MENU;
		}
		else if (_lastState == PAUSE)
		{
			_gameState = PAUSE;
		}
	}
}

void MouseReleasedSettings(sf::Event& _event)
{
	if (_event.type == sf::Event::MouseButtonReleased && _event.mouseButton.button == sf::Mouse::Left && settings.volumeRectSelected)
	{
		settings.volumeRectSelected = false;
	}
}

void MouseMovedSettings(sf::Event& _event)
{
	sf::Vector2f mouse = { (float)_event.mouseMove.x , (float)_event.mouseMove.y };

	if (_event.type == sf::Event::MouseMoved)
	{
		for (unsigned char i = 0; i < settings.buttonList.size(); i++)
		{
			if (RectContains(settings.buttonList[i].sprite.getGlobalBounds(), mouse) && !settings.buttonList[i].isSelected)
			{
				PlaySoundFromList(GetButtonSelectSound(), 5);
			}
			if (RectContains(settings.buttonList[i].sprite.getGlobalBounds(), mouse))
			{

				for (unsigned char j = 0; j < settings.buttonList.size(); j++)
				{

					settings.buttonList[j].isSelected = false;

				}
				settings.buttonList[i].isSelected = true;
			}
			else
			{
				settings.buttonList[i].isSelected = false;
			}
		}
	}
}

void KeyPressedSettings(GameData& _gameData)
{
	if (_gameData.event.type == sf::Event::KeyPressed && _gameData.event.key.code == sf::Keyboard::Escape && !GetAnyButtonIsPressed())
	{
		if (_gameData.lastState == MENU)
		{
			_gameData.gameState = MENU;
		}
		else if (_gameData.lastState == PAUSE)
		{
			_gameData.gameState = PAUSE;
		}
	}
	else if (_gameData.event.type == sf::Event::KeyPressed && _gameData.event.key.code == sf::Keyboard::Escape && GetAnyButtonIsPressed())
	{
		SetAllButtonsNotSelectedNotPressedKB();
	}
}

void SoundMultiplierSecurity(void)
{
	if (settings.soundMultiplier < 0.01f)
	{
		settings.soundMultiplier = 0.f;
	}
	if (settings.soundMultiplier > 0.99f)
	{
		settings.soundMultiplier = 1.f;
	}
}

float GetSoundMultiplier(void)
{
	return settings.soundMultiplier;
}

sf::Font& GetSettingsFont(void)
{
	return settings.textFont;
}