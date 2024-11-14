#ifndef  COMMON_H

#define COMMON_H

#include "Utils.h"

#define LINE_GRID 17 
#define COLUMN_GRID 17
#define MAX_LINE_GAMEBOARD 13
#define MAX_COLUMN_GAMEBOARD 15
#define OFFSET_GRID_LINE 2
#define OFFSET_GRID_COLUMN 1
#define NB_CHARACTERS 4
#define NB_PLAYERS 4
#define MAX_TURN 20
#define NB_INIT 9
#define NB_DICES 3

#define HITBOX_WIDTH GetScreen().width * 0.1823f
#define HITBOX_HEIGHT GetScreen().height * 0.0926f

enum PlayersNumber
{
	PLAYER_1,
	PLAYER_2,
	PLAYER_3,
	PLAYER_4
};

enum CharactersNames
{
	MARGARET_TCHATCHEUR,
	RONALD_RAYBAN,
	JV_FRANCO,
	VLAD_INPUT
};

enum Stats
{
	MONEY,
	REPUTATION,
	VOTERS,
	TAX
};

enum KeyBindingsName
{
	KB_DICES,
	KB_ENDTURN,
	KB_SHORTCUT,
	KB_NWAY
};

enum TileType
{
	GRASS,
	START,
	BONUS_MONEY,
	BONUS_REPUTATION,
	BONUS_VOTERS,
	BONUS_MONEY_SHORTCUT,
	BONUS_REPUTATION_SHORTCUT,
	BONUS_VOTERS_SHORTCUT,
	REPUTATION_MONEY,
	REPUTATION_VOTERS,
	REPUTATION_MONEY_SHORTCUT,
	REPUTATION_VOTERS_SHORTCUT,
	MALUS_MONEY,
	MALUS_REPUTATION,
	MALUS_VOTERS,
	MALUS_MONEY_SHORTCUT,
	MALUS_REPUTATION_SHORTCUT,
	MALUS_VOTERS_SHORTCUT,
	ACTION,
	CHANCE,
	MYSTERY,
	TAX_AUDIT,
	PARLIAMENTARY_COUNCIL,
	BREAK,
	EXAM,
	SALARY,
	TAXES
};

enum GameState
{
	PREMENU,
	MENU,
	CHARACTER_SELECTION,
	GAME,
	PAUSE,
	GAMEOVER,
	SETTINGS,
	CREDITS,
	RULES
};

enum CardButtonType
{
	BUTTON_DISCARD,
	BUTTON_KEEP,
	BUTTON_USE,
	BUTTON_NO,
	BUTTON_YES
};

enum Chien
{
	CHIEN,
	SUCCESS,
	FAIL
};

struct VectorRoads
{
	std::vector<sf::Vector2f> mainRoad1;
	std::vector<sf::Vector2f> shortcutRoad1;
	std::vector<sf::Vector2f> mainRoad2;
	std::vector<sf::Vector2f> shortcutRoad2;
};

struct Animation
{
	float timer;
	int maxFrame;
	int currentFrame;
	sf::Vector2u frameSize;
	bool upToDownFinished;
	bool isPlaying;
	bool isLooping;
	bool isAssigned;
	sf::IntRect rect;
	int linePlaying;
	int maxLine;
	float resetAnimTime;

};

struct Button
{
	sf::Texture* texture = NULL;
	sf::Sprite sprite;
	sf::Vector2u size;
	sf::Vector2f pos;
	std::vector<Animation> animation;
	CardButtonType type = (CardButtonType)0;
	bool isSelected = false;
	bool canBeSelected = false;
	bool isPressed = false;
};

struct GameData
{
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock dtClock;
	float dt;
	int gameState;
	int lastState;
	float loadingScreenCompteur;
	bool loadingScreenFinish;
};

