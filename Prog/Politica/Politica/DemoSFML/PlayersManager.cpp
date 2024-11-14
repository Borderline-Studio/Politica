#include"PlayersManager.h"

Player players[NB_PLAYERS];
SpriteSorting spriteSorting[NB_PLAYERS];
Intersection intersectionsPos[NB_INTERSECTIONS];
ChoiceArrow choiceArrow[NB_ARROWS];
TileShining tileShining[NB_TILE_SHINING];
unsigned char lastPlayerPlayed = 0;
unsigned char parliamentaryCouncilSound = 0;
float timerScaleArrow = 0;

void InitPlayersGestion(void)
{
	InitPlayersGestionSprites();
	InitPlayers();
	InitIntersections();
	InitPlayersChoiceArrow();

	for (int i = 0; i < NB_PLAYERS; i++)
	{
		spriteSorting[i].pos = players[i].pos;
		spriteSorting[i].playerIndex = i;
	}
	parliamentaryCouncilSound = AddSound("Assets/Sounds/ParliamentaryCouncil.ogg");
}

void UpdatePlayers(GameData& _gameData)
{
	//std::cout << "Player " << (int)(GetActivePlayer() + 1) << " : " << std::endl;
	//std::cout << std::endl;
	//std::cout << "Current Intersection :" << (int)players[GetActivePlayer()].curIntersection << std::endl;
	//std::cout << "Number tiles moving :" << (int)players[GetActivePlayer()].nbTilesMoving << std::endl;
	//std::cout << "Direction :" << (int)players[GetActivePlayer()].dir << std::endl;
	//std::cout << "IsGoingToFiscalControl : " << (int)players[GetActivePlayer()].goingToFiscalControl << std::endl;
	//std::cout << "IsMoving : " << (int)players[GetActivePlayer()].isMoving << std::endl;
	//std::cout << "Reverse Move : " << players[GetActivePlayer()].reverseMove << std::endl;
	//std::cout << "LastPlayerPlayed : " << (int)(lastPlayerPlayed + 1) << std::endl;
	//std::cout << "choiceInter 1 : " << players[GetActivePlayer()].isOnChoiceInterNB1 << std::endl;
	//std::cout << "choiceInter 2 : " << players[GetActivePlayer()].isOnChoiceInterNB2 << std::endl;
	//std::cout << "on Shortcut 1 : " << players[GetActivePlayer()].isOnShortCut1 << std::endl;
	//std::cout << "on Shortcut 2 : " << players[GetActivePlayer()].isOnShortCut2 << std::endl;
	//std::cout << "goingToStartSquare " << players[GetActivePlayer()].goingToStartSquare << std::endl;
	//std::cout << "HasChosenWay : " << players[GetActivePlayer()].hasChosenWay << std::endl;
	//std::cout << "AI can Draw a card : " << players[GetActivePlayer()].ai.canDrawACard << std::endl;
	//std::cout << "AI has already played a card : " << GetHasAlreadyPlayedCard() << std::endl;
	//std::cout << std::endl;

	//std::cout << "Money : " << players[GetActivePlayer()].money << std::endl;
	//std::cout << "Reputation : " << players[GetActivePlayer()].reputation << std::endl;
	//std::cout << "Voters : " << players[GetActivePlayer()].voters << std::endl;
	//std::cout << "Taxes : " << (int)players[GetActivePlayer()].taxes << std::endl;

	//IA
	PlayTrickDieCard(GetActivePlayer(), _gameData.dt);
	LaunchDicesAI(GetActivePlayer(), _gameData.dt);
	//Normal

	UpdateChoiceArrow(_gameData.dt, GetActivePlayer());

	UpdateIsOnShortCut(GetActivePlayer());
	UpdateChoiceIntersection(GetActivePlayer(), _gameData.dt);
	//AI
	ChooseAnIntersectionAI(GetActivePlayer());
	//
	UpdateReverseMoveShortCut(GetActivePlayer());
	MovePlayers(_gameData, GetActivePlayer());
	UpdatePlayerGoingToFiscalControl(GetActivePlayer());
	UpdatePlayerGoingToStartSquare(GetActivePlayer());
	UpdatePlayerMystery(GetActivePlayer());
	DoubleResestMystery();
	UpdateSpiteSort();
	UpdateParliamentaryCouncil(GetActivePlayer());
	DoubleResestParliamentaryCouncil();

	//IA

	ManageTaxesTileAI(_gameData.dt, GetActivePlayer());
	ManageChanceCardsAI(GetActivePlayer(), _gameData.dt);
	ManageActionCardsAI(GetActivePlayer(), _gameData.dt);
	PlayActionCards(GetActivePlayer(), _gameData.dt);
	ManageBlackMailAI(GetTargetPlayerAI(), _gameData.dt);
	ManageMuzzleAI(GetTargetPlayerAI(), _gameData.dt);
	ManagePutschAI(GetActivePlayer(), _gameData.dt);
	EndTurnAI(GetActivePlayer(), _gameData.dt);
}

void DisplayPlayers(sf::RenderWindow& _window)
{
	DisplayChoiceArrowBeforePlayers(_window, GetActivePlayer());

	for (unsigned char i = 0; i < NB_PLAYERS; i++)
	{
		_window.draw(players[spriteSorting[i].playerIndex].sprite);
	}

	switch (GetActivePlayer())
	{
	case PLAYER_1:
		_window.draw(players[PLAYER_1].spriteArrow);
		break;
	case PLAYER_2:
		_window.draw(players[PLAYER_2].spriteArrow);
		break;
	case PLAYER_3:
		_window.draw(players[PLAYER_3].spriteArrow);
		break;
	case PLAYER_4:
		_window.draw(players[PLAYER_4].spriteArrow);
		break;
	}

	DisplayChoiceArrowAfterPlayers(_window, GetActivePlayer());
}

void MousePressedPlayers(sf::Event& _event, unsigned char& _activePlayer)
{
	if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left && (players[_activePlayer].isOnChoiceInterNB1 || players[_activePlayer].isOnChoiceInterNB2) && !players[_activePlayer].hasChosenWay && players[_activePlayer].nbTilesMoving > 0)
	{
		for (unsigned char i = 0; i < NB_ARROWS; i++)
		{
			if (RectContains(choiceArrow[i].sprite.getGlobalBounds(), (sf::Vector2f)sf::Mouse::getPosition()))
			{
				sf::Vector2f pos = { choiceArrow[i].sprite.getGlobalBounds().left, choiceArrow[i].sprite.getGlobalBounds().top };
				if (SpriteContainsPixelPerfect(choiceArrow[i].image, pos, (sf::Vector2f)sf::Mouse::getPosition()))
				{
					if (players[_activePlayer].isOnChoiceInterNB1 && i == RIGHT_ARR)
					{
						players[_activePlayer].hasChosenWay = true;
						players[_activePlayer].isOnChoiceInterNB1 = false;
						players[_activePlayer].hasChosenShortCut1 = false;
						timerScaleArrow = 0;
						choiceArrow[i].sprite.setScale(0.f, 0.f);
					}
					else if (players[_activePlayer].isOnChoiceInterNB1 && i == DOWN_NB1_ARR)
					{
						players[_activePlayer].curIntersection = 6;
						players[_activePlayer].hasChosenWay = true;
						players[_activePlayer].isOnChoiceInterNB1 = false;
						players[_activePlayer].hasChosenShortCut1 = true;
						UpdateOrientationPlayers(_activePlayer);
						timerScaleArrow = 0;
						choiceArrow[i].sprite.setScale(0.f, 0.f);
					}
					else if (players[_activePlayer].isOnChoiceInterNB2 && i == LEFT_ARR)
					{
						players[_activePlayer].hasChosenWay = true;
						players[_activePlayer].isOnChoiceInterNB2 = false;
						players[_activePlayer].hasChosenShortCut2 = false;
						timerScaleArrow = 0;
						choiceArrow[i].sprite.setScale(0.f, 0.f);
					}
					else if (players[_activePlayer].isOnChoiceInterNB2 && i == DOWN_NB2_ARR)
					{
						players[_activePlayer].curIntersection = 14;
						players[_activePlayer].hasChosenWay = true;
						players[_activePlayer].isOnChoiceInterNB2 = false;
						players[_activePlayer].hasChosenShortCut2 = true;
						UpdateOrientationPlayers(_activePlayer);
						timerScaleArrow = 0;
						choiceArrow[i].sprite.setScale(0.f, 0.f);
					}
				}
			}
		}
	}
}

void KeyPressedPlayers(sf::Event _event)
{
	if (_event.type == sf::Event::KeyPressed)
	{
		ChoosingAWayOnIntersection(_event.key.code, GetActivePlayer());
	}
}


//Init Functions

void InitPlayersGestionSprites(void)
{
	for (unsigned char i = 0; i < NB_PLAYERS; i++)
	{
		players[i].sprite = LoadSprite("Assets/Images/Players/Player" + ToString(i + 1) + ".png");
		players[i].spriteArrow = LoadSprite("Assets/Images/Players/ArrowP" + ToString(i + 1) + ".png");
	}
	players[0].spriteOffset = { PosToScreenX(0), PosToScreenY(-5) };
	players[1].spriteOffset = { PosToScreenX(-5), PosToScreenY(0) };
	players[2].spriteOffset = { PosToScreenX(5), PosToScreenY(0) };
	players[3].spriteOffset = { PosToScreenX(0), PosToScreenY(5) };
}

