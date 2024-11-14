#ifndef HUD_H
#define HUD_H

#include "Common.h"
#include "Animation.h"
#include "Audio.h"

#define NB_LINES_RULES 37
#define INTERLINE_SPACE 70

struct Putsch
{
	bool isAvailable;
	bool isPutsching;
	unsigned char hasSucceeded;
	int value;
};

struct HUD
{
	Putsch putsch[NB_PLAYERS];

	Button endTurnButton;

	sf::Texture openRulesTexture;
	Button openRulesButton;
	sf::Texture closeRulesTexture;
	Button closeRulesButton;
	sf::Texture leftArrowTexture;
	Button leftArrowButton;
	sf::Texture rightArrowTexture;
	Button rightArrowButton;

	Button dicesButton;
	Button putschButton;

	bool areRulesDisplaying = false;
	sf::Texture rulesTexture;
	sf::Sprite rulesSprite;

	sf::Sprite taxeLetter;
	Button buttonNo;
	Button buttonYes;
	sf::Text notEnoughtMoneys;
	bool showNotEnoughtMoneys = false;
	float timer = 0;

	sf::Font rulesFont;
	sf::Text rulesText[NB_LINES_RULES];
	sf::Text nbSheetRulesText;
	int rulesSheet = 0;

	sf::Sprite putschTextBackground;
	sf::Text putschText;

	sf::Sprite timelineSprite;
	sf::Sprite whiteSquareSprite;

	sf::Sprite malusIcon;
	sf::Sprite bonusIcon;
	sf::Sprite chanceIcon;
	sf::Sprite actionIcon;
	sf::Sprite taxIcon;
	sf::Sprite breakIcon;
	sf::Sprite parliamentIcon;
	sf::Sprite examenIcon;
	sf::Sprite controlIcon;
	sf::Sprite salaryIcon;
	sf::Sprite mysteryIcon;
	sf::Sprite reputationIcon;
	sf::Sprite putschIcon;
	sf::Sprite votersIcon;

	int turnPageSound;

	sf::Sprite cardSprite;
	sf::Sprite playerIcon[4];
	sf::Text playerPseudo[4];
	sf::Text playerReward[4];
	float parliamentaryResultsTimer;
	bool isParliamentaryFinished;

	sf::Texture cardTexture;
	bool lastButton = 0;
};

void InitButtons();
void InitTexts();
void InitTimeline();
void InitIcons();
void InitParliamentaryResults();
void InitHUD();

void ReloadHud(void);

void CheckMouseButtonCollisionHUD();
void UpdateRules(float& _dt);
void UpdateButtonsHUD(float&);
void UpdatePutsch();
void UpdateParliamentaryResults(float&);
void UpdateHUD(float&);
void UpdateTaxScale(float& _dt);

void DisplayRulesButtons(sf::RenderWindow&);
void DisplayRulesTexts(sf::RenderWindow&);
void DisplayIcons(sf::RenderWindow&);
void DisplayRules(sf::RenderWindow&);

void DisplayEndTurn(sf::RenderWindow&);
void DisplayButtons(sf::RenderWindow&);
void DisplayTimeline(sf::RenderWindow&);
void DisplayPutsch(sf::RenderWindow&);
void DisplayParliamentaryResults(sf::RenderWindow&);
void DisplayHUD(sf::RenderWindow&);

void MousePressedRules(sf::Event, GameData&);
void MousePressedHUD(sf::Event, GameData&);

void MouseMovedHUD();

void KeyPressedRules(sf::Event&, GameData&);

void ReloadHud(void);

#endif
