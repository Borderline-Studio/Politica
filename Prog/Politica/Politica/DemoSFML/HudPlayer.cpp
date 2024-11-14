#include "HudPlayer.h"

HudPlayer player[NB_PLAYERS];


sf::Font font;

sf::Sprite margaretTchatcheur;
sf::Sprite jVFranco;
sf::Sprite ronaldRayban;
sf::Sprite vladInput;
sf::Text isOnIntersection;
sf::Text parlemantaryTexts[2];

sf::Sprite mystery;
sf::Sprite parlemantary;

bool parlemantaryIsAppears = 0;
bool parlemantaryIsDisappears = 0;
bool mysteryIsAppears = 0;
bool mysteryIsDisappears = 0;
float timerParlemantary = 0;
float timerMystery = 0;

void InitHudPlayer()
{
	font.loadFromFile("Assets/Fonts/HudFont.ttf");

	margaretTchatcheur = LoadSprite("Assets/Images/Hud/MargaretTchatcheur.png");
	margaretTchatcheur.setScale(ScaleToScreen(0.70f, 0.70f));
	jVFranco = LoadSprite("Assets/Images/Hud/JVFranco.png");
	jVFranco.setScale(ScaleToScreen(0.70f, 0.70f));
	ronaldRayban = LoadSprite("Assets/Images/Hud/RonaldRayban.png");
	ronaldRayban.setScale(ScaleToScreen(0.70f, 0.70f));
	vladInput = LoadSprite("Assets/Images/Hud/VladInput.png");
	vladInput.setScale(ScaleToScreen(0.70f, 0.70f));

	player[0].pos = { GetScreen().width * 0.02604f,GetScreen().height * 0.898148f };
	player[0].sprite = LoadSprite("Assets/Images/Hud/PlayerHud1.png");

	player[1].pos = { GetScreen().width * 0.2239f,GetScreen().height * 0.898148f };
	player[1].sprite = LoadSprite("Assets/Images/Hud/PlayerHud2.png");

	player[2].pos = { GetScreen().width * 0.5923f,GetScreen().height * 0.898148f };
	player[2].sprite = LoadSprite("Assets/Images/Hud/PlayerHud3.png");

	player[3].pos = { GetScreen().width * 0.79166f,GetScreen().height * 0.898148f };
	player[3].sprite = LoadSprite("Assets/Images/Hud/PlayerHud4.png");

	isOnIntersection.setString("Choisis une intersection avec les touches\ndirectionnelles.");
	isOnIntersection.setFont(font);
	isOnIntersection.setPosition(PosToScreen({ 0,175 }));

	mystery = LoadSprite("Assets/Images/Hud/MysteryCard.png", true);
	mystery.setPosition(PosToScreen({ 1920 / 2,1080 / 2 }));

	parlemantary = LoadSprite("Assets/Images/Hud/Card.png", true);
	parlemantary.setPosition(PosToScreen({ 1920 / 2,1080 / 2 }));

	CreateText(parlemantaryTexts[0], GetSettingsFont(), "MARGARET TCHATCHEUR", 50, sf::Color::White);
	CreateText(parlemantaryTexts[1], GetSettingsFont(), "VEUILLEZ LANCER LE DÉ", 40, sf::Color::White);
	parlemantaryTexts[0].setPosition(GetScreen().width / 2, GetScreen().height / 2 - PosToScreenY(130));
	parlemantaryTexts[1].setPosition(GetScreen().width / 2, GetScreen().height / 2 + PosToScreenY(90));

	for (int i = 0; i < NB_PLAYERS; i++)
	{
		//player[i].sprite.setColor(player[i].color);
		player[i].speed = SPEED;
		player[i].down = true;
		player[i].isMoving = false;
		player[i].timer = 0;

		player[i].money.setString(ToString(GetPlayerMoney(i)));
		player[i].money.setPosition({ player[i].pos.x + PosToScreenX(85),player[i].pos.y + PosToScreenY(30) });
		player[i].money.setFont(font);
		player[i].money.setFillColor(sf::Color::White);
		player[i].money.setCharacterSize(20);
		player[i].money.setScale(ScaleToScreen(1.f, 1.f));


		player[i].reputation.setString(ToString(GetPlayersReputation(i)));
		player[i].reputation.setPosition({ player[i].pos.x + PosToScreenX(260),player[i].pos.y + PosToScreenY(28) });
		player[i].reputation.setFont(font);
		player[i].reputation.setFillColor(sf::Color::White);
		player[i].reputation.setCharacterSize(20);
		player[i].reputation.setScale(ScaleToScreen(1.f, 1.f));


		player[i].voters.setString(ToString(GetPlayersVoters(i)));
		player[i].voters.setPosition({ player[i].pos.x + PosToScreenX(85) ,player[i].pos.y + PosToScreenY(70) });
		player[i].voters.setFont(font);
		player[i].voters.setFillColor(sf::Color::White);
		player[i].voters.setCharacterSize(20);
		player[i].voters.setScale(ScaleToScreen(1.f, 1.f));


		player[i].unpaidTax.setString(ToString(GetNbTaxes(i)));
		player[i].unpaidTax.setPosition({ player[i].pos.x + PosToScreenX(260) ,player[i].pos.y + PosToScreenY(70) });
		player[i].unpaidTax.setFont(font);
		player[i].unpaidTax.setFillColor(sf::Color::White);
		player[i].unpaidTax.setCharacterSize(20);
		player[i].unpaidTax.setScale(ScaleToScreen(1.f, 1.f));

		player[i].posCaricature = player[i].pos + PosToScreen({ 8,40 });
		player[i].nameCaricature.setFont(font);
		player[i].nameCaricature.setCharacterSize(20);
		player[i].nameCaricature.setScale(ScaleToScreen(1.f, 1.f));

	}
}

