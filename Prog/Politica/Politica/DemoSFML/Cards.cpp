#include "Cards.h"

std::vector<Card> actionCardsStack;
std::vector<Card> chanceCardsStack;
std::vector<Card> actionDiscard;
std::vector<Card> chanceDiscard;
std::vector<Card> cardList;
std::vector<std::vector<Card>> playersCards;

Stack stackAction;
Stack stackChance;

Button cardButtonList[NB_CARD_BUTTONS];

CardType typeActiveCard;
CardType typeActiveStack;
CardButtonType lastButtonPressed;

bool isACardSelected = 0;
bool isACardIsPlaying = 0;
bool isDenunciationIsPlaying = 0;
bool isBlackmailIsPlaying = 0;
bool isMischievousDiceIsPlaying = 0;
bool isDebateIsPlaying = 0;
bool isTrickDieIsPlaying = 0;
bool isCardAppears = 0;
bool isCardDisappears = 0;
bool isInsertAppears = 0;
bool isInsertDisappears = 0;
bool isTargetInsertDisappears = 0;
bool isAnyCardDisplaying = 0;
bool isCardEffectAlreadyResolved = 0;
bool isAIHasChosenActionCardButton = 0;
bool trickDieAIResolved = 1;
bool lastDicesResultWasADouble = 0;

Insert targetSelectionInsert;
Insert muzzleInsert;
Insert blackmailInsert;

unsigned char targetPlayer;

sf::Text targetSelectionText;
sf::Text MuzzleText[NB_MUZZLE_TEXTS];
sf::Text blackmailText[NB_BLACKMAIL_TEXTS];

unsigned char cardSounds[NB_CARD_SOUNDS];

float timerScaleCards = 0;
float timerScaleTargetInsert = 1;

// AI
float timerCardChoiceAI = 0;
float timerPlayCard = 0.f;
bool isOkay = false;
bool hasAlreadyPlayedCard = false;
bool IsAIpayingTax = false;
unsigned char randomCard = 254;
float timerPlayTrickDie = 0.f;
unsigned char randomDice = 254;
unsigned char randomDice2 = 254;
unsigned char randomBlackMail = 0;
float timerBlackMailAI = 0.f;
float timerMuzzleAI = 0.f;
unsigned char launchingAttackPlayer = 5;
bool callAFriendAIBool = 0;


// Init
void InitCards()
{
	InitCardStack(stackAction, "Assets/Images/Cards/ActionBackside.png", "Assets/Images/Cards/ActionBacksideCanBeSelected.png", "Assets/Images/Cards/ActionBacksideSelected.png", GetScreen().width * 0.89f, GetScreen().height * 0.79f);
	InitCardStack(stackChance, "Assets/Images/Cards/ChanceBackside.png", "Assets/Images/Cards/ChanceBacksideCanBeSelected.png", "Assets/Images/Cards/ChanceBacksideSelected.png", GetScreen().width * 0.11f, GetScreen().height * 0.79f);
	InitCardStackType();
	InitActionCards();
	InitChanceCards();
	MixUpCards(actionCardsStack);
	MixUpCards(chanceCardsStack);
	InitPlayerCards();
	InitCardButton();
	InitInserts();
	InitInsertTexts();
	InitCardSounds();
}

void ReloadCards(void)
{
	for (unsigned char i = 0; i < NB_PLAYERS; i++)
	{
		while (!playersCards[i].empty())
		{
			SwapCardFromVectorToVector(playersCards[i], actionDiscard);
		}
	}
	while (!actionCardsStack.empty())
	{
		SwapCardFromVectorToVector(actionCardsStack, actionDiscard);
	}

	while (!chanceCardsStack.empty())
	{
		SwapCardFromVectorToVector(chanceCardsStack, chanceDiscard);
	}

	ResetCardStack(actionCardsStack, stackAction);
	ResetCardStack(chanceCardsStack, stackChance);
	UnDrawCardButtons();
	UnDrawInsertButtons();

	isACardSelected = 0;
	isACardIsPlaying = 0;
	isDenunciationIsPlaying = 0;
	isBlackmailIsPlaying = 0;
	isMischievousDiceIsPlaying = 0;
	isDebateIsPlaying = 0;
	isTrickDieIsPlaying = 0;
	isCardAppears = 0;
	isCardDisappears = 0;
	isInsertAppears = 0;
	isInsertDisappears = 0;
	isTargetInsertDisappears = 0;
	isAnyCardDisplaying = 0;
	isCardEffectAlreadyResolved = 0;
	isAIHasChosenActionCardButton = 0;
	trickDieAIResolved = 1;
	lastDicesResultWasADouble = 0;
	callAFriendAIBool = 0;

	timerScaleCards = 0;
	timerScaleTargetInsert = 1;
	timerCardChoiceAI = 0;

	timerPlayCard = 0.f;
	isOkay = false;
	hasAlreadyPlayedCard = false;
	randomCard = 254;
	timerPlayTrickDie = 0.f;
	randomDice = 254;
	randomDice2 = 254;
	randomBlackMail = 0;
	timerBlackMailAI = 0.f;
	timerMuzzleAI = 0.f;
	launchingAttackPlayer = 5;

	stackAction.canBeSelected = false;
	stackChance.canBeSelected = false;
}

void InitCardStack(Stack& _cardStack, std::string _file, std::string _file2, std::string _file3, float _posX, float _posY)
{
	_cardStack.texture[STACK].loadFromFile(_file);
	_cardStack.texture[STACK_CAN_BE_SELECTED].loadFromFile(_file2);
	_cardStack.texture[STACK_SELECTED].loadFromFile(_file3);
	_cardStack.sprite.setTexture(_cardStack.texture[STACK]);
	_cardStack.size = _cardStack.texture[STACK].getSize();
	sf::Vector2f origin = { _cardStack.size.x / 2.f, _cardStack.size.y / 2.f };
	_cardStack.sprite.setOrigin(origin);
	_cardStack.sprite.setScale(ScaleToScreen(1.f, 1.f));
	_cardStack.pos = { _posX, _posY };
	_cardStack.sprite.setPosition(_cardStack.pos);
	_cardStack.canBeSelected = false;
	_cardStack.isSelected = false;
}

void InitCardStackType(void)
{
	stackAction.type = ACTION_CARD;
	stackChance.type = CHANCE_CARD;
}

Card CreateCard(std::string _file, CardType _type, bool _canBeKept)
{
	Card temp;
	temp.texture = new sf::Texture;
	temp.texture->loadFromFile(_file);
	temp.sprite.setTexture(*temp.texture);
	temp.type = _type;
	sf::Vector2f origin = { temp.texture->getSize().x / 2.f, temp.texture->getSize().y / 2.f };
	temp.sprite.setOrigin(origin);
	temp.sprite.setScale(ScaleToScreen(1.f, 1.f));
	temp.pos = { GetScreen().width / 2.f, GetScreen().height / 2.f };
	temp.sprite.setPosition(temp.pos);

	temp.canBeKept = _canBeKept;
	temp.isDisplay = false;
	temp.isSelected = false;
	return temp;
}

void InitActionCards()
{
	for (int i = 0; i < NB_CARDS_ACTION; i++)
	{
		int temp = i / 2;
		//int temp = rand() % 2;

		switch (temp)
		{
		case 0:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionMuzzle.png", ACTION_MUZZLE, true));
			break;
		case 1:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionDenunciation.png", ACTION_DENUNCIATION, true));
			break;
		case 2:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionHumanitarianAid.png", ACTION_HUMANITARIAN_AID));
			break;
		case 3:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionVoterPurchase.png", ACTION_VOTER_PURCHASE));
			break;
		case 4:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionCallAFriend.png", ACTION_CALL_A_FRIEND, true));
			break;
		case 5:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionSecretService.png", ACTION_SECRET_SERVICE));
			break;
		case 6:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionFlyers.png", ACTION_FLYERS));
			break;
		case 7:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionMisappropriation.png", ACTION_MISAPPROPRIATION));
			break;
		case 8:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionAccountHack.png", ACTION_ACCOUNT_HACK, true));
			break;
		case 9:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionMeeting.png", ACTION_MEETING));
			break;
		case 10:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionDebate.png", ACTION_DEBATE, true));
			break;
		case 11:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionMishievousDice.png", ACTION_MISCHIEVOUS_DICE));
			break;
		case 12:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionFreeTurn.png", ACTION_FREE_TURN));
			break;
		case 13:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionTrickDie.png", ACTION_TRICK_DIE, true));
			break;
		case 14:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionBlackmail.png", ACTION_BLACKMAIL, true));
			break;
		case 15:
			actionCardsStack.push_back(CreateCard("Assets/Images/Cards/ActionCharityAction.png", ACTION_CHARITY_ACTION));
			break;
		default:
			std::cout << "probleme d'init" << std::endl;
			break;
		}
	}
}

void InitChanceCards()
{
	for (int i = 0; i < NB_CARDS_CHANCE; i++)
	{
		int temp = i / 2;

		switch (temp)
		{
		case 0:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceLostWallet.png", CHANCE_LOST_WALLET));
			break;
		case 1:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceFindingBill.png", CHANCE_FINDING_BILL));
			break;
		case 2:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceSpeechError.png", CHANCE_SPEECH_ERROR));
			break;
		case 3:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceSmoothTalker.png", CHANCE_SMOOTH_TALKER));
			break;
		case 4:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChancePrivateJet.png", CHANCE_PRIVATE_JET));
			break;
		case 5:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceDoubtfullAffair.png", CHANCE_DOUBTFUL_AFFAIR));
			break;
		case 6:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceFundRaising.png", CHANCE_FUNDRAISING));
			break;
		case 7:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceTaxes.png", CHANCE_TAXES));
			break;
		case 8:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceHalt.png", CHANCE_HALT));
			break;
		case 9:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceStoneInShoe.png", CHANCE_STONE_IN_SHOE));
			break;
		case 10:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceRockInShoe.png", CHANCE_ROCK_IN_SHOE));
			break;
		case 11:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceLittleHelp.png", CHANCE_LITTLE_HELP));
			break;
		case 12:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceBigHelp.png", CHANCE_BIG_HELP));
			break;
		case 13:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceOffshoreFinancing.png", CHANCE_OFFSHORE_FINANCING));
			break;
		case 14:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceFakeNews.png", CHANCE_FAKE_NEWS));
			break;
		case 15:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceWebDevelopment.png", CHANCE_WEB_DEVELOPMENT));
			break;
		case 16:
			chanceCardsStack.push_back(CreateCard("Assets/Images/Cards/ChanceBuzz.png", CHANCE_BUZZ));
			break;
		default:
			std::cout << "probleme d'init" << std::endl;
			break;
		}
	}
}


void MixUpCards(std::vector<Card>& _cardsStack)
{
	std::random_shuffle(_cardsStack.begin(), _cardsStack.end());
}

void InitPlayerCards()
{
	for (int i = 0; i < NB_PLAYERS; i++)
	{
		playersCards.push_back(cardList);
	}
}

