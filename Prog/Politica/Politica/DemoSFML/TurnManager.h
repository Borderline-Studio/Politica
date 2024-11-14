#ifndef TURN_MANAGER_H

#define TURN_MANAGER_H

#include"Common.h"
#include"Audio.h"

struct TurnManager
{
	unsigned char nbTurns;
	unsigned char nbTurns4players;
	unsigned char activePlayer;
};

void UpdateTurnManager(float& _dt, int& _state);

#endif // !TURN_MANAGER_H


