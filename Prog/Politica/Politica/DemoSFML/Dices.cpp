#include"Dices.h"

Dices dices[NB_DICES];
Dices motionlessDice;
TextureDices textureDices;

bool waitLaunchDice = false;
float timerLaunchDice = 0.f;

//
// Moving dices
// 

void InitMovingDices()
{
	// Chargement des textures des 6 faces d'un dé.

	for (unsigned char i = 0; i < NB_ANIMS; i++)
	{
		textureDices.dice[i].loadFromFile("Assets/Images/Dices/Dice" + ToString(i + 1) + ".png");
	}

	// Affectation des textures à l'animation dans le désordre pour simuler une animation de dé qui roule.

	dices[0].anim[0].setTexture(textureDices.dice[2]);
	dices[0].anim[1].setTexture(textureDices.dice[1]);
	dices[0].anim[2].setTexture(textureDices.dice[0]);
	dices[0].anim[3].setTexture(textureDices.dice[5]);
	dices[0].anim[4].setTexture(textureDices.dice[3]);
	dices[0].anim[5].setTexture(textureDices.dice[4]);

	dices[1].anim[0].setTexture(textureDices.dice[4]);
	dices[1].anim[1].setTexture(textureDices.dice[2]);
	dices[1].anim[2].setTexture(textureDices.dice[5]);
	dices[1].anim[3].setTexture(textureDices.dice[3]);
	dices[1].anim[4].setTexture(textureDices.dice[0]);
	dices[1].anim[5].setTexture(textureDices.dice[1]);

	dices[2].anim[0].setTexture(textureDices.dice[1]);
	dices[2].anim[1].setTexture(textureDices.dice[4]);
	dices[2].anim[2].setTexture(textureDices.dice[3]);
	dices[2].anim[3].setTexture(textureDices.dice[0]);
	dices[2].anim[4].setTexture(textureDices.dice[5]);
	dices[2].anim[5].setTexture(textureDices.dice[2]);

	dices->launchedDices = 2;

	dices[0].pos = { PosToScreenX(830), PosToScreenY(480) };
	dices[1].pos = { PosToScreenX(970), PosToScreenY(480) };
	dices[2].pos = { PosToScreenX(900), PosToScreenY(620) };

	for (unsigned char i = 0; i < NB_DICES; i++)
	{
		for (unsigned char j = 0; j < NB_ANIMS; j++)
		{
			dices[i].anim[j].setScale(ScaleToScreen(1.f, 1.f));
			dices[i].anim[j].setPosition(dices[i].pos);
		}
	}

	// Timer pour l'animation de dé qui roule.
	dices[0].maxTimerRoll = 1;
	dices[1].maxTimerRoll = 2;
	dices[2].maxTimerRoll = 3;

	dices[0].isDiceHasRolling = false;
	dices[0].diceRollSound = AddSound("Assets/Sounds/DiceRoll.ogg");

	// Le temps que les dés restent afficher à l'écran
	for (int i = 0; i < NB_DICES; i++)
	{
		dices[i].maxTimerAvailable = dices[dices->launchedDices - 1].maxTimerRoll + 1;
		dices[i].sprite.setPosition(dices[i].pos);
		dices[i].size = sf::Vector2f(textureDices.dice->getSize());
	}
}


void ReloadMovingDices(void)
{
	dices->launchedDices = 2;
	for (int i = 0; i < NB_DICES; i++)
	{
		dices[i].isDiceHasRolling = false;
		dices[i].isDiceAvailable = false;
		dices[i].isDiceRolling = false;
		dices[i].maxTimerRoll = i + 1;
	}
}