void ReloadHudPlayer(void)
{
	for (int i = 0; i < NB_PLAYERS; i++)
	{
		player[i].down = true;
		player[i].isMoving = false;
	}
}

bool playerMouseIsColling(unsigned char _playerID)
{
	sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition();

	sf::FloatRect rect = { player[_playerID].pos.x,  player[_playerID].pos.y, HITBOX_WIDTH, HITBOX_HEIGHT };
	if (RectContains(rect, mousePos))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool playerIsClicked(unsigned char _playerID)
{
	if (playerMouseIsColling(_playerID))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void isMoving(unsigned char _playerID, GameData& _gameData)
{
	if (player[_playerID].isMoving && player[_playerID].down)
	{

		if (player[_playerID].pos.y <= MAX_HEIGHT)
		{
			player[_playerID].pos.y = MAX_HEIGHT;
			player[_playerID].down = false;
			player[_playerID].isMoving = false;
			player[_playerID].timer = 0;
		}
		else
		{
			//player[_playerID].pos.y -= player[_playerID].speed * _gameData.dt;
			player[_playerID].timer += _gameData.dt;
			player[_playerID].pos = Lerp({ player[_playerID].pos.x,MIN_HEIGHT }, { player[_playerID].pos.x,MAX_HEIGHT }, EaseOutQuart(player[_playerID].timer));
		}
	}
	else if (player[_playerID].isMoving && !player[_playerID].down || _playerID != GetActivePlayer())
	{
		if (player[_playerID].pos.y >= MIN_HEIGHT)
		{
			player[_playerID].pos.y = MIN_HEIGHT;
			player[_playerID].down = true;
			player[_playerID].isMoving = false;
			player[_playerID].timer = 0;
		}
		else
		{
			//player[_playerID].pos.y += player[_playerID].speed * _gameData.dt;
			player[_playerID].timer += _gameData.dt;
			player[_playerID].pos = Lerp({ player[_playerID].pos.x,MAX_HEIGHT }, { player[_playerID].pos.x,MIN_HEIGHT }, EaseOutQuart(player[_playerID].timer));
		}
	}
	player[_playerID].money.setPosition({ player[_playerID].pos.x + PosToScreenX(150) - player[_playerID].money.getGlobalBounds().width / 2,player[_playerID].pos.y + PosToScreenY(35) });
	player[_playerID].reputation.setPosition({ player[_playerID].pos.x + PosToScreenX(280) - player[_playerID].reputation.getGlobalBounds().width / 2 ,player[_playerID].pos.y + PosToScreenY(35) });
	player[_playerID].voters.setPosition({ player[_playerID].pos.x + PosToScreenX(150) - player[_playerID].voters.getGlobalBounds().width / 2 , player[_playerID].pos.y + PosToScreenY(65) });
	player[_playerID].unpaidTax.setPosition({ player[_playerID].pos.x + PosToScreenX(280) - player[_playerID].unpaidTax.getGlobalBounds().width / 2 ,player[_playerID].pos.y + PosToScreenY(65) });
	player[_playerID].posCaricature = player[_playerID].pos + PosToScreen({ 8,40 });
	player[_playerID].nameCaricature.setPosition(player[_playerID].pos + PosToScreen({ 24,5 }));

}

void UpdateTextChangeStat(GameData& _gameData)
{
	for (int i = 0; i < NB_PLAYERS; i++)
	{
		if (!player[i].vectorText.empty())
		{
			for (int j = 0; j < player[i].vectorText.size(); j++)
			{
				if (player[i].vectorText[j].timerChangeStat <= MAX_TIMER)
				{
					player[i].vectorText[j].timerChangeStat += _gameData.dt;

					player[i].vectorText[j].posChangeStat.y -= player[i].vectorText[j].changingStatSpeed * _gameData.dt;
					if (player[i].vectorText[j].posChangeStat.y < player[i].vectorText[j].changeStatMaxHeight - (j * PosToScreenY(20)))
					{
						player[i].vectorText[j].posChangeStat.y = player[i].vectorText[j].changeStatMaxHeight - (j * PosToScreenY(20));
					}
					if (player[i].vectorText[j].typeStat != TAX)
					{
						if (player[i].vectorText[j].changeStatValue >= 0)
						{
							player[i].vectorText[j].changeStat.setFillColor(sf::Color::Yellow);
							player[i].vectorText[j].textChangeStat.setFillColor(sf::Color::Yellow);
						}
						else
						{
							player[i].vectorText[j].changeStat.setFillColor(sf::Color::Red);
							player[i].vectorText[j].textChangeStat.setFillColor(sf::Color::Red);
						}
					}
					else
					{
						if (player[i].vectorText[j].changeStatValue >= 0)
						{
							player[i].vectorText[j].changeStat.setFillColor(sf::Color::Red);
							player[i].vectorText[j].textChangeStat.setFillColor(sf::Color::Red);
						}
						else
						{
							player[i].vectorText[j].changeStat.setFillColor(sf::Color::Yellow);
							player[i].vectorText[j].textChangeStat.setFillColor(sf::Color::Yellow);
						}
					}
					player[i].vectorText[j].changeStat.setPosition(player[i].vectorText[j].posChangeStat.x, player[i].vectorText[j].posChangeStat.y - (j * PosToScreenY(20)));
					player[i].vectorText[j].changeStatRect.setPosition({ player[i].vectorText[j].posChangeStat.x - PosToScreenX(5) - player[i].vectorText[j].textChangeStat.getGlobalBounds().width, player[i].vectorText[j].posChangeStat.y - (j * PosToScreenY(20)) + PosToScreenY(2) });

					player[i].vectorText[j].textChangeStat.setPosition({ player[i].vectorText[j].posChangeStat.x - player[i].vectorText[j].textChangeStat.getGlobalBounds().width, player[i].vectorText[j].posChangeStat.y - (j * PosToScreenY(20)) });
				}
				else
				{
					player[i].vectorText.erase(player[i].vectorText.begin() + j);
				}
			}

		}
	}
}

void UpdateHudPlayer(GameData& _gameData)
{

	for (int i = 0; i < NB_PLAYERS; i++)
	{
		player[i].money.setString(ToString(GetPlayerMoney(i)));
		player[i].reputation.setString(ToString(GetPlayersReputation(i)));
		player[i].voters.setString(ToString(GetPlayersVoters(i)));
		player[i].unpaidTax.setString(ToString(GetNbTaxes(i)));

		if (playerIsClicked(i) && i == GetActivePlayer() && !GetIsACardSelected() && !GetPlayerGoingToFiscalControl(i) && !GetIsInParliamentaryCouncil() && !GetPlayerIsAnAI(GetActivePlayer()))
		{
			player[i].isMoving = true;
		}

		isMoving(i, _gameData);
		UpdateTextChangeStat(_gameData);
	}
	UpdateParlemtaryScale(_gameData.dt);
	UpdateMysteryScale(_gameData.dt);
	//AddParticleHudPlayer(player[GetActivePlayer()].pos);
	//UpdateParticleHudPlayer(_gameData);
}

void UpdateParlemtaryScale(float& _dt)
{
	if (GetIsInParliamentaryCouncil() || GetIsDebateIsPlaying())
	{
		if (GetDicesButton().isPressed)
		{
			parlemantaryIsDisappears = true;
		}

		if (parlemantaryIsAppears)
		{
			timerParlemantary += 3 * _dt;
			if (timerParlemantary < 1)
			{
				parlemantary.setScale(EaseInOutQuart(timerParlemantary), EaseInOutQuart(timerParlemantary));
			}
			else
			{
				parlemantary.setScale(1.f, 1.f);
				parlemantaryIsAppears = false;
				timerParlemantary = 1;
			}
		}
		else if (parlemantaryIsDisappears)
		{

			timerParlemantary -= 3 * _dt;
			if (timerParlemantary > 0)
			{
				parlemantary.setScale(EaseInOutQuart(timerParlemantary), EaseInOutQuart(timerParlemantary));
			}
			else if (timerParlemantary <= 0)
			{
				parlemantary.setScale(0.f, 0.f);
				parlemantaryIsDisappears = false;
				timerParlemantary = 0;
			}
		}
	}
}

void UpdateMysteryScale(float& _dt)
{
	if (GetPlayerIsOnMysterytile(GetActivePlayer())/* && !GetDiceHasRolling() && !GetIsInParliamentaryCouncil()*/)
	{
		if (GetDicesButton().isPressed)
		{
			mysteryIsDisappears = true;
		}

		if (mysteryIsAppears)
		{
			timerMystery += 3 * _dt;
			if (timerMystery < 1)
			{
				mystery.setScale(EaseInOutQuart(timerMystery), EaseInOutQuart(timerMystery));
			}
			else
			{
				mystery.setScale(1.f, 1.f);
				mysteryIsAppears = false;
				timerMystery = 1;
			}
		}
		else if (mysteryIsDisappears)
		{

			timerMystery -= 3 * _dt;
			if (timerMystery > 0)
			{
				mystery.setScale(EaseInOutQuart(timerMystery), EaseInOutQuart(timerMystery));
			}
			else if (timerMystery <= 0)
			{
				mystery.setScale(0.f, 0.f);
				mysteryIsDisappears = false;
				timerMystery = 0;
			}
		}
	}
}

void DisplayHudPlayer(sf::RenderWindow& _window)
{
	//DrawParticleHudPlayer(_window);
	for (int i = 0; i < NB_PLAYERS; i++)
	{

		if (!player[i].vectorText.empty())
		{
			for (int j = 0; j < player[i].vectorText.size(); j++)
			{

				_window.draw(player[i].vectorText[j].changeStatRect);
				_window.draw(player[i].vectorText[j].changeStat);
				_window.draw(player[i].vectorText[j].textChangeStat);
			}
		}

		BlitSprite(player[i].sprite, player[i].pos, _window);
		_window.draw(player[i].money);
		_window.draw(player[i].reputation);
		_window.draw(player[i].voters);
		_window.draw(player[i].unpaidTax);
		BlitSprite(player[i].spriteCaricature, player[i].posCaricature, _window);
		_window.draw(player[i].nameCaricature);
		if (GetPlayerIsOnChoiceIntersection(GetActivePlayer()) && GetPlayerNbTilesMoving(GetActivePlayer()) > 0 && !GetPlayerHasChosenWay(GetActivePlayer()))
		{
			_window.draw(isOnIntersection);
		}
		if (GetPlayerIsOnMysterytile(i))
		{
			_window.draw(mystery);
		}
		if (GetIsInParliamentaryCouncil() || GetIsDebateIsPlaying() || parlemantaryIsAppears || parlemantaryIsDisappears)
		{
			_window.draw(parlemantary);
		}
		if (!parlemantaryIsAppears && !parlemantaryIsDisappears && !GetDiceIsRolling() && !GetDiceHasRolling())
		{
			if (GetIsInParliamentaryCouncil() || GetIsDebateIsPlaying())
			{
				_window.draw(parlemantaryTexts[0]);
				_window.draw(parlemantaryTexts[1]);
			}
		}
	}
}

void SetCaricatureHudPlayer()
{
	for (int i = 0; i < NB_PLAYERS; i++)
	{
		switch (GetPlayerCharacterChosen(i))
		{
		case MARGARET_TCHATCHEUR:
			player[i].spriteCaricature = margaretTchatcheur;
			break;
		case RONALD_RAYBAN:
			player[i].spriteCaricature = ronaldRayban;
			break;
		case JV_FRANCO:
			player[i].spriteCaricature = jVFranco;
			break;
		case VLAD_INPUT:
			player[i].spriteCaricature = vladInput;
			break;
		default:
			break;
		}
		player[i].nameCaricature.setString(GetPlayerPseudo(i));
	}
}

void SetTextStat(unsigned char _playerID, int _changeStat, Stats _stats)
{
	Text temp;
	temp.changeStat.setFont(font);
	temp.changeStat.setCharacterSize(20);
	temp.changingStatSpeed = 80;
	temp.textChangeStat.setFont(font);
	temp.textChangeStat.setCharacterSize(20);
	temp.timerChangeStat = 0;

	switch (_stats)
	{
	case MONEY:
		temp.textChangeStat.setString("A  : ");
		temp.changeStat.setString(ToString(_changeStat));
		temp.posChangeStat = GetPlayerPos(_playerID);
		temp.typeStat = MONEY;
		break;
	case REPUTATION:
		temp.textChangeStat.setString("R : ");
		temp.changeStat.setString(ToString(_changeStat));
		temp.posChangeStat = GetPlayerPos(_playerID);
		temp.typeStat = REPUTATION;
		break;
	case VOTERS:
		temp.textChangeStat.setString("E : ");
		temp.changeStat.setString(ToString(_changeStat));
		temp.posChangeStat = GetPlayerPos(_playerID);
		temp.typeStat = VOTERS;
		break;
	case TAX:
		temp.textChangeStat.setString("T : ");
		temp.changeStat.setString(ToString(_changeStat));
		temp.posChangeStat = GetPlayerPos(_playerID);
		temp.typeStat = TAX;
		break;
	default:
		std::cout << "Set Text Stat is kasser" << std::endl;
		break;
	}
	switch (_playerID)
	{
	case 0:

		temp.posChangeStat.x += -temp.changeStat.getGlobalBounds().width / 2 + PosToScreenX(60);

		break;
	case 1:

		temp.posChangeStat.x += -temp.changeStat.getGlobalBounds().width / 2 + PosToScreenX(35);
		temp.posChangeStat.y += PosToScreenY(14);
		break;
	case 2:

		temp.posChangeStat.x += -temp.changeStat.getGlobalBounds().width / 2 + PosToScreenX(75);
		temp.posChangeStat.y += PosToScreenY(14);
		break;
	case 3:

		temp.posChangeStat.x += -temp.changeStat.getGlobalBounds().width / 2 + PosToScreenX(60);
		temp.posChangeStat.y += PosToScreenY(28);
		break;

	}

	temp.changeStatValue = _changeStat;
	temp.changeStatMaxHeight = temp.posChangeStat.y - PosToScreenY(20);
	temp.changeStatRect.setSize({ temp.changeStat.getGlobalBounds().width + PosToScreenX(10) + temp.textChangeStat.getGlobalBounds().width,PosToScreenY(1.5f) * temp.changeStat.getGlobalBounds().height });
	temp.changeStatRect.setFillColor(sf::Color::Color({ 187, 174, 152 }));
	player[_playerID].vectorText.push_back(temp);
}

bool GetHudPlayerIsMoving()
{
	return player[GetActivePlayer()].isMoving;
}

//Attention peut faire crash
unsigned char GetTargetPlayer()
{

	for (int i = 0; i < NB_PLAYERS; i++)
	{
		if (playerMouseIsColling(i))
		{
			return i;
		}
	}
	return 5;
}

unsigned int GetHudPlayerSpeed()
{
	return SPEED;
}

sf::Vector2f GetHudPlayerOrigin(unsigned char _playerID)
{
	return player[_playerID].pos;
}

bool GetHudPlayerIsDown()
{
	return player[GetActivePlayer()].down;
}

bool GetHudPlayerActivePlayerCollision()
{
	return playerMouseIsColling(GetActivePlayer());
}

bool GetHudPlayerNoneActivePlayerCollision()
{
	for (int i = 0; i < NB_PLAYERS; i++)
	{
		if (i != (GetActivePlayer()))
		{
			if (playerMouseIsColling(i))
			{
				return true;
			}
		}
	}
	return false;
}

bool GetParliamentaryIsDisappears()
{
	return parlemantaryIsDisappears;
}

bool GetMysteryIsDisappears()
{
	return mysteryIsDisappears;
}

void SetHudPlayerIsMoving(unsigned char _playerID, bool _isMoving)
{
	player[_playerID].isMoving = _isMoving;
}

void SetParliamentaryIsAppears(bool _isAppears)
{
	if (timerParlemantary == 0)
	{
		parlemantaryIsAppears = _isAppears;
		parlemantary.setScale(0.f, 0.f);
	}
}

void SetParliamentaryIsDisappears(bool _isDisappears)
{
	parlemantaryIsDisappears = _isDisappears;
}

void SetMysteryIsAppears(bool _isAppears)
{
	if (timerParlemantary == 0)
	{
		mysteryIsAppears = _isAppears;
		mystery.setScale(0.f, 0.f);
	}
}

void SetMysteryIsDisappears(bool _isDisappears)
{
	mysteryIsDisappears = _isDisappears;
}

void SetPseudoInInsert(unsigned char _player)
{
	SetCenteredString(parlemantaryTexts[0], GetPlayerPseudo(_player));
}
