#include "Common.h"
#include "GameState.h"

int main()
{
	GameData gameData;
	srand((unsigned int)time(NULL));
	Init(gameData);

	while (gameData.window.isOpen())
	{
		PollEvent(gameData);
		Update(gameData);
		Display(gameData);
	}
}


