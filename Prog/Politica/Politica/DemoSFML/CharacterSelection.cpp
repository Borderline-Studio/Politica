#include"CharacterSelection.h"

CharacterSelection CS;
NBPlayersSelection nbPlayersSelection;
CharacterSelectionSound characterSelectionSound;

void InitCharacterSelection(GameData& _gameData)
{
	SetLoadingScreenText("Loading Character Selection");
	DisplayLoadingScreen(_gameData);

	std::string path = "Assets/Images/CharacterSelection/";
	CreateFadeRect(CS.fade, true);
	CS.fade.rect.setSize(sf::Vector2f(GetScreen().width * 2.f, GetScreen().height));

	SetLoadingScreenText("Loading Character Selection/Avatars");
	DisplayLoadingScreen(_gameData);

	InitAvatars(path);
	InitNameModification(path);
	InitCharacterSelectionPlayerReadyText();

	SetLoadingScreenText("Loading Character Selection/Backgrounds");
	DisplayLoadingScreen(_gameData);
	InitCharacterSelectionBackground(path);

	SetLoadingScreenText("Loading Character Selection/Buttons");
	DisplayLoadingScreen(_gameData);
	InitCharacterSelectionButton();

	//NBPSelect
	InitNBPlayersSelection(path);
	CS.music = AddMusic("Assets/Musics/CharacterSelection.wav");
}

void ReloadCharacterSelection(void)
{
	CreateFadeRect(CS.fade, true);
	CS.fade.rect.setSize(sf::Vector2f(GetScreen().width * 2.f, GetScreen().height));
	//CS.fade.timer = CS.fade.timerMin;
	//SetAlphaCharacterSelection();

	CS.playerChoosing = PLAYER_1;
	CS.AIChoosing = 0;
	CS.currentButton = READY;

	CS.buttonList[READY].isSelected = false;
	CS.buttonList[PLAY_CS].isSelected = false;
	CS.buttonList[READY].isPressed = false;
	CS.buttonList[PLAY_CS].isPressed = false;

	CS.nameModifIsSelected = false;

	CS.names[MARGARET_TCHATCHEUR].string = "Margaret Tchatcheur";
	CS.names[RONALD_RAYBAN].string = "Ronald Rayban";
	CS.names[JV_FRANCO].string = "J.V Franco";
	CS.names[VLAD_INPUT].string = "Vlad Input";

	CS.playerSelectionString = "J1";
	CreateText(CS.playerSelectionText, GetSettingsFont(), CS.playerSelectionString, 50, GetPlayerColor(CS.playerChoosing), true);

	CS.playerSelectionText.setString(CS.playerSelectionString);
	CS.playerSelectionText.setFillColor(GetPlayerColor(CS.playerChoosing));

	for (unsigned char i = 0; i < NB_CHARACTERS; i++)
	{
		CS.names[i].enteringName = false;
		CreateText(CS.names[i].text, GetSettingsFont(), CS.names[i].string, 20, sf::Color::White);
		CreateText(CS.playerReadyText[i], GetSettingsFont(), "J1", 45, GetPlayerColor(i), true);
		CreateText(CS.readyText[i], GetSettingsFont(), "PRET", 45, GetPlayerColor(i), true);
		CS.selector[i].sprite.setColor(GetPlayerColor(CS.playerChoosing));
		CS.selector[i].isSelected = false;

		CS.avatarSprite[i].setColor(sf::Color{ 255, 255, 255, 255 });
	}

	//nbPlayersSelection
	nbPlayersSelection.camera.setCenter(GetScreen().width / 2.f, GetScreen().height / 2.f);
	nbPlayersSelection.goingToCS = false;
	nbPlayersSelection.isOnCS = false;
	nbPlayersSelection.nbAI = 0;
	characterSelectionSound.characterSelected = AddSound("Assets/Sounds/CharacterSelected.ogg");
}



void UpdateCharacterSelection(GameData& _gameData)
{

	PlayMusic(CS.music, true, 0.f);
	FadeCharacterSelection(_gameData, 25.f, 2.f);
	UpdateButtonsCS(_gameData.dt);
	UpdateNBPlayersSelection(_gameData.dt);
	UpdateAnimationIsEntitySelected(CS.animationNameModif, CS.nameModifIsSelected, CS.nameSelectionAreaSprite);
}


