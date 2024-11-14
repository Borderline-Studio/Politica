#include "PreMenu.h"

PreMenu preMenu;

void InitPreMenu(GameData& _gameData)
{
	SetLoadingScreenText("Loading PreMenu/Sprite");
	DisplayLoadingScreen(_gameData);

	preMenu.texture.loadFromFile("Assets/Images/PreMenu/logoCreajeux.png");
	preMenu.texture.setSmooth(true);
	preMenu.textureLogo.loadFromFile("Assets/Images/PreMenu/Logo.png");
	preMenu.textureLogo.setSmooth(true);
	preMenu.sprite.setTexture(preMenu.texture);
	sf::Vector2u size = preMenu.texture.getSize();
	preMenu.sprite.setOrigin((float)size.x/2.f, (float)size.y/2.f);
	preMenu.sprite.setScale(GetScreen().width / (preMenu.texture.getSize().x* 2), GetScreen().width / (preMenu.texture.getSize().y*2));
	preMenu.sprite.setPosition(GetScreen().width/2, GetScreen().height / 2);

	SetLoadingScreenText("Loading PreMenu/Fade");
	DisplayLoadingScreen(_gameData);

	CreateFade(preMenu.fade, true);
	preMenu.isOnLogo = false;
	preMenu.fade.timerMax = 4;
	preMenu.fade.color = sf::Color(255, 255, 255, (sf::Uint8)preMenu.fade.alpha);
}

void FadePreMenu(int& _state, float& _dt)
{
	if (preMenu.fade.isFadingOut)
	{
		preMenu.fade.timer = preMenu.fade.timer - _dt;
		preMenu.fade.alpha = fmaxf((preMenu.fade.timer / preMenu.fade.timerMax) * preMenu.fade.alphaMax, (float)preMenu.fade.alphaMin);
		preMenu.fade.color = sf::Color(255, 255, 255, (sf::Uint8)preMenu.fade.alpha);
		preMenu.sprite.setColor(preMenu.fade.color);

		if (preMenu.fade.timer <= preMenu.fade.timerMin)
		{
			preMenu.fade.isFadingOut = false;
			if (!preMenu.isOnLogo)
			{
				preMenu.sprite.setTexture(preMenu.textureLogo, true);
				sf::Vector2u size = preMenu.textureLogo.getSize();
				preMenu.sprite.setOrigin((float)size.x / 2.f, (float)size.y / 2.f);
				preMenu.sprite.setScale(ScaleToScreen(1, 1));
				preMenu.fade.isFadingIn = true;
				preMenu.isOnLogo = true;
			}
			else
			{
				_state = MENU;
			}
		}
	}

	if (preMenu.fade.isFadingIn)
	{
		preMenu.fade.timer = preMenu.fade.timer + _dt;
		preMenu.fade.alpha = fminf((preMenu.fade.timer / preMenu.fade.timerMax) * preMenu.fade.alphaMax, preMenu.fade.alphaMax);
		preMenu.fade.color = sf::Color(255, 255, 255, (sf::Uint8)preMenu.fade.alpha);
		preMenu.sprite.setColor(preMenu.fade.color);

		if (preMenu.fade.timer >= preMenu.fade.timerMax)
		{
			preMenu.fade.isFadingIn = false;
			preMenu.fade.isFadingOut = true;
		}
	}
}

void DisplayPreMenu(sf::RenderWindow& _window)
{
	_window.draw(preMenu.sprite);
}

void KeypressedPreMenu(sf::Event::KeyEvent& _keyEvt, int& _state)
{
	if (_keyEvt.code == sf::Keyboard::Enter)
	{
		_state = MENU;
	}
}

void MousePressedPreMenu(int& _state, sf::Event::MouseButtonEvent& _buttonEvt)
{
	if (_buttonEvt.button == sf::Mouse::Left)
	{
		_state = MENU;
	}
}