void LaunchMovingDices(GameData& _gameData)
{
	for (int i = 0; i < dices->launchedDices; i++)
	{
		// Test si on lance le dé
		if (dices[i].isDiceAvailable)
		{
			if (dices->launchedDices != 3)
			{
				dices[i].timerAvailable += _gameData.dt;
			}
			if (dices[i].timerAvailable < dices[i].maxTimerAvailable)
			{
				// Test si l'animation du dé est en cours
				if (dices[i].isDiceRolling)
				{
					dices[i].timerRoll += _gameData.dt;
					if (dices[i].timerRoll < dices[i].maxTimerRoll)
					{
						dices[i].globalTime += _gameData.dt;
						if (dices[i].globalTime >= MAX_TIME)
						{
							dices[i].globalTime = 0.f;
						}
						// Animation du roulement des dés
						if (i == 0)
						{
							PlaySoundFromList(dices[0].diceRollSound, 100);
						}
						dices[i].currentFrame = (int)(NB_ANIMS * dices[i].globalTime / MAX_TIME);
						dices[i].sprite = dices[i].anim[dices[i].currentFrame];
					}
					else
					{
						// Fin de l'animation
						dices[i].isDiceRolling = false;
						dices[i].timerRoll = 0.f;
					}
				}
				else
				{
					// Affectation de la bonne texture correspondant à la valeur aléatoire du dé
					dices[i].sprite.setTexture(textureDices.dice[dices[i].value - 1]);
				}
			}
			else
			{
				// Fin de l'affichage du dé
				if (!GetIsMischievousDiceIsPlaying() && !GetPlayerIsOnMysterytile(GetActivePlayer()) && !GetIsInParliamentaryCouncil() && !GetPlayerIsPutsching(GetActivePlayer()))
				{
					if (GetIsTrickDieIsPlaying() && dices->hasChosen && i == 2)
					{
						SetPlayerNBTilesMoving(GetActivePlayer(), dices->riggedValue);
						SetAICanDrawACard(GetActivePlayer(), false);
						dices->riggedValue = 0;
						SetIsTrickDieIsPlaying(false);
						dices->hasChosen = false;
						SetLaunchedDices(2);
						SetPlayerIsMoving(GetActivePlayer(), true);
					}
					else
					{

						SetPlayerNBTilesMoving(GetActivePlayer(), dices[0].value + dices[1].value);
						SetAICanDrawACard(GetActivePlayer(), false);
						if (dices[0].value == dices[1].value)
						{
							dices->isReplaying = true;
						}
						SetPlayerIsMoving(GetActivePlayer(), true);

					}
				}
				else if (GetPlayerIsOnMysterytile(GetActivePlayer()))
				{
					SetAICanDrawACard(GetActivePlayer(), false);
				}
				dices[i].isDiceAvailable = false;
				dices[i].timerAvailable = 0.f;
			}
		}
	}
}

void RiggedDices(GameData& _gameData)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();

	for (int i = 0; i < NB_DICES; i++)
	{
		if (dices->launchedDices == 3)
		{
			if (RectContains(dices[i].sprite.getGlobalBounds(), sf::Vector2f(mousePos)))
			{
				dices[i].isOvered = true;
			}
			else
			{
				dices[i].isOvered = false;
			}
		}
		else
		{
			dices[i].maxTimerAvailable = dices[dices->launchedDices - 1].maxTimerRoll + 1;
		}

	}
}


void DisplayMovingDices(sf::RenderWindow& _window)
{
	for (int i = 0; i < dices->launchedDices; i++)
	{
		if (dices[i].isDiceAvailable)
		{
			if (dices[i].isOvered)
			{
				dices[i].sprite.setColor(sf::Color(255, 255, 255, 210));
			}
			else if (dices[i].isSelected)
			{
				dices[i].sprite.setColor(sf::Color(255, 255, 255, 150));
			}
			else
			{
				dices[i].sprite.setColor(sf::Color(255, 255, 255, 255));
			}
			if (dices->launchedDices == 1)
			{
				dices[0].sprite.setPosition(PosToScreen({ 900, 480 }));
			}
			else
			{
				dices[0].sprite.setPosition(PosToScreen({ 830, 480 }));
			}
			_window.draw(dices[i].sprite);
		}
	}
}


void MousePressedMovingDices(sf::Event _event)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	if (_event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && RectContains(GetDicesButton().sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && GetNoOneIsMoving() && !GetDiceHasRolling() && !GetActionStackCanBeSelected() && !GetChanceStackCanBeSelected() && GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()))
	{
		GetDicesButton().isPressed = true;
		SetDiceIsRollingTrue();
	}
	for (int i = 0; i < NB_DICES; i++)
	{
		if (dices[i].isOvered && !dices[i].isSelected && dices->nbSelected < 2 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && _event.type == sf::Event::MouseButtonPressed)
		{
			dices[i].isSelected = true;
			dices->nbSelected++;
		}
		else if (dices[i].isOvered && dices[i].isSelected && sf::Mouse::isButtonPressed(sf::Mouse::Left) && _event.type == sf::Event::MouseButtonPressed)
		{
			dices[i].isSelected = false;
			dices->nbSelected--;
		}
	}
}