void InitCardButton()
{
	float posY = PosToScreenY(738.2f);
	float posXLeft = PosToScreenX(816);
	float posXMiddle = PosToScreenX(1920.f / 2.f);
	float posXRight = PosToScreenX(1104);
	sf::Vector2f scale = ScaleToScreen(1.f, 1.f);
	cardButtonList[BUTTON_KEEP] = CreateButton("Assets/Images/Cards/CardButtonKeep.png", posY, true, scale, posXLeft, 3);
	cardButtonList[BUTTON_DISCARD] = CreateButton("Assets/Images/Cards/CardButtonDiscard.png", posY, true, scale, posXMiddle, 3);
	cardButtonList[BUTTON_USE] = CreateButton("Assets/Images/Cards/CardButtonUse.png", posY, true, scale, posXRight, 3);
	cardButtonList[BUTTON_NO] = CreateButton("Assets/Images/Cards/CardButtonRefuse.png", posY, true, scale, posXLeft, 3);
	cardButtonList[BUTTON_YES] = CreateButton("Assets/Images/Cards/CardButtonAccept.png", posY, true, scale, posXRight, 3);

	for (int i = BUTTON_DISCARD; i <= BUTTON_USE; i++)
	{
		cardButtonList[i].canBeSelected = false;
		cardButtonList[i].type = (CardButtonType)i;
		CreateAnimationLeftToRight(cardButtonList[i].animation[0], 3, 1, cardButtonList[i].texture->getSize());
	}
	for (int i = BUTTON_NO; i <= BUTTON_YES; i++)
	{
		cardButtonList[i].canBeSelected = false;
		cardButtonList[i].type = (CardButtonType)i;
		CreateAnimationLeftToRight(cardButtonList[i].animation[0], 3, 1, cardButtonList[i].texture->getSize());
	}
}

void InitInserts()
{
	sf::Vector2f pos(GetScreen().width / 2.f, GetScreen().height / 2.f);

	targetSelectionInsert.sprite = LoadSprite("Assets/Images/Cards/TargetSelectionInsert.png", true);
	targetSelectionInsert.sprite.setPosition(pos);

	muzzleInsert.sprite = LoadSprite("Assets/Images/Cards/MuzzleInsert.png", true);
	muzzleInsert.sprite.setPosition(pos);

	blackmailInsert.sprite = LoadSprite("Assets/Images/Cards/BlackmailInsert.png", true);
	blackmailInsert.sprite.setPosition(pos);
}

// Init The differents texts in inserts
void InitInsertTexts()
{
	sf::Font& font = GetSettingsFont();
	float posX(targetSelectionInsert.sprite.getGlobalBounds().left + targetSelectionInsert.sprite.getGlobalBounds().width/2.f);
	float posY(targetSelectionInsert.sprite.getGlobalBounds().top + targetSelectionInsert.sprite.getGlobalBounds().height / 2.f - PosToScreenY(6));

	// Target selection text
	CreateText(targetSelectionText, font, "VEUILLE CLIQUER SUR L'ENCART DU JOUEUR CIBLÉ", 30, sf::Color::White);
	targetSelectionText.setPosition(posX, posY /*- 55*/);

	// Muzzle text
	CreateText(MuzzleText[0], font, "MARGARET TCHATCHEUR", 40, sf::Color::White);
	CreateText(MuzzleText[1], font, "VOULEZ VOUS UTILISER VOTRE MUSELIÈRE ?", 30, sf::Color::White);
	MuzzleText[0].setPosition(posX, posY - PosToScreenY(110));
	MuzzleText[1].setPosition(posX, posY + PosToScreenY(30));

	// Blackmail text
	CreateText(blackmailText[3], font, "MARGARET TCHATCHEUR", 40, sf::Color::White);
	CreateText(blackmailText[0], font, "ACCEPTER LE CHANTAGE ET PAYER 30K", 30, sf::Color::White);
	CreateText(blackmailText[1], font, "OU", 30, sf::Color::White);
	CreateText(blackmailText[2], font, "PERDRE 2 RÉPUTATION ET 200 ÉLECTEURS", 30, sf::Color::White);
	blackmailText[0].setPosition(posX, posY - PosToScreenY(26));
	blackmailText[1].setPosition(posX, posY + PosToScreenY(21));
	blackmailText[2].setPosition(posX, posY + PosToScreenY(72));
	blackmailText[3].setPosition(posX, posY - PosToScreenY(110));
}

void InitCardSounds()
{
	cardSounds[CARD_PICK] = AddSound("Assets/Sounds/CardPick.ogg");
	cardSounds[CARD_PLAYED] = AddSound("Assets/Sounds/CardPlayed.ogg");
}

// Update
void UpdateCards(GameData& _gameData)
{
	UpdateCardsButtonsAnimation();
	UpdateInsertsButtonsAnimation();

	if (!GetPlayerIsAnAI(GetActivePlayer()) || (GetPlayerIsAnAI(GetActivePlayer()) && (GetIsBlackMailPlaying() || GetIsDenunciationPlaying())))
	{
		CheckIfMousePressedOnCard(_gameData, playersCards);
	}

	PlaceCardsInPlayerStack();
	ResolveActionMischievousDice();
	ResolveActionDebate(targetPlayer);
	UpdateCardsScale(_gameData.dt);
	UpdateButtonScale(_gameData.dt);
	UpdateInsertScale(_gameData.dt);
	UpdateTargetInsertScale(_gameData.dt);
}

void UpdateCardsButtonsAnimation()
{
	for (unsigned char i = BUTTON_DISCARD; i <= BUTTON_USE; i++)
	{
		UpdateAnimationIsEntitySelected(cardButtonList[i].animation[0], cardButtonList[i].isSelected, cardButtonList[i].sprite);
	}
}

void UpdateInsertsButtonsAnimation()
{
	for (unsigned char i = BUTTON_NO; i <= BUTTON_YES; i++)
	{
		UpdateAnimationIsEntitySelected(cardButtonList[i].animation[0], cardButtonList[i].isSelected, cardButtonList[i].sprite);
	}
}

void SwapCardFromVectorToVector(std::vector<Card>& _fromVector, std::vector<Card>& _toVector)
{
	isAnyCardDisplaying = false;
	_fromVector[_fromVector.size() - 1].isDisplay = false;
	_toVector.push_back(_fromVector[_fromVector.size() - 1]);
	_fromVector.pop_back();
}

void SwapActionCardToDiscard(std::vector<Card>& _cardList, unsigned char _index)
{
	if (!_cardList.empty())
	{
		isAnyCardDisplaying = false;
		_cardList[_index].isDisplay = false;
		_cardList[_index].sprite.setPosition(GetScreen().width / 2.f, GetScreen().height / 2.f);
		_cardList[_index].sprite.setScale(ScaleToScreen(1.f, 1.f));
		actionDiscard.push_back(_cardList[_index]);
		_cardList.erase(_cardList.begin() + _index);
	}
}

void ResetCardStack(std::vector<Card>& _cardVector, Stack& _stack)
{
	if (_stack.type == CHANCE_CARD)
	{
		_cardVector = chanceDiscard;
		chanceDiscard.clear();
	}
	else
	{
		_cardVector = actionDiscard;
		actionDiscard.clear();
	}
	MixUpCards(_cardVector);
}

void ReplaceCardButtons(bool _isKeepDisplay, bool _isDiscardDisplay, bool _isUseDisplay)
{
	float posXLeft = PosToScreenX(816);
	float posXMiddle = PosToScreenX(1920 /2.f);

	if (_isDiscardDisplay && _isUseDisplay)
	{
		cardButtonList[BUTTON_DISCARD].pos.x = posXLeft;
		cardButtonList[BUTTON_DISCARD].sprite.setPosition(cardButtonList[BUTTON_DISCARD].pos);
		cardButtonList[BUTTON_DISCARD].canBeSelected = true;
		cardButtonList[BUTTON_USE].canBeSelected = true;
	}
	else if (_isKeepDisplay && _isUseDisplay)
	{
		cardButtonList[BUTTON_KEEP].pos.x = posXLeft;
		cardButtonList[BUTTON_KEEP].sprite.setPosition(cardButtonList[BUTTON_KEEP].pos);
		cardButtonList[BUTTON_KEEP].canBeSelected = true;
		cardButtonList[BUTTON_USE].canBeSelected = true;
	}
	else if (_isKeepDisplay)
	{
		cardButtonList[BUTTON_KEEP].pos.x = posXMiddle;
		cardButtonList[BUTTON_KEEP].sprite.setPosition(cardButtonList[BUTTON_KEEP].pos);
		cardButtonList[BUTTON_KEEP].canBeSelected = true;
	}
	else if (_isDiscardDisplay)
	{
		cardButtonList[BUTTON_DISCARD].pos.x = posXMiddle;
		cardButtonList[BUTTON_DISCARD].sprite.setPosition(cardButtonList[BUTTON_DISCARD].pos);
		cardButtonList[BUTTON_DISCARD].canBeSelected = true;
	}
}

void PlaceCardsInPlayerStack()
{
	for (int i = 0; i < NB_PLAYERS; i++)
	{
		if (!playersCards[i].empty())
		{
			for (int j = 0; j < playersCards[i].size(); j++)
			{
				if (!isACardSelected)
				{
					float x = GetHudPlayerOrigin(i).x;
					float y = GetHudPlayerOrigin(i).y;
					sf::Vector2f startPos = { x + PosToScreenX(175) , y + PosToScreenY(280) };
					sf::Vector2f scale = ScaleToScreen(CARD_SCALE_VALUE, CARD_SCALE_VALUE);
					sf::Vector2f nextPos = { startPos.x, startPos.y + (j - 1) * STEP_BETWEEN_CARDS };
					playersCards[i][j].sprite.setScale(scale);
					playersCards[i][j].pos = nextPos;
					playersCards[i][j].sprite.setPosition(nextPos);
				}
			}
		}
	}
}

void CheckIfMousePressedOnCard(GameData& _gameData, std::vector<std::vector<Card>>& _playersCards)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !GetHudPlayerIsMoving())
	{
		unsigned char activePlayer = GetActivePlayer();
		sf::Vector2i mouse = sf::Mouse::getPosition();

		if (!_playersCards[activePlayer].empty())
		{
			if (!isACardSelected)
			{
				for (int i = 0; i < _playersCards[activePlayer].size(); i++)
				{

					sf::Vector2f scale = ScaleToScreen(CARD_SCALE_VALUE, CARD_SCALE_VALUE);
					float width = _playersCards[activePlayer][i].texture->getSize().x * scale.x;
					float height = _playersCards[activePlayer][i].texture->getSize().y * scale.y;
					float left = _playersCards[activePlayer][i].sprite.getPosition().x - width / 2;
					float top = _playersCards[activePlayer][i].sprite.getPosition().y - height / 2;
					float rectHeight = STEP_BETWEEN_CARDS;
					sf::FloatRect rect(left, top, width, rectHeight);

					if (i == _playersCards[activePlayer].size() - 1)
					{
						if (RectContains(_playersCards[activePlayer][i].sprite.getGlobalBounds(), (sf::Vector2f)mouse))
						{
							sf::Vector2f pos((float)mouse.x, (float)mouse.y + height - STEP_BETWEEN_CARDS);
							_playersCards[activePlayer][i].isSelected = true;
							isACardSelected = true;
							_playersCards[activePlayer][i].sprite.setScale(ScaleToScreen(1.f, 1.f));
							_playersCards[activePlayer][i].sprite.setPosition((sf::Vector2f)pos);
						}
					}
					else
					{
						if (RectContains(rect, (sf::Vector2f)mouse))
						{
							sf::Vector2f pos((float)mouse.x, (float)mouse.y + height - STEP_BETWEEN_CARDS);
							_playersCards[activePlayer][i].isSelected = true;
							isACardSelected = true;
							_playersCards[activePlayer][i].sprite.setScale(ScaleToScreen(1.f, 1.f));
							_playersCards[activePlayer][i].sprite.setPosition((sf::Vector2f)pos);
						}
					}
				}
			}
		}
	}
}

