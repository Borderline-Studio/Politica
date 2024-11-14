#include"KeyBindings.h"

KeyBindings keyBindings;
KeyBindingsButton buttonListKB[BUTTON_NBR];
sf::Text keyTextList[BUTTON_NBR];

KeyBindingsButton& CreateKeyBindingsButton(float _x, float _y, sf::Texture& _texture)
{
	KeyBindingsButton* temp = new KeyBindingsButton;

	temp->sprite = CreateSpriteWithAnims(_texture, sf::Vector2i(2, 1), true, ScaleToScreen(1.f, 1.f), PosToScreen(sf::Vector2f(_x, _y)));

	temp->isSelectedKeyBindings = false;
	temp->isPressedKeyBindings = false;

	return (*temp);
}

void CreateKeyBindingsKeyText(sf::Text& _text, std::string _str, sf::Font& _font)
{
	CreateText(_text, _font, _str, 42, sf::Color::White);
}

void InitKeys(void)
{
	keyBindings.keyCode[KB_DICES] = sf::Keyboard::D;
	keyBindings.keyCode[KB_ENDTURN] = sf::Keyboard::Enter;
	keyBindings.keyCode[KB_SHORTCUT] = sf::Keyboard::A;
	keyBindings.keyCode[KB_NWAY] = sf::Keyboard::E;

	CreateText(keyBindings.keyDescription[KB_DICES], GetSettingsFont(), "Lancer les dés", 42, sf::Color::White, false);
	CreateText(keyBindings.keyDescription[KB_ENDTURN], GetSettingsFont(), "Fin de tour", 42, sf::Color::White, false);
	CreateText(keyBindings.keyDescription[KB_SHORTCUT], GetSettingsFont(), "Raccourci", 42, sf::Color::White, false);
	CreateText(keyBindings.keyDescription[KB_NWAY], GetSettingsFont(), "Chemin normal", 42, sf::Color::White, false);

}

void InitKeyBindingsButtons(void)
{
	keyBindings.textureKeyButton.loadFromFile("Assets/Images/Settings/KeyButton.png");
	keyBindings.textureResetButton.loadFromFile("Assets/Images/Settings/ResetButton.png");

	keyBindings.resetButton = CreateButton("Assets/Images/Settings/ResetButton.png", PosToScreenY(252), true, ScaleToScreen(1.f, 1.f));
	keyBindings.resetButton.isSelected = false;
	keyBindings.resetButton.isPressed = false;

	buttonListKB[KB_DICES] = CreateKeyBindingsButton(644, 380, keyBindings.textureKeyButton); 
	buttonListKB[KB_ENDTURN] = CreateKeyBindingsButton(644, 495, keyBindings.textureKeyButton);

	buttonListKB[KB_SHORTCUT] = CreateKeyBindingsButton(1254, 380, keyBindings.textureKeyButton);
	buttonListKB[KB_NWAY] = CreateKeyBindingsButton(1254, 495, keyBindings.textureKeyButton);


	CreateAnimationLeftToRight(keyBindings.resetButton.animation[0], 3, 1, keyBindings.textureResetButton.getSize());

	for (unsigned char i = 0; i < BUTTON_NBR; i++)
	{
		CreateAnimationLeftToRight(buttonListKB[i].animation, 2, 1, keyBindings.textureKeyButton.getSize());
	}

	for (unsigned char i = 0; i < BUTTON_NBR; i++)
	{
		keyBindings.keyDescription[i].setPosition(buttonListKB[i].sprite.getPosition().x + buttonListKB[i].sprite.getGlobalBounds().width / 4.f + PosToScreenX(20), buttonListKB[i].sprite.getPosition().y - keyBindings.keyDescription[i].getGlobalBounds().height/2.f);
	}

}

void InitKeyBindingsTexts(void)
{
	CreateKeyBindingsKeyText(keyTextList[KB_DICES], "D");
	CreateKeyBindingsKeyText(keyTextList[KB_ENDTURN], "Entrée");
	CreateKeyBindingsKeyText(keyTextList[KB_SHORTCUT], "A");
	CreateKeyBindingsKeyText(keyTextList[KB_NWAY], "E");

	for (int i = 0; i < BUTTON_NBR; i++)
	{
		sf::Vector2f pos = { buttonListKB[i].sprite.getPosition().x ,buttonListKB[i].sprite.getPosition().y - PosToScreenY(10) };
		keyTextList[i].setPosition(pos);
	}
}