void DisplayCharacterSelection(sf::RenderWindow& _window)
{
	_window.setView(nbPlayersSelection.camera);
	_window.draw(CS.background);

	if (nbPlayersSelection.goingToCS || nbPlayersSelection.isOnCS)
	{
		DisplayAvatars(_window);

		_window.draw(CS.modifyRectSprite);
		_window.draw(CS.nameSelectionAreaSprite);
		_window.draw(CS.buttonList[CS.currentButton].sprite);

		if (GetCharacterSelectedBool(CS.playerChoosing))
		{
			_window.draw(CS.playerSelectionText);
		}

		DisplayPlayerReadyTexts(_window);

		DisplayNames(_window);
	}

	if (!nbPlayersSelection.isOnCS)
	{
		DisplayNBPlayersSelection(_window);
	}

	_window.draw(CS.fade.rect);

}

void KeyPressedCharacterSelection(GameData& _gameData)
{

	if (_gameData.event.type == sf::Event::KeyPressed && !CS.fade.isFadingIn && !CS.fade.isFadingOut)
	{
		ChangeGameStateKeyPressed(_gameData);
		EnterToValidateNameOrCharacter(_gameData);
		EraseLetterModifiedName(_gameData);
	}

	if (_gameData.event.type == sf::Event::TextEntered && !CS.fade.isFadingIn && !CS.fade.isFadingOut)
	{
		WriteToModifyName(_gameData);
	}

	KeyPressedNBPlayersSelection(_gameData);
}

void MousePressedCharacterSelection(GameData& _gameData)
{
	sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(_gameData.window);


	mouse = { mouse.x + nbPlayersSelection.camera.getCenter().x - GetScreen().width / 2,mouse.y + nbPlayersSelection.camera.getCenter().y - GetScreen().height / 2 };

	if (_gameData.event.type == sf::Event::MouseButtonPressed && _gameData.event.mouseButton.button == sf::Mouse::Left && !CS.fade.isFadingIn && !CS.fade.isFadingOut)
	{

		CollisionMouseButtonCS(mouse);
		CollisionMouseButtonNBPlayersSelection(mouse);
		ResetCharacterSelectionOnClick(mouse);
		ConfirmCharacterSelection(mouse);
	}
}

void MouseMovedCharacterSelection(sf::Event::MouseMoveEvent& _buttonEvt)
{
	CheckMouseButtonCollisionCharacterSelection(_buttonEvt);
	CheckMouseButtonCollisionNBPlayersSelection(_buttonEvt);
}


//init functions

void InitAvatars(std::string& _path)
{
	InitAvatarsSprites(_path);
	InitAvatarsNamesSprites(_path);
	InitAvatarsPosition();
	InitAvatarsSelectedRect(_path);
	CS.playerChoosing = PLAYER_1;
}

void InitCharacterSelectionBackground(std::string& _path)
{
	CS.background = LoadSprite(_path + "Background.png");

	CS.background.setScale(GetScreen().width / (CS.background.getLocalBounds().width / 2), GetScreen().height / CS.background.getLocalBounds().height);
}

void InitCharacterSelectionPlayerReadyText(void)
{
	for (unsigned char i = 0; i < NB_CHARACTERS; i++)
	{
		CreateText(CS.playerReadyText[i], GetSettingsFont(), "J1", 45, GetPlayerColor(i), true);
		CreateText(CS.readyText[i], GetSettingsFont(), "PRET", 45, GetPlayerColor(i), true);

		CS.playerReadyText[i].setPosition(sf::Vector2f(CS.avatarSprite[i].getPosition().x, CS.avatarSprite[i].getPosition().y - PosToScreenY(35)));
		CS.readyText[i].setPosition(sf::Vector2f(CS.avatarSprite[i].getPosition().x, CS.avatarSprite[i].getPosition().y + PosToScreenY(35)));
	}
}

void InitAvatarsPosition(void)
{
	sf::Vector2f initialOffset = { PosToScreenX(179), PosToScreenY(50) };

	for (unsigned char i = 0; i < NB_CHARACTERS; i++)
	{
		if (i == MARGARET_TCHATCHEUR)
		{
			CS.avatarSprite[i].setPosition(initialOffset.x + CS.nameRect[i].getGlobalBounds().width / 2 + GetScreen().width, initialOffset.y + CS.avatarSprite[i].getGlobalBounds().height / 2 + PosToScreenY(22));
			CS.nameRect[i].setPosition(initialOffset.x + CS.nameRect[i].getGlobalBounds().width / 2 + GetScreen().width, initialOffset.y + CS.nameRect[i].getGlobalBounds().height / 2);
		}
		else
		{
			CS.nameRect[i].setPosition(CS.nameRect[i - 1].getPosition().x + CS.nameRect[i - 1].getGlobalBounds().width + PosToScreenX(120), CS.nameRect[i - 1].getPosition().y);
			CS.avatarSprite[i].setPosition(CS.nameRect[i].getPosition().x, initialOffset.y + CS.avatarSprite[i].getGlobalBounds().height / 2 + PosToScreenY(22));
		}
	}
}