void ActiveYesAndNoButtons()
{
	for (size_t i = BUTTON_NO; i <= BUTTON_YES; i++)
	{
		cardButtonList[i].canBeSelected = true;
	}
}

void UpdateCardsScale(float _dt)
{
	if (isCardAppears)
	{
		timerScaleCards += 2 * _dt;
		if (timerScaleCards < 1)
		{
			if (typeActiveStack == CHANCE_CARD)
			{
				chanceCardsStack[chanceCardsStack.size() - 1].sprite.setScale(EaseInOutQuart(timerScaleCards), EaseInOutQuart(timerScaleCards));

			}
			if (typeActiveStack == ACTION_CARD)
			{
				actionCardsStack[actionCardsStack.size() - 1].sprite.setScale(EaseInOutQuart(timerScaleCards), EaseInOutQuart(timerScaleCards));

			}
		}
		else
		{
			if (typeActiveStack == CHANCE_CARD)
			{
				chanceCardsStack[chanceCardsStack.size() - 1].sprite.setScale(1, 1);
			}
			if (typeActiveStack == ACTION_CARD)
			{
				actionCardsStack[actionCardsStack.size() - 1].sprite.setScale(1, 1);
			}

			isCardAppears = false;
			timerScaleCards = 1;
		}
	}
	else if (isCardDisappears)
	{
		timerScaleCards -= 2 * _dt;
		if (timerScaleCards > 0)
		{
			if (typeActiveStack == CHANCE_CARD)
			{
				chanceCardsStack[chanceCardsStack.size() - 1].sprite.setScale(EaseInOutQuart(timerScaleCards), EaseInOutQuart(timerScaleCards));

			}
			if (typeActiveStack == ACTION_CARD)
			{
				actionCardsStack[actionCardsStack.size() - 1].sprite.setScale(EaseInOutQuart(timerScaleCards), EaseInOutQuart(timerScaleCards));

			}
		}
		else if (timerScaleCards <= 0)
		{
			if (typeActiveStack == CHANCE_CARD)
			{
				chanceCardsStack[chanceCardsStack.size() - 1].sprite.setScale(0.f, 0.f);
				if (lastButtonPressed == BUTTON_DISCARD)
				{
					SwapCardFromVectorToVector(chanceCardsStack, chanceDiscard);
				}
			}
			else if (typeActiveStack == ACTION_CARD)
			{
				unsigned char activePlayer = GetActivePlayer();

				actionCardsStack[actionCardsStack.size() - 1].sprite.setScale(0.f, 0.f);
				switch (lastButtonPressed)
				{
				case BUTTON_DISCARD:
					SwapCardFromVectorToVector(actionCardsStack, actionDiscard);
					break;
				case BUTTON_KEEP:
					SwapCardFromVectorToVector(actionCardsStack, playersCards[activePlayer]);
					break;
				case BUTTON_USE:
					SwapCardFromVectorToVector(actionCardsStack, actionDiscard);
					break;
				case BUTTON_NO:
					break;
				case BUTTON_YES:
					break;
				default:
					std::cout << "Probleme Swaping" << std::endl;
					break;
				}
			}
			UnDrawCardButtons();
			if ((GetPlayerIsOnMysterytile(GetActivePlayer()) || !GetPlayerHasTookMisteryAction(GetActivePlayer())) && GetPlayerIsAnAI(GetActivePlayer()))
			{
				SetPlayerHasTookMysteryAction(GetActivePlayer(), true);
				SetMysteryActionPlayingAI(GetActivePlayer(), false);
			}
			isAnyCardDisplaying = false;
			isCardDisappears = false;
			timerScaleCards = 0;
		}
	}
}

void UpdateButtonScale(float _dt)
{
	if (isCardAppears || isInsertAppears)
	{
		if (timerScaleCards <= 1)
		{
			for (int i = 0; i < NB_CARD_BUTTONS; i++)
			{
				cardButtonList[i].sprite.setScale(EaseInQuart(timerScaleCards), EaseInQuart(timerScaleCards));
			}
		}
		else
		{
			for (int i = 0; i < NB_CARD_BUTTONS; i++)
			{
				cardButtonList[i].sprite.setScale(1.f, 1.f);
			}
		}
	}
	else if (isCardDisappears || isInsertDisappears)
	{
		if (timerScaleCards >= 0)
		{
			for (int i = 0; i < NB_CARD_BUTTONS; i++)
			{
				cardButtonList[i].sprite.setScale(EaseInQuart(timerScaleCards), EaseInQuart(timerScaleCards));
			}
		}
		else
		{
			for (int i = 0; i < NB_CARD_BUTTONS; i++)
			{
				cardButtonList[i].sprite.setScale(0.f, 0.f);
			}
		}
	}
}

void UpdateInsertScale(float _dt)
{
	if (isInsertAppears)
	{
		if (isDenunciationIsPlaying)
		{
			timerScaleCards += 2 * _dt;
			if (timerScaleCards < 1)
			{
				muzzleInsert.sprite.setScale(EaseInOutQuart(timerScaleCards), EaseInOutQuart(timerScaleCards));
			}
			else
			{
				muzzleInsert.sprite.setScale(1.f, 1.f);
				isInsertAppears = false;
				timerScaleCards = 1;
			}
		}
		else if (isBlackmailIsPlaying)
		{
			timerScaleCards += 2 * _dt;
			if (timerScaleCards < 1)
			{
				blackmailInsert.sprite.setScale(EaseInOutQuart(timerScaleCards), EaseInOutQuart(timerScaleCards));
			}
			else
			{
				blackmailInsert.sprite.setScale(1.f, 1.f);
				isInsertAppears = false;
				timerScaleCards = 1;
			}
		}
	}
	else if (isCardDisappears || isInsertDisappears)
	{
		if (isDenunciationIsPlaying)
		{
			timerScaleCards -= 2 * _dt;
			if (timerScaleCards > 0)
			{
				muzzleInsert.sprite.setScale(EaseInOutQuart(timerScaleCards), EaseInOutQuart(timerScaleCards));
			}
			else if (timerScaleCards <= 0)
			{
				muzzleInsert.sprite.setScale(0.f, 0.f);

				if (lastButtonPressed == BUTTON_NO)
				{
					isDenunciationIsPlaying = false;
					ResolveActionMuzzle(targetPlayer);
				}
				else
				{
					for (size_t i = 0; i < playersCards[targetPlayer].size(); i++)
					{
						if (playersCards[targetPlayer][i].type == ACTION_MUZZLE)
						{
							SwapActionCardToDiscard(playersCards[targetPlayer], (unsigned char)i);
						}
					}
				}
				UnDrawInsertButtons();
				isDenunciationIsPlaying = false;
				isInsertDisappears = false;
				timerScaleCards = 0;
			}
		}
		else if (isBlackmailIsPlaying)
		{
			timerScaleCards -= 2 * _dt;
			if (timerScaleCards > 0)
			{
				blackmailInsert.sprite.setScale(EaseInOutQuart(timerScaleCards), EaseInOutQuart(timerScaleCards));
			}
			else if (timerScaleCards <= 0)
			{
				std::cout << "last button : " << lastButtonPressed << std::endl;
				blackmailInsert.sprite.setScale(0.f, 0.f);
				isBlackmailIsPlaying = false;
				bool isAccepted = true;
				if (lastButtonPressed == BUTTON_NO)
				{
					isAccepted = false;
				}
				else if (lastButtonPressed == BUTTON_YES)
				{
					isAccepted = true;
				}
				ResolveActionBlackmail(GetActivePlayer(), targetPlayer, isAccepted);
				isInsertDisappears = false;
				UnDrawInsertButtons();
				timerScaleCards = 0;
			}
		}
	}
}

void UpdateTargetInsertScale(float _dt)
{
	if (isACardIsPlaying && isTargetInsertDisappears)
	{
		timerScaleTargetInsert -= 3 * _dt;
		if (timerScaleTargetInsert > 0)
		{
			targetSelectionInsert.sprite.setScale(EaseInOutQuart(timerScaleTargetInsert), EaseInOutQuart(timerScaleTargetInsert));
		}
		else if (timerScaleTargetInsert <= 0)
		{
			isACardIsPlaying = false;
			isTargetInsertDisappears = false;
			timerScaleTargetInsert = 1;
		}
	}
}

void InitActionMischievousDice()
{
	if (!GetDiceHasRolling())
	{
		lastDicesResultWasADouble = true;
	}
	setDiceHasRolling(false);
	isMischievousDiceIsPlaying = true;
	SetLaunchedDices(1);
}

void InitActionDebate()
{
	if (!GetDiceHasRolling())
	{
		lastDicesResultWasADouble = true;
	}
	isDebateIsPlaying = true;
	SetLaunchedDices(1);
	setDiceHasRolling(false);
	SetParliamentaryIsAppears(true);
	SetPseudoInInsert(GetActivePlayer());
}

void ResolveActionOnTarget(CardType& _type)
{
	targetSelectionInsert.sprite.setScale(1.f, 1.f);
	isACardIsPlaying = true;
	typeActiveCard = _type;
}

#pragma region ResolveActionCards

void ResolveActionDenunciation(unsigned char _targetPlayer)
{
	for (int i = 0; i < playersCards[_targetPlayer].size(); i++)
	{
		if (playersCards[_targetPlayer][i].type == ACTION_MUZZLE)
		{
			MuzzleText[0].setString(GetPlayerPseudo(_targetPlayer));
			MuzzleText[0].setOrigin(MuzzleText[0].getGlobalBounds().width / 2, MuzzleText[0].getGlobalBounds().height / 2);
			isDenunciationIsPlaying = true;
			muzzleInsert.sprite.setScale(1.f, 1.f);
			isInsertAppears = true;
			for (size_t i = BUTTON_NO; i <= BUTTON_YES; i++)
			{
				cardButtonList[i].canBeSelected = true;
			}
		}
	}

	if (!isDenunciationIsPlaying)
	{
		AddPlayerReputation(_targetPlayer, -2);
		AddPlayerVoters(_targetPlayer, -200);
	}
}

void ResolveActionMuzzle(unsigned char _targetPlayer)
{
	AddPlayerReputation(_targetPlayer, -2);
	AddPlayerVoters(_targetPlayer, -200);
}

void ResolveActionHumanitarianAid(unsigned char _activePlayer)
{
	AddPlayerMoney(_activePlayer, -30000);
	AddPlayerReputation(_activePlayer, 2);
	AddPlayerVoters(_activePlayer, 250);
}

