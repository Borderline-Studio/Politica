#include"TurnManager.h"

TurnManager turnManager;

void InitTurnManager(void)
{
	turnManager.nbTurns = 0;
	turnManager.nbTurns4players = 0;
	turnManager.activePlayer = PLAYER_1;
}

void UpdateTurnManager(float& _dt, int& _state)
{
	if (turnManager.nbTurns == MAX_TURN && !GetIsInParliamentaryCouncil() && !GetGameFadeOut())
	{
		unsigned char activePlayer = PLAYER_1;
		setDiceHasRolling(false);
		SetLaunchedDices(1);
		SetIsInParliamentaryCouncil(true);
		SetParliamentaryIsAppears(true);
		SetPseudoInInsert(activePlayer);
		SetNoOneIsMoving(false);
		PlaySoundFromList(GetParliamentaryCouncilSound(), 50);
	}
	if (GetPlayerHasFinishedTurn(turnManager.activePlayer) && !GetPlayerGoingToFiscalControl(turnManager.activePlayer) && !GetIsDebateIsPlaying() && !GetIsInParliamentaryCouncil())
	{
		turnManager.nbTurns4players++;

		SetLaunchedDices(2);
		SetHasAlreadyPlayedCard(false);
		SetAICanDrawACard(turnManager.activePlayer, false);
		SetIsAIHasChosenActionCardButton(false);
		setDiceHasRolling(false);
		SetIsCardEffectAlreadyResolved(false);
		SetPlayerHasTookMysteryAction(turnManager.activePlayer, true);
		SetMysteryActionPlayingAI(GetActivePlayer(), false);
		SetPlayerHasChooseToPaidTaxesOrNot(turnManager.activePlayer, true);
		SetPlayerIsOnMysterytile(turnManager.activePlayer, false);
		SetPlayerHasAlreadyMoved(turnManager.activePlayer, false);
		SetPlayerIsOnParliamentarytile(turnManager.activePlayer, false);

		if (turnManager.activePlayer < PLAYER_4)
		{
			turnManager.activePlayer++;
		}
		else
		{
			turnManager.activePlayer = PLAYER_1;
			turnManager.nbTurns++;
			for (unsigned char i = 0; i < NB_PLAYERS; i++)
			{
				SetPlayerHasFinishedTurn(i, false);
			}
		}
	}
}

unsigned char& GetActivePlayer(void)
{
	return turnManager.activePlayer;
}

void SetActivePlayer(unsigned char& _i)
{
	if (_i >= PLAYER_1 && _i <= PLAYER_4)
	{
		turnManager.activePlayer = _i;
	}
	else
	{
		std::cout << "error on setActivePlayer" << std::endl;
	}
}

unsigned char GetNbTurns(void)
{
	return turnManager.nbTurns;
}

unsigned char GetNbTurns4Players(void)
{
	return turnManager.nbTurns4players;
}