int GetTileWidth(void);
Button CreateButton(std::string _file, float _y, bool _isCentered, sf::Vector2f _scale = ScaleToScreen(1.f, 1.f), float _x = GetScreen().width / 2, unsigned char _nbFramesX = 3);
void SetAlphaMenu(float _alpha = 0.f);
void SetFadeMenuOn(void);
void SetAlphaCharacterSelection(float _alpha = 0.f);
std::string GetPlayerName(unsigned char _i);
unsigned char GetNbAI(void);
void SetAlphaFadeGame(float _alpha = 0.f);
void SetGridType(int _line, int _column, int _type);
int GetTileType(int _line, int _column);
float GetSoundMultiplier(void);
sf::Font& GetSettingsFont(void);
void SetLastState(GameData& _gameData);
sf::Keyboard::Key GetKey(int _i);
std::string GetKeyText(int _i);
bool GetAnyButtonIsPressed(void);
void SetAllButtonsNotSelectedNotPressedKB(void);
void SetGameFadeOut(bool _fadeOut);
bool GetGameFadeOut(void);
unsigned char& GetActivePlayer(void);
void SetActivePlayer(unsigned char& _i);
unsigned char GetNbTurns(void);
unsigned char GetNbTurns4Players(void);
void UpdateTilesAction(sf::Vector2f _gridPos, int _playerIdx);
bool GetDiceHasRolling(void);
void setDiceHasRolling(bool _value);
bool GetDiceisAvailable(void);
int GetMenuMusic();
bool GetDiceIsRolling(void);
void DisplayLoadingScreen(GameData& _gameData);
void SetLoadingScreenText(const sf::String& _string);
VectorRoads GetVectorRoad(void);
int GetButtonPressSound();
int GetButtonSelectSound();