void ResolveActionVoterPurchase(unsigned char _activePlayer)
{
	AddPlayerMoney(_activePlayer, -30000);
	AddPlayerReputation(_activePlayer, -2);
	AddPlayerVoters(_activePlayer, 500);
}

void ResolveActionCallAFriend(unsigned char _targetPlayer)
{
	SetPlayerMovingToFiscalControl(_targetPlayer);
}

void ResolveActionSecretService(unsigned char _targetPlayer)
{
	AddPlayerReputation(_targetPlayer, -1);
}

void ResolveActionFlyers(unsigned char _activePlayer)
{
	AddPlayerMoney(_activePlayer, -10000);
	AddPlayerVoters(_activePlayer, 100);
}

void ResolveActionMisappropriation(unsigned char _activePlayer)
{
	if (GetPlayersReputation(_activePlayer) < 0)
	{
		AddPlayerMoney(_activePlayer, 40000);
	}
	else
	{
		AddPlayerMoney(_activePlayer, 20000);
	}
	AddPlayerReputation(_activePlayer, -1);
}

void ResolveActionAccountHack(unsigned char _activePlayer, unsigned char _targetPlayer)
{
	AddPlayerMoney(_activePlayer, 20000);
	AddPlayerMoney(_targetPlayer, -20000);
}

void ResolveActionMeeting(unsigned char _activePlayer)
{
	AddPlayerMoney(_activePlayer, -20000);
	AddPlayerVoters(_activePlayer, 300);
}

void ResolveActionDebate(unsigned char _targetPlayer)
{
	if (isDebateIsPlaying && GetDiceHasRolling() && !GetDiceIsRolling() && !GetDiceisAvailable())
	{
		unsigned char activePlayer = GetActivePlayer();
		char activePlayerReputation;
		unsigned char diceResult = GetFirstDiceValue();
		unsigned char lastPlayer;
		bool hasActivePlayerPlayed = false;

		if (activePlayer != _targetPlayer)
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
			SetLastPlayerPlayed(activePlayer);
			SetActivePlayer(_targetPlayer);
			SetParliamentaryIsAppears(true);
			SetPseudoInInsert(_targetPlayer);
			setDiceHasRolling(false);
			activePlayer = _targetPlayer;
			SetNoOneIsMoving(false);
		}
		else if (activePlayer == _targetPlayer)
		{
			printf("Mes couilles");

			activePlayerReputation = GetPlayersReputation(activePlayer);
			lastPlayer = GetLastPlayerPlayed();

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

			if (GetDicesValue(lastPlayer) < GetDicesValue(activePlayer))
			{
				AddPlayerVoters(lastPlayer, -200);
				AddPlayerVoters(activePlayer, 200);
			}
			else if (GetDicesValue(lastPlayer) > GetDicesValue(activePlayer))
			{
				AddPlayerVoters(lastPlayer, 200);
				AddPlayerVoters(activePlayer, -200);
			}
			else if (GetDicesValue(lastPlayer) == GetDicesValue(activePlayer))
			{
				if (GetPlayersReputation(activePlayer) > GetPlayersReputation(lastPlayer))
				{
					AddPlayerVoters(lastPlayer, -200);
					AddPlayerVoters(activePlayer, 200);
				}
				else
				{
					AddPlayerVoters(lastPlayer, 200);
					AddPlayerVoters(activePlayer, -200);
				}
			}

			if (!GetPlayerHasAlreadyMoved(lastPlayer))
			{
				setDiceHasRolling(false);
				SetLaunchedDices(2);
			}
			SetNoOneIsMoving(false);
			SetActivePlayer(lastPlayer);
			isDebateIsPlaying = false;
			if (lastDicesResultWasADouble)
			{
				setDiceHasRolling(false);
				SetPlayerHasAlreadyMoved(activePlayer, false);
				lastDicesResultWasADouble = false;
			}
		}
	}
}

void ResolveActionMischievousDice()
{
	if (isMischievousDiceIsPlaying && GetDiceHasRolling() && !GetDiceIsRolling() && !GetDiceisAvailable())
	{
		unsigned char activePlayer = GetActivePlayer();
		unsigned char diceResult = GetFirstDiceValue();
		switch (diceResult)
		{
		case 1:
			AddPlayerMoney(activePlayer, -20000);
			break;
		case 2:
			AddPlayerReputation(activePlayer, -2);
			break;
		case 3:
			AddPlayerVoters(activePlayer, -200);
			break;
		case 4:
			AddPlayerMoney(activePlayer, 20000);
			break;
		case 5:
			AddPlayerReputation(activePlayer, 2);
			break;
		case 6:
			AddPlayerVoters(activePlayer, 200);
			break;
		default:
			std::cout << "Probleme\n";
			break;
		}
		if (lastDicesResultWasADouble)
		{
			setDiceHasRolling(false);
			SetPlayerHasAlreadyMoved(activePlayer, false);
			lastDicesResultWasADouble = false;
		}
		SetLaunchedDices(2);
		isMischievousDiceIsPlaying = false;
	}
}

void ResolveActionFreeTurn(unsigned char _activePlayer)
{
	SetLaunchedDices(2);
	setDiceHasRolling(false);
}

void ResolveActionTrickDie(unsigned char _activePlayer)
{
	SetLaunchedDices(3);
	isTrickDieIsPlaying = true;
}

void ResolveActionBlackmail(unsigned char _activePlayer, unsigned char _targetPlayer, bool _isAccepted)
{
	if (_isAccepted)
	{
		AddPlayerMoney(_activePlayer, 30000);
		AddPlayerMoney(_targetPlayer, -30000);
	}
	else
	{
		AddPlayerReputation(_targetPlayer, -2);
		AddPlayerVoters(_targetPlayer, -200);
	}
}

void ResolveActionCharityAction(unsigned char _activePlayer)
{
	AddPlayerMoney(_activePlayer, -10000);
	AddPlayerReputation(_activePlayer, 2);
}

#pragma endregion ResolveActionCards

#pragma region ResolveChanceCards

void ResolveChanceLostWallet(unsigned char _activePlayer)
{
	AddPlayerMoney(_activePlayer, -10000);
}

void ResolveChanceFindingBill(unsigned char _activePlayer)
{
	AddPlayerMoney(_activePlayer, 10000);
}

void ResolveChanceSpeechError(unsigned char _activePlayer)
{
	AddPlayerVoters(_activePlayer, -100);
}

void ResolveChanceSmoothTalker(unsigned char _activePlayer)
{
	AddPlayerVoters(_activePlayer, 100);
}

void ResolveChancePrivateJet(unsigned char _activePlayer)
{
	SetPlayerMovingToStartSquare(_activePlayer);
}

void ResolveChanceDoubtfulAffair(unsigned char _activePlayer)
{
	AddPlayerReputation(_activePlayer, -2);
	AddPlayerVoters(_activePlayer, -100);
}

void ResolveChanceFundraising(unsigned char _activePlayer)
{
	int moneyMultiplier = GetPlayersVoters(_activePlayer) / 500;
	AddPlayerMoney(_activePlayer, moneyMultiplier * 10000);
}

void ResolveChanceHalt(unsigned char _activePlayer)
{
	SetPlayerMovingToFiscalControl(_activePlayer);
}

void ResolveChanceStoneInShoe(unsigned char _activePlayer)
{
	SetPlayerReverseMove(_activePlayer, 2);
}

void ResolveChanceRockInShoe(unsigned char _activePlayer)
{
	SetPlayerReverseMove(_activePlayer, 3);
}

void ResolveChanceLittleHelp(unsigned char _activePlayer)
{
	SetPlayerMoveForward(_activePlayer, 2);
}

void ResolveChanceBigHelp(unsigned char _activePlayer)
{
	SetPlayerMoveForward(_activePlayer, 3);
}

void ResolveChanceOffshoreFinancing(unsigned char _activePlayer)
{
	AddPlayerMoney(_activePlayer, 30000);
	AddPlayerReputation(_activePlayer, -2);
}

void ResolveChanceFakeNews(unsigned char _activePlayer)
{
	AddPlayerReputation(_activePlayer, -2);
}

void ResolveChanceWebDevelopment(unsigned char _activePlayer)
{
	AddPlayerReputation(_activePlayer, 2);
}

void ResolveChanceBuzz(unsigned char _activePlayer)
{
	AddPlayerReputation(_activePlayer, 1);
	AddPlayerVoters(_activePlayer, 100);
}

#pragma endregion ResolveChanceCards

// Display
void DisplayCards(sf::RenderWindow& _window)
{
	DisplayStacks(_window);
	DisplayActiveCard(actionCardsStack, _window);
	DisplayActiveCard(chanceCardsStack, _window);
	DisplayCardButtons(_window);
	DisplayInserts(_window);
}

void DisplayStacks(sf::RenderWindow& _window)
{
	_window.draw(stackAction.sprite);
	_window.draw(stackChance.sprite);
}

void DisplayActiveCard(std::vector<Card>& _cardVector, sf::RenderWindow& _window)
{
	for (int i = 0; i < _cardVector.size(); i++)
	{
		if (_cardVector[i].isDisplay)
		{
			_window.draw(_cardVector[i].sprite);
		}
	}
}

void DisplayPlayerCards(sf::RenderWindow& _window)
{
	for (int i = 0; i < NB_PLAYERS; i++)
	{
		for (int j = 0; j < playersCards[i].size(); j++)
		{
			if (!playersCards[i][j].isSelected)
			{
				_window.draw(playersCards[i][j].sprite);
			}
		}
		for (int j = 0; j < playersCards[i].size(); j++)
		{
			if (playersCards[i][j].isSelected)
			{
				_window.draw(playersCards[i][j].sprite);
			}
		}
	}
}

void DisplayCardButtons(sf::RenderWindow& _window)
{
	for (int i = 0; i < NB_CARD_BUTTONS; i++)
	{
		if (cardButtonList[i].canBeSelected)
		{
			_window.draw(cardButtonList[i].sprite);
		}
	}
}

void UnDrawCardButtons()
{
	for (int i = BUTTON_DISCARD; i <= BUTTON_USE; i++)
	{
		cardButtonList[i].canBeSelected = false;
	}
}

void UnDrawInsertButtons()
{
	for (int i = BUTTON_NO; i <= BUTTON_YES; i++)
	{
		cardButtonList[i].canBeSelected = false;
	}
}

void DisplayInserts(sf::RenderWindow& _window)
{
	if (isACardIsPlaying)
	{
		_window.draw(targetSelectionInsert.sprite);
		if (!isTargetInsertDisappears)
		{
			_window.draw(targetSelectionText);
		}
	}
	else if (isDenunciationIsPlaying)
	{
		_window.draw(muzzleInsert.sprite);
		if (!isInsertAppears && !isInsertDisappears)
		{
			for (int i = 0; i < NB_MUZZLE_TEXTS; i++)
			{
				_window.draw(MuzzleText[i]);
			}
		}

		for (size_t i = BUTTON_NO; i <= BUTTON_YES; i++)
		{
			_window.draw(cardButtonList[i].sprite);
		}
	}
	else if (isBlackmailIsPlaying)
	{
		_window.draw(blackmailInsert.sprite);
		if (!isInsertAppears && !isInsertDisappears)
		{
			for (int i = 0; i < NB_BLACKMAIL_TEXTS; i++)
			{
				_window.draw(blackmailText[i]);
			}
		}

		for (size_t i = BUTTON_NO; i <= BUTTON_YES; i++)
		{
			_window.draw(cardButtonList[i].sprite);
		}
	}
}

