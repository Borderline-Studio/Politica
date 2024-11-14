#ifndef CHARACTER_SELECTION_H

#define CHARACTER_SELECTION_H

#include "Common.h"
#include "Animation.h"
#include "Audio.h"

#define NAME_LIMIT 20
#define NB_BUTTONS_CS 2
#define NB_BUTTONS_NBP 4

enum ButtonCS
{
	READY,
	PLAY_CS
};

enum ButtonNBPlayers
{
	NO_AI,
	ONE_AI,
	TWO_AI,
	THREE_AI
};

struct NameModification
{
	bool enteringName = false;
	std::string string;
	sf::Text text;
};

struct Selector
{
	sf::Sprite sprite;
	bool isSelected;
};

struct CharacterSelection
{
	sf::Sprite avatarSprite[NB_CHARACTERS];

	sf::Texture selectorTexture;
	Selector selector[NB_CHARACTERS];

	sf::Sprite nameRect[NB_CHARACTERS];

	sf::Sprite modifyRectSprite;

	sf::Sprite background;

	sf::Texture nameSelectionAreaTexture;
	sf::Sprite nameSelectionAreaSprite;
	Animation animationNameModif;
	bool nameModifIsSelected;

	Fade fade;
	std::vector<Button> buttonList;
	NameModification names[NB_CHARACTERS];

	unsigned char playerChoosing = 0;
	unsigned char AIChoosing = 0;

	sf::Text playerSelectionText;
	std::string playerSelectionString;

	unsigned char currentButton = 0;

	sf::Text playerReadyText[NB_CHARACTERS];
	sf::Text readyText[NB_CHARACTERS];

	unsigned char music;
};

struct NBPlayersSelection
{
	std::vector<Button> buttonList;
	unsigned char nbAI = 0;
	bool goingToCS = false;
	bool isOnCS = false;
	sf::View camera;
	sf::Text text;
	char buttonSelected = 0;
};

struct CharacterSelectionSound
{
	unsigned char characterSelected;
};

void InitCharacterSelection(GameData& _gameData);

void InitAvatars(std::string& _path);

void InitCharacterSelectionBackground(std::string& _path);

void InitCharacterSelectionPlayerReadyText(void);

void InitAvatarsPosition(void);

void InitAvatarsSelectedRect(std::string _path);

void InitAvatarsSprites(std::string& _path);

void InitCharacterSelectionButton(void);

void InitAvatarsNamesSprites(std::string& _path);

void InitNameModification(std::string& _path);

void InitNBPlayersSelection(std::string& _path);

void FadeCharacterSelection(GameData& _gameData, float _maxVolume = 25.f, float _speedPerSec = 1.f);

void UpdateButtonsCS(float& _dt);

void UpdateNBPlayersSelection(float& _dt);

void UpdateNBPlayersSelectionButtons(void);

void UpdateCharacterSelection(GameData& _gameData);

void DisplayCharacterSelection(sf::RenderWindow& _window);

void DisplayAvatars(sf::RenderWindow& _window);

void DisplayNames(sf::RenderWindow& _window);

void DisplayPlayerReadyTexts(sf::RenderWindow& _window);

void DisplayNBPlayersSelection(sf::RenderWindow& _window);

void KeyPressedNBPlayersSelection(GameData& _gameData);

void CheckMouseButtonCollisionCharacterSelection(sf::Event::MouseMoveEvent& _buttonEvt);

void CheckMouseButtonCollisionNBPlayersSelection(sf::Event::MouseMoveEvent& _buttonEvt);

void SetCharacterSelectedByPlayer(unsigned char& _i);

void CollisionMouseButtonCS(sf::Vector2f& _mouse);

void CollisionMouseButtonNBPlayersSelection(sf::Vector2f& _mouse);

void ResetCharacterSelectionOnClick(sf::Vector2f& _mouse);

void ConfirmCharacterSelection(sf::Vector2f& _mouse);

void MousePressedCharacterSelection(GameData& _gameData);

void MouseMovedCharacterSelection(sf::Event::MouseMoveEvent& _buttonEvt);

void EraseLetterModifiedName(GameData& _gameData);

void WriteToModifyName(GameData& _gameData);

void KeyPressedCharacterSelection(GameData& _gameData);

void ChangeGameStateKeyPressed(GameData& _gameData);

void EnterToValidateNameOrCharacter(GameData& _gameData);

void SetCharacterLockedAndUpdateCurrentPlayer(void);

#endif // !CHARACTER_SELECTION_H