//playerCommon
void SetPlayerReady(unsigned char _i, bool _isReady);
bool GetPlayerReady(unsigned char _i);
void SetPlayerCharacterSelected(unsigned char _i, bool _characterSelected);
bool GetCharacterSelectedBool(unsigned char _i);
sf::Color GetPlayerColor(unsigned char _i);
bool GetAllPlayersReady(void);
bool GetPlayerIsMoving(unsigned char _i);
sf::Vector2f GetPlayerPosGrid(unsigned char _i);
int GetPlayerMoney(unsigned char _i);
int GetPlayersReputation(unsigned char _i);
int GetPlayersVoters(unsigned char _i);
void AddPlayerMoney(unsigned char _i, int _money);
void AddPlayerReputation(unsigned char _i, int _reputation);
void AddPlayerVoters(unsigned char _i, int _voters);
void SetPlayerIsMoving(unsigned char _i, bool _bool);
void SetPlayerNBTilesMoving(unsigned char _i, int _nbTiles);
bool GetNoOneIsMoving(void);
void AddTaxes(unsigned char _i, char _nbTaxes);
int GetNbTaxes(unsigned char _i);
void SetPlayerReverseMove(unsigned char _i, int _nbTilesMoving);
void SetPlayerMovingToFiscalControl(unsigned char _i);
void SetPlayerMovingToStartSquare(unsigned char _i);
void SetPlayerMoveForward(unsigned char _i, int _nbTilesMoving);
void SetPlayerCharacterChosen(unsigned char _player, unsigned char _character);
unsigned char GetPlayerCharacterChosen(unsigned char _i);
bool GetPlayerHasFinishedTurn(unsigned char _activePlayer);
sf::Vector2f GetGridOffset(void);
sf::Vector2f GetCell(int _line, int _column, int _z);
void SetPlayerHasFinishedTurn(int _i, bool _finishedTurn);
int GetFirstDiceValue();
int GetSecondDiceValue();
int GetThirdDiceValue();
unsigned char GetAnyDiceValue(unsigned char _i);
bool GetLaunchedDices(void);
void SetDiceIsSelected(unsigned char _i, bool _bool);
bool GetDiceIsSelected(unsigned char _i);
void SetDicesNbSelected(unsigned char _i);
unsigned char GetDicesNbSelected(void);
void SetLaunchedDices(int);
void SetDiceIsRollingTrue(void);
sf::Vector2f GetPlayerPos(int _i);
bool GetPlayerHasChooseToPaidTaxesOrNot(unsigned char _i);
void SetPlayerHasAlreadyMoved(unsigned char _i, bool _bool);
bool GetPlayerHasAlreadyMoved(unsigned char _i);
void SetPlayerHasChooseToPaidTaxesOrNot(unsigned char _i, bool _bool);
int GetPlayerNbTilesMoving(unsigned char _i);
bool GetHudAreRulesDisplaying();
bool GetPlayerIsOnTaxe(unsigned char _i);
void SetPlayerIsOnTaxe(unsigned char _i, bool _bool);
void SetPlayerIsOnMysterytile(unsigned char _i, bool _bool);
bool GetPlayerIsOnMysterytile(unsigned char _i);
void SetIsInParliamentaryCouncil(bool _bool);
bool GetIsInParliamentaryCouncil();
void SetPlayerIsOnParliamentarytile(unsigned char _i, bool _bool);
bool GetPlayerIsOnParliamentarytile(unsigned char _i);
bool GetPlayerIsAnAI(unsigned char _i);
void SetPlayerIsAnAI(unsigned char _i, bool _bool);
void SetNoOneIsMoving(bool _bool);
bool GetPlayerHasTookMisteryAction(unsigned char _i);
bool GetPlayerIsOnChoiceIntersection(unsigned char _i);
unsigned char& GetParliamentaryCouncilSound(void);
bool GetPlayerHasChosenWay(unsigned char _i);
bool GetAICanDrawACard(unsigned char _i);
void SetAICanDrawACard(unsigned char _i, bool _bool);
void SetPlayerName(unsigned char _i, std::string _name);
void setDiceisAvailable(bool _value);
void SetPlayerHasTookMysteryAction(unsigned char _i, bool _bool);
std::string GetPlayerPseudo(unsigned char _i);
bool GetPlayerGoingToFiscalControl(unsigned char _i);
void SetLastPlayerPlayed(unsigned char _i);
unsigned char& GetLastPlayerPlayed(void);
void SetDicesValue(unsigned char _i, unsigned char _amount);
unsigned char GetDicesValue(unsigned char _i);
Button& GetDicesButton();
void SetButtonYesTaxes();
void SetButtonNoTaxes();
bool GetPlayerReplaying();
void SetPlayerReplaying(bool _bool);
void SetDicesRiggedValue(unsigned char _value);
unsigned char GetRiggedDicesValue(void);
void ResetRiggedDices(void);
bool GetTaxesButtonPressed(void);
bool GetPutschIsAvailable(unsigned char& _activePlayer);
bool GetPlayerIsPutsching(unsigned char& _activePlayer);
void SetPlayerIsPutsching(unsigned char& _activePlayer);
void ManageBlackMailAI(unsigned char& _targetPlayer, float& _dt);
void ManageMuzzleAI(unsigned char& _targetPlayer, float& _dt);
void ManagePutschAI(unsigned char& _activePlayer, float& _dt);
float GetThirdDiceMaxTimerRoll();
void SetIsParliamentaryFinished(bool);
int GetParliamentaryPlayerOrder(int);
void SetMysteryActionPlayingAI(unsigned char& _activePlayer, bool _bool);
bool GetIsParliamentaryFinished();
void SetHUDPlayerPseudo();
void SetHUDPlayerIcon();
void ClearDicesVector();
unsigned char GetPlayerCurrentIntersection(unsigned char& _i);
unsigned char GetPlayerDir(unsigned char& _i);
bool GetIsPlayerReverseMoving(unsigned char& _i);
bool GetPlayerIsOnShortcut1(unsigned char& _i);
bool GetPlayerIsOnShortcut2(unsigned char& _i);
bool GetPlayerGoingToStartSquare(unsigned char& _i);
bool GetMysteryActionPlaying(unsigned char& _i);
void SetPlayerVoters(unsigned char& _i, unsigned short int _voters);
void SetPlayerMoney(unsigned char& _i, unsigned int _money);
void SetPlayerReputation(unsigned char& _i, int _reputation);

//Hud player

void SetTextStat(unsigned char _playerID, int _changeStat, Stats _stats);
bool GetHudPlayerIsMoving();
void SetHudPlayerIsMoving(unsigned char _playerID, bool _isMovinging);
void SetParliamentaryIsAppears(bool _isAppears);
void SetParliamentaryIsDisappears(bool _isDisappears);
void SetMysteryIsAppears(bool _isAppears);
void SetMysteryIsDisappears(bool _isDisappears);
void SetPseudoInInsert(unsigned char _player);