// Mouse Moved
void MouseMovedCards(sf::Event::MouseMoveEvent _buttonEvt)
{
	CheckMouseStackCollision(stackAction, _buttonEvt);
	CheckMouseStackCollision(stackChance, _buttonEvt);
	for (int i = BUTTON_DISCARD; i <= BUTTON_USE; i++)
	{
		CheckMouseCardButtonCollision(cardButtonList[i], _buttonEvt);
	}
	CheckMouseInsertButtonCollision(cardButtonList, _buttonEvt);
	UpdateSelectedCardPosition(_buttonEvt);
}

void CheckMouseStackCollision(Stack& _stack, sf::Event::MouseMoveEvent _buttonEvt)
{
	sf::Vector2f mouse = { (float)_buttonEvt.x , (float)_buttonEvt.y };

	if (_stack.canBeSelected && GetHudPlayerIsDown() && !GetHudPlayerIsMoving())
	{
		if (RectContains(_stack.sprite.getGlobalBounds(), mouse))
		{
			_stack.isSelected = true;
			_stack.sprite.setTexture(_stack.texture[STACK_SELECTED]);
		}
		else
		{
			_stack.isSelected = false;
			_stack.sprite.setTexture(_stack.texture[STACK_CAN_BE_SELECTED]);
		}
	}
}

void CheckMouseCardButtonCollision(Button& _button, sf::Event::MouseMoveEvent _buttonEvt)
{
	sf::Vector2f mouse = { (float)_buttonEvt.x , (float)_buttonEvt.y };

	if (_button.canBeSelected)
	{
		if (RectContains(_button.sprite.getGlobalBounds(), mouse))
		{
			_button.isSelected = true;
		}
		else
		{
			_button.isSelected = false;
		}
	}
}

void CheckMouseInsertButtonCollision(Button* _button, sf::Event::MouseMoveEvent _buttonEvt)
{
	sf::Vector2f mouse = { (float)_buttonEvt.x , (float)_buttonEvt.y };
	for (int i = BUTTON_NO; i <= BUTTON_YES; i++)
	{
		if (_button[i].canBeSelected)
		{
			if (RectContains(_button[i].sprite.getGlobalBounds(), mouse) && !_button[i].isSelected)
			{
				PlaySoundFromList(GetButtonSelectSound(), 5);
			}

			if (RectContains(_button[i].sprite.getGlobalBounds(), mouse))
			{
				_button[i].isSelected = true;
			}
			else
			{
				_button[i].isSelected = false;
			}
		}
	}
}

void UpdateSelectedCardPosition(sf::Event::MouseMoveEvent _buttonEvt)
{
	unsigned char activePlayer = GetActivePlayer();
	sf::Vector2i mouse = sf::Mouse::getPosition();

	if (!playersCards[activePlayer].empty())
	{
		for (unsigned char i = 0; i < playersCards[activePlayer].size(); i++)
		{
			sf::Vector2f scale = ScaleToScreen(CARD_SCALE_VALUE, CARD_SCALE_VALUE);
			float height = playersCards[activePlayer][i].texture->getSize().y * scale.y;
			sf::Vector2f pos((float)mouse.x, (float)mouse.y + height - STEP_BETWEEN_CARDS);
			if (playersCards[activePlayer][i].isSelected)
			{
				playersCards[activePlayer][i].sprite.setPosition((sf::Vector2f)pos);
			}
		}
	}
}

// Mouse Pressed
void MousePressedCards(GameData& _gameData, sf::Event::MouseButtonEvent _buttonEvt)
{
	CheckMousePressedStack(_gameData, _buttonEvt, actionCardsStack, stackAction);
	CheckMousePressedStack(_gameData, _buttonEvt, chanceCardsStack, stackChance);
	for (int i = 0; i < NB_CARD_BUTTONS; i++)
	{
		if (cardButtonList[i].canBeSelected)
		{
			CheckMousePressedCardButton(_gameData, _buttonEvt, cardButtonList[i]);
		}
	}
	CheckMousePressedTargetSelection(_gameData, _buttonEvt);
	CheckMousePressedInsertsButton(_gameData, _buttonEvt, cardButtonList);
}

void CheckMousePressedStack(GameData& _gameData, sf::Event::MouseButtonEvent _buttonEvt, std::vector<Card>& _cardVector, Stack& _stack)
{
	if (_gameData.event.type == sf::Event::MouseButtonPressed && _buttonEvt.button == sf::Mouse::Left)
	{
		if (_stack.canBeSelected && GetHudPlayerIsDown() && !GetHudPlayerIsMoving())
		{

			sf::Vector2i mouse = sf::Mouse::getPosition();
			if (RectContains(_stack.sprite.getGlobalBounds(), (sf::Vector2f)mouse))
			{
				PlaySoundFromList(cardSounds[CARD_PICK], 100);
				typeActiveCard = _stack.type;
				typeActiveStack = _stack.type;
				_stack.canBeSelected = false;
				_stack.sprite.setTexture(_stack.texture[STACK]);
				if (_cardVector.empty())
				{
					ResetCardStack(_cardVector, _stack);
				}

				for (int i = 0; i < NB_CARD_BUTTONS; i++)
				{
					cardButtonList[i].sprite.setScale(0.f, 0.f);
				}
				_cardVector[_cardVector.size() - 1].sprite.setScale(0.f, 0.f);
				if (_cardVector[_cardVector.size() - 1].type != CHANCE_TAXES)
				{
					_cardVector[_cardVector.size() - 1].isDisplay = true;
					isCardAppears = true;
				}

				isAnyCardDisplaying = true;


				switch (_cardVector[_cardVector.size() - 1].type)
				{
				case ACTION_MUZZLE:
					ReplaceCardButtons(true, false, false);
					break;
				case ACTION_DENUNCIATION:
					ReplaceCardButtons(true, false, true);
					break;
				case ACTION_HUMANITARIAN_AID:
					ReplaceCardButtons(false, true, true);
					break;
				case ACTION_VOTER_PURCHASE:
					ReplaceCardButtons(false, true, true);
					break;
				case ACTION_CALL_A_FRIEND:
					ReplaceCardButtons(true, false, true);
					break;
				case ACTION_SECRET_SERVICE:
					ReplaceCardButtons(true, false, true);
					break;
				case ACTION_FLYERS:
					ReplaceCardButtons(false, true, true);
					break;
				case ACTION_MISAPPROPRIATION:
					ReplaceCardButtons(false, true, true);
					break;
				case ACTION_ACCOUNT_HACK:
					ReplaceCardButtons(true, false, true);
					break;
				case ACTION_MEETING:
					ReplaceCardButtons(false, true, true);
					break;
				case ACTION_DEBATE:
					ReplaceCardButtons(true, false, true);
					break;
				case ACTION_MISCHIEVOUS_DICE:
					ReplaceCardButtons(false, true, true);
					break;
				case ACTION_FREE_TURN:
					if (!GetDiceHasRolling())
					{
						ReplaceCardButtons(true, false, false);
					}
					else
					{
						ReplaceCardButtons(true, false, true);
					}
					break;
				case ACTION_TRICK_DIE:
					ReplaceCardButtons(true, false, false);
					break;
				case ACTION_BLACKMAIL:
					ReplaceCardButtons(true, false, true);
					break;
				case ACTION_CHARITY_ACTION:
					ReplaceCardButtons(false, true, true);
					break;
				case CHANCE_TAXES:
					SetPlayerIsOnTaxe(GetActivePlayer(), true);
					SetTaxIsAppears(true);
					SetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer(), false);
					SwapCardFromVectorToVector(chanceCardsStack, chanceDiscard);
					break;
				default:
					ReplaceCardButtons(false, true, false);
					break;
				}
			}
		}
	}
}

void CheckMousePressedCardButton(GameData& _gameData, sf::Event::MouseButtonEvent _buttonEvt, Button& _button)
{
	if (_gameData.event.type == sf::Event::MouseButtonPressed && _buttonEvt.button == sf::Mouse::Left)
	{
		sf::Vector2i mouse = sf::Mouse::getPosition();
		if (RectContains(_button.sprite.getGlobalBounds(), (sf::Vector2f)mouse))
		{
			unsigned char activePlayer = GetActivePlayer();
			PlaySoundFromList(GetButtonPressSound(), 50);
			lastButtonPressed = _button.type;
			isCardDisappears = true;

			if (_button.type == BUTTON_DISCARD)
			{
				switch (typeActiveCard)
				{
				case ACTION_CARD:
					;
					break;
				case CHANCE_CARD:
					switch (chanceCardsStack[chanceCardsStack.size() - 1].type)
					{
					case CHANCE_LOST_WALLET:
						ResolveChanceLostWallet(activePlayer);
						break;
					case CHANCE_FINDING_BILL:
						ResolveChanceFindingBill(activePlayer);
						break;
					case CHANCE_SPEECH_ERROR:
						ResolveChanceSpeechError(activePlayer);
						break;
					case CHANCE_SMOOTH_TALKER:
						ResolveChanceSmoothTalker(activePlayer);
						break;
					case CHANCE_PRIVATE_JET:
						ResolveChancePrivateJet(activePlayer);
						break;
					case CHANCE_DOUBTFUL_AFFAIR:
						ResolveChanceDoubtfulAffair(activePlayer);
						break;
					case CHANCE_FUNDRAISING:
						ResolveChanceFundraising(activePlayer);
						break;
					case CHANCE_TAXES:
						break;
					case CHANCE_HALT:
						ResolveChanceHalt(activePlayer);
						break;
					case CHANCE_STONE_IN_SHOE:
						ResolveChanceStoneInShoe(activePlayer);
						break;
					case CHANCE_ROCK_IN_SHOE:
						ResolveChanceRockInShoe(activePlayer);
						break;
					case CHANCE_LITTLE_HELP:
						ResolveChanceLittleHelp(activePlayer);
						break;
					case CHANCE_BIG_HELP:
						ResolveChanceBigHelp(activePlayer);
						break;
					case CHANCE_OFFSHORE_FINANCING:
						ResolveChanceOffshoreFinancing(activePlayer);
						break;
					case CHANCE_FAKE_NEWS:
						ResolveChanceFakeNews(activePlayer);
						break;
					case CHANCE_WEB_DEVELOPMENT:
						ResolveChanceWebDevelopment(activePlayer);
						break;
					case CHANCE_BUZZ:
						ResolveChanceBuzz(activePlayer);
						break;
					default:
						break;
					}
					break;
				default:
					std::cout << "Problème\n";
					break;
				}
			}
			else if (_button.type == BUTTON_USE)
			{
				CardType type = actionCardsStack[actionCardsStack.size() - 1].type;
				switch (type)
				{
				case ACTION_DENUNCIATION:
					ResolveActionOnTarget(type);
					break;
				case ACTION_HUMANITARIAN_AID:
					ResolveActionHumanitarianAid(activePlayer);
					break;
				case ACTION_VOTER_PURCHASE:
					ResolveActionVoterPurchase(activePlayer);
					break;
				case ACTION_CALL_A_FRIEND:
					ResolveActionOnTarget(type);
					break;
				case ACTION_SECRET_SERVICE:
					ResolveActionOnTarget(type);
					break;
				case ACTION_FLYERS:
					ResolveActionFlyers(activePlayer);
					break;
				case ACTION_MISAPPROPRIATION:
					ResolveActionMisappropriation(activePlayer);
					break;
				case ACTION_ACCOUNT_HACK:
					ResolveActionOnTarget(type);
					break;
				case ACTION_MEETING:
					ResolveActionMeeting(activePlayer);
					break;
				case ACTION_DEBATE:
					ResolveActionOnTarget(type);
					break;
				case ACTION_MISCHIEVOUS_DICE:
					InitActionMischievousDice();
					break;
				case ACTION_FREE_TURN:
					ResolveActionFreeTurn(activePlayer);
					break;
				case ACTION_TRICK_DIE:
					ResolveActionTrickDie(activePlayer);
					break;
				case ACTION_BLACKMAIL:
					ResolveActionOnTarget(type);
					break;
				case ACTION_CHARITY_ACTION:
					ResolveActionCharityAction(activePlayer);
					break;
				default:
					break;
				}
				if (!GetHudPlayerIsDown())
				{
					SetHudPlayerIsMoving(activePlayer, true);
				}
			}
			else if (_button.type == BUTTON_KEEP)
			{
				;
			}
		}
	}
}