void InitGuide(void)
{
	keyBindings.rectGuide.setSize(sf::Vector2f(GetScreen().width, PosToScreenY(149)));
	keyBindings.rectGuide.setPosition(sf::Vector2f(0, PosToScreenY(464)));
	keyBindings.rectGuide.setFillColor(sf::Color(0, 0, 0, 150));


	CreateText(keyBindings.textGuide, GetSettingsFont(), "Appuyez sur une touche pour l'associer", 65, sf::Color::White, false);
	keyBindings.textGuide.setPosition(sf::Vector2f(PosToScreenX(374), PosToScreenY(497)));
}



void InitKeyBindings(GameData& _gameData)
{
	SetLoadingScreenText("Loading Key Bindings/Keys");
	DisplayLoadingScreen(_gameData);
	InitKeys();

	SetLoadingScreenText("Loading Key Bindings/Button");
	DisplayLoadingScreen(_gameData);
	InitKeyBindingsButtons();

	SetLoadingScreenText("Loading Key Bindings/Texts");
	DisplayLoadingScreen(_gameData);
	InitKeyBindingsTexts();

	SetLoadingScreenText("Loading Key Bindings/Guide");
	DisplayLoadingScreen(_gameData);
	InitGuide();
}

void ReloadKeyBindings(void)
{
	//InitKeys();

	keyBindings.resetButton.isSelected = false;
	keyBindings.resetButton.isPressed = false;
}

void UpdateKeyBindings(float _dt)
{
	UpdateAnimationButton(keyBindings.resetButton.animation[0], keyBindings.resetButton.sprite, keyBindings.resetButton.isSelected, keyBindings.resetButton.isPressed, _dt);

	for (unsigned int i = 0; i < BUTTON_NBR; i++)
	{
		UpdateKBListAnimation(i, _dt);

		if (keyBindings.keyCode[i] == sf::Keyboard::Unknown)
		{
			keyTextList[i].setString(" ");
		}
	}
}

void UpdateKBListAnimation(unsigned char _i, float _dt)
{
	if (buttonListKB[_i].isSelectedKeyBindings)
	{
		UpdateAnimationIsEntitySelected(buttonListKB[_i].animation, buttonListKB[_i].isSelectedKeyBindings, buttonListKB[_i].sprite);

	}
	else if (buttonListKB[_i].isPressedKeyBindings)
	{
		UpdateAnimationIsEntitySelected(buttonListKB[_i].animation, buttonListKB[_i].isPressedKeyBindings, buttonListKB[_i].sprite);

	}
	else
	{
		UpdateAnimationIsEntitySelected(buttonListKB[_i].animation, buttonListKB[_i].isSelectedKeyBindings, buttonListKB[_i].sprite);

	}
}


void DisplayKeyBindingsButtons(sf::RenderWindow& _window)
{
	for (unsigned int i = 0; i < BUTTON_NBR; i++)
	{
		_window.draw(buttonListKB[i].sprite);
	}
}

void DisplayKeyBindingsTexts(sf::RenderWindow& _window)
{
	for (unsigned int i = 0; i < BUTTON_NBR; i++)
	{
		_window.draw(keyTextList[i]);
	}
}

void DisplayKeyGuide(sf::RenderWindow& _window)
{
	for (unsigned int i = 0; i < BUTTON_NBR; i++)
	{
		if (buttonListKB[i].isPressedKeyBindings)
		{
			_window.draw(keyBindings.rectGuide);
			_window.draw(keyBindings.textGuide);
		}
	}
}

void DisplayKeyDescription(sf::RenderWindow& _window)
{
	for (unsigned char i = 0; i < BUTTON_NBR; i++)
	{
		_window.draw(keyBindings.keyDescription[i]);
	}
}



void DisplayKeyBindings(sf::RenderWindow& _window)
{
	DisplayKeyBindingsButtons(_window);
	DisplayKeyBindingsTexts(_window);
	DisplayKeyDescription(_window);
	DisplayKeyGuide(_window);
	_window.draw(keyBindings.resetButton.sprite);
}