void KeyPressedMovingDices(sf::Event& _event)
{
	if (_event.type == sf::Event::KeyPressed && _event.key.code == GetKey(KB_DICES) && GetNoOneIsMoving() && !GetDiceHasRolling() && !GetActionStackCanBeSelected() && !GetChanceStackCanBeSelected() && GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()))
	{
		if (GetIsDebateIsPlaying() || GetIsInParliamentaryCouncil())
		{
			SetParliamentaryIsDisappears(true);
		}
		else if (GetPlayerIsOnMysterytile(GetActivePlayer()) && !GetIsInParliamentaryCouncil())
		{
			SetMysteryIsDisappears(true);
		}
		SetDiceIsRollingTrue();
	}
	if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Enter && dices->nbSelected == 2)
	{
		for (int i = 0; i < NB_DICES; i++)
		{
			if (dices[i].isSelected)
			{
				dices->riggedValue += dices[i].value;
				if (dices->riggedValue == dices[i].value * 2)
				{
					dices->isReplaying = true;
				}
				else
				{
					dices->isReplaying = false;
				}
			}
			dices[i].isSelected = false;
			dices->hasChosen = true;
			dices->nbSelected = 0;
			dices[i].timerAvailable = dices[i].maxTimerAvailable;
		}
	}
}


bool GetDiceisAvailable(void)
{
	return dices[0].isDiceAvailable;
}

bool GetDiceHasRolling(void)
{
	return dices[0].isDiceHasRolling;
}

bool GetDiceIsRolling(void)
{
	return dices[0].isDiceRolling;
}

void setDiceHasRolling(bool _value)
{
	dices[0].isDiceHasRolling = _value;
}

void setDiceisAvailable(bool _value)
{
	for (int i = 0; i < dices->launchedDices; i++)
	{
		dices[i].isDiceAvailable = _value;
	}
}

int GetFirstDiceValue(void)
{
	return dices[0].value;
}

int GetSecondDiceValue(void)
{
	return dices[1].value;
}

int GetThirdDiceValue(void)
{
	return dices[2].value;
}

unsigned char GetAnyDiceValue(unsigned char _i)
{
	return dices[_i].value;
}

bool GetLaunchedDices(void)
{
	return dices->launchedDices;
}

void SetDiceIsSelected(unsigned char _i, bool _bool)
{
	dices[_i].isSelected = _bool;
}

bool GetDiceIsSelected(unsigned char _i)
{
	return dices[_i].isSelected;
}

void SetDicesNbSelected(unsigned char _i)
{
	dices->nbSelected = _i;
}

unsigned char GetDicesNbSelected(void)
{
	return dices->nbSelected;
}

void SetLaunchedDices(int _launchedDices)
{
	dices->launchedDices = _launchedDices;
}

void SetDiceIsRollingTrue(void)
{
	// Var for active player
	unsigned char AP = GetActivePlayer();
	if (GetIsInParliamentaryCouncil() || GetIsDebateIsPlaying() || GetPlayerIsOnMysterytile(AP) && !GetPlayerHasTookMisteryAction(AP))
	{
		waitLaunchDice = true;
	}
	else
	{
		for (unsigned char i = 0; i < dices->launchedDices; i++)
		{
			dices[i].isDiceRolling = true;
			dices[i].isDiceAvailable = true;
			rand(); rand(); rand();
			dices[i].value = rand() % NB_ANIMS + 1;
			setDiceHasRolling(true);
		}
	}

}

bool GetPlayerReplaying()
{
	return dices->isReplaying;
}

void SetPlayerReplaying(bool _bool)
{
	dices->isReplaying = _bool;
}

void SetDicesRiggedValue(unsigned char _value)
{
	dices->riggedValue = _value;
}

unsigned char GetRiggedDicesValue(void)
{
	return dices->riggedValue;
}

void ResetRiggedDices(void)
{
	for (unsigned char i = 0; i < NB_DICES; i++)
	{
		dices[i].isSelected = false;
		dices->hasChosen = true;
		dices->nbSelected = 0;
		dices[i].timerAvailable = 610.f;
	}

}

float GetThirdDiceMaxTimerRoll()
{
	return dices[2].maxTimerRoll;
}


//
// Common functions
//

void InitDices()
{
	InitMovingDices();
}

void ReloadDices()
{
	ReloadMovingDices();
}

void UpdateDices(GameData& _gameData)
{
	LaunchMovingDices(_gameData);
	RiggedDices(_gameData);

	if (waitLaunchDice)
	{
		timerLaunchDice += _gameData.dt;
		if (timerLaunchDice > 0.333f)
		{
			waitLaunchDice = false;
			timerLaunchDice = 0.f;

			for (unsigned char i = 0; i < dices->launchedDices; i++)
			{
				dices[i].isDiceRolling = true;
				dices[i].isDiceAvailable = true;
				rand(); rand(); rand();
				dices[i].value = rand() % NB_ANIMS + 1;
				setDiceHasRolling(true);
			}
		}
	}
}

void DisplayDices(sf::RenderWindow& _window)
{
	DisplayMovingDices(_window);
}

void MousePressedDices(sf::Event _event)
{
	MousePressedMovingDices(_event);
}

void KeyPressedDices(sf::Event& _event)
{
	KeyPressedMovingDices(_event);
}