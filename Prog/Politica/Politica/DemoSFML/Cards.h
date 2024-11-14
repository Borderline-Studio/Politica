#ifndef CARDS_H
#define CARDS_H

#include "Common.h"
#include "Animation.h"
#include "Audio.h"

#define NB_CARDS_ACTION 32
#define NB_CARDS_CHANCE 34
#define NB_CARD_BUTTONS 5
#define NB_BLACKMAIL_TEXTS 4
#define NB_MUZZLE_TEXTS 2
#define NB_CARD_SOUNDS 2
// Scale of a card when in player's hand
#define CARD_SCALE_VALUE 0.57f
// Distance between two cards when in player's hand
#define STEP_BETWEEN_CARDS (1 / 30.f) * GetScreen().height

// Type of a card
enum CardType
{
	ACTION_MUZZLE,
	ACTION_DENUNCIATION,
	ACTION_HUMANITARIAN_AID,
	ACTION_VOTER_PURCHASE,
	ACTION_CALL_A_FRIEND,
	ACTION_SECRET_SERVICE,
	ACTION_FLYERS,
	ACTION_MISAPPROPRIATION,
	ACTION_ACCOUNT_HACK,
	ACTION_MEETING,
	ACTION_DEBATE,
	ACTION_MISCHIEVOUS_DICE,
	ACTION_FREE_TURN,
	ACTION_TRICK_DIE,
	ACTION_BLACKMAIL,
	ACTION_CHARITY_ACTION,
	CHANCE_LOST_WALLET,
	CHANCE_FINDING_BILL,
	CHANCE_SPEECH_ERROR,
	CHANCE_SMOOTH_TALKER,
	CHANCE_PRIVATE_JET,
	CHANCE_DOUBTFUL_AFFAIR,
	CHANCE_FUNDRAISING,
	CHANCE_TAXES,
	CHANCE_HALT,
	CHANCE_STONE_IN_SHOE,
	CHANCE_ROCK_IN_SHOE,
	CHANCE_LITTLE_HELP,
	CHANCE_BIG_HELP,
	CHANCE_OFFSHORE_FINANCING,
	CHANCE_FAKE_NEWS,
	CHANCE_WEB_DEVELOPMENT,
	CHANCE_BUZZ,
	ACTION_CARD,
	CHANCE_CARD
};

enum StackTexture
{
	STACK,
	STACK_CAN_BE_SELECTED,
	STACK_SELECTED
};

// Sounds for cards
enum CardSounds
{
	CARD_PICK,
	CARD_PLAYED,
};

// Frontside of a card
struct Card
{
	sf::Texture* texture;
	sf::Sprite sprite;
	CardType type;
	sf::Vector2f pos;
	bool canBeKept;
	bool isDisplay;
	bool isSelected;
};

// Backside of a stack
struct Stack
{
	sf::Texture texture[3];
	sf::Sprite sprite;
	sf::Vector2u size;
	sf::Vector2f pos;
	CardType type;
	bool canBeSelected;
	bool isSelected;
};

// Insert for special actions
struct Insert
{
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f pos;
};

#pragma region Init
// General init for cards
void InitCards();
// Reinit card datas for a new game
void ReloadCards(void);
// Init datas for a card stack
void InitCardStack(Stack& _cardStack, std::string _file, std::string _file2, std::string _file3, float _posX, float _posY);
// Init type of the two stacks
void InitCardStackType(void);
// Create a new card
Card CreateCard(std::string _file, CardType _type, bool _canBeKept = false);
// Init all action cards datas
void InitActionCards();
// Init all chance cards datas
void InitChanceCards();
// Mix up the choosen card stack
void MixUpCards(std::vector<Card>& _cardsStack);
// Init datas for future player's cards
void InitPlayerCards();
// Init buttons to interact with cards
void InitCardButton();
// Init insert for special actions
void InitInserts();
// Init texts in each insert
void InitInsertTexts();
// Init sounds for cards
void InitCardSounds();
#pragma endregion Init

#pragma region Update
void UpdateCards(GameData& _gameData);
void UpdateCardsButtonsAnimation();
void UpdateInsertsButtonsAnimation();
void SwapCardFromVectorToVector(std::vector<Card>& _fromVector, std::vector<Card>& _toVector);
void SwapActionCardToDiscard(std::vector<Card>& _cardList, unsigned char _index);
void ResetCardStack(std::vector<Card>& _cardVector, Stack& _stack);
void ReplaceCardButtons(bool _isKeepDisplay, bool _isDiscardDisplay, bool _isUseDisplay);
void PlaceCardsInPlayerStack();
void CheckIfMousePressedOnCard(GameData& _gameData, std::vector<std::vector<Card>>& _playersCards);
void ActiveYesAndNoButtons();
void UpdateCardsScale(float _dt);
void UpdateButtonScale(float _dt);
void UpdateInsertScale(float _dt);
void UpdateTargetInsertScale(float _dt);
void InitActionMischievousDice();
void InitActionDebate();
void ResolveActionOnTarget(CardType& _type);
#pragma endregion Update