void InitAvatarsSelectedRect(std::string _path)
{
	CS.selectorTexture.loadFromFile(_path + "CharacterSelector.png");

	for (unsigned char i = 0; i < NB_CHARACTERS; i++)
	{
		CS.selector[i].sprite =  CreateSprite(CS.selectorTexture, CS.nameRect[i].getPosition(), true);
		CS.selector[i].isSelected = false;
		CS.selector[i].sprite.setColor(GetPlayerColor(PLAYER_1));
	}

	CS.playerSelectionString = "J1";
	CreateText(CS.playerSelectionText, GetSettingsFont(), CS.playerSelectionString, 45, GetPlayerColor(CS.playerChoosing), true);

	CS.playerSelectionText.setPosition(CS.selector[CS.playerChoosing].sprite.getPosition().x, CS.selector[CS.playerChoosing].sprite.getPosition().y - PosToScreenY(235));
}

void InitAvatarsSprites(std::string& _path)
{
	CS.avatarSprite[MARGARET_TCHATCHEUR] = LoadSprite(_path + "MargaretTchatcheur2.png", true);
	CS.avatarSprite[RONALD_RAYBAN] = LoadSprite(_path + "RonaldRayban2.png", true);
	CS.avatarSprite[JV_FRANCO] = LoadSprite(_path + "JVFranco2.png", true);
	CS.avatarSprite[VLAD_INPUT] = LoadSprite(_path + "VladInput2.png", true);
}

void InitCharacterSelectionButton(void)
{
	CS.buttonList.push_back(CreateButton("Assets/Images/CharacterSelection/ReadyButton.png", CS.modifyRectSprite.getPosition().y, true, ScaleToScreen(1.f, 1.f), PosToScreenX(699) + CS.modifyRectSprite.getPosition().x, 2));
	CS.buttonList.push_back(CreateButton("Assets/Images/CharacterSelection/PlayButton.png", CS.modifyRectSprite.getPosition().y, true, ScaleToScreen(1.f, 1.f), PosToScreenX(699) + CS.modifyRectSprite.getPosition().x));
	CS.buttonList[READY].isSelected = false;
	CS.buttonList[PLAY_CS].isSelected = false;

	CS.buttonList[READY].isPressed = false;
	CS.buttonList[PLAY_CS].isPressed = false;

	CS.currentButton = READY;

	CreateAnimationLeftToRight(CS.buttonList[READY].animation[0], 2, 1, CS.buttonList[READY].texture->getSize());
	CreateAnimationLeftToRight(CS.buttonList[PLAY_CS].animation[0], 3, 1, CS.buttonList[PLAY_CS].texture->getSize());
	characterSelectionSound.characterSelected = AddSound("Assets/Sounds/CharacterSelected.ogg");
}

void InitAvatarsNamesSprites(std::string& _path)
{
	for (unsigned char i = 0; i < NB_CHARACTERS; i++)
	{
		CS.nameRect[i] = LoadSprite(_path + "CharacterNameRectangle.png", true);
	}

}

void InitNameModification(std::string& _path)
{
	CS.modifyRectSprite = LoadSprite(_path + "CharacterModifiedNameRectangle.png", true);

	CS.nameSelectionAreaTexture.loadFromFile(_path + "CharacterModifiedNameSelectionArea.png");
	CreateAnimationLeftToRight(CS.animationNameModif, 2, 1, CS.nameSelectionAreaTexture.getSize());
	CS.nameModifIsSelected = false;

	CS.nameSelectionAreaSprite.setTexture(CS.nameSelectionAreaTexture);
	CS.nameSelectionAreaSprite.setOrigin(CS.nameSelectionAreaTexture.getSize().x / 4.f, CS.nameSelectionAreaTexture.getSize().y / 2.f);
	CS.nameSelectionAreaSprite.setScale(ScaleToScreen(0.8f, 0.8f));


	CS.names[MARGARET_TCHATCHEUR].string = "Margaret Tchatcheur";
	CS.names[RONALD_RAYBAN].string = "Ronald Rayban";
	CS.names[JV_FRANCO].string = "J.V Franco";
	CS.names[VLAD_INPUT].string = "Vlad Input";

	CS.modifyRectSprite.setPosition(PosToScreenX(600) + CS.modifyRectSprite.getGlobalBounds().width / 2 + GetScreen().width, PosToScreenY(930) + CS.modifyRectSprite.getGlobalBounds().height / 2);
	CS.nameSelectionAreaSprite.setPosition(PosToScreenX(690) + CS.nameSelectionAreaSprite.getGlobalBounds().width / 4 + GetScreen().width, PosToScreenY(930) + CS.modifyRectSprite.getGlobalBounds().height / 2);

	for (unsigned char i = 0; i < NB_CHARACTERS; i++)
	{
		CS.names[i].enteringName = false;
		CreateText(CS.names[i].text, GetSettingsFont(), CS.names[i].string, 20, sf::Color::White);
		CS.names[i].text.setPosition(CS.nameSelectionAreaSprite.getPosition());
	}
}