void InitPlayers(void)
{
	for (unsigned char i = 0; i < NB_PLAYERS; i++)
	{
		players[i].dir = RIGHT;
		players[i].name = GetPlayerName(players[i].characterChosen);

		players[i].pos = GetCell(2, 13, 1);
		players[i].initialPos = GetCell(2, 13, 1);
		players[i].sprite.setPosition(players[i].pos);
		players[i].spriteArrow.setPosition(players[i].pos);

		players[i].money = 50000;
		players[i].reputation = 0;
		players[i].voters = 1000;
		players[i].taxes = 0;
		players[i].hasChooseToPaidTaxesOrNot = true;

		players[i].timer = 0.f;
		players[i].nextPosGrid = sf::Vector2f(2, 13);
		players[i].InitialposGrid = sf::Vector2f(2, 13);
		players[i].curIntersection = 1;
		players[i].isMoving = false;
		players[i].intersectionReached = false;
		players[i].hasAlreadyMoved = false;

		players[i].hasChosenWay = false;
		players[i].isOnChoiceInterNB1 = false;
		players[i].isOnChoiceInterNB2 = false;
		players[i].hasChosenShortCut1 = false;
		players[i].hasChosenShortCut2 = false;
		players[i].isOnShortCut1 = false;
		players[i].isOnShortCut2 = false;

		players[i].goingToFiscalControl = false;
		players[i].goingToStartSquare = false;
		players[i].reverseMove = false;

		players[i].isReady = false;
		players[i].characterSelected = false;
		players[i].characterChosen = 0;
		players[i].hasFinishedTurn = false;

		players[i].dicesValue = 0;
		players[i].isInParliamentaryCouncil = false;
		players[i].hasTookMysteryAction = true;
		players[i].isOnTaxe = false;
		players[i].isOnMysteryTile = false;

		players[i].isAnAI = false;
		players[i].ai.timerDelay = 0.f;
		players[i].ai.canDrawACard = false;
		players[i].ai.isPutsching = false;
		players[i].ai.mysteryActionPlaying = false;
	}
}

void ReloadPlayersNewGame(void)
{
	for (unsigned char i = 0; i < NB_PLAYERS; i++)
	{
		players[i].dir = RIGHT;

		players[i].pos = GetCell(2, 13, 1);
		players[i].initialPos = GetCell(2, 13, 1);
		players[i].sprite.setPosition(players[i].pos);
		players[i].spriteArrow.setPosition(players[i].pos);

		players[i].money = 50000;
		players[i].reputation = 0;
		players[i].voters = 1000;
		players[i].taxes = 0;
		players[i].hasChooseToPaidTaxesOrNot = true;

		players[i].timer = 0.f;
		players[i].nextPosGrid = sf::Vector2f(2, 13);
		players[i].InitialposGrid = sf::Vector2f(2, 13);
		players[i].curIntersection = 1;
		players[i].isMoving = false;
		players[i].intersectionReached = false;
		players[i].hasAlreadyMoved = false;

		players[i].hasChosenWay = false;
		players[i].isOnChoiceInterNB1 = false;
		players[i].isOnChoiceInterNB2 = false;
		players[i].hasChosenShortCut1 = false;
		players[i].hasChosenShortCut2 = false;
		players[i].isOnShortCut1 = false;
		players[i].isOnShortCut2 = false;

		players[i].goingToFiscalControl = false;
		players[i].goingToStartSquare = false;
		players[i].reverseMove = false;
		players[i].isInParliamentaryCouncil = false;
		players[i].hasTookMysteryAction = true;
		players[i].isOnTaxe = false;
		players[i].isOnMysteryTile = false;


		players[i].hasFinishedTurn = false;

		players[i].dicesValue = 0;

		players[i].ai.timerDelay = 0.f;

		spriteSorting[i].pos = players[i].pos;
		spriteSorting[i].playerIndex = i;
		players[i].ai.canDrawACard = false;
		players[i].ai.isPutsching = false;
		players[i].ai.mysteryActionPlaying = false;
	}
}

void InitIntersections(void)
{
	intersectionsPos[0].posGrid = sf::Vector2f(2, 13);
	intersectionsPos[1].posGrid = sf::Vector2f(2, 4);
	intersectionsPos[2].posGrid = sf::Vector2f(2, 2);
	intersectionsPos[3].posGrid = sf::Vector2f(6, 2);
	intersectionsPos[4].posGrid = sf::Vector2f(6, 1);
	intersectionsPos[5].posGrid = sf::Vector2f(12, 1);
	intersectionsPos[6].posGrid = sf::Vector2f(12, 4);
	intersectionsPos[7].posGrid = sf::Vector2f(12, 6);
	intersectionsPos[8].posGrid = sf::Vector2f(9, 6);
	intersectionsPos[9].posGrid = sf::Vector2f(4, 6);
	intersectionsPos[10].posGrid = sf::Vector2f(4, 8);
	intersectionsPos[11].posGrid = sf::Vector2f(4, 11);
	intersectionsPos[12].posGrid = sf::Vector2f(12, 11);
	intersectionsPos[13].posGrid = sf::Vector2f(12, 8);
	intersectionsPos[14].posGrid = sf::Vector2f(14, 8);
	intersectionsPos[15].posGrid = sf::Vector2f(14, 13);
	intersectionsPos[16].posGrid = sf::Vector2f(13, 13);
	intersectionsPos[17].posGrid = sf::Vector2f(13, 15);
	intersectionsPos[18].posGrid = sf::Vector2f(8, 15);
	intersectionsPos[19].posGrid = sf::Vector2f(8, 13);
	intersectionsPos[20].posGrid = sf::Vector2f(4, 13);

	for (unsigned char i = 0; i < NB_INTERSECTIONS; i++)
	{
		intersectionsPos[i].pos = GetCell((int)intersectionsPos[i].posGrid.x, (int)intersectionsPos[i].posGrid.y, 1);
	}
}

void InitPlayersChoiceArrow(void)
{
	for (unsigned char i = 0; i < NB_ARROWS; i++)
	{
		if (i == 0 || i == 1)
		{
			choiceArrow[i].sprite = LoadSprite("Assets/Images/Players/ChoiceArrow1.png", true);
			choiceArrow[i].image = choiceArrow[i].sprite.getTexture()->copyToImage();
		}
		else
		{
			choiceArrow[i].sprite = LoadSprite("Assets/Images/Players/ChoiceArrow" + ToString(i) + ".png", true);
			choiceArrow[i].image = choiceArrow[i].sprite.getTexture()->copyToImage();
		}

		choiceArrow[i].sprite.setOrigin(choiceArrow[i].sprite.getTexture()->getSize().x / 2.f, choiceArrow[i].sprite.getTexture()->getSize().y * 3.f / 4.f);
		choiceArrow[i].sprite.setScale(0.f, 0.f);
	}

	sf::Texture tempTexture;
	sf::Vector2u sizeAnime;

	tempTexture.loadFromFile("Assets/Images/Players/ArrowInter.png");
	sizeAnime = tempTexture.getSize();
	tileShining[0].sprite = LoadSprite("Assets/Images/Players/ArrowInter.png", false);
	tileShining[1].sprite = LoadSprite("Assets/Images/Players/ArrowInter.png", false);
	CreateAnimationLeftToRight(tileShining[0].anim, 9, 1, sizeAnime);
	CreateAnimationLeftToRight(tileShining[1].anim, 9, 1, sizeAnime);

	choiceArrow[DOWN_NB1_ARR].posGrid = sf::Vector2f(3, 4);

	choiceArrow[DOWN_NB2_ARR].posGrid = sf::Vector2f(5, 8);

	choiceArrow[LEFT_ARR].posGrid = sf::Vector2f(4, 9);

	choiceArrow[RIGHT_ARR].posGrid = sf::Vector2f(2, 3);
}


//Update Functions
void MovePlayers(GameData& _gameData, unsigned char& _activePlayer)
{
	if (!players[_activePlayer].isOnChoiceInterNB1 && !players[_activePlayer].isOnChoiceInterNB2 && !GetIsDebateIsPlaying() && !GetIsMischievousDiceIsPlaying() && !players[_activePlayer].isOnMysteryTile && !GetIsTrickDieIsPlaying() && !players[_activePlayer].isInParliamentaryCouncil)
	{
		if (players[_activePlayer].timer >= 1.f)
		{
			UpdateNextMovePlayer(_activePlayer);
		}
		else
		{
			UpdatePlayerMovesAccordingToDir(_activePlayer);
			UpdatePlayerMoveCerp(_gameData.dt, _activePlayer);
		}
	}
}



void UpdateChoiceIntersection(unsigned char& _activePlayer, float& _dt)
{
	if (players[_activePlayer].InitialposGrid == intersectionsPos[1].posGrid && !players[_activePlayer].hasChosenWay)
	{
		players[_activePlayer].isOnChoiceInterNB1 = true;
	}
	else if (players[_activePlayer].InitialposGrid == intersectionsPos[10].posGrid && !players[_activePlayer].hasChosenWay)
	{
		players[_activePlayer].isOnChoiceInterNB2 = true;
	}

	UpdateAnimationLeftToRight(tileShining[0].anim, tileShining[0].sprite, 12, 0, true, true, _dt);
	UpdateAnimationLeftToRight(tileShining[1].anim, tileShining[1].sprite, 12, 0, true, true, _dt);
}