//Attention peut faire crash
unsigned char GetTargetPlayer();
unsigned int GetHudPlayerSpeed();
sf::Vector2f GetHudPlayerOrigin(unsigned char _playerID);
bool GetHudPlayerIsDown();
bool GetHudPlayerActivePlayerCollision();
bool GetHudPlayerNoneActivePlayerCollision();
bool GetParliamentaryIsDisappears();
bool GetMysteryIsDisappears();
void SetCaricatureHudPlayer();
int GetPlayerHasSucceededPutsch(int);

// Cards Accessor
bool GetIsACardSelected();
bool GetIsMischievousDiceIsPlaying();
bool GetIsDebateIsPlaying();
bool GetIsTrickDieIsPlaying();
bool GetChanceStackCanBeSelected();
bool GetActionStackCanBeSelected();
bool GetAIHasCardsInHand(unsigned char _i);
bool GetIsAnyCardDisplaying(void);
bool GetHasAlreadyPlayedCard(void);
char GetIsTrickDieInHand(unsigned char& _activePlayer);
bool GetIsMuzzleInHand(unsigned char& _activePlayer);
unsigned char GetNBCardsInHand(unsigned char& _activePlayer);
bool GetIsCardIsPlaying(void);
bool GetIsBlackMailPlaying(void);
bool GetIsDenunciationPlaying(void);
bool GetInsertIsDisplay(void);
bool GetIsTrickDieAIResolved(void);
unsigned char GetNbProblematicCardsInHand(unsigned char& _activePlayer);
unsigned char& GetTargetPlayerAI(void);
bool GetTrickDiePlayedThisTurn(void);
sf::Vector2f& GetActionStackPosition();
bool GetIsCardEffectAlreadyResolved(void);
sf::Vector2f& GetChanceStackPosition();
// Cards Mutator
void SetChanceStackCanBeSelected();
void SetActionStackCanBeSelected();
void SetIsMischievousDiceIsPlaying(bool _bool);
void SetIsDebateIsPlaying(bool _bool);
void SetIsTrickDieIsPlaying(bool _bool);
void SetIsCardEffectAlreadyResolved(bool _bool);
void SetHasAlreadyPlayedCard(bool _bool);
void SetIsAIHasChosenActionCardButton(bool _bool);
void SetIsTrickDieAIResolved(bool _bool);
void SetTrickDiePlayedThisTurn(bool _bool);

// Cards Artificial Intelligence
void TakeCardFromActionStackAI(void);
void TakeCardFromChanceStackAI(void);
void ManageChanceCardsChoiceAI(float& _dt);
void ManageActionCardsChoiceAI(float& _dt);
void ActionCardsManagerAI(unsigned char& _activePlayer, float& _dt);
void ManageTrickDieAI(unsigned char& _activePlayer, char _index, float& _dt);
void BlackMailResponseAI(float& _dt);
void DenunciationResponseAI(unsigned char& _activePlayer, float& _dt);


//reload
void Reload(void); //global reload
void ReloadNewGame(void);
void ReloadCharacterSelection(void);
void ReloadCredits(void);
void ReloadGameFade(void);
void ReloadMenu(void);
void ReloadPause(void);
void ReloadSettings(void);
void InitPlayers(void);
void ReloadPlayersNewGame(void);
void InitTurnManager(void);
void ReloadKeyBindings(void);
void ReloadGameOver(void);

//Particle
void InitFireWork();
void AddParticleHud(sf::Vector2f& _hudPlayerPos);
void UpdateFireWork(float& _dt);
void UpdateParticleHudPlayer(float& _dt);
void UpdateParticleGameOver(float& _dt);
void DrawParticleHudPlayer(sf::RenderWindow& _window);
void DrawParticleGameOver(sf::RenderWindow& _window);
void AddParticleStack(sf::Vector2f& _hudPos);

//HUD
void SetTaxIsAppears(bool _isAppears);
void SetTaxIsDisappears(bool _isDisappears);
#endif // ! GAMESTATE_H