void CheckMousePressedInsertsButton(GameData& _gameData, sf::Event::MouseButtonEvent _buttonEvt, Button* _button)
{
	if (_gameData.event.type == sf::Event::MouseButtonPressed && _buttonEvt.button == sf::Mouse::Left)
	{
		sf::Vector2i mouse = sf::Mouse::getPosition();
		for (int i = BUTTON_NO; i <= BUTTON_YES; i++)
		{
			if (_button[i].canBeSelected)
			{
				if (isDenunciationIsPlaying)
				{
					if (RectContains(_button[i].sprite.getGlobalBounds(), (sf::Vector2f)mouse))
					{
						PlaySoundFromList(GetButtonPressSound(), 50);
						lastButtonPressed = _button[i].type;
						isInsertDisappears = true;
					}
				}
				else if (isBlackmailIsPlaying)
				{
					if (RectContains(_button[i].sprite.getGlobalBounds(), (sf::Vector2f)mouse))
					{
						lastButtonPressed = _button[i].type;
						PlaySoundFromList(GetButtonPressSound(), 50);
						isInsertDisappears = true;
					}
				}
			}
		}
	}
}

void CheckMousePressedTargetSelection(GameData& _gameData, sf::Event::MouseButtonEvent _buttonEvt)
{
	if (_gameData.event.type == sf::Event::MouseButtonPressed && _buttonEvt.button == sf::Mouse::Left && isACardIsPlaying)
	{
		unsigned char activePlayer;
		PlaySoundFromList(GetButtonPressSound(), 50);

		activePlayer = GetActivePlayer();
		targetPlayer = GetTargetPlayer();
		if (GetHudPlayerNoneActivePlayerCollision())
		{
			isTargetInsertDisappears = true;
			switch (typeActiveCard)
			{
			case ACTION_DENUNCIATION:
				ResolveActionDenunciation(targetPlayer);
				break;
			case ACTION_CALL_A_FRIEND:
				ResolveActionCallAFriend(targetPlayer);
				break;
			case ACTION_SECRET_SERVICE:
				ResolveActionSecretService(targetPlayer);
				break;
			case ACTION_ACCOUNT_HACK:
				ResolveActionAccountHack(activePlayer, targetPlayer);
				break;
			case ACTION_DEBATE:
				InitActionDebate();
				break;
			case ACTION_BLACKMAIL:
				isBlackmailIsPlaying = true;
				blackmailInsert.sprite.setScale(1.f, 1.f);
				isInsertAppears = true;
				blackmailText[3].setString(GetPlayerPseudo(targetPlayer));
				blackmailText[3].setOrigin(blackmailText[3].getGlobalBounds().width / 2, blackmailText[3].getGlobalBounds().height / 2);
				ActiveYesAndNoButtons();
				break;
			default:
				break;
			}
		}
	}
}

void MouseReleasedCards(GameData& _gameData, sf::Event::MouseButtonEvent _buttonEvt)
{
	if (_gameData.event.type == sf::Event::MouseButtonReleased && _buttonEvt.button == sf::Mouse::Left)
	{
		unsigned char activePlayer = GetActivePlayer();

		if (!playersCards[activePlayer].empty())
		{
			for (int i = 0; i < playersCards[activePlayer].size(); i++)
			{
				if (playersCards[activePlayer][i].isSelected)
				{
					playersCards[activePlayer][i].isSelected = false;
					isACardSelected = false;
					targetPlayer = GetTargetPlayer();

					if (GetHudPlayerNoneActivePlayerCollision())
					{
						PlaySoundFromList(GetButtonPressSound(), 50);

						switch (playersCards[activePlayer][i].type)
						{
						case ACTION_DENUNCIATION:
							SwapActionCardToDiscard(playersCards[activePlayer], i);
							SetHudPlayerIsMoving(activePlayer, true);
							ResolveActionDenunciation(targetPlayer);
							break;
						case ACTION_CALL_A_FRIEND:
							SwapActionCardToDiscard(playersCards[activePlayer], i);
							SetHudPlayerIsMoving(activePlayer, true);
							ResolveActionCallAFriend(targetPlayer);
							break;
						case ACTION_SECRET_SERVICE:
							SwapActionCardToDiscard(playersCards[activePlayer], i);
							SetHudPlayerIsMoving(activePlayer, true);
							ResolveActionSecretService(targetPlayer);
							break;
						case ACTION_ACCOUNT_HACK:
							SwapActionCardToDiscard(playersCards[activePlayer], i);
							SetHudPlayerIsMoving(activePlayer, true);
							ResolveActionAccountHack(activePlayer, targetPlayer);
							break;
						case ACTION_BLACKMAIL:
							SwapActionCardToDiscard(playersCards[activePlayer], i);
							SetHudPlayerIsMoving(activePlayer, true);
							isBlackmailIsPlaying = true;
							blackmailInsert.sprite.setScale(1.f, 1.f);
							isInsertAppears = true;
							blackmailText[3].setString(GetPlayerPseudo(targetPlayer));
							blackmailText[3].setOrigin(blackmailText[3].getGlobalBounds().width / 2, blackmailText[3].getGlobalBounds().height / 2);
							ActiveYesAndNoButtons();
							break;
						case ACTION_DEBATE:
							SwapActionCardToDiscard(playersCards[activePlayer], i);
							SetHudPlayerIsMoving(activePlayer, true);
							isDebateIsPlaying = true;
							InitActionDebate();
							break;
						default:
							break;
						}
					}
					else if (GetHudPlayerActivePlayerCollision())
					{
						PlaySoundFromList(GetButtonPressSound(), 50);

						switch (playersCards[activePlayer][i].type)
						{
						case ACTION_FREE_TURN:
							if (GetPlayerHasAlreadyMoved(activePlayer) && GetDiceHasRolling())
							{
								SwapActionCardToDiscard(playersCards[activePlayer], i);
								SetHudPlayerIsMoving(activePlayer, true);
								ResolveActionFreeTurn(activePlayer);
							}
							break;
						case ACTION_TRICK_DIE:
							if (!GetPlayerHasAlreadyMoved(activePlayer))
							{
								SwapActionCardToDiscard(playersCards[activePlayer], i);
								SetHudPlayerIsMoving(activePlayer, true);
								ResolveActionTrickDie(activePlayer);
							}

							break;
						default:
							break;
						}
					}
				}
			}
		}
	}
}

// Accessors
#pragma region Accessors
bool GetIsACardSelected()
{
	return isACardSelected;
}

bool GetIsMischievousDiceIsPlaying()
{
	return isMischievousDiceIsPlaying;
}

bool GetIsDebateIsPlaying()
{
	return isDebateIsPlaying;
}

bool GetIsTrickDieIsPlaying()
{
	return isTrickDieIsPlaying;
}

bool GetChanceStackCanBeSelected()
{
	return stackChance.canBeSelected;
}

bool GetActionStackCanBeSelected()
{
	return stackAction.canBeSelected;
}

bool GetAIHasCardsInHand(unsigned char _i)
{
	return !playersCards[_i].empty();
}

bool GetIsAnyCardDisplaying(void)
{
	return isAnyCardDisplaying;
}

bool GetHasAlreadyPlayedCard(void)
{
	return hasAlreadyPlayedCard;
}

char GetIsTrickDieInHand(unsigned char& _activePlayer)
{
	for (unsigned char i = 0; i < playersCards[_activePlayer].size(); i++)
	{
		if (playersCards[_activePlayer][i].type == ACTION_TRICK_DIE)
		{
			return i;
		}
	}

	return -1;
}

bool GetIsMuzzleInHand(unsigned char& _activePlayer)
{
	for (unsigned char i = 0; i < playersCards[_activePlayer].size(); i++)
	{
		if (playersCards[_activePlayer][i].type == ACTION_MUZZLE)
		{
			return true;
		}
	}

	return false;
}

unsigned char GetNBCardsInHand(unsigned char& _activePlayer)
{
	return playersCards[_activePlayer].size();
}

bool GetIsCardIsPlaying(void)
{
	return isACardIsPlaying;
}

bool GetIsBlackMailPlaying(void)
{
	return isBlackmailIsPlaying;
}

bool GetIsDenunciationPlaying(void)
{
	return isDenunciationIsPlaying;
}

bool GetInsertIsDisplay(void)
{
	if (isACardIsPlaying)
	{
		return isACardIsPlaying;
	}
	else if (isBlackmailIsPlaying)
	{
		return isBlackmailIsPlaying;
	}
	else if (isDenunciationIsPlaying)
	{
		return isDenunciationIsPlaying;
	}
	else
	{
		return false;
	}
}

bool GetIsTrickDieAIResolved(void)
{
	return trickDieAIResolved;
}

unsigned char GetNbProblematicCardsInHand(unsigned char& _activePlayer)
{
	unsigned char nbCards = 0;
	for (unsigned char i = 0; i < playersCards[_activePlayer].size(); i++)
	{
		if (playersCards[_activePlayer][i].type == ACTION_MUZZLE || playersCards[_activePlayer][i].type == ACTION_TRICK_DIE)
		{
			nbCards++;
		}
	}
	return nbCards;
}

unsigned char& GetTargetPlayerAI(void)
{
	return targetPlayer;
}
sf::Vector2f& GetChanceStackPosition()
{
	return stackChance.pos;
}
sf::Vector2f& GetActionStackPosition()
{
	return stackAction.pos;
}

bool GetIsCardEffectAlreadyResolved(void)
{
	return isCardEffectAlreadyResolved;
}


#pragma endregion Accessors