void UpdateOrientationPlayers(unsigned char& _activePlayer)
{


	if (players[_activePlayer].curIntersection > 19 && !players[_activePlayer].reverseMove && !players[_activePlayer].goingToFiscalControl)
	{
		players[_activePlayer].curIntersection = 0;

	}
	else if (players[_activePlayer].curIntersection > 20 && !players[_activePlayer].reverseMove)
	{
		players[_activePlayer].curIntersection = 0;
	}

	switch (players[_activePlayer].curIntersection)
	{
	case 0:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = LEFT;
		}
		else
		{
			players[_activePlayer].dir = UP;
		}
		break;
	case 1:
		if (players[_activePlayer].reverseMove && !players[_activePlayer].hasChosenShortCut1)
		{
			players[_activePlayer].hasChosenWay = true;
			players[_activePlayer].dir = LEFT;
		}
		else if (players[_activePlayer].reverseMove && players[_activePlayer].hasChosenShortCut1)
		{
			players[_activePlayer].hasChosenWay = true;
			players[_activePlayer].dir = UP;
		}
		//else if (!players[_activePlayer].reverseMove && players[_activePlayer].hasChosenShortCut1)
		//{
		//	players[_activePlayer].dir = DOWN;
		//}
		else if (!players[_activePlayer].reverseMove) /*&& !players[_activePlayer].hasChosenShortCut1)*/
		{
			players[_activePlayer].dir = RIGHT;
		}
		break;
	case 2:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = UP;
		}
		else
		{
			players[_activePlayer].dir = RIGHT;
		}
		break;
	case 3:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = LEFT;
		}
		else
		{
			players[_activePlayer].dir = DOWN;
		}
		break;
	case 4:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = UP;
		}
		else
		{
			players[_activePlayer].dir = RIGHT;
		}
		break;
	case 5:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = RIGHT;
		}
		else
		{
			players[_activePlayer].dir = DOWN;
		}
		break;
	case 6:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = RIGHT;
		}
		else if (!players[_activePlayer].reverseMove && players[_activePlayer].hasChosenShortCut1)
		{
			players[_activePlayer].dir = DOWN;
		}
		else if (!players[_activePlayer].reverseMove && !players[_activePlayer].hasChosenShortCut1)
		{
			players[_activePlayer].dir = LEFT;
		}
		break;
	case 7:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = DOWN;
		}
		else
		{
			players[_activePlayer].dir = LEFT;
		}
		break;
	case 8:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = DOWN;
		}
		else
		{
			players[_activePlayer].dir = UP;
		}
		break;
	case 9:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = RIGHT;
		}
		else
		{
			players[_activePlayer].dir = UP;
		}
		break;
	case 10:
		if (players[_activePlayer].reverseMove && !players[_activePlayer].hasChosenShortCut2)
		{
			players[_activePlayer].hasChosenWay = true;
			players[_activePlayer].dir = RIGHT;
		}
		else if (players[_activePlayer].reverseMove && players[_activePlayer].hasChosenShortCut2)
		{
			players[_activePlayer].hasChosenWay = true;
			players[_activePlayer].dir = UP;
		}
		//else if (!players[_activePlayer].reverseMove && players[_activePlayer].hasChosenShortCut2)
		//{
		//	players[_activePlayer].dir = DOWN;
		//}
		else if (!players[_activePlayer].reverseMove) /*&& !players[_activePlayer].hasChosenShortCut2)*/
		{
			players[_activePlayer].dir = LEFT;
		}
		break;
	case 11:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = UP;
		}
		else
		{
			players[_activePlayer].dir = LEFT;
		}
		break;
	case 12:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = LEFT;
		}
		else
		{
			players[_activePlayer].dir = DOWN;
		}
		break;
	case 13:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = UP;
		}
		else if (!players[_activePlayer].reverseMove && !players[_activePlayer].hasChosenShortCut2)
		{
			players[_activePlayer].dir = RIGHT;
		}
		else if (!players[_activePlayer].reverseMove && players[_activePlayer].hasChosenShortCut2)
		{
			players[_activePlayer].dir = DOWN;
		}
		break;
	case 14:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = RIGHT;
		}
		else
		{
			players[_activePlayer].dir = DOWN;
		}
		break;
	case 15:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = DOWN;
		}
		else
		{
			players[_activePlayer].dir = LEFT;
		}
		break;
	case 16:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = RIGHT;

		}
		else
		{
			players[_activePlayer].dir = UP;

		}
		break;
	case 17:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = DOWN;

		}
		else
		{
			players[_activePlayer].dir = LEFT;

		}
		break;
	case 18:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = LEFT;

		}
		else
		{
			players[_activePlayer].dir = UP;

		}
		break;
	case 19:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = DOWN;

		}
		else
		{
			players[_activePlayer].dir = RIGHT;

		}
		break;
	case 20:
		if (players[_activePlayer].reverseMove)
		{
			players[_activePlayer].dir = DOWN;

		}
		else
		{
			players[_activePlayer].dir = UP;

		}
		break;
	default:
		std::cout << "value problem in updateOrientationPlayers" << std::endl;
		break;
	}

}



void UpdatePlayerGoingToFiscalControl(unsigned char& _activePlayer)
{
	if (players[_activePlayer].goingToFiscalControl && (players[_activePlayer].InitialposGrid == intersectionsPos[8].posGrid || players[_activePlayer].InitialposGrid == intersectionsPos[20].posGrid))
	{
		UpdateFinishMovement(_activePlayer);

		players[_activePlayer].goingToFiscalControl = false;
		SetActivePlayer(lastPlayerPlayed);
		SetLaunchedDices(2);

	}

	if (players[_activePlayer].goingToFiscalControl)
	{
		players[_activePlayer].hasChosenWay = true;
		players[_activePlayer].isOnChoiceInterNB1 = false;
		players[_activePlayer].isOnChoiceInterNB2 = false;
		players[_activePlayer].hasChosenShortCut1 = false;
		players[_activePlayer].hasChosenShortCut2 = false;
	}

}



void UpdatePlayerGoingToStartSquare(unsigned char& _activePlayer)
{
	if (players[_activePlayer].goingToStartSquare && players[_activePlayer].InitialposGrid == intersectionsPos[0].posGrid)
	{

		UpdateFinishMovement(_activePlayer);


		if (lastPlayerPlayed != _activePlayer)
		{
			SetActivePlayer(lastPlayerPlayed);
		}
		SetLaunchedDices(2);
	}

	if (players[_activePlayer].goingToStartSquare)
	{
		players[_activePlayer].hasChosenWay = true;
		players[_activePlayer].isOnChoiceInterNB1 = false;
		players[_activePlayer].isOnChoiceInterNB2 = false;
		players[_activePlayer].hasChosenShortCut1 = false;
		players[_activePlayer].hasChosenShortCut2 = false;
	}
}



void UpdateIsOnShortCut(unsigned char& _activePlayer)
{
	if (players[_activePlayer].hasChosenShortCut1 && players[_activePlayer].InitialposGrid.y == intersectionsPos[1].posGrid.y && players[_activePlayer].InitialposGrid.x > intersectionsPos[1].posGrid.x && players[_activePlayer].InitialposGrid.x <= intersectionsPos[6].posGrid.x)
	{
		players[_activePlayer].isOnShortCut1 = true;
	}
	else
	{
		players[_activePlayer].isOnShortCut1 = false;
	}

	if (players[_activePlayer].hasChosenShortCut2 && players[_activePlayer].InitialposGrid.y == intersectionsPos[10].posGrid.y && players[_activePlayer].InitialposGrid.x > intersectionsPos[10].posGrid.x && players[_activePlayer].InitialposGrid.x <= intersectionsPos[13].posGrid.x)
	{
		players[_activePlayer].isOnShortCut2 = true;
	}
	else
	{
		players[_activePlayer].isOnShortCut2 = false;
	}
}



void UpdateReverseMoveShortCut(unsigned char& _activePlayer)
{
	if (players[_activePlayer].reverseMove && players[_activePlayer].isOnShortCut1)
	{
		players[_activePlayer].curIntersection = 1;
		UpdateOrientationPlayers(_activePlayer);
	}
	if (players[_activePlayer].reverseMove && players[_activePlayer].isOnShortCut2)
	{
		players[_activePlayer].curIntersection = 10;
		UpdateOrientationPlayers(_activePlayer);
	}

	if (players[_activePlayer].reverseMove && players[_activePlayer].isOnChoiceInterNB1)
	{
		players[_activePlayer].isOnChoiceInterNB1 = false;
		players[_activePlayer].hasChosenWay = true;
		players[_activePlayer].curIntersection = 0;
		UpdateOrientationPlayers(_activePlayer);
	}

	if (players[_activePlayer].reverseMove && players[_activePlayer].isOnChoiceInterNB2)
	{
		players[_activePlayer].isOnChoiceInterNB2 = false;
		players[_activePlayer].hasChosenWay = true;
		players[_activePlayer].curIntersection = 9;
		UpdateOrientationPlayers(_activePlayer);
	}
}




void UpdateFinishMovement(unsigned char& _activePlayer)
{
	players[_activePlayer].intersectionReached = false;
	players[_activePlayer].InitialposGrid = players[_activePlayer].nextPosGrid;
	players[_activePlayer].initialPos = players[_activePlayer].pos;
	players[_activePlayer].timer = 0.f;
	players[_activePlayer].isMoving = false;
	players[_activePlayer].nbTilesMoving = 0;
	players[_activePlayer].hasChosenWay = false;

	if (players[_activePlayer].InitialposGrid != sf::Vector2f(2, 13))
	{
		UpdateTilesAction(players[_activePlayer].InitialposGrid, _activePlayer);
	}
	else if (players[_activePlayer].InitialposGrid == sf::Vector2f(2, 13) && (GetNbTurns4Players() > 0 || players[_activePlayer].hasAlreadyMoved) && !players[_activePlayer].goingToStartSquare)
	{
		UpdateTilesAction(players[_activePlayer].InitialposGrid, _activePlayer);
	}

	players[_activePlayer].goingToFiscalControl = false;
	players[_activePlayer].goingToStartSquare = false;

	if (GetPlayerReplaying() && !GetIsInParliamentaryCouncil() && !GetPlayerIsOnMysterytile(GetActivePlayer()))
	{
		setDiceHasRolling(false);
		SetPlayerReplaying(false);
	}
}



void UpdateCurrentIntersection(unsigned char& _activePlayer)
{
	if (players[_activePlayer].reverseMove)
	{
		if (players[_activePlayer].curIntersection == 7 && !players[_activePlayer].hasChosenShortCut1)
		{
			players[_activePlayer].curIntersection = 5;
			UpdateOrientationPlayers(_activePlayer);
		}
		else if (players[_activePlayer].curIntersection == 14 && players[_activePlayer].hasChosenShortCut2)
		{
			players[_activePlayer].curIntersection = 10;
			UpdateOrientationPlayers(_activePlayer);
		}
		//ici , peut etre rajouter la gestion du recul juste avant le départ
		else if (players[_activePlayer].curIntersection <= 0)
		{
			players[_activePlayer].curIntersection = 19;
			UpdateOrientationPlayers(_activePlayer);
		}
		else
		{
			players[_activePlayer].curIntersection--;
			UpdateOrientationPlayers(_activePlayer);
		}
	}
	else
	{
		if (players[_activePlayer].curIntersection == 5 && !players[_activePlayer].hasChosenShortCut1)
		{
			players[_activePlayer].curIntersection = 7;
			UpdateOrientationPlayers(_activePlayer);
		}
		else if ((players[_activePlayer].curIntersection == 7 && !players[_activePlayer].goingToFiscalControl) || (players[_activePlayer].curIntersection == 19 && !players[_activePlayer].goingToFiscalControl))
		{
			players[_activePlayer].curIntersection += 2;
			UpdateOrientationPlayers(_activePlayer);
		}
		else
		{
			players[_activePlayer].curIntersection++;
			UpdateOrientationPlayers(_activePlayer);
		}
	}
}