void InitNBPlayersSelection(std::string& _path)
{

	nbPlayersSelection.buttonList.push_back(CreateButton(_path + std::to_string(1) + "Player.png", PosToScreenY(411), true, ScaleToScreen(1.f, 1.f)));
	nbPlayersSelection.buttonList.push_back(CreateButton(_path + std::to_string(2) + "Player.png", PosToScreenY(518), true, ScaleToScreen(1.f, 1.f)));
	nbPlayersSelection.buttonList.push_back(CreateButton(_path + std::to_string(3) + "Player.png", PosToScreenY(625), true, ScaleToScreen(1.f, 1.f)));
	nbPlayersSelection.buttonList.push_back(CreateButton(_path + std::to_string(4) + "Player.png", PosToScreenY(732), true, ScaleToScreen(1.f, 1.f)));

	nbPlayersSelection.goingToCS = false;
	nbPlayersSelection.isOnCS = false;
	nbPlayersSelection.nbAI = 0;
	nbPlayersSelection.camera.setSize(sf::Vector2f(GetScreen().width, GetScreen().height));
	nbPlayersSelection.camera.setCenter(GetScreen().width / 2.f, GetScreen().height / 2.f);

	CreateText(nbPlayersSelection.text, GetSettingsFont(), "Choisissez le nombre de joueurs", 65, sf::Color::White, true);

	nbPlayersSelection.text.setPosition(GetScreen().width/2.f, PosToScreenY(100));

	for (auto it = nbPlayersSelection.buttonList.begin(); it < nbPlayersSelection.buttonList.end(); it++)
	{
		CreateAnimationLeftToRight(it->animation[0], 3, 1, it->sprite.getTexture()->getSize());
	}
}

void FadeCharacterSelection(GameData& _gameData, float _maxVolume, float _speedPerSec)
{

	if (CS.fade.isFadingIn)
	{
		CS.fade.timer = CS.fade.timer - _gameData.dt * _speedPerSec;

		CS.fade.alpha = fmaxf((CS.fade.timer / CS.fade.timerMax) * CS.fade.alphaMax, CS.fade.alphaMin);
		SetMusicVolume(CS.music, fminf(((CS.fade.timerMax - CS.fade.timer) / CS.fade.timerMax) * (_maxVolume * GetSoundMultiplier()), _maxVolume * GetSoundMultiplier()));

		CS.fade.color = sf::Color(0, 0, 0, (sf::Uint8)CS.fade.alpha);
		CS.fade.rect.setFillColor(CS.fade.color);

		if (CS.fade.timer <= CS.fade.timerMin)
		{
			CS.fade.isFadingIn = false;
		}
	}

	if (CS.fade.isFadingOut)
	{
		CS.fade.timer = CS.fade.timer + _gameData.dt * _speedPerSec;

		CS.fade.alpha = fminf((CS.fade.timer / CS.fade.timerMax) * CS.fade.alphaMax, CS.fade.alphaMax);
		SetMusicVolume(CS.music, fmaxf(((CS.fade.timerMax - CS.fade.timer) / CS.fade.timerMax) * (_maxVolume * GetSoundMultiplier()), 0.f));

		CS.fade.color = sf::Color(0, 0, 0, (sf::Uint8)CS.fade.alpha);
		CS.fade.rect.setFillColor(CS.fade.color);

		if (CS.fade.timer >= CS.fade.timerMax)
		{
			_gameData.window.setView(_gameData.window.getDefaultView());
			CS.fade.isFadingOut = false;
			_gameData.gameState = GAME;
			StopMusic(CS.music);

			for (unsigned char i = 0; i < NB_PLAYERS; i++)
			{
				SetPlayerName(i, GetPlayerName(GetPlayerCharacterChosen(i)));

			}
			SetCaricatureHudPlayer();
			SetHUDPlayerPseudo();
			SetHUDPlayerIcon();
		}
	}
}