void SetKey(unsigned char _i, sf::Keyboard::Key _keyEvt, std::string _str)
{

	for (unsigned char j = 0; j < BUTTON_NBR; j++)
	{
		if (_keyEvt == keyBindings.keyCode[j])
		{
			CreateKeyBindingsKeyText(keyTextList[j], " ", GetSettingsFont());
			keyBindings.keyCode[j] = sf::Keyboard::Unknown;
			CreateKeyBindingsKeyText(keyTextList[_i], _str, GetSettingsFont());
			keyBindings.keyCode[_i] = _keyEvt;
			break;
		}
		else
		{
			if (j == (BUTTON_NBR - 1) && _keyEvt != keyBindings.keyCode[j])
			{
				CreateKeyBindingsKeyText(keyTextList[_i], _str, GetSettingsFont());
				keyBindings.keyCode[_i] = _keyEvt;
			}
		}
	}


}


void KeyPressedKeyBindings(sf::Event& _event)
{
	if (_event.type == sf::Event::KeyPressed)
	{
		sf::Keyboard::Key key = _event.key.code;


		for (unsigned char i = 0; i < BUTTON_NBR; i++)
		{

			if (buttonListKB[i].isPressedKeyBindings && key != 40 && key != 43 && key != 44 && key != 48 && key != 53 && key != 54 && key != 61 && key != 62 && key != 63 && key != 64 && key != 65 && key != 66 && key != sf::Keyboard::Escape)
			{

				switch (key)
				{
				case sf::Keyboard::A:
					SetKey(i, key, "A");
					break;
				case sf::Keyboard::B:
					SetKey(i, key, "B");
					break;
				case sf::Keyboard::C:
					SetKey(i, key, "C");
					break;
				case sf::Keyboard::D:
					SetKey(i, key, "D");
					break;
				case sf::Keyboard::E:
					SetKey(i, key, "E");
					break;
				case sf::Keyboard::F:
					SetKey(i, key, "F");
					break;
				case sf::Keyboard::G:
					SetKey(i, key, "G");
					break;
				case sf::Keyboard::H:
					SetKey(i, key, "H");
					break;
				case sf::Keyboard::I:
					SetKey(i, key, "I");
					break;
				case sf::Keyboard::J:
					SetKey(i, key, "J");
					break;
				case sf::Keyboard::K:
					SetKey(i, key, "K");
					break;
				case sf::Keyboard::L:
					SetKey(i, key, "L");
					break;
				case sf::Keyboard::M:
					SetKey(i, key, "M");
					break;
				case sf::Keyboard::N:
					SetKey(i, key, "N");
					break;
				case sf::Keyboard::O:
					SetKey(i, key, "O");
					break;
				case sf::Keyboard::P:
					SetKey(i, key, "P");
					break;
				case sf::Keyboard::Q:
					SetKey(i, key, "Q");
					break;
				case sf::Keyboard::R:
					SetKey(i, key, "R");
					break;
				case sf::Keyboard::S:
					SetKey(i, key, "S");
					break;
				case sf::Keyboard::T:
					SetKey(i, key, "T");
					break;
				case sf::Keyboard::U:
					SetKey(i, key, "U");
					break;
				case sf::Keyboard::V:
					SetKey(i, key, "V");
					break;
				case sf::Keyboard::W:
					SetKey(i, key, "W");
					break;
				case sf::Keyboard::X:
					SetKey(i, key, "X");
					break;
				case sf::Keyboard::Y:
					SetKey(i, key, "Y");
					break;
				case sf::Keyboard::Z:
					SetKey(i, key, "Z");
					break;
				case sf::Keyboard::Numpad0:
					SetKey(i, key, "PavéNum0");
					break;
				case sf::Keyboard::Numpad1:
					SetKey(i, key, "PavéNum1");
					break;
				case sf::Keyboard::Numpad2:
					SetKey(i, key, "PavéNum2");
					break;
				case sf::Keyboard::Numpad3:
					SetKey(i, key, "PavéNum3");
					break;
				case sf::Keyboard::Numpad4:
					SetKey(i, key, "PavéNum4");
					break;
				case sf::Keyboard::Numpad5:
					SetKey(i, key, "PavéNum5");
					break;
				case sf::Keyboard::Numpad6:
					SetKey(i, key, "PavéNum6");
					break;
				case sf::Keyboard::Numpad7:
					SetKey(i, key, "PavéNum7");
					break;
				case sf::Keyboard::Numpad8:
					SetKey(i, key, "PavéNum8");
					break;
				case sf::Keyboard::Numpad9:
					SetKey(i, key, "PavéNum9");
					break;
				case sf::Keyboard::Num0:
					SetKey(i, key, "0");
					break;
				case sf::Keyboard::Num1:
					SetKey(i, key, "1");
					break;
				case sf::Keyboard::Num2:
					SetKey(i, key, "2");
					break;
				case sf::Keyboard::Num3:
					SetKey(i, key, "3");
					break;
				case sf::Keyboard::Num4:
					SetKey(i, key, "4");
					break;
				case sf::Keyboard::Num5:
					SetKey(i, key, "5");
					break;
				case sf::Keyboard::Num6:
					SetKey(i, key, "6");
					break;
				case sf::Keyboard::Num7:
					SetKey(i, key, "7");
					break;
				case sf::Keyboard::Num8:
					SetKey(i, key, "8");
					break;
				case sf::Keyboard::Num9:
					SetKey(i, key, "9");
					break;
				case sf::Keyboard::F1:
					SetKey(i, key, "F1");
					break;
				case sf::Keyboard::F2:
					SetKey(i, key, "F2");
					break;
				case sf::Keyboard::F3:
					SetKey(i, key, "F3");
					break;
				case sf::Keyboard::F4:
					SetKey(i, key, "F4");
					break;
				case sf::Keyboard::F5:
					SetKey(i, key, "F5");
					break;
				case sf::Keyboard::F6:
					SetKey(i, key, "F6");
					break;
				case sf::Keyboard::F7:
					SetKey(i, key, "F7");
					break;
				case sf::Keyboard::F8:
					SetKey(i, key, "F8");
					break;
				case sf::Keyboard::F9:
					SetKey(i, key, "F9");
					break;
				case sf::Keyboard::F10:
					SetKey(i, key, "F10");
					break;
				case sf::Keyboard::F11:
					SetKey(i, key, "F11");
					break;
				case sf::Keyboard::F12:
					SetKey(i, key, "F12");
					break;
				case sf::Keyboard::Up:
					SetKey(i, key, "Flèche Haut");
					break;
				case sf::Keyboard::Down:
					SetKey(i, key, "Flèche Bas");
					break;
				case sf::Keyboard::Left:
					SetKey(i, key, "Flèche Gauche");
					break;
				case sf::Keyboard::Right:
					SetKey(i, key, "Flèche Droite");
					break;
				case sf::Keyboard::Escape:
					SetKey(i, key, "Echap");
					break;
				case sf::Keyboard::LControl:
					SetKey(i, key, "CtrlGauche");
					break;
				case sf::Keyboard::LShift:
					SetKey(i, key, "MajGauche");
					break;
				case sf::Keyboard::LAlt:
					SetKey(i, key, "AltGauche");
					break;
				case sf::Keyboard::RControl:
					SetKey(i, key, "CtrlDroite");
					break;
				case sf::Keyboard::RShift:
					SetKey(i, key, "MajDroite");
					break;
				case sf::Keyboard::RAlt:
					SetKey(i, key, "AltDroite");
					break;
				case sf::Keyboard::Menu:
					SetKey(i, key, "Menu");
					break;
				case sf::Keyboard::RBracket:
					SetKey(i, key, "^");
					break;
				case sf::Keyboard::Period:
					SetKey(i, key, ";");
					break;
				case sf::Keyboard::Equal:
					SetKey(i, key, "=");
					break;
				case sf::Keyboard::Space:
					SetKey(i, key, "Espace");
					break;
				case sf::Keyboard::Enter:
					SetKey(i, key, "Entree");
					break;
				case sf::Keyboard::BackSpace:
					SetKey(i, key, "Retour");
					break;
				case sf::Keyboard::Tab:
					SetKey(i, key, "Tab");
					break;
				case sf::Keyboard::Add:
					SetKey(i, key, "+");
					break;
				case sf::Keyboard::Subtract:
					SetKey(i, key, "-");
					break;
				case sf::Keyboard::Multiply:
					SetKey(i, key, "*");
					break;
				case sf::Keyboard::LBracket:
					SetKey(i, key, ")");
					break;
				case sf::Keyboard::Quote:
					SetKey(i, key, "²");
					break;
				case sf::Keyboard::Comma:
					SetKey(i, key, ",");
					break;

				default:
					SetKey(i, sf::Keyboard::Unknown, " ");
					break;
				}

				buttonListKB[i].isSelectedKeyBindings = false;
				buttonListKB[i].isPressedKeyBindings = false;

			}
		}
	}
}