void UpdateTurningPointMovement(unsigned char& _activePlayer)
{
	if (players[_activePlayer].nbTilesMoving > 0)
	{
		UpdateCurrentIntersection(_activePlayer);

		players[_activePlayer].intersectionReached = false;
		players[_activePlayer].InitialposGrid = players[_activePlayer].nextPosGrid;

		if (players[_activePlayer].InitialposGrid == sf::Vector2f(2, 13) && GetNbTurns4Players() != 0 && !players[_activePlayer].goingToStartSquare && !players[_activePlayer].goingToFiscalControl)
		{
			UpdateTilesAction(players[_activePlayer].InitialposGrid, _activePlayer);
		}
		else if (players[_activePlayer].InitialposGrid == sf::Vector2f(2, 13) && players[_activePlayer].goingToStartSquare)
		{
			players[_activePlayer].nbTilesMoving = 0;
			UpdateTilesAction(players[_activePlayer].InitialposGrid, _activePlayer);
		}
		else if ((players[_activePlayer].InitialposGrid == intersectionsPos[5].posGrid || players[_activePlayer].InitialposGrid == intersectionsPos[12].posGrid) && !players[_activePlayer].goingToFiscalControl && !players[_activePlayer].goingToStartSquare && !players[_activePlayer].reverseMove)
		{
			UpdateTilesAction(players[_activePlayer].InitialposGrid, _activePlayer);
		}

		players[_activePlayer].initialPos = players[_activePlayer].pos;
		players[_activePlayer].timer = 0.f;
	}

	else
	{
		UpdateCurrentIntersection(_activePlayer);
		UpdateFinishMovement(_activePlayer);
		ResetReverseMove(_activePlayer);

		players[_activePlayer].hasAlreadyMoved = true;
	}
}

void ResetReverseMove(unsigned char& _activePlayer)
{
	if (players[_activePlayer].reverseMove)
	{
		if (players[_activePlayer].isOnShortCut1)
		{
			players[_activePlayer].curIntersection = 6;
			players[_activePlayer].reverseMove = false;
			UpdateOrientationPlayers(_activePlayer);
		}
		else if (players[_activePlayer].isOnShortCut2)
		{
			players[_activePlayer].curIntersection = 14;
			players[_activePlayer].reverseMove = false;
			UpdateOrientationPlayers(_activePlayer);
		}
		//peut etre ajouter la gestion des intersections controle fiscal
		else
		{
			if (players[_activePlayer].curIntersection == 7 || (players[_activePlayer].curIntersection == 5 && !players[_activePlayer].hasChosenShortCut1))
			{
				players[_activePlayer].curIntersection += 2; //peut cause des bugs
			}
			else
			{
				players[_activePlayer].curIntersection++;
			}
			players[_activePlayer].reverseMove = false;
			UpdateOrientationPlayers(_activePlayer);
		}
	}
}


void UpdateNextMovePlayer(unsigned char& _activePlayer)
{
	if (players[_activePlayer].intersectionReached)
	{
		UpdateTurningPointMovement(_activePlayer);
	}
	else
	{
		UpdateFinishMovement(_activePlayer);
		ResetReverseMove(_activePlayer);

		players[_activePlayer].hasAlreadyMoved = true;
	}
}

void UpdatePlayerMovesAccordingToDir(unsigned char& _activePlayer)
{
	if (players[_activePlayer].isMoving && players[_activePlayer].timer == 0.f)
	{

		switch (players[_activePlayer].dir)
		{
		case UP:


			if (players[_activePlayer].nextPosGrid.x - players[_activePlayer].nbTilesMoving <= intersectionsPos[players[_activePlayer].curIntersection].posGrid.x)
			{
				players[_activePlayer].nbTilesMoving -= (int)fabsf(players[_activePlayer].nextPosGrid.x - intersectionsPos[players[_activePlayer].curIntersection].posGrid.x);
				players[_activePlayer].nextPosGrid = intersectionsPos[players[_activePlayer].curIntersection].posGrid;
				players[_activePlayer].intersectionReached = true;
			}
			else
			{
				players[_activePlayer].nextPosGrid = sf::Vector2f(players[_activePlayer].nextPosGrid.x - players[_activePlayer].nbTilesMoving, players[_activePlayer].nextPosGrid.y);
				players[_activePlayer].nbTilesMoving = 0;
			}


			break;
		case DOWN:

			if (players[_activePlayer].nextPosGrid.x + players[_activePlayer].nbTilesMoving >= intersectionsPos[players[_activePlayer].curIntersection].posGrid.x)
			{
				players[_activePlayer].nbTilesMoving -= (int)fabsf(players[_activePlayer].nextPosGrid.x - intersectionsPos[players[_activePlayer].curIntersection].posGrid.x);
				players[_activePlayer].nextPosGrid = intersectionsPos[players[_activePlayer].curIntersection].posGrid;
				players[_activePlayer].intersectionReached = true;
			}
			else
			{
				players[_activePlayer].nextPosGrid = sf::Vector2f(players[_activePlayer].nextPosGrid.x + players[_activePlayer].nbTilesMoving, players[_activePlayer].nextPosGrid.y);
				players[_activePlayer].nbTilesMoving = 0;
			}



			break;
		case LEFT:

			if (players[_activePlayer].nextPosGrid.y + players[_activePlayer].nbTilesMoving >= intersectionsPos[players[_activePlayer].curIntersection].posGrid.y)
			{
				players[_activePlayer].nbTilesMoving -= (int)fabsf(players[_activePlayer].nextPosGrid.y - intersectionsPos[players[_activePlayer].curIntersection].posGrid.y);
				players[_activePlayer].nextPosGrid = intersectionsPos[players[_activePlayer].curIntersection].posGrid;
				players[_activePlayer].intersectionReached = true;
			}
			else
			{
				players[_activePlayer].nextPosGrid = sf::Vector2f(players[_activePlayer].nextPosGrid.x, players[_activePlayer].nextPosGrid.y + players[_activePlayer].nbTilesMoving);
				players[_activePlayer].nbTilesMoving = 0;
			}




			break;
		case RIGHT: // intersections 1, 2, 4, 12


			if (players[_activePlayer].nextPosGrid.y - players[_activePlayer].nbTilesMoving <= intersectionsPos[players[_activePlayer].curIntersection].posGrid.y)
			{
				players[_activePlayer].nbTilesMoving -= (int)fabsf(players[_activePlayer].nextPosGrid.y - intersectionsPos[players[_activePlayer].curIntersection].posGrid.y);
				players[_activePlayer].nextPosGrid = intersectionsPos[players[_activePlayer].curIntersection].posGrid;
				players[_activePlayer].intersectionReached = true;
			}
			else
			{
				players[_activePlayer].nextPosGrid = sf::Vector2f(players[_activePlayer].nextPosGrid.x, players[_activePlayer].nextPosGrid.y - players[_activePlayer].nbTilesMoving);
				players[_activePlayer].nbTilesMoving = 0;
			}



			break;
		default:
			break;
		}
	}
}

void UpdatePlayerMoveCerp(float _dt, unsigned char& _activePlayer)
{
	if (players[_activePlayer].isMoving)
	{
		if (players[_activePlayer].goingToFiscalControl || players[_activePlayer].goingToStartSquare)
		{
			players[_activePlayer].timer += 1.6f * _dt;
		}
		else
		{
			players[_activePlayer].timer += _dt;
		}

		players[_activePlayer].pos = Cerp(players[_activePlayer].initialPos,
			GetCell((int)players[_activePlayer].nextPosGrid.x, (int)players[_activePlayer].nextPosGrid.y, 1),
			players[_activePlayer].timer);

		players[_activePlayer].sprite.setPosition(players[_activePlayer].pos);
		players[_activePlayer].spriteArrow.setPosition(players[_activePlayer].pos);
	}
}

void UpdatePlayerMystery(unsigned char& _activePlayer)
{
	if (players[_activePlayer].isOnMysteryTile && GetDiceHasRolling() && !GetDiceisAvailable() && !players[_activePlayer].hasTookMysteryAction && !players[_activePlayer].isInParliamentaryCouncil && (!players[_activePlayer].isAnAI || (players[_activePlayer].isAnAI && !players[_activePlayer].ai.mysteryActionPlaying)))
	{
		unsigned char activePlayer = 0;
		switch (GetFirstDiceValue())
		{
		case 1:
			SetPlayerIsOnTaxe(_activePlayer, true);
			SetTaxIsAppears(true);
			SetPlayerHasChooseToPaidTaxesOrNot(_activePlayer, false);
			players[_activePlayer].hasTookMysteryAction = true;
			break;
		case 2:
			SetChanceStackCanBeSelected();
			if (!players[_activePlayer].isAnAI)
			{
				players[_activePlayer].hasTookMysteryAction = true;
			}
			else
			{
				players[_activePlayer].ai.mysteryActionPlaying = true;
			}
			break;
		case 3:
			SetChanceStackCanBeSelected();
			if (!players[_activePlayer].isAnAI)
			{
				players[_activePlayer].hasTookMysteryAction = true;
			}
			else
			{
				players[_activePlayer].ai.mysteryActionPlaying = true;
			}
			break;
		case 4:
			SetActionStackCanBeSelected();
			if (!players[_activePlayer].isAnAI)
			{
				players[_activePlayer].hasTookMysteryAction = true;
			}
			else
			{
				players[_activePlayer].ai.mysteryActionPlaying = true;
			}
			break;
		case 5:
			SetActionStackCanBeSelected();
			if (!players[_activePlayer].isAnAI)
			{
				players[_activePlayer].hasTookMysteryAction = true;
			}
			else
			{
				players[_activePlayer].ai.mysteryActionPlaying = true;
			}
			break;
		case 6:
			setDiceHasRolling(false);
			SetLaunchedDices(1);
			SetIsInParliamentaryCouncil(true);
			SetLastPlayerPlayed(_activePlayer);
			SetActivePlayer(activePlayer);
			SetParliamentaryIsAppears(true);
			SetPseudoInInsert(activePlayer);
			SetNoOneIsMoving(false);
			PlaySoundFromList(parliamentaryCouncilSound, 50);
			break;
		default:
			std::cout << "error mystery tile" << std::endl;
			break;
		}
		SetPlayerIsMoving(_activePlayer, false);
	}
}

