#ifndef  GAMESTATE_H

#define GAMESTATE_H

#include"Common.h"
#include"Screen.h"
#include"Game.h"
#include"Menu.h"
#include"PreMenu.h"
#include"Pause.h"
#include"GameOver.h"
#include"Settings.h"
#include"Credits.h"
#include"KeyBindings.h"
#include"CharacterSelection.h"
#include"LoadingScreen.h"
#include"Cursor.h"

void Init(GameData& _gameData);
void Update(GameData& _gameData);
void PollEvent(GameData& _gameData);
void Display(GameData& _gameData);
#endif // ! GAMESTATE_H