void MousePressedKeyBindings(sf::Event _event)
{

	if (_event.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2i mouse = sf::Mouse::getPosition();

		for (unsigned char i = 0; i < BUTTON_NBR; i++)
		{
			if (_event.mouseButton.button == sf::Mouse::Left && RectContains(buttonListKB[i].sprite.getGlobalBounds(), (sf::Vector2f)mouse))
			{
				for (unsigned char j = 0; j < BUTTON_NBR; j++)
				{
					buttonListKB[j].isPressedKeyBindings = false;
				}
				buttonListKB[i].isPressedKeyBindings = true;
				PlaySoundFromList(GetButtonPressSound(), 50);
			}

			if (_event.mouseButton.button == sf::Mouse::Left && !RectContains(buttonListKB[i].sprite.getGlobalBounds(), (sf::Vector2f)mouse) && !RectContains(keyBindings.resetButton.sprite.getGlobalBounds(), (sf::Vector2f)mouse))
			{
				buttonListKB[i].isPressedKeyBindings = false;
				buttonListKB[i].isSelectedKeyBindings = false;
			}
		}
		if (_event.mouseButton.button == sf::Mouse::Left && RectContains(keyBindings.resetButton.sprite.getGlobalBounds(), (sf::Vector2f)mouse))
		{
			PlaySoundFromList(GetButtonPressSound(), 50);
			keyBindings.resetButton.isPressed = true;
			SetKey(KB_DICES, sf::Keyboard::D, "D");
			SetKey(KB_ENDTURN, sf::Keyboard::Enter, "Entrée");
			SetKey(KB_SHORTCUT, sf::Keyboard::A, "A");
			SetKey(KB_NWAY, sf::Keyboard::E, "E");
		}

	}
}