void UpdateParliamentaryCouncil(unsigned char& _activePlayer)
{
	if (players[_activePlayer].isInParliamentaryCouncil && GetDiceHasRolling() && !GetDiceisAvailable() && !GetIsParliamentaryFinished())
	{
		unsigned char activePlayer = _activePlayer;
		char activePlayerReputation;
		unsigned char diceResult = GetFirstDiceValue();
		unsigned char lastPlayer;
		bool hasActivePlayerPlayed = false;

		if (activePlayer == PLAYER_1)
		{
			activePlayerReputation = GetPlayersReputation(activePlayer);
			if (activePlayerReputation < 0)
			{
				SetDicesValue(activePlayer, diceResult - 1);
			}
			else if (activePlayerReputation > 0)
			{
				SetDicesValue(activePlayer, diceResult + 1);
			}
			else
			{
				SetDicesValue(activePlayer, diceResult);
			}
			activePlayer = PLAYER_2;
			SetActivePlayer(activePlayer);
			SetParliamentaryIsAppears(true);
			SetPseudoInInsert(activePlayer);
			setDiceHasRolling(false);
			SetNoOneIsMoving(false);
		}
		else if (activePlayer == PLAYER_2)
		{
			activePlayerReputation = GetPlayersReputation(activePlayer);
			if (activePlayerReputation < 0)
			{
				SetDicesValue(activePlayer, diceResult - 1);
			}
			else if (activePlayerReputation > 0)
			{
				SetDicesValue(activePlayer, diceResult + 1);
			}
			else
			{
				SetDicesValue(activePlayer, diceResult);
			}
			activePlayer = PLAYER_3;
			SetActivePlayer(activePlayer);
			SetParliamentaryIsAppears(true);
			SetPseudoInInsert(activePlayer);
			setDiceHasRolling(false);
			SetNoOneIsMoving(false);
		}
		else if (activePlayer == PLAYER_3)
		{
			activePlayerReputation = GetPlayersReputation(activePlayer);
			if (activePlayerReputation < 0)
			{
				SetDicesValue(activePlayer, diceResult - 1);
			}
			else if (activePlayerReputation > 0)
			{
				SetDicesValue(activePlayer, diceResult + 1);
			}
			else
			{
				SetDicesValue(activePlayer, diceResult);
			}
			activePlayer = PLAYER_4;
			SetActivePlayer(activePlayer);
			SetParliamentaryIsAppears(true);
			SetPseudoInInsert(activePlayer);
			setDiceHasRolling(false);
			SetNoOneIsMoving(false);
		}

		else if (activePlayer == PLAYER_4)
		{
			activePlayerReputation = GetPlayersReputation(activePlayer);
			lastPlayer = GetLastPlayerPlayed();
			bool randomRead = false;

			if (activePlayerReputation < 0)
			{
				SetDicesValue(activePlayer, diceResult - 1);
			}
			else if (activePlayerReputation > 0)
			{
				SetDicesValue(activePlayer, diceResult + 1);
			}
			else
			{
				SetDicesValue(activePlayer, diceResult);
			}

			for (int i = 0; i < NB_PLAYERS; i++)
			{
				sf::Vector2i dice;
				dice.x = GetDicesValue(i);
				dice.y = i;
				players->dicesVector.push_back(dice);
			}

			SortDicesVectorDiceValue(players->dicesVector, NB_PLAYERS);

			// 2 + petites valeurs égales
			if (players->dicesVector[0].x == players->dicesVector[1].x)
			{
				// 3 + petites valeurs égales
				if (players->dicesVector[1].x == players->dicesVector[2].x)
				{
					//tous egaux
					if (players->dicesVector[2].x == players->dicesVector[3].x)
					{
						SortDicesVectorReputation(players->dicesVector, 0, NB_PLAYERS);
						ParliamentaryDistributeVoters(players->dicesVector);

					}
					else
					{
						SortDicesVectorReputation(players->dicesVector, 0, 3);
						ParliamentaryDistributeVoters(players->dicesVector);
					}
				}
				else
				{
					SortDicesVectorReputation(players->dicesVector, 0, 2);
					ParliamentaryDistributeVoters(players->dicesVector);
				}
			}
			//2 valeurs intermedière égales
			else if (players->dicesVector[1].x == players->dicesVector[2].x)
			{
				// 3 + grandes valeurs égales
				if (players->dicesVector[2].x == players->dicesVector[3].x)
				{
					SortDicesVectorReputation(players->dicesVector, 1, NB_PLAYERS);
					ParliamentaryDistributeVoters(players->dicesVector);

				}
				else
				{
					SortDicesVectorReputation(players->dicesVector, 1, 3);
					ParliamentaryDistributeVoters(players->dicesVector);
				}
			}
			//2 valeurs + grande égales
			else if (players->dicesVector[2].x == players->dicesVector[3].x)
			{
				SortDicesVectorReputation(players->dicesVector, 2, NB_PLAYERS);
				ParliamentaryDistributeVoters(players->dicesVector);
			}
			// aucun dé de la meme valeur 
			else
			{
				ParliamentaryDistributeVoters(players->dicesVector);
			}

			SetIsParliamentaryFinished(true);
		}
	}
}

void DoubleResestMystery()
{
	if (GetPlayerReplaying() && players[GetActivePlayer()].hasTookMysteryAction && GetPlayerIsOnMysterytile(GetActivePlayer()))
	{
		SetLaunchedDices(2);
		setDiceHasRolling(false);
		SetPlayerReplaying(false);
		SetMysteryActionPlayingAI(GetActivePlayer(), false);
		SetPlayerIsOnMysterytile(GetActivePlayer(), false);
	}
	if (players[GetActivePlayer()].hasTookMysteryAction && GetPlayerIsOnMysterytile(GetActivePlayer()))
	{
		SetPlayerIsOnMysterytile(GetActivePlayer(), false);
	}
}

void DoubleResestParliamentaryCouncil()
{
	if (GetPlayerReplaying() && players[GetActivePlayer()].isOnParliamentaryCouncilTile && !GetIsInParliamentaryCouncil())
	{
		SetLaunchedDices(2);
		setDiceHasRolling(false);
		SetPlayerReplaying(false);
	}
}

void UpdateSpiteSort(void)
{
	/*if (!GetNoOneIsMoving())*/
	{
		for (int i = 0; i < NB_PLAYERS; i++)
		{
			spriteSorting[i].pos = players[spriteSorting[i].playerIndex].pos + players[spriteSorting[i].playerIndex].spriteOffset;
			//spriteSorting[spriteSorting[i].playerIndex].pos = CartesianToIsometric(spriteSorting[spriteSorting[i].playerIndex].pos.x, spriteSorting[spriteSorting[i].playerIndex].pos.y, 1, (float)GetTileWidth());
		}

		for (int i = 0; i < NB_PLAYERS; i++)
		{
			for (int j = 0; j < NB_PLAYERS - 1; j++)
			{
				if (spriteSorting[j + 1].pos.y < spriteSorting[j].pos.y)
				{
					SpriteSorting tempSorting = spriteSorting[j + 1];
					spriteSorting[j + 1] = spriteSorting[j];
					spriteSorting[j] = tempSorting;
				}
			}
		}
	}
}

//KeyPressed

void ChoosingAWayOnIntersection(sf::Keyboard::Key _key, unsigned char& _activePlayer)
{
	if (players[_activePlayer].nbTilesMoving > 0)
	{
		if (players[_activePlayer].isOnChoiceInterNB1 && (_key == GetKey(KB_NWAY) || _key == sf::Keyboard::Right))
		{
			players[_activePlayer].hasChosenWay = true;
			players[_activePlayer].isOnChoiceInterNB1 = false;
			players[_activePlayer].hasChosenShortCut1 = false;
			timerScaleArrow = 0;
			choiceArrow[DOWN_NB1_ARR].sprite.setScale(0.f, 0.f);
			choiceArrow[RIGHT_ARR].sprite.setScale(0.f, 0.f);
		}
		else if (players[_activePlayer].isOnChoiceInterNB2 && (_key == GetKey(KB_NWAY) || _key == sf::Keyboard::Left))
		{

			players[_activePlayer].hasChosenWay = true;
			players[_activePlayer].isOnChoiceInterNB2 = false;
			players[_activePlayer].hasChosenShortCut2 = false;
			timerScaleArrow = 0;
			choiceArrow[DOWN_NB2_ARR].sprite.setScale(0.f, 0.f);
			choiceArrow[LEFT_ARR].sprite.setScale(0.f, 0.f);
		}

		else if (players[_activePlayer].isOnChoiceInterNB1 && (_key == GetKey(KB_SHORTCUT) || _key == sf::Keyboard::Down))
		{

			players[_activePlayer].curIntersection = 6;
			players[_activePlayer].hasChosenWay = true;
			players[_activePlayer].isOnChoiceInterNB1 = false;
			players[_activePlayer].hasChosenShortCut1 = true;
			UpdateOrientationPlayers(_activePlayer);
			timerScaleArrow = 0;
			choiceArrow[DOWN_NB1_ARR].sprite.setScale(0.f, 0.f);
			choiceArrow[RIGHT_ARR].sprite.setScale(0.f, 0.f);
		}
		else if (players[_activePlayer].isOnChoiceInterNB2 && (_key == GetKey(KB_SHORTCUT) || _key == sf::Keyboard::Down))
		{

			players[_activePlayer].curIntersection = 14;
			players[_activePlayer].hasChosenWay = true;
			players[_activePlayer].isOnChoiceInterNB2 = false;
			players[_activePlayer].hasChosenShortCut2 = true;
			UpdateOrientationPlayers(_activePlayer);
			timerScaleArrow = 0;
			choiceArrow[DOWN_NB2_ARR].sprite.setScale(0.f, 0.f);
			choiceArrow[LEFT_ARR].sprite.setScale(0.f, 0.f);
		}
	}
}

void SortDicesVectorDiceValue(std::vector<sf::Vector2i>& _vector, int _size)
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size - 1; j++)
		{
			if (_vector[j + 1].x < _vector[j].x)
			{
				sf::Vector2i diceTemp = _vector[j + 1];
				_vector[j + 1] = _vector[j];
				_vector[j] = diceTemp;
			}
		}
	}
}