void UpdateButtonsCS(float& _dt)
{
	if (GetCharacterSelectedBool(CS.playerChoosing))
	{
		CS.buttonList[READY].isSelected = true;
	}
	else
	{
		CS.buttonList[READY].isSelected = false;
	}

	if (CS.currentButton == READY)
	{
		UpdateAnimationIsEntitySelected(CS.buttonList[READY].animation[0], CS.buttonList[READY].isSelected, CS.buttonList[READY].sprite);
	}
	else
	{
		UpdateAnimationButton(CS.buttonList[PLAY_CS].animation[0], CS.buttonList[PLAY_CS].sprite, CS.buttonList[PLAY_CS].isSelected, CS.buttonList[PLAY_CS].isPressed, _dt);
	}
}

void UpdateNBPlayersSelection(float& _dt)
{
	for (auto it = nbPlayersSelection.buttonList.begin(); it < nbPlayersSelection.buttonList.end(); it++)
	{
		UpdateAnimationButton(it->animation[0], it->sprite, it->isSelected, it->isPressed, _dt);
	}

	if (nbPlayersSelection.goingToCS)
	{
		nbPlayersSelection.camera.move(sf::Vector2f(PosToScreenX(1900.f) * _dt, 0.f));

		if (nbPlayersSelection.camera.getCenter().x >= GetScreen().width * 1.5f)
		{
			nbPlayersSelection.goingToCS = false;
			nbPlayersSelection.isOnCS = true;
		}
	}

	UpdateNBPlayersSelectionButtons();
}

void UpdateNBPlayersSelectionButtons(void)
{
	for (unsigned char i = 0; i < nbPlayersSelection.buttonList.size(); i++)
	{
		if (nbPlayersSelection.buttonSelected == i)
		{
			nbPlayersSelection.buttonList[i].isSelected = true;
		}
		else
		{
			nbPlayersSelection.buttonList[i].isSelected = false;
		}
	}
}


void DisplayAvatars(sf::RenderWindow& _window)
{
	for (unsigned char i = 0; i < NB_CHARACTERS; i++)
	{
		if (CS.selector[i].isSelected)
		{
			_window.draw(CS.selector[i].sprite);
		}
		_window.draw(CS.nameRect[i]);
		_window.draw(CS.avatarSprite[i]);
	}
}

void DisplayNames(sf::RenderWindow& _window)
{
	for (int i = 0; i < NB_CHARACTERS; i++)
	{
		if (CS.names[i].enteringName)
		{
			CS.names[i].text.setCharacterSize(33);
			CS.names[i].text.setPosition(CS.nameSelectionAreaSprite.getPosition().x, CS.nameSelectionAreaSprite.getPosition().y - CS.nameSelectionAreaSprite.getGlobalBounds().height / 3.f);
			CS.names[i].text.setOrigin(CS.names[i].text.getGlobalBounds().width / 2.f, 0);
			_window.draw(CS.names[i].text);
		}
		CS.names[i].text.setCharacterSize(25);
		CS.names[i].text.setPosition(CS.nameRect[i].getPosition().x, CS.nameRect[i].getPosition().y + CS.nameRect[i].getGlobalBounds().height / 2.f - PosToScreenY(55));
		CS.names[i].text.setOrigin(CS.names[i].text.getGlobalBounds().width / 2.f, 0);
		_window.draw(CS.names[i].text);
	}
}

void DisplayPlayerReadyTexts(sf::RenderWindow& _window)
{
	for (unsigned char i = 0; i < NB_CHARACTERS; i++)
	{
		if (GetPlayerReady(i) && nbPlayersSelection.isOnCS)
		{
			_window.draw(CS.playerReadyText[GetPlayerCharacterChosen(i)]);
			_window.draw(CS.readyText[GetPlayerCharacterChosen(i)]);
		}
	}
}

void DisplayNBPlayersSelection(sf::RenderWindow& _window)
{
	_window.draw(nbPlayersSelection.text);

	for (auto it = nbPlayersSelection.buttonList.begin(); it < nbPlayersSelection.buttonList.end(); it++)
	{
		if (!nbPlayersSelection.isOnCS)
		{
			_window.draw(it->sprite);
		}
	}
}

