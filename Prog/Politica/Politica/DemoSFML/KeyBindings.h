#ifndef KEY_BINDINGS_H

#define KEY_BINDINGS_H

#include"Common.h"
#include"Animation.h"
#include"Audio.h"

#define BUTTON_NBR 4

struct KeyBindings
{
	sf::Keyboard::Key keyCode[BUTTON_NBR];
	sf::Text keyDescription[BUTTON_NBR];
	Button resetButton;

	sf::RectangleShape rectGuide;
	sf::Text textGuide;

	sf::Texture textureKeyButton;
	sf::Texture textureResetButton;
};

struct KeyBindingsButton
{
	sf::Sprite sprite;
	Animation animation;
	bool isSelectedKeyBindings;
	bool isPressedKeyBindings;
};

KeyBindingsButton& CreateKeyBindingsButton(float _x, float _y, sf::Texture& _texture);

void CreateKeyBindingsKeyText(sf::Text& _text, std::string _str, sf::Font& _font = GetSettingsFont());

void InitKeyBindingsButtons(void);

void InitKeyBindingsTexts(void);

void InitGuide(void);

void InitKeyBindings(GameData& _gameData);

void UpdateKeyBindings(float _dt);

void UpdateKBListAnimation(unsigned char _i, float _dt);

void DisplayKeyBindingsButtons(sf::RenderWindow& _window);

void DisplayKeyBindingsTexts(sf::RenderWindow& _window);

void DisplayKeyGuide(sf::RenderWindow& _window);

void DisplayKeyDescription(sf::RenderWindow& _window);

void DisplayKeyBindings(sf::RenderWindow& _window);

void SetKey(unsigned char _i, sf::Keyboard::Key _keyEvt, std::string _str);

void KeyPressedKeyBindings(sf::Event& _event);

void MousePressedKeyBindings(sf::Event _event);

void CheckMouseButtonCollisionKB(sf::Event::MouseMoveEvent& _buttonEvt);

void MouseMovedKB(sf::Event& _event);
#endif // !KEY_BINDINGS_H


