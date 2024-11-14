#include"Credits.h"

CreditsData credits;

void InitCredits(GameData& _gameData)
{
	SetLoadingScreenText("Loading Credits/Sprites");
	DisplayLoadingScreen(_gameData);
	credits.texture.loadFromFile("Assets/Images/Credits/Credits.png");
	credits.texture.setSmooth(true);
	credits.sprite.setTexture(credits.texture);
	credits.posY = GetScreen().height;
	sf::Vector2f pos = { 0, 0 };
	credits.sprite.setPosition(pos);
	credits.sprite.setScale(GetScreen().width / credits.texture.getSize().x, GetScreen().height / credits.texture.getSize().y);
	credits.speed = 100;

	credits.quitButton = CreateButton("Assets/Images/Hud/Cross.png", PosToScreenY(35), true, ScaleToScreen(1.f, 1.f), GetScreen().width - PosToScreenX(35));

	CreateAnimationLeftToRight(credits.quitButton.animation[0], 3, 1, credits.quitButton.texture->getSize());
}

void ReloadCredits(void)
{
	credits.posY = GetScreen().height;
	sf::Vector2f pos = { 0, 0 };
	credits.sprite.setPosition(pos);
}

void UpdateCredits(float _dt)
{
	//if (credits.posY >= 0)
	//{
	//	credits.posY -= credits.speed * _dt;
	//	sf::Vector2f pos = { 0, credits.posY };
	//	credits.sprite.setPosition(pos);
	//}
	UpdateAnimationButton(credits.quitButton.animation[0], credits.quitButton.sprite, credits.quitButton.isSelected, credits.quitButton.isPressed, _dt);
}

void DisplayCredits(sf::RenderWindow& _window)
{
	_window.draw(credits.sprite);
	_window.draw(credits.quitButton.sprite);
}

void KeyPressedCredits(int& _state, sf::Event& _event)
{
	if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape)
	{
		_state = MENU;
		//credits.posY = GetScreen().height;
	}

}

void MousePressedCredits(int& _state, sf::Event& _event)
{
	sf::Vector2f mouse = { (float)_event.mouseButton.x , (float)_event.mouseButton.y };
	if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left && RectContains(credits.quitButton.sprite.getGlobalBounds(), mouse))
	{
		PlaySoundFromList(GetButtonPressSound(), 50);
		_state = MENU;
		//	//credits.posY = GetScreen().height;
	}
}

void MouseMovedCredits(sf::Event& _event)
{
	sf::Vector2f mouse = { (float)_event.mouseMove.x , (float)_event.mouseMove.y };

	if (_event.type == sf::Event::MouseMoved)
	{
		if (RectContains(credits.quitButton.sprite.getGlobalBounds(), mouse))
		{
			if (!credits.quitButton.isSelected)
			{
				PlaySoundFromList(GetButtonSelectSound(), 5);
			}
			credits.quitButton.isSelected = true;
		}
		else
		{
			credits.quitButton.isSelected = false;
		}
	}
}