void KeyPressedNBPlayersSelection(GameData& _gameData)
{

	if (_gameData.event.type == sf::Event::KeyPressed && !CS.fade.isFadingIn && !CS.fade.isFadingOut)
	{
		switch (_gameData.event.key.code)
		{

		case sf::Keyboard::Down:

			if (nbPlayersSelection.buttonSelected != THREE_AI)
			{
				++nbPlayersSelection.buttonSelected;
			}
			else
			{
				nbPlayersSelection.buttonSelected = NO_AI;
			}

			nbPlayersSelection.buttonList[nbPlayersSelection.buttonSelected].isSelected = true;

			break;

		case sf::Keyboard::Up:



			if (nbPlayersSelection.buttonSelected != NO_AI)
			{
				--nbPlayersSelection.buttonSelected;
			}
			else
			{
				nbPlayersSelection.buttonSelected = THREE_AI;
			}

			nbPlayersSelection.buttonList[nbPlayersSelection.buttonSelected].isSelected = true;


			break;

		case sf::Keyboard::Enter:

			for (unsigned char i = 0; i < nbPlayersSelection.buttonList.size(); i++)
			{
				if (nbPlayersSelection.buttonList[i].isSelected && !CS.fade.isFadingIn && !CS.fade.isFadingOut && !nbPlayersSelection.goingToCS && !nbPlayersSelection.isOnCS)
				{
					nbPlayersSelection.buttonList[i].isPressed = true;
					nbPlayersSelection.goingToCS = true;

					nbPlayersSelection.nbAI = fabsf((i + 1) - NB_PLAYERS);
				}
			}

			break;

		default:
			break;
		}
	}
}



void CheckMouseButtonCollisionCharacterSelection(sf::Event::MouseMoveEvent& _buttonEvt)
{
	sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition();
	mouse = { mouse.x + nbPlayersSelection.camera.getCenter().x - GetScreen().width / 2.f,mouse.y + nbPlayersSelection.camera.getCenter().y - GetScreen().height / 2.f };

	if (CS.currentButton == PLAY_CS)
	{
		if (RectContains(CS.buttonList[CS.currentButton].sprite.getGlobalBounds(), mouse) && !CS.buttonList[CS.currentButton].isSelected && !CS.fade.isFadingOut)
		{
			PlaySoundFromList(GetButtonSelectSound(), 5);
		}
		if (RectContains(CS.buttonList[CS.currentButton].sprite.getGlobalBounds(), mouse))
		{
			CS.buttonList[CS.currentButton].isSelected = true;
		}
		else
		{
			CS.buttonList[CS.currentButton].isSelected = false;
		}
	}
}

void CheckMouseButtonCollisionNBPlayersSelection(sf::Event::MouseMoveEvent& _buttonEvt)
{
	sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition();
	mouse = { mouse.x + nbPlayersSelection.camera.getCenter().x - GetScreen().width / 2.f,mouse.y + nbPlayersSelection.camera.getCenter().y - GetScreen().height / 2.f };

	for (unsigned char i = 0; i < nbPlayersSelection.buttonList.size(); i++)
	{
		if (RectContains(nbPlayersSelection.buttonList[i].sprite.getGlobalBounds(), mouse) && !nbPlayersSelection.isOnCS && !nbPlayersSelection.buttonList[i].isSelected && !CS.fade.isFadingIn)
		{
			PlaySoundFromList(GetButtonSelectSound(), 5);
		}
		if (RectContains(nbPlayersSelection.buttonList[i].sprite.getGlobalBounds(), mouse) && !nbPlayersSelection.isOnCS)
		{

			for (unsigned char j = 0; j < nbPlayersSelection.buttonList.size(); j++)
			{

				nbPlayersSelection.buttonList[j].isSelected = false;

			}
			nbPlayersSelection.buttonList[i].isSelected = true;
			nbPlayersSelection.buttonSelected = i;
		}
	}
}

void SetCharacterSelectedByPlayer(unsigned char& _i)
{
	for (unsigned char k = 0; k < NB_CHARACTERS; k++)
	{
		CS.selector[k].isSelected = false;
		CS.names[k].enteringName = false;
		SetPlayerCharacterSelected(k, false);
	}
	SetPlayerCharacterSelected(CS.playerChoosing, true);
	SetPlayerCharacterChosen(CS.playerChoosing, _i);

	CS.playerSelectionText.setPosition(CS.selector[GetPlayerCharacterChosen(CS.playerChoosing)].sprite.getPosition().x, CS.selector[CS.playerChoosing].sprite.getPosition().y - PosToScreenY(235));
	CS.selector[_i].isSelected = true;
	CS.names[_i].enteringName = true;
	CS.nameModifIsSelected = true;
	PlaySoundRepeated(characterSelectionSound.characterSelected, 50.f);
}