// Mutators
#pragma region Mutators
void SetChanceStackCanBeSelected()
{
	stackChance.canBeSelected = true;
	stackChance.sprite.setTexture(stackChance.texture[STACK_CAN_BE_SELECTED]);
}

void SetActionStackCanBeSelected()
{
	stackAction.canBeSelected = true;
	stackAction.sprite.setTexture(stackAction.texture[STACK_CAN_BE_SELECTED]);
}

void SetIsMischievousDiceIsPlaying(bool _bool)
{
	isMischievousDiceIsPlaying = _bool;
}

void SetIsDebateIsPlaying(bool _bool)
{
	isDebateIsPlaying = _bool;
}

void SetIsTrickDieIsPlaying(bool _bool)
{
	isTrickDieIsPlaying = _bool;
}

void SetIsCardEffectAlreadyResolved(bool _bool)
{
	isCardEffectAlreadyResolved = _bool;
}

void SetHasAlreadyPlayedCard(bool _bool)
{
	hasAlreadyPlayedCard = _bool;
}

void SetIsAIHasChosenActionCardButton(bool _bool)
{
	isAIHasChosenActionCardButton = _bool;
}

void SetIsTrickDieAIResolved(bool _bool)
{
	trickDieAIResolved = _bool;
}
#pragma endregion Mutators






























































#pragma region AI
void TakeCardFromActionStackAI(void)
{
	if (stackAction.canBeSelected && GetHudPlayerIsDown() && !GetHudPlayerIsMoving())
	{
		PlaySoundFromList(cardSounds[CARD_PICK], 100);
		typeActiveCard = stackAction.type;
		typeActiveStack = stackAction.type;
		stackAction.canBeSelected = false;
		stackAction.sprite.setTexture(stackAction.texture[STACK]);
		if (actionCardsStack.empty())
		{
			ResetCardStack(actionCardsStack, stackAction);
		}

		for (int i = 0; i < NB_CARD_BUTTONS; i++)
		{
			cardButtonList[i].sprite.setScale(0.f, 0.f);
		}
		actionCardsStack[actionCardsStack.size() - 1].sprite.setScale(0.f, 0.f);
		actionCardsStack[actionCardsStack.size() - 1].isDisplay = true;
		isAnyCardDisplaying = true;
		isCardAppears = true;

		switch (actionCardsStack[actionCardsStack.size() - 1].type)
		{
		case ACTION_MUZZLE:
			ReplaceCardButtons(true, false, false);
			break;
		case ACTION_DENUNCIATION:
			ReplaceCardButtons(true, false, true);
			break;
		case ACTION_HUMANITARIAN_AID:
			ReplaceCardButtons(false, true, true);
			break;
		case ACTION_VOTER_PURCHASE:
			ReplaceCardButtons(false, true, true);
			break;
		case ACTION_CALL_A_FRIEND:
			ReplaceCardButtons(true, false, true);
			break;
		case ACTION_SECRET_SERVICE:
			ReplaceCardButtons(true, false, true);
			break;
		case ACTION_FLYERS:
			ReplaceCardButtons(false, true, true);
			break;
		case ACTION_MISAPPROPRIATION:
			ReplaceCardButtons(false, true, true);
			break;
		case ACTION_ACCOUNT_HACK:
			ReplaceCardButtons(true, false, true);
			break;
		case ACTION_MEETING:
			ReplaceCardButtons(false, true, true);
			break;
		case ACTION_DEBATE:
			ReplaceCardButtons(true, false, true);
			break;
		case ACTION_MISCHIEVOUS_DICE:
			ReplaceCardButtons(false, true, true);
			break;
		case ACTION_FREE_TURN:
			if (!GetDiceHasRolling())
			{
				ReplaceCardButtons(true, false, false);
			}
			else
			{
				ReplaceCardButtons(true, false, true);
			}
			break;
		case ACTION_TRICK_DIE:
			ReplaceCardButtons(true, false, false);
			break;
		case ACTION_BLACKMAIL:
			ReplaceCardButtons(true, false, true);
			break;
		case ACTION_CHARITY_ACTION:
			ReplaceCardButtons(false, true, true);
			break;
		default:
			ReplaceCardButtons(false, true, false);
			break;
		}
		SetAICanDrawACard(GetActivePlayer(), false);
	}
}

void TakeCardFromChanceStackAI(void)
{
	if (stackChance.canBeSelected && GetHudPlayerIsDown() && !GetHudPlayerIsMoving() && GetAICanDrawACard(GetActivePlayer()))
	{
		PlaySoundFromList(cardSounds[CARD_PICK], 100);
		typeActiveCard = stackChance.type;
		typeActiveStack = stackChance.type;
		stackChance.canBeSelected = false;
		stackChance.sprite.setTexture(stackChance.texture[STACK]);
		if (chanceCardsStack.empty())
		{
			ResetCardStack(chanceCardsStack, stackChance);
		}

		//timerScaleCards = 0;
		for (int i = 0; i < NB_CARD_BUTTONS; i++)
		{
			cardButtonList[i].sprite.setScale(0.f, 0.f);
		}
		chanceCardsStack[chanceCardsStack.size() - 1].sprite.setScale(0.f, 0.f);
		if (chanceCardsStack[chanceCardsStack.size() - 1].type != CHANCE_TAXES)
		{
			chanceCardsStack[chanceCardsStack.size() - 1].isDisplay = true;
			ReplaceCardButtons(false, true, false);
			isCardAppears = true;
			IsAIpayingTax = false;
			isAnyCardDisplaying = true;
		}
		else
		{
			SetPlayerIsOnTaxe(GetActivePlayer(), true);
			SetTaxIsAppears(true);
			SetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer(), false);
			SwapCardFromVectorToVector(chanceCardsStack, chanceDiscard);
			IsAIpayingTax = true;
		}



		SetAICanDrawACard(GetActivePlayer(), false);
	}
}

float timerChanceCardChoiceAI = 0.f;

void ManageChanceCardsChoiceAI(float& _dt)
{
	if (!isCardEffectAlreadyResolved)
	{
		if (!IsAIpayingTax)
		{
			timerChanceCardChoiceAI += _dt;
			unsigned char activePlayer = GetActivePlayer();
			if (timerChanceCardChoiceAI >= 3.5f)
			{
				PlaySoundFromList(GetButtonPressSound(), 50);
				isCardDisappears = true;
				lastButtonPressed = BUTTON_DISCARD;

				switch (chanceCardsStack[chanceCardsStack.size() - 1].type)
				{
				case CHANCE_LOST_WALLET:
					ResolveChanceLostWallet(activePlayer);
					break;
				case CHANCE_FINDING_BILL:
					ResolveChanceFindingBill(activePlayer);
					break;
				case CHANCE_SPEECH_ERROR:
					ResolveChanceSpeechError(activePlayer);
					break;
				case CHANCE_SMOOTH_TALKER:
					ResolveChanceSmoothTalker(activePlayer);
					break;
				case CHANCE_PRIVATE_JET:
					ResolveChancePrivateJet(activePlayer);
					break;
				case CHANCE_DOUBTFUL_AFFAIR:
					ResolveChanceDoubtfulAffair(activePlayer);
					break;
				case CHANCE_FUNDRAISING:
					ResolveChanceFundraising(activePlayer);
					break;
				case CHANCE_TAXES:
					break;
				case CHANCE_HALT:
					ResolveChanceHalt(activePlayer);
					break;
				case CHANCE_STONE_IN_SHOE:
					ResolveChanceStoneInShoe(activePlayer);
					break;
				case CHANCE_ROCK_IN_SHOE:
					ResolveChanceRockInShoe(activePlayer);
					break;
				case CHANCE_LITTLE_HELP:
					ResolveChanceLittleHelp(activePlayer);
					break;
				case CHANCE_BIG_HELP:
					ResolveChanceBigHelp(activePlayer);
					break;
				case CHANCE_OFFSHORE_FINANCING:
					ResolveChanceOffshoreFinancing(activePlayer);
					break;
				case CHANCE_FAKE_NEWS:
					ResolveChanceFakeNews(activePlayer);
					break;
				case CHANCE_WEB_DEVELOPMENT:
					ResolveChanceWebDevelopment(activePlayer);
					break;
				case CHANCE_BUZZ:
					ResolveChanceBuzz(activePlayer);
					break;
				default:
					std::cout << "Probleme AI chance";
					break;
				}

				timerChanceCardChoiceAI = 0;
				isCardEffectAlreadyResolved = true;
			}
		}
	}
}

void ManageActionCardsChoiceAI(float& _dt)
{
	if (!isAIHasChosenActionCardButton)
	{
		unsigned char random;
		unsigned char activePlayer = GetActivePlayer();
		timerCardChoiceAI += _dt;
		if (timerCardChoiceAI >= 3.5f)
		{

			PlaySoundFromList(GetButtonPressSound(), 50);
			isCardDisappears = true;

			random = rand() % 2;
			CardType type = actionCardsStack[actionCardsStack.size() - 1].type;

			switch (type)
			{
			case ACTION_MUZZLE:
				lastButtonPressed = BUTTON_KEEP;
				break;
			case ACTION_DENUNCIATION:
				lastButtonPressed = BUTTON_KEEP;
				//ResolveActionOnTarget(type);
				break;
			case ACTION_HUMANITARIAN_AID:

				if (random == 0)
				{
					lastButtonPressed = BUTTON_DISCARD;
				}
				else
				{
					lastButtonPressed = BUTTON_USE;
					ResolveActionHumanitarianAid(activePlayer);
				}

				break;
			case ACTION_VOTER_PURCHASE:
				if (random == 0)
				{
					lastButtonPressed = BUTTON_DISCARD;
				}
				else
				{
					lastButtonPressed = BUTTON_USE;
					ResolveActionVoterPurchase(activePlayer);
				}

				break;
			case ACTION_CALL_A_FRIEND:
				lastButtonPressed = BUTTON_KEEP;
				//ResolveActionOnTarget(type);
				break;
			case ACTION_SECRET_SERVICE:
				lastButtonPressed = BUTTON_KEEP;
				//ResolveActionOnTarget(type);
				break;
			case ACTION_FLYERS:
				if (random == 0)
				{
					lastButtonPressed = BUTTON_DISCARD;
				}
				else
				{
					lastButtonPressed = BUTTON_USE;
					ResolveActionFlyers(activePlayer);
				}
				break;
			case ACTION_MISAPPROPRIATION:
				if (random == 0)
				{
					lastButtonPressed = BUTTON_DISCARD;
				}
				else
				{
					lastButtonPressed = BUTTON_USE;
					ResolveActionMisappropriation(activePlayer);
				}
				break;
			case ACTION_ACCOUNT_HACK:
				lastButtonPressed = BUTTON_KEEP;
				//ResolveActionOnTarget(type);
				break;
			case ACTION_MEETING:
				if (random == 0)
				{
					lastButtonPressed = BUTTON_DISCARD;
				}
				else
				{
					lastButtonPressed = BUTTON_USE;
					ResolveActionMeeting(activePlayer);
				}
				break;
			case ACTION_DEBATE:
				lastButtonPressed = BUTTON_KEEP;
				//ResolveActionOnTarget(type);
				break;
			case ACTION_MISCHIEVOUS_DICE:
				if (random == 0)
				{
					lastButtonPressed = BUTTON_DISCARD;
				}
				else
				{
					lastButtonPressed = BUTTON_USE;
					InitActionMischievousDice();
				}

				break;
			case ACTION_FREE_TURN:
				if (random == 0)
				{
					lastButtonPressed = BUTTON_KEEP;
				}
				else if (random == 1 && GetDiceHasRolling())
				{
					lastButtonPressed = BUTTON_USE;
					ResolveActionFreeTurn(activePlayer);
				}
				else
				{
					lastButtonPressed = BUTTON_KEEP;
				}
				break;
			case ACTION_TRICK_DIE:

				lastButtonPressed = BUTTON_KEEP;
				break;
			case ACTION_BLACKMAIL:
				lastButtonPressed = BUTTON_KEEP;
				//ResolveActionOnTarget(type);
				break;
			case ACTION_CHARITY_ACTION:
				if (random == 0)
				{
					lastButtonPressed = BUTTON_DISCARD;
				}
				else
				{
					lastButtonPressed = BUTTON_USE;
					ResolveActionCharityAction(activePlayer);
				}
				break;
			default:
				std::cout << "problème ia action" << std::endl;
				break;
			}

			timerCardChoiceAI = 0;
			isAIHasChosenActionCardButton = true;
		}
	}
}