#pragma region ResolveActionCards
void ResolveActionMuzzle(unsigned char _targetPlayer);
void ResolveActionDenunciation(unsigned char _targetPlayer);
void ResolveActionHumanitarianAid(unsigned char _activePlayer);
void ResolveActionVoterPurchase(unsigned char _activePlayer);
void ResolveActionCallAFriend(unsigned char _targetPlayer);
void ResolveActionSecretService(unsigned char _targetPlayer);
void ResolveActionFlyers(unsigned char _activePlayer);
void ResolveActionAccountHack(unsigned char _activePlayer, unsigned char _targetPlayer);
void ResolveActionMeeting(unsigned char _activePlayer);
void ResolveActionDebate(unsigned char _targetPlayer);
void ResolveActionMischievousDice();
void ResolveActionFreeTurn(unsigned char _activePlayer);
void ResolveActionTrickDie(unsigned char _activePlayer);
void ResolveActionBlackmail(unsigned char _activePlayer, unsigned char _targetPlayer, bool _isAccepted);
#pragma endregion ResolveActionCards

#pragma region ResolveChanceCards
void ResolveChanceLostWallet(unsigned char _activePlayer);
void ResolveChanceFindingBill(unsigned char _activePlayer);
void ResolveChanceSpeechError(unsigned char _activePlayer);
void ResolveChanceSmoothTalker(unsigned char _activePlayer);
void ResolveChancePrivateJet(unsigned char _activePlayer);
void ResolveChanceDoubtfulAffair(unsigned char _activePlayer);
void ResolveChanceFundraising(unsigned char _activePlayer);
void ResolveChanceHalt(unsigned char _activePlayer);
void ResolveChanceStoneInShoe(unsigned char _activePlayer);
void ResolveChanceRockInShoe(unsigned char _activePlayer);
void ResolveChanceLittleHelp(unsigned char _activePlayer);
void ResolveChanceBigHelp(unsigned char _activePlayer);
void ResolveChanceOffshoreFinancing(unsigned char _activePlayer);
void ResolveChanceFakeNews(unsigned char _activePlayer);
void ResolveChanceWebDevelopment(unsigned char _activePlayer);
#pragma endregion ResolveChanceCards

#pragma region Display
void DisplayCards(sf::RenderWindow& _window);
void DisplayStacks(sf::RenderWindow& _window);
void DisplayActiveCard(std::vector<Card>& _cardVector, sf::RenderWindow& _window);
void DisplayPlayerCards(sf::RenderWindow& _window);
void DisplayCardButtons(sf::RenderWindow& _window);
void UnDrawCardButtons();
void UnDrawInsertButtons();
void DisplayInserts(sf::RenderWindow& _window);
#pragma endregion Display

#pragma region MouseMoved
void MouseMovedCards(sf::Event::MouseMoveEvent _buttonEvt);
void CheckMouseStackCollision(Stack& _stack, sf::Event::MouseMoveEvent _buttonEvt);
void CheckMouseCardButtonCollision(Button& _button, sf::Event::MouseMoveEvent _buttonEvt);
void CheckMouseInsertButtonCollision(Button* _button, sf::Event::MouseMoveEvent _buttonEvt);
void UpdateSelectedCardPosition(sf::Event::MouseMoveEvent _buttonEvt);
#pragma endregion MouseMoved

#pragma region MousePressed
void MousePressedCards(GameData& _gameData, sf::Event::MouseButtonEvent _buttonEvt);
void CheckMousePressedStack(GameData& _gameData, sf::Event::MouseButtonEvent _buttonEvt, std::vector<Card>& _cardVector, Stack& _stack);
void CheckMousePressedCardButton(GameData& _gameData, sf::Event::MouseButtonEvent _buttonEvt, Button& _button);
void CheckMousePressedInsertsButton(GameData& _gameData, sf::Event::MouseButtonEvent _buttonEvt, Button* _button);
void CheckMousePressedTargetSelection(GameData& _gameData, sf::Event::MouseButtonEvent _buttonEvt);
#pragma endregion MousePressed

void MouseReleasedCards(GameData& _gameData, sf::Event::MouseButtonEvent _buttonEvt);

#endif // !CARDS_H