void CollisionMouseButtonCS(sf::Vector2f& _mouse)
{
	if (GetCharacterSelectedBool(CS.playerChoosing) && CS.buttonList[CS.currentButton].isSelected && RectContains(CS.buttonList[CS.currentButton].sprite.getGlobalBounds(), _mouse))
	{
		SetCharacterLockedAndUpdateCurrentPlayer();
		PlaySoundRepeated(characterSelectionSound.characterSelected, 50.f);
	}
	else if (CS.currentButton == PLAY_CS && CS.buttonList[CS.currentButton].isSelected && RectContains(CS.buttonList[CS.currentButton].sprite.getGlobalBounds(), _mouse))
	{
		CS.buttonList[PLAY_CS].isPressed = true;
		CS.fade.isFadingIn = false;
		CS.fade.isFadingOut = true;
		PlaySoundFromList(GetButtonPressSound(), 50);
	}
}

void CollisionMouseButtonNBPlayersSelection(sf::Vector2f& _mouse)
{
	for (unsigned char i = 0; i < nbPlayersSelection.buttonList.size(); i++)
	{
		if (nbPlayersSelection.buttonList[i].isSelected && RectContains(nbPlayersSelection.buttonList[i].sprite.getGlobalBounds(), _mouse))
		{
			nbPlayersSelection.buttonList[i].isPressed = true;
			nbPlayersSelection.goingToCS = true;

			nbPlayersSelection.nbAI = fabsf((i + 1) - NB_PLAYERS);

			PlaySoundFromList(GetButtonPressSound(), 50);
		}
	}

}

void ResetCharacterSelectionOnClick(sf::Vector2f& _mouse)
{
	for (unsigned char i = 0; i < NB_CHARACTERS; i++)
	{
		if (!RectContains(CS.avatarSprite[i].getGlobalBounds(), _mouse))
		{
			SetPlayerCharacterSelected(CS.playerChoosing, false);
			CS.selector[i].isSelected = false;
			CS.names[i].enteringName = false;
			CS.nameModifIsSelected = false;
			CS.nameSelectionAreaSprite.setTexture(CS.nameSelectionAreaTexture);

		}
	}
}

void ConfirmCharacterSelection(sf::Vector2f& _mouse)
{
	for (unsigned char i = 0; i < NB_CHARACTERS; i++)
	{
		if (RectContains(CS.nameRect[i].getGlobalBounds(), _mouse))
		{

			switch (CS.playerChoosing)
			{
			case 0:
				SetCharacterSelectedByPlayer(i);
				break;
			case 1:
				if (GetPlayerCharacterChosen(PLAYER_1) != i)
				{
					SetCharacterSelectedByPlayer(i);
				}
				break;
			case 2:
				if (GetPlayerCharacterChosen(PLAYER_1) != i && GetPlayerCharacterChosen(PLAYER_2) != i)
				{
					SetCharacterSelectedByPlayer(i);
				}
				break;
			case 3:
				if (GetPlayerCharacterChosen(PLAYER_1) != i && GetPlayerCharacterChosen(PLAYER_2) != i && GetPlayerCharacterChosen(PLAYER_3) != i)
				{
					SetCharacterSelectedByPlayer(i);
				}
				break;
			}
		}
	}
}


void EraseLetterModifiedName(GameData& _gameData)
{
	for (unsigned char i = 0; i < NB_CHARACTERS; i++)
	{
		if (_gameData.event.key.code == sf::Keyboard::BackSpace && CS.names[i].string.size() >= 1 && CS.names[i].enteringName)
		{
			CS.names[i].string.erase(CS.names[i].string.size() - 1);
			CS.names[i].text.setString((sf::String)CS.names[i].string);
			CS.names[i].text.setOrigin(CS.names[i].text.getGlobalBounds().width / 2.f, 0);
		}

	}
}

void WriteToModifyName(GameData& _gameData)
{
	for (unsigned char i = 0; i < NB_CHARACTERS; i++)
	{
		if (CS.names[i].enteringName && CS.names[i].string.size() <= NAME_LIMIT && _gameData.event.text.unicode != 8) // 8 correspond à la touche backspace
		{
			CS.names[i].string += ConvertKeyToString(_gameData.event.text);
			CS.names[i].text.setString((sf::String)CS.names[i].string);
			CS.names[i].text.setOrigin(CS.names[i].text.getGlobalBounds().width / 2.f, 0);
		}
	}
}