void SortDicesVectorReputation(std::vector<sf::Vector2i>& _vector, int _start, int _end)
{
	for (int i = _start; i < _end; i++)
	{
		for (int j = _start; j < _end - 1; j++)
		{
			if (GetPlayersReputation(_vector[j + 1].y) < GetPlayersReputation(_vector[j].y))
			{
				sf::Vector2i diceTemp = _vector[j + 1];
				_vector[j + 1] = _vector[j];
				_vector[j] = diceTemp;
			}
		}
	}
}

void ParliamentaryDistributeVoters(std::vector<sf::Vector2i> _vector)
{
	AddPlayerVoters(_vector[0].y, -200);
	AddPlayerVoters(_vector[1].y, -100);
	AddPlayerVoters(_vector[2].y, 100);
	AddPlayerVoters(_vector[3].y, 200);
}

void UpdateChoiceArrow(float& _dt, unsigned char& _activePlayer)
{
	if (players[_activePlayer].isOnChoiceInterNB1 && !players[_activePlayer].hasChosenWay && players[_activePlayer].nbTilesMoving > 0)
	{
		if (timerScaleArrow < 1)
		{
			timerScaleArrow += _dt;
			choiceArrow[DOWN_NB1_ARR].sprite.setScale(ScaleToScreen(EaseOutBounce(timerScaleArrow), EaseOutBounce(timerScaleArrow)));
			choiceArrow[RIGHT_ARR].sprite.setScale(ScaleToScreen(EaseOutBounce(timerScaleArrow), EaseOutBounce(timerScaleArrow)));
		}
		else
		{
			choiceArrow[DOWN_NB1_ARR].sprite.setScale(ScaleToScreen(1, 1));
			choiceArrow[RIGHT_ARR].sprite.setScale(ScaleToScreen(1, 1));
		}

	}
	else if (players[_activePlayer].isOnChoiceInterNB2 && !players[_activePlayer].hasChosenWay && players[_activePlayer].nbTilesMoving > 0)
	{
		if (timerScaleArrow < 1)
		{
			timerScaleArrow += _dt;
			choiceArrow[DOWN_NB2_ARR].sprite.setScale(ScaleToScreen(EaseOutBounce(timerScaleArrow), EaseOutBounce(timerScaleArrow)));
			choiceArrow[LEFT_ARR].sprite.setScale(ScaleToScreen(EaseOutBounce(timerScaleArrow), EaseOutBounce(timerScaleArrow)));

		}
		else
		{
			choiceArrow[DOWN_NB2_ARR].sprite.setScale(ScaleToScreen(1, 1));
			choiceArrow[LEFT_ARR].sprite.setScale(ScaleToScreen(1, 1));
		}

	}
}

void DisplayChoiceArrowAfterPlayers(sf::RenderWindow& _window, unsigned char& _activePlayer)
{
	if (players[_activePlayer].isOnChoiceInterNB1 && !players[_activePlayer].hasChosenWay && players[_activePlayer].nbTilesMoving > 0)
	{

		choiceArrow[DOWN_NB1_ARR].isoPos = CartesianToIsometric(3, 4, 1, (float)GetTileWidth());
		choiceArrow[DOWN_NB1_ARR].sprite.setPosition(sf::Vector2f(choiceArrow[DOWN_NB1_ARR].isoPos.x + GetGridOffset().x + PosToScreenX(choiceArrow[DOWN_NB1_ARR].sprite.getLocalBounds().width / 2.f), choiceArrow[DOWN_NB1_ARR].isoPos.y + GetGridOffset().y + PosToScreenY(choiceArrow[DOWN_NB1_ARR].sprite.getLocalBounds().height * 3 / 4.f)));
		_window.draw(choiceArrow[DOWN_NB1_ARR].sprite);

		VectorRoads vectorRoads = GetVectorRoad();

		tileShining[1].isoPos = CartesianToIsometric(vectorRoads.shortcutRoad1[players[_activePlayer].nbTilesMoving - 1].x, vectorRoads.shortcutRoad1[players[_activePlayer].nbTilesMoving - 1].y, 1, (float)GetTileWidth());
		tileShining[1].sprite.setPosition(sf::Vector2f(tileShining[1].isoPos.x + GetGridOffset().x, tileShining[1].isoPos.y + GetGridOffset().y));
		_window.draw(tileShining[1].sprite);

	}
	else if (players[_activePlayer].isOnChoiceInterNB2 && !players[_activePlayer].hasChosenWay && players[_activePlayer].nbTilesMoving > 0)
	{
		choiceArrow[DOWN_NB2_ARR].isoPos = CartesianToIsometric(5, 8, 1, (float)GetTileWidth());
		choiceArrow[DOWN_NB2_ARR].sprite.setPosition(sf::Vector2f(choiceArrow[DOWN_NB2_ARR].isoPos.x + GetGridOffset().x + PosToScreenX(choiceArrow[DOWN_NB2_ARR].sprite.getLocalBounds().width / 2.f), choiceArrow[DOWN_NB2_ARR].isoPos.y + GetGridOffset().y + PosToScreenY(choiceArrow[DOWN_NB2_ARR].sprite.getLocalBounds().height * 3 / 4.f)));
		_window.draw(choiceArrow[DOWN_NB2_ARR].sprite);

		choiceArrow[LEFT_ARR].isoPos = CartesianToIsometric(4, 9, 1, (float)GetTileWidth());
		choiceArrow[LEFT_ARR].sprite.setPosition(sf::Vector2f(choiceArrow[LEFT_ARR].isoPos.x + GetGridOffset().x + PosToScreenX(choiceArrow[LEFT_ARR].sprite.getLocalBounds().width / 2.f), choiceArrow[LEFT_ARR].isoPos.y + GetGridOffset().y + PosToScreenY(choiceArrow[LEFT_ARR].sprite.getLocalBounds().height * 3 / 4.f)));
		_window.draw(choiceArrow[LEFT_ARR].sprite);

		VectorRoads vectorRoads = GetVectorRoad();

		tileShining[0].isoPos = CartesianToIsometric(vectorRoads.mainRoad2[players[_activePlayer].nbTilesMoving - 1].x, vectorRoads.mainRoad2[players[_activePlayer].nbTilesMoving - 1].y, 1, (float)GetTileWidth());
		tileShining[0].sprite.setPosition(sf::Vector2f(tileShining[0].isoPos.x + GetGridOffset().x, tileShining[0].isoPos.y + GetGridOffset().y));
		_window.draw(tileShining[0].sprite);

		tileShining[1].isoPos = CartesianToIsometric(vectorRoads.shortcutRoad2[players[_activePlayer].nbTilesMoving - 1].x, vectorRoads.shortcutRoad2[players[_activePlayer].nbTilesMoving - 1].y, 1, (float)GetTileWidth());
		tileShining[1].sprite.setPosition(sf::Vector2f(tileShining[1].isoPos.x + GetGridOffset().x, tileShining[1].isoPos.y + GetGridOffset().y));
		_window.draw(tileShining[1].sprite);
	}
}

void DisplayChoiceArrowBeforePlayers(sf::RenderWindow& _window, unsigned char& _activePlayer)
{
	if (players[_activePlayer].isOnChoiceInterNB1 && !players[_activePlayer].hasChosenWay && players[_activePlayer].nbTilesMoving > 0)
	{
		choiceArrow[RIGHT_ARR].isoPos = CartesianToIsometric(2, 3, 1, (float)GetTileWidth());
		choiceArrow[RIGHT_ARR].sprite.setPosition(sf::Vector2f(choiceArrow[RIGHT_ARR].isoPos.x + GetGridOffset().x + PosToScreenX(choiceArrow[RIGHT_ARR].sprite.getLocalBounds().width / 2.f), choiceArrow[RIGHT_ARR].isoPos.y + GetGridOffset().y + PosToScreenY(choiceArrow[RIGHT_ARR].sprite.getLocalBounds().height * 3 / 4.f)));
		_window.draw(choiceArrow[RIGHT_ARR].sprite);

		VectorRoads vectorRoads = GetVectorRoad();
		tileShining[0].isoPos = CartesianToIsometric(vectorRoads.mainRoad1[players[_activePlayer].nbTilesMoving - 1].x, vectorRoads.mainRoad1[players[_activePlayer].nbTilesMoving - 1].y, 1, (float)GetTileWidth());
		tileShining[0].sprite.setPosition(sf::Vector2f(tileShining[0].isoPos.x + GetGridOffset().x, tileShining[0].isoPos.y + GetGridOffset().y));
		_window.draw(tileShining[0].sprite);
	}
}


//Set and Get functions

void SetPlayerCharacterChosen(unsigned char _player, unsigned char _character)
{
	players[_player].characterChosen = _character;
}

unsigned char GetPlayerCharacterChosen(unsigned char _i)
{
	return players[_i].characterChosen;
}

bool GetPlayerHasFinishedTurn(unsigned char _activePlayer)
{
	return players[_activePlayer].hasFinishedTurn;
}


void SetPlayerReady(unsigned char _i, bool _isReady)
{
	players[_i].isReady = _isReady;
}

bool GetPlayerReady(unsigned char _i)
{
	return players[_i].isReady;
}

sf::Color GetPlayerColor(unsigned char _i)
{
	switch (_i)
	{
	case PLAYER_1:
		return sf::Color::Red;
		break;
	case PLAYER_2:
		return sf::Color::Blue;
		break;
	case PLAYER_3:
		return sf::Color::Green;
		break;
	case PLAYER_4:
		return sf::Color::Yellow;
		break;
	default:
		return sf::Color::White;
		break;
	}
}

void SetPlayerCharacterSelected(unsigned char _i, bool _characterSelected)
{
	players[_i].characterSelected = _characterSelected;
}

bool GetCharacterSelectedBool(unsigned char _i)
{
	return players[_i].characterSelected;
}