void MouseMovedKB(sf::Event& _event)
{
	if (_event.type == sf::Event::MouseMoved)
	{
		CheckMouseButtonCollisionKB(_event.mouseMove);
	}
}

void CheckMouseButtonCollisionKB(sf::Event::MouseMoveEvent& _buttonEvt)
{
	sf::Vector2f mouse = { (float)_buttonEvt.x , (float)_buttonEvt.y };

	for (unsigned char i = 0; i < BUTTON_NBR; i++)
	{
		for (unsigned char j = 0; j < BUTTON_NBR; j++)
		{
			if (RectContains(buttonListKB[i].sprite.getGlobalBounds(), mouse) && !buttonListKB[i].isSelectedKeyBindings && !GetAnyButtonIsPressed())
			{
				PlaySoundFromList(GetButtonSelectSound(), 5);
			}
			if (RectContains(keyBindings.resetButton.sprite.getGlobalBounds(), mouse) && !keyBindings.resetButton.isSelected && !GetAnyButtonIsPressed())
			{
				PlaySoundFromList(GetButtonSelectSound(), 5);
			}
			if (RectContains(buttonListKB[i].sprite.getGlobalBounds(), mouse) && !GetAnyButtonIsPressed())
			{
				buttonListKB[j].isSelectedKeyBindings = false;
				buttonListKB[i].isSelectedKeyBindings = true;
			}
			else if (RectContains(keyBindings.resetButton.sprite.getGlobalBounds(), mouse) && !GetAnyButtonIsPressed())
			{
				buttonListKB[i].isSelectedKeyBindings = false;
				keyBindings.resetButton.isSelected = true;

			}
			else
			{
				buttonListKB[i].isSelectedKeyBindings = false;
				keyBindings.resetButton.isSelected = false;
			}
		}

	}
}

sf::Keyboard::Key GetKey(int _i)
{
	return keyBindings.keyCode[_i];
}

std::string GetKeyText(int _i)
{
	return keyTextList[_i].getString();
}

bool GetAnyButtonIsPressed(void)
{
	unsigned char nbButtonsSelected = 0;
	for (unsigned char i = 0; i < BUTTON_NBR; i++)
	{
		if (buttonListKB[i].isPressedKeyBindings)
		{
			++nbButtonsSelected;
		}
	}

	if (nbButtonsSelected > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void SetAllButtonsNotSelectedNotPressedKB(void)
{
	for (unsigned char i = 0; i < BUTTON_NBR; i++)
	{
		buttonListKB[i].isPressedKeyBindings = false;
		buttonListKB[i].isSelectedKeyBindings = false;
	}
}