void ChangeGameStateKeyPressed(GameData& _gameData)
{
	for (unsigned char i = 0; i < NB_BUTTONS_CS; i++)
	{
		if (_gameData.event.key.code == sf::Keyboard::Enter && CS.currentButton == PLAY_CS && GetAllPlayersReady())
		{
			CS.fade.isFadingIn = false;
			CS.fade.isFadingOut = true;
			PlaySoundFromList(GetButtonPressSound(), 50);
		}
		if (_gameData.event.key.code == sf::Keyboard::Escape)
		{
			_gameData.window.setView(_gameData.window.getDefaultView());
			SetAlphaMenu(255.f);
			SetFadeMenuOn();
			_gameData.gameState = MENU;
			StopMusic(CS.music);
		}
	}
}

void EnterToValidateNameOrCharacter(GameData& _gameData)
{

	if (_gameData.event.key.code == sf::Keyboard::Enter)
	{
		if (!CS.names[GetPlayerCharacterChosen(CS.playerChoosing)].enteringName && GetCharacterSelectedBool(CS.playerChoosing))
		{
			SetPlayerCharacterSelected(CS.playerChoosing, false);
			CS.selector[GetPlayerCharacterChosen(CS.playerChoosing)].isSelected = false;
			SetCharacterLockedAndUpdateCurrentPlayer();

		}
		else if (CS.names[GetPlayerCharacterChosen(CS.playerChoosing)].enteringName && GetCharacterSelectedBool(CS.playerChoosing))
		{
			CS.names[GetPlayerCharacterChosen(CS.playerChoosing)].enteringName = false;
			CS.nameModifIsSelected = false;
			CS.nameSelectionAreaSprite.setTexture(CS.nameSelectionAreaTexture);

		}
	}


}

void SetCharacterLockedAndUpdateCurrentPlayer(void)
{
	SetPlayerReady(CS.playerChoosing, true);

	unsigned char j = GetPlayerCharacterChosen(CS.playerChoosing);
	CS.avatarSprite[j].setColor(sf::Color{ 125, 125, 125, 255 });

	if (GetAllPlayersReady() && !CS.buttonList[CS.currentButton].isPressed)
	{
		SetPlayerName(CS.playerChoosing, CS.names[CS.playerChoosing].string);

		if (nbPlayersSelection.nbAI == 0)
		{
			CS.playerReadyText[j].setString("J" + ToString(4));
			CS.readyText[j].setString("PRET");

		}
		else
		{
			CS.playerReadyText[j].setString("IA " + ToString(CS.AIChoosing));
			CS.readyText[j].setString("PRETE");
		}
		CS.playerReadyText[j].setFillColor(GetPlayerColor(PLAYER_4));
		CS.readyText[j].setFillColor(GetPlayerColor(PLAYER_4));

		CS.currentButton = PLAY_CS;
	}
	else
	{

		SetPlayerName(CS.playerChoosing, CS.names[CS.playerChoosing].string);
		CS.playerChoosing++;

		if (CS.playerChoosing <= NB_PLAYERS - (nbPlayersSelection.nbAI + 1))
		{
			CS.playerSelectionString = "J" + ToString(CS.playerChoosing + 1);
			CS.playerReadyText[j].setString("J" + ToString(CS.playerChoosing));
			CS.readyText[j].setString("PRET");
		}
		else
		{

			CS.playerSelectionString = "IA " + ToString(CS.AIChoosing + 1);

			if (CS.playerChoosing - 1 <= NB_PLAYERS - (nbPlayersSelection.nbAI + 1))
			{
				CS.playerReadyText[j].setString("J" + ToString(CS.playerChoosing));
				CS.readyText[j].setString("PRET");
			}
			else
			{
				CS.playerReadyText[j].setString("IA " + ToString(CS.AIChoosing));
				CS.readyText[j].setString("PRETE");
			}

			CS.AIChoosing++;
			SetPlayerIsAnAI(CS.playerChoosing, true);
		}

		CS.playerSelectionText.setString(CS.playerSelectionString);
		CS.playerSelectionText.setFillColor(GetPlayerColor(CS.playerChoosing));

		CS.playerReadyText[j].setFillColor(GetPlayerColor(CS.playerChoosing - 1));
		CS.readyText[j].setFillColor(GetPlayerColor(CS.playerChoosing - 1));

		for (unsigned char k = 0; k < NB_PLAYERS; k++)
		{
			CS.selector[k].sprite.setColor(GetPlayerColor(CS.playerChoosing));
		}
	}

}

void SetAlphaCharacterSelection(float _alpha)
{
	CS.fade.alpha = _alpha;
	CS.fade.color.a = _alpha;
	CS.fade.rect.setFillColor(CS.fade.color);
}


std::string GetPlayerName(unsigned char _i)
{
	return CS.names[_i].string;
}

unsigned char GetNbAI(void)
{
	return nbPlayersSelection.nbAI;
}