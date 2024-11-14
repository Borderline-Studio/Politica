#ifndef PLAYERS_GESTION_H
#define PLAYERS_GESTION_H

#include "Common.h"
#include"Animation.h"
#include"Audio.h"

#define NB_ANIMATIONS 4
#define NB_INTERSECTIONS 21
#define NB_ARROWS 4
#define NB_TILE_SHINING 2


enum Direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};
enum ArrowType
{
	DOWN_NB1_ARR,
	DOWN_NB2_ARR,
	RIGHT_ARR,
	LEFT_ARR

};

enum ShortCutChoice
{
	SHORTCUT,
	NORMAL
};

struct Intersection
{
	sf::Vector2f pos;
	sf::Vector2f posGrid;
};

struct AI
{
	float timerDelay = 0.f;
	bool canDrawACard = true;
	bool isPutsching = false;
	bool mysteryActionPlaying = false;
};

struct SpriteSorting
{
	sf::Vector2f pos;
	int playerIndex = 0;
};

struct Player
{
	sf::Sprite sprite;
	sf::Sprite spriteArrow;

	bool characterSelected = false;
	bool isReady = false;
	unsigned char characterChosen = 0;
	std::string name;

	bool hasFinishedTurn = false;
	sf::Vector2f pos;
	sf::Vector2f spriteOffset;

	sf::Vector2f initialPos;
	Direction dir = (Direction) 0;
	bool isMoving = false;
	int nbTilesMoving = 0;
	bool hasAlreadyMoved = false;

	bool isOnChoiceInterNB1 = false;
	bool isOnChoiceInterNB2 = false;
	bool hasChosenWay = false;
	bool hasChosenShortCut1 = false;
	bool hasChosenShortCut2 = false;
	bool isOnShortCut1 = false;
	bool isOnShortCut2 = false;

	bool isOnTaxe = false;
	bool isOnMysteryTile = false;
	bool isInParliamentaryCouncil = false;
	bool isOnParliamentaryCouncilTile = false;
	bool hasTookMysteryAction = false;

	int money = 0;
	int voters = 0;
	int reputation = 0;
	unsigned char taxes = 0;
	bool hasChooseToPaidTaxesOrNot = false;

	float timer = 0;
	int curIntersection = 0;
	bool intersectionReached = false;

	bool goingToFiscalControl = false;
	bool goingToStartSquare = false;
	bool reverseMove = false;
	
	sf::Vector2f nextPosGrid;
	sf::Vector2f InitialposGrid;

	unsigned char dicesValue = 0;

	bool isAnAI = false;
	AI ai;

	std::vector<sf::Vector2i> dicesVector;
};


struct ChoiceArrow
{
	sf::Sprite sprite;
	sf::Vector2f pos;
	sf::Vector2f isoPos;
	sf::Vector2f posGrid;
	sf::Image image;

};

struct TileShining
{
	sf::Sprite sprite;
	sf::Vector2f pos;
	sf::Vector2f isoPos;
	sf::Vector2f posGrid;
	Animation anim;
};

void InitPlayersGestion(void);
void InitPlayersGestionSprites(void);
void InitIntersections(void);
void InitPlayersChoiceArrow(void);
void UpdatePlayers(GameData& _gameData);
void UpdateIsOnShortCut(unsigned char& _activePlayer);
void UpdateReverseMoveShortCut(unsigned char& _activePlayer);
void MovePlayers(GameData& _gameData, unsigned char& _activePlayer);
void UpdateChoiceIntersection(unsigned char& _activePlayer, float& _dt);
void UpdatePlayerGoingToFiscalControl(unsigned char& _activePlayer);
void UpdatePlayerGoingToStartSquare(unsigned char& _activePlayer);
void UpdateFinishMovement(unsigned char& _activePlayer);
void UpdateCurrentIntersection(unsigned char& _activePlayer);
void UpdateNextMovePlayer(unsigned char& _activePlayer);
void UpdatePlayerMovesAccordingToDir(unsigned char& _activePlayer);
void UpdatePlayerMoveCerp(float _dt, unsigned char& _activePlayer);
void UpdatePlayerMystery(unsigned char& _activePlayer);
void UpdateParliamentaryCouncil(unsigned char& _activePlayer);
void DoubleResestMystery();
void DoubleResestParliamentaryCouncil();
void UpdateSpiteSort(void);
void UpdateTurningPointMovement(unsigned char& _activePlayer);
void ResetReverseMove(unsigned char& _activePlayer);
void UpdateOrientationPlayers(unsigned char& _activePlayer);
void DisplayPlayers(sf::RenderWindow& _window);

void MousePressedPlayers(sf::Event& _event, unsigned char& _activePlayer);

void KeyPressedPlayers(sf::Event _event);

void SortDicesVectorDiceValue(std::vector<sf::Vector2i>& _vector, int _size);
void SortDicesVectorReputation(std::vector<sf::Vector2i>& _vector,int _start, int _end);
void ParliamentaryDistributeVoters(std::vector<sf::Vector2i> _vector);

void UpdateChoiceArrow(float& _dt, unsigned char& _activePlayer);

void DisplayChoiceArrowAfterPlayers(sf::RenderWindow& _window, unsigned char& _activePlayer);

void DisplayChoiceArrowBeforePlayers(sf::RenderWindow& _window, unsigned char& _activePlayer);

void ChoosingAWayOnIntersection(sf::Keyboard::Key _key, unsigned char& _activePlayer);



void LaunchDicesAI(unsigned char& _activePlayer, float& _dt);

void ChooseAnIntersectionAI(unsigned char& _activePlayer);

void EndTurnAI(unsigned char& _activePlayer, float& _dt);

void ManageTaxesTileAI(float& _dt, unsigned char& _activePlayer);

void ManageChanceCardsAI(unsigned char& _activePlayer, float& _dt);

void ManageActionCardsAI(unsigned char& _activePlayer, float& _dt);

void PlayActionCards(unsigned char& _activePlayer, float& _dt);

void PlayTrickDieCard(unsigned char& _activePlayer, float& _dt);


#endif