void ActionCardsManagerAI(unsigned char& _activePlayer, float& _dt)
{
	if (!isCardEffectAlreadyResolved)
	{
		unsigned char random;
		timerPlayCard += _dt;
		if (timerPlayCard == _dt)
		{
			for (unsigned char i = 0; i < playersCards[_activePlayer].size(); i++)
			{
				if (playersCards[_activePlayer][i].type != ACTION_MUZZLE && playersCards[_activePlayer][i].type != ACTION_TRICK_DIE)
				{
					isOkay = true;
				}
			}

			if (GetHudPlayerIsDown() && isOkay)
			{
				SetHudPlayerIsMoving(GetActivePlayer(), true);
			}
		}

		if (!isOkay)
		{
			timerPlayCard = 0.f;
			isOkay = false;
			hasAlreadyPlayedCard = true;
			isCardEffectAlreadyResolved = true;
			isAnyCardDisplaying = false;

			if (!GetHudPlayerIsDown())
			{
				SetHudPlayerIsMoving(_activePlayer, true);
			}

		}

		if (timerPlayCard > 1.f && isOkay)
		{
			if (timerPlayCard < 1.f + _dt)
			{
				do
				{
					randomCard = rand() % playersCards[_activePlayer].size();

				} while (playersCards[_activePlayer][randomCard].type == ACTION_MUZZLE || playersCards[_activePlayer][randomCard].type == ACTION_TRICK_DIE);

				playersCards[_activePlayer][randomCard].isSelected = true;
				isACardSelected = true;
				playersCards[_activePlayer][randomCard].sprite.setScale(ScaleToScreen(1.f, 1.f));
			}

			if (playersCards[_activePlayer][randomCard].isSelected && timerPlayCard > 2.f)
			{
				if (timerPlayCard < 2.f + _dt && playersCards[_activePlayer][randomCard].type != ACTION_FREE_TURN)
				{
					do
					{
						targetPlayer = rand() % 4;
					} while (targetPlayer == _activePlayer);
				}

				PlaySoundFromList(GetButtonPressSound(), 50);
				playersCards[_activePlayer][randomCard].isSelected = false;
				isACardSelected = false;

				switch (playersCards[_activePlayer][randomCard].type)
				{
				case ACTION_DENUNCIATION:
					random = rand() % 2;
					//if (random == 0)
					//{
					//c'est la merde
					SwapActionCardToDiscard(playersCards[_activePlayer], randomCard);
					SetHudPlayerIsMoving(_activePlayer, true);
					launchingAttackPlayer = _activePlayer;
					//SetActivePlayer(targetPlayer);
					ResolveActionDenunciation(targetPlayer);

					//}

					break;
				case ACTION_CALL_A_FRIEND:
					random = rand() % 2;
					//if (random == 0)
					//{

					for (unsigned char i = 0; i < NB_PLAYERS; i++)
					{
						if (GetNbTaxes(i) != 0 && i != _activePlayer)
						{
							callAFriendAIBool = true;
						}
					}
					if (callAFriendAIBool)
					{
						do
						{
							targetPlayer = rand() % 4;
						} while (GetNbTaxes(targetPlayer) < 1 || targetPlayer == _activePlayer);
					}
					else
					{
						playersCards[_activePlayer][randomCard].isDisplay = false;
						timerPlayCard = 0.f;
						isOkay = false;
						hasAlreadyPlayedCard = true;
						isCardEffectAlreadyResolved = true;
						break;
					}

					callAFriendAIBool = false;
					SwapActionCardToDiscard(playersCards[_activePlayer], randomCard);
					SetHudPlayerIsMoving(_activePlayer, true);
					ResolveActionCallAFriend(targetPlayer);
					//}

					break;
				case ACTION_SECRET_SERVICE:
					random = rand() % 2;
					//if (random == 0)
					//{
					SwapActionCardToDiscard(playersCards[_activePlayer], randomCard);
					SetHudPlayerIsMoving(_activePlayer, true);
					ResolveActionSecretService(targetPlayer);
					//}

					break;
				case ACTION_ACCOUNT_HACK:
					random = rand() % 2;
					//if (random == 0)
					//{
					SwapActionCardToDiscard(playersCards[_activePlayer], randomCard);
					SetHudPlayerIsMoving(_activePlayer, true);
					ResolveActionAccountHack(_activePlayer, targetPlayer);
					//}

					break;
				case ACTION_BLACKMAIL:
					random = rand() % 2;
					//if (random == 0)
					//{
					//c'est la merde

					SwapActionCardToDiscard(playersCards[_activePlayer], randomCard);
					SetHudPlayerIsMoving(_activePlayer, true);
					launchingAttackPlayer = _activePlayer;
					isBlackmailIsPlaying = true;
					blackmailInsert.sprite.setScale(1.f, 1.f);
					isCardAppears = true;
					blackmailText[3].setString(GetPlayerPseudo(targetPlayer));
					blackmailText[3].setOrigin(blackmailText[3].getGlobalBounds().width / 2, blackmailText[3].getGlobalBounds().height / 2);
					ActiveYesAndNoButtons();

					//}

					break;
				case ACTION_DEBATE:
					random = rand() % 2;
					//if (random == 0)
					//{
					SwapActionCardToDiscard(playersCards[_activePlayer], randomCard);
					SetHudPlayerIsMoving(_activePlayer, true);
					isDebateIsPlaying = true;
					InitActionDebate();
					//}

					break;
				case ACTION_FREE_TURN:
					random = rand() % 2;
					//if (random == 0)
					//{
					SwapActionCardToDiscard(playersCards[_activePlayer], randomCard);
					SetHudPlayerIsMoving(_activePlayer, true);
					ResolveActionFreeTurn(_activePlayer);
					//}

					break;
				default:
					break;
				}
				timerPlayCard = 0.f;
				isOkay = false;
				hasAlreadyPlayedCard = true;
				isCardEffectAlreadyResolved = true;

				if (!GetHudPlayerIsDown())
				{
					SetHudPlayerIsMoving(_activePlayer, true);
				}
			}
		}
	}

}

void ManageTrickDieAI(unsigned char& _activePlayer, char _index, float& _dt)
{
	if (_index != -1 || !trickDieAIResolved)
	{
		timerPlayTrickDie += _dt;

		if (timerPlayTrickDie == _dt)
		{
			trickDieAIResolved = false;
			if (GetHudPlayerIsDown())
			{
				SetHudPlayerIsMoving(GetActivePlayer(), true);
			}
		}

		if (timerPlayTrickDie > 1.f && timerPlayTrickDie <= 2.f)
		{
			playersCards[_activePlayer][_index].isSelected = true;
			isACardSelected = true;
			playersCards[_activePlayer][_index].sprite.setScale(ScaleToScreen(1.f, 1.f));
		}
		else if (timerPlayTrickDie > 2.f && !isTrickDieIsPlaying && !trickDieAIResolved)
		{
			PlaySoundFromList(GetButtonPressSound(), 50);
			playersCards[_activePlayer][_index].isSelected = false;
			isACardSelected = false;

			SwapActionCardToDiscard(playersCards[_activePlayer], _index);
			SetHudPlayerIsMoving(_activePlayer, true);
			ResolveActionTrickDie(_activePlayer);

			if (!GetHudPlayerIsDown())
			{
				SetHudPlayerIsMoving(_activePlayer, true);
			}
		}
		else if (timerPlayTrickDie > 3.f + GetThirdDiceMaxTimerRoll() && !trickDieAIResolved)
		{
			if (timerPlayTrickDie <= 3.f + GetThirdDiceMaxTimerRoll() + _dt)
			{
				randomDice = rand() % NB_DICES;
				SetDiceIsSelected(randomDice, true);
			}

			if (timerPlayTrickDie > 3.5f + GetThirdDiceMaxTimerRoll() && timerPlayTrickDie <= 3.5f + GetThirdDiceMaxTimerRoll() + _dt)
			{
				do
				{
					randomDice2 = rand() % NB_DICES;
				} while (randomDice2 == randomDice);

				SetDiceIsSelected(randomDice2, true);
				SetDicesNbSelected(2);
			}

			if (timerPlayTrickDie > 4.f + GetThirdDiceMaxTimerRoll())
			{
				SetDicesRiggedValue(GetAnyDiceValue(randomDice) + GetAnyDiceValue(randomDice2));
				if (GetAnyDiceValue(randomDice) == GetAnyDiceValue(randomDice2))
				{
					SetPlayerReplaying(true);
				}
				else
				{
					SetPlayerReplaying(false);
				}

				ResetRiggedDices();
				timerPlayTrickDie = 0.f;
				trickDieAIResolved = true;
				hasAlreadyPlayedCard = true;
			}
		}
	}
}

void BlackMailResponseAI(float& _dt)
{

	timerBlackMailAI += _dt;

	if (timerBlackMailAI > 2.25f)
	{
		randomBlackMail = rand() % 2;
		PlaySoundFromList(GetButtonPressSound(), 50);

		if (randomBlackMail == 0)
		{
			lastButtonPressed = BUTTON_NO;
		}
		else
		{
			lastButtonPressed = BUTTON_YES;
		}
		isInsertDisappears = true;
		timerBlackMailAI = 0.f;
	}
}

void DenunciationResponseAI(unsigned char& _targetPlayer, float& _dt)
{
	timerMuzzleAI += _dt;

	if (timerMuzzleAI > 2.25f)
	{
		PlaySoundFromList(GetButtonPressSound(), 50);
		bool isMuzzleDiscard = false;

		for (unsigned char i = 0; i < playersCards[_targetPlayer].size(); i++)
		{
			if (playersCards[_targetPlayer][i].type == ACTION_MUZZLE && !isMuzzleDiscard)
			{
				SwapActionCardToDiscard(playersCards[_targetPlayer], i);
				isMuzzleDiscard = true;
			}
		}
		isInsertDisappears = true;
		timerMuzzleAI = 0.f;
	}
}

#pragma endregion AI