bool GetAllPlayersReady(void)
{
	if (players[0].isReady && players[1].isReady && players[2].isReady && players[3].isReady)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GetPlayerIsMoving(unsigned char _i)
{
	return players[_i].isMoving;
}

sf::Vector2f GetPlayerPosGrid(unsigned char _i)
{
	return players[_i].nextPosGrid;
}

int GetPlayerMoney(unsigned char _i)
{
	return players[_i].money;
}

int GetPlayersReputation(unsigned char _i)
{
	return players[_i].reputation;
}

int GetPlayersVoters(unsigned char _i)
{
	return players[_i].voters;
}

void SetPlayerHasFinishedTurn(int _i, bool _finishedTurn)
{
	players[_i].hasFinishedTurn = _finishedTurn;
}

void AddPlayerMoney(unsigned char _i, int _money)
{
	players[_i].money += _money;
	SetTextStat(_i, _money, MONEY);
}

void AddPlayerReputation(unsigned char _i, int _reputation)
{
	players[_i].reputation += _reputation;
	SetTextStat(_i, _reputation, REPUTATION);
}

void AddPlayerVoters(unsigned char _i, int _voters)
{
	if ((players[_i].voters + _voters) < 0)
	{
		players[_i].voters = 0;
	}
	else
	{
		players[_i].voters += _voters;
	}
	SetTextStat(_i, _voters, VOTERS);
}

void SetPlayerIsMoving(unsigned char _i, bool _bool)
{
	players[_i].isMoving = _bool;
}

void SetPlayerNBTilesMoving(unsigned char _i, int _nbTiles)
{
	players[_i].nbTilesMoving = _nbTiles;
}

bool GetNoOneIsMoving(void)
{
	if (!players[PLAYER_1].isMoving && !players[PLAYER_2].isMoving && !players[PLAYER_3].isMoving && !players[PLAYER_4].isMoving)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AddTaxes(unsigned char _i, char _nbTaxes)
{
	players[_i].taxes += _nbTaxes;
	SetTextStat(_i, _nbTaxes, TAX);
}

int GetNbTaxes(unsigned char _i)
{
	return players[_i].taxes;
}

void SetPlayerReverseMove(unsigned char _i, int _nbTilesMoving)
{
	players[_i].reverseMove = true;

	if (players[_i].curIntersection <= 0)
	{
		players[_i].curIntersection = 19;
		UpdateOrientationPlayers(_i);
	}
	else
	{
		if (players[_i].curIntersection == 9)
		{
			players[_i].curIntersection -= 2;
		}
		else
		{
			players[_i].curIntersection--;
		}
		UpdateOrientationPlayers(_i);
	}

	players[_i].isMoving = true;
	players[_i].nbTilesMoving = _nbTilesMoving;
	players[_i].isOnMysteryTile = false;
	players[_i].hasAlreadyMoved = false;
	SetAICanDrawACard(GetActivePlayer(), false);
}

void SetPlayerMovingToFiscalControl(unsigned char _i)
{
	lastPlayerPlayed = GetActivePlayer();
	SetActivePlayer(_i);
	players[_i].isMoving = true;
	players[_i].hasChosenWay = true;
	players[_i].intersectionReached = false;
	players[_i].goingToFiscalControl = true;

	if (players[_i].goingToFiscalControl && players[_i].curIntersection == 9 && players[_i].InitialposGrid.x >= intersectionsPos[8].posGrid.x)
	{
		players[_i].curIntersection = 8;
		UpdateOrientationPlayers(_i);
	}

	players[_i].nbTilesMoving = 120;

	if (players[_i].curIntersection > 20 && !players[_i].reverseMove)
	{
		players[_i].curIntersection = 0;
		UpdateOrientationPlayers(_i);
	}
	players[_i].isOnMysteryTile = false;
	players[_i].hasAlreadyMoved = false;
}

void SetPlayerMovingToStartSquare(unsigned char _i)
{
	lastPlayerPlayed = GetActivePlayer();
	SetActivePlayer(_i);
	players[_i].goingToStartSquare = true;
	players[_i].isMoving = true;
	players[_i].hasChosenWay = true;
	players[_i].nbTilesMoving = 120;
	players[_i].isOnMysteryTile = false;
	players[_i].hasAlreadyMoved = false;
}

void SetPlayerMoveForward(unsigned char _i, int _nbTilesMoving)
{
	players[_i].isMoving = true;
	players[_i].nbTilesMoving = _nbTilesMoving;
	players[_i].isOnMysteryTile = false;
	players[_i].hasAlreadyMoved = false;
	SetAICanDrawACard(GetActivePlayer(), false);
}

sf::Vector2f GetPlayerPos(int _i)
{
	return players[_i].pos;
}

bool GetPlayerHasChooseToPaidTaxesOrNot(unsigned char _i)
{
	return players[_i].hasChooseToPaidTaxesOrNot;
}

void SetPlayerHasAlreadyMoved(unsigned char _i, bool _bool)
{
	players[_i].hasAlreadyMoved = _bool;
}

bool GetPlayerHasAlreadyMoved(unsigned char _i)
{
	return players[_i].hasAlreadyMoved;
}

void SetPlayerHasChooseToPaidTaxesOrNot(unsigned char _i, bool _bool)
{
	players[_i].hasChooseToPaidTaxesOrNot = _bool;
}

int GetPlayerNbTilesMoving(unsigned char _i)
{
	return players[_i].nbTilesMoving;
}

bool GetPlayerIsOnTaxe(unsigned char _i)
{
	return players[_i].isOnTaxe;
}

void SetPlayerIsOnTaxe(unsigned char _i, bool _bool)
{
	players[_i].isOnTaxe = _bool;
}

void SetPlayerIsOnMysterytile(unsigned char _i, bool _bool)
{
	players[_i].isOnMysteryTile = _bool;
}

void SetPlayerIsOnParliamentarytile(unsigned char _i, bool _bool)
{
	players[_i].isOnParliamentaryCouncilTile = _bool;
}

bool GetPlayerIsOnMysterytile(unsigned char _i)
{
	return players[_i].isOnMysteryTile;
}

bool GetPlayerIsOnParliamentarytile(unsigned char _i)
{
	return players[_i].isOnParliamentaryCouncilTile;
}

void SetPlayerName(unsigned char _i, std::string _name)
{
	players[_i].name = _name;
}

std::string GetPlayerPseudo(unsigned char _i)
{
	return players[_i].name;
}

bool GetPlayerGoingToFiscalControl(unsigned char _i)
{
	return players[_i].goingToFiscalControl;
}

void SetLastPlayerPlayed(unsigned char _i)
{
	lastPlayerPlayed = _i;
}

unsigned char& GetLastPlayerPlayed(void)
{
	return lastPlayerPlayed;
}

void SetDicesValue(unsigned char _i, unsigned char _amount)
{
	players[_i].dicesValue = _amount;
}

unsigned char GetDicesValue(unsigned char _i)
{
	return players[_i].dicesValue;
}

void SetIsInParliamentaryCouncil(bool _bool)
{
	for (int i = 0; i < NB_PLAYERS; i++)
	{
		players[i].isInParliamentaryCouncil = _bool;
	}
}

void SetPlayerHasTookMysteryAction(unsigned char _i, bool _bool)
{
	players[_i].hasTookMysteryAction = _bool;
}

bool GetIsInParliamentaryCouncil()
{
	return players[0].isInParliamentaryCouncil;
}

bool GetPlayerIsAnAI(unsigned char _i)
{
	return players[_i].isAnAI;
}

void SetPlayerIsAnAI(unsigned char _i, bool _bool)
{
	players[_i].isAnAI = _bool;
}

void SetNoOneIsMoving(bool _bool)
{
	for (int i = 0; i < NB_PLAYERS; i++)
	{
		players[i].isMoving = false;
	}
}

bool GetPlayerHasTookMisteryAction(unsigned char _i)
{
	return players[_i].hasTookMysteryAction;
}

bool GetPlayerIsOnChoiceIntersection(unsigned char _i)
{
	if (players[_i].isOnChoiceInterNB1 || players[_i].isOnChoiceInterNB2)
	{
		return true;
	}

	return false;
}

unsigned char& GetParliamentaryCouncilSound(void)
{
	return parliamentaryCouncilSound;
}

bool GetPlayerHasChosenWay(unsigned char _i)
{
	return players[_i].hasChosenWay;
}

bool GetAICanDrawACard(unsigned char _i)
{
	return players[_i].ai.canDrawACard;
}

void SetAICanDrawACard(unsigned char _i, bool _bool)
{
	players[_i].ai.canDrawACard = _bool;
}

int GetParliamentaryPlayerOrder(int _i)
{
	return players->dicesVector[_i].y;
}

void SetMysteryActionPlayingAI(unsigned char& _activePlayer, bool _bool)
{
	players[_activePlayer].ai.mysteryActionPlaying = _bool;
}

void ClearDicesVector()
{
	players->dicesVector.clear();
}

unsigned char GetPlayerCurrentIntersection(unsigned char& _i)
{
	return players[_i].curIntersection;
}

unsigned char GetPlayerDir(unsigned char& _i)
{
	return players[_i].dir;
}

bool GetIsPlayerReverseMoving(unsigned char& _i)
{
	return players[_i].reverseMove;
}

bool GetPlayerIsOnShortcut1(unsigned char& _i)
{
	return players[_i].isOnShortCut1;
}

bool GetPlayerIsOnShortcut2(unsigned char& _i)
{
	return players[_i].isOnShortCut2;
}

bool GetPlayerGoingToStartSquare(unsigned char& _i)
{
	return players[_i].goingToStartSquare;
}

bool GetMysteryActionPlaying(unsigned char& _i)
{
	return players[_i].ai.mysteryActionPlaying;
}

void SetPlayerVoters(unsigned char& _i, unsigned short int _voters)
{
	players[_i].voters = _voters;
}

void SetPlayerMoney(unsigned char& _i, unsigned int _money)
{
	players[_i].money = _money;
}

void SetPlayerReputation(unsigned char& _i, int _reputation)
{
	players[_i].reputation = _reputation;
}








































































































// IA


void LaunchDicesAI(unsigned char& _activePlayer, float& _dt)
{
	if (players[_activePlayer].isAnAI && !GetDiceHasRolling() && !GetIsAnyCardDisplaying() && !GetIsParliamentaryFinished() && (!players[_activePlayer].ai.isPutsching || (players[_activePlayer].ai.isPutsching && GetPutschIsAvailable(_activePlayer))) && (GetIsTrickDieAIResolved() || (!GetIsTrickDieAIResolved() && GetIsTrickDieIsPlaying())) && GetNoOneIsMoving() && !GetIsBlackMailPlaying() && !GetIsDenunciationPlaying() && !players[_activePlayer].goingToFiscalControl && !players[_activePlayer].goingToStartSquare && players[_activePlayer].hasChooseToPaidTaxesOrNot && !GetGameFadeOut())
	{

		players[_activePlayer].ai.timerDelay += _dt;
		if (players[_activePlayer].ai.timerDelay > 1.25f && !GetIsDebateIsPlaying() && !GetIsInParliamentaryCouncil() && !GetPlayerIsOnMysterytile(_activePlayer))
		{
			SetDiceIsRollingTrue();
			players[_activePlayer].ai.timerDelay = 0.f;
		}
		else if (players[_activePlayer].ai.timerDelay > 2.5f && (GetIsDebateIsPlaying() || GetIsInParliamentaryCouncil() || GetPlayerIsOnMysterytile(_activePlayer)))
		{
			if (GetIsDebateIsPlaying() || GetIsInParliamentaryCouncil())
			{
				SetParliamentaryIsDisappears(true);
			}
			else if (GetPlayerIsOnMysterytile(_activePlayer) && !GetPlayerHasTookMisteryAction(_activePlayer))
			{
				SetMysteryIsDisappears(true);
			}

			SetDiceIsRollingTrue();
			players[_activePlayer].ai.timerDelay = 0.f;
		}
	}

}

void ChooseAnIntersectionAI(unsigned char& _activePlayer)
{
	if (players[_activePlayer].isAnAI && (players[_activePlayer].isOnChoiceInterNB1 || players[_activePlayer].isOnChoiceInterNB2) && !players[_activePlayer].hasChosenWay)
	{
		unsigned char random = 0;
		random = rand() % 2;

		if (random == 0)
		{
			if (players[_activePlayer].isOnChoiceInterNB1)
			{
				players[_activePlayer].hasChosenWay = true;
				players[_activePlayer].isOnChoiceInterNB1 = false;
				players[_activePlayer].hasChosenShortCut1 = false;
			}
			else if (players[_activePlayer].isOnChoiceInterNB2)
			{

				players[_activePlayer].hasChosenWay = true;
				players[_activePlayer].isOnChoiceInterNB2 = false;
				players[_activePlayer].hasChosenShortCut2 = false;
			}

		}
		else
		{
			if (players[_activePlayer].isOnChoiceInterNB1)
			{
				players[_activePlayer].curIntersection = 6;
				players[_activePlayer].hasChosenWay = true;
				players[_activePlayer].isOnChoiceInterNB1 = false;
				players[_activePlayer].hasChosenShortCut1 = true;
				UpdateOrientationPlayers(_activePlayer);


			}
			else if (players[_activePlayer].isOnChoiceInterNB2)
			{
				players[_activePlayer].curIntersection = 14;
				players[_activePlayer].hasChosenWay = true;
				players[_activePlayer].isOnChoiceInterNB2 = false;
				players[_activePlayer].hasChosenShortCut2 = true;
				UpdateOrientationPlayers(_activePlayer);


			}
		}
	}
}

void EndTurnAI(unsigned char& _activePlayer, float& _dt)
{
	if (players[_activePlayer].isAnAI && !players[_activePlayer].isMoving && GetDiceHasRolling() && (!GetPlayerIsOnMysterytile(_activePlayer) || (GetPlayerIsOnMysterytile(_activePlayer) && players[_activePlayer].hasTookMysteryAction)) && !GetIsParliamentaryFinished() && !GetIsDenunciationPlaying() && !players[_activePlayer].ai.isPutsching && !GetIsBlackMailPlaying() && !GetDiceisAvailable() && players[_activePlayer].hasChooseToPaidTaxesOrNot && !GetTaxesButtonPressed() && !GetIsAnyCardDisplaying() && !players[_activePlayer].ai.canDrawACard && (!GetAIHasCardsInHand(_activePlayer) || (GetAIHasCardsInHand(_activePlayer) && (GetHasAlreadyPlayedCard() || GetIsCardEffectAlreadyResolved())) || (GetAIHasCardsInHand(_activePlayer) && GetNBCardsInHand(_activePlayer) == GetNbProblematicCardsInHand(_activePlayer))))
	{
		players[_activePlayer].ai.timerDelay += _dt;
		if (players[_activePlayer].ai.timerDelay > 0.3f)
		{
			if (players[_activePlayer].money < 0)
			{
				AddPlayerVoters(_activePlayer, -50);
			}
			players[_activePlayer].ai.timerDelay = 0.f;
			players[_activePlayer].hasFinishedTurn = true;
			setDiceHasRolling(false);

		}
	}
}

void ManageTaxesTileAI(float& _dt, unsigned char& _activePlayer)
{
	if (players[_activePlayer].isAnAI && players[_activePlayer].isOnTaxe && !players[_activePlayer].hasChooseToPaidTaxesOrNot && !GetTaxesButtonPressed())
	{
		unsigned char random = 0;
		players[_activePlayer].ai.timerDelay += _dt;

		if (players[_activePlayer].ai.timerDelay > 3.5f)
		{
			random = rand() % 3;
			if (random < 2 && players[_activePlayer].money >= 20000)
			{
				SetButtonYesTaxes();
				SetTaxIsDisappears(true);
			}
			else
			{
				SetButtonNoTaxes();
				SetTaxIsDisappears(true);
			}
			players[_activePlayer].hasTookMysteryAction = true;
			players[_activePlayer].ai.timerDelay = 0.f;
		}
	}
}

void ManageChanceCardsAI(unsigned char& _activePlayer, float& _dt)
{
	if (players[_activePlayer].isAnAI && GetChanceStackCanBeSelected() && !players[_activePlayer].isMoving && (GetTileType(players[_activePlayer].InitialposGrid.x, players[_activePlayer].InitialposGrid.y) == CHANCE || (GetPlayerIsOnMysterytile(_activePlayer) && !players[_activePlayer].hasTookMysteryAction && GetDiceHasRolling() && !GetDiceisAvailable() && (GetFirstDiceValue() == 2 || GetFirstDiceValue() == 3))) && !GetIsAnyCardDisplaying() && !GetIsInParliamentaryCouncil() && !GetIsDebateIsPlaying() && GetPlayerHasAlreadyMoved(_activePlayer))
	{
		SetAICanDrawACard(_activePlayer, true);
		TakeCardFromChanceStackAI();
		SetIsCardEffectAlreadyResolved(false);
	}

	if (players[_activePlayer].isAnAI && !players[_activePlayer].isMoving && (GetTileType(players[_activePlayer].InitialposGrid.x, players[_activePlayer].InitialposGrid.y) == CHANCE || (GetPlayerIsOnMysterytile(_activePlayer) && !players[_activePlayer].hasTookMysteryAction && (GetFirstDiceValue() == 2 || GetFirstDiceValue() == 3))) && GetIsAnyCardDisplaying() && GetPlayerHasAlreadyMoved(_activePlayer))
	{
		ManageChanceCardsChoiceAI(_dt);
	}
}

void ManageActionCardsAI(unsigned char& _activePlayer, float& _dt)
{
	if (players[_activePlayer].isAnAI && GetActionStackCanBeSelected() && !players[_activePlayer].isMoving && (GetTileType(players[_activePlayer].InitialposGrid.x, players[_activePlayer].InitialposGrid.y) == ACTION || (GetPlayerIsOnMysterytile(_activePlayer) && !players[_activePlayer].hasTookMysteryAction && GetDiceHasRolling() && !GetDiceisAvailable() && (GetFirstDiceValue() == 4 || GetFirstDiceValue() == 5))) && !GetIsAnyCardDisplaying() && !GetIsInParliamentaryCouncil() && !GetIsDebateIsPlaying() && GetPlayerHasAlreadyMoved(_activePlayer))
	{
		SetAICanDrawACard(_activePlayer, true);
		TakeCardFromActionStackAI();
		SetIsAIHasChosenActionCardButton(false);
		SetIsCardEffectAlreadyResolved(false);
	}

	if (players[_activePlayer].isAnAI && !players[_activePlayer].isMoving && (GetTileType(players[_activePlayer].InitialposGrid.x, players[_activePlayer].InitialposGrid.y) == ACTION || (GetPlayerIsOnMysterytile(_activePlayer) && !players[_activePlayer].hasTookMysteryAction && (GetFirstDiceValue() == 4 || GetFirstDiceValue() == 5))) && GetIsAnyCardDisplaying() && GetPlayerHasAlreadyMoved(_activePlayer))
	{
		ManageActionCardsChoiceAI(_dt);
	}
}

void PlayActionCards(unsigned char& _activePlayer, float& _dt)
{
	if (players[_activePlayer].isAnAI && !players[_activePlayer].isMoving && GetDiceHasRolling() && !GetDiceisAvailable() && players[_activePlayer].hasChooseToPaidTaxesOrNot && !GetTaxesButtonPressed() && !GetIsAnyCardDisplaying() && GetAIHasCardsInHand(_activePlayer) && !GetIsParliamentaryFinished())
	{
		ActionCardsManagerAI(_activePlayer, _dt);
	}
}

void PlayTrickDieCard(unsigned char& _activePlayer, float& _dt)
{
	if (players[_activePlayer].isAnAI && !players[_activePlayer].hasAlreadyMoved && GetNoOneIsMoving() && !GetIsAnyCardDisplaying() && !GetIsBlackMailPlaying() && !GetIsDenunciationPlaying() && !GetIsDebateIsPlaying() && !GetIsInParliamentaryCouncil())
	{
		ManageTrickDieAI(_activePlayer, GetIsTrickDieInHand(_activePlayer), _dt);
	}
}

void ManageBlackMailAI(unsigned char& _targetPlayer, float& _dt)
{
	if (players[_targetPlayer].isAnAI && GetIsBlackMailPlaying())
	{
		BlackMailResponseAI(_dt);
	}
}

void ManageMuzzleAI(unsigned char& _targetPlayer, float& _dt)
{
	if (players[_targetPlayer].isAnAI && GetIsDenunciationPlaying())
	{
		DenunciationResponseAI(_targetPlayer, _dt);
	}
}

void ManagePutschAI(unsigned char& _activePlayer, float& _dt)
{
	if (players[_activePlayer].isAnAI && GetPutschIsAvailable(_activePlayer) && !players[_activePlayer].ai.isPutsching)
	{
		players[_activePlayer].ai.timerDelay += _dt;
		if (players[_activePlayer].ai.timerDelay > 0.5f)
		{
			SetPlayerIsPutsching(_activePlayer);
			players[_activePlayer].ai.isPutsching = true;
			players[_activePlayer].ai.timerDelay = 0.f;
		}
	}
}

