#include "TilesManager.h"

TileSound tileSound;

VectorRoads vectorRoads;

void InitTiles(void)
{
	// 90 case
	//principal road
	SetGridType(2, 13, START);
	SetGridType(2, 12, MALUS_MONEY);
	SetGridType(2, 11, BONUS_MONEY);
	SetGridType(2, 10, MYSTERY);
	SetGridType(2, 9, CHANCE);
	SetGridType(2, 8, ACTION);
	SetGridType(2, 7, TAXES);
	SetGridType(2, 6, ACTION);
	SetGridType(2, 5, MALUS_VOTERS);
	SetGridType(2, 4, MYSTERY);
	SetGridType(2, 3, BONUS_REPUTATION);
	SetGridType(2, 2, ACTION);
	SetGridType(3, 2, MALUS_MONEY);
	SetGridType(4, 2, CHANCE);
	SetGridType(5, 2, ACTION);
	SetGridType(6, 2, REPUTATION_VOTERS);
	SetGridType(6, 1, BONUS_REPUTATION);
	SetGridType(7, 1, MALUS_REPUTATION);
	SetGridType(8, 1, MYSTERY);
	SetGridType(9, 1, ACTION);
	SetGridType(10, 1, REPUTATION_MONEY);
	SetGridType(11, 1, CHANCE);
	SetGridType(12, 1, SALARY);
	SetGridType(12, 2, MALUS_VOTERS);
	SetGridType(12, 3, BONUS_REPUTATION);
	SetGridType(12, 4, MALUS_REPUTATION);
	SetGridType(12, 5, ACTION);
	SetGridType(12, 6, REPUTATION_MONEY);
	SetGridType(11, 6, CHANCE);
	SetGridType(10, 6, BONUS_REPUTATION);
	SetGridType(9, 6, TAX_AUDIT);
	SetGridType(8, 6, MALUS_MONEY);
	SetGridType(7, 6, PARLIAMENTARY_COUNCIL);
	SetGridType(6, 6, CHANCE);
	SetGridType(5, 6, REPUTATION_VOTERS);
	SetGridType(4, 6, ACTION);
	SetGridType(4, 7, CHANCE);
	SetGridType(4, 8, BREAK);
	SetGridType(4, 9, BONUS_REPUTATION);
	SetGridType(4, 10, MALUS_MONEY);
	SetGridType(4, 11, MALUS_REPUTATION);
	SetGridType(5, 11, ACTION);
	SetGridType(6, 11, BONUS_VOTERS);
	SetGridType(7, 11, BONUS_MONEY);
	SetGridType(8, 11, MYSTERY);
	SetGridType(9, 11, CHANCE);
	SetGridType(10, 11, REPUTATION_VOTERS);
	SetGridType(11, 11, BONUS_REPUTATION);
	SetGridType(12, 11, SALARY);
	SetGridType(12, 10, ACTION);
	SetGridType(12, 9, CHANCE);
	SetGridType(12, 8, BONUS_REPUTATION);
	SetGridType(13, 8, CHANCE);
	SetGridType(14, 8, MALUS_REPUTATION);
	SetGridType(14, 9, TAXES);
	SetGridType(14, 10, BONUS_REPUTATION);
	SetGridType(14, 11, REPUTATION_MONEY);
	SetGridType(14, 12, MYSTERY);
	SetGridType(14, 13, PARLIAMENTARY_COUNCIL);
	SetGridType(13, 13, BREAK);
	SetGridType(13, 14, BONUS_REPUTATION);
	SetGridType(13, 15, MALUS_REPUTATION);
	SetGridType(12, 15, ACTION);
	SetGridType(11, 15, CHANCE);
	SetGridType(10, 15, MYSTERY);
	SetGridType(9, 15, REPUTATION_MONEY);
	SetGridType(8, 15, EXAM);
	SetGridType(8, 14, ACTION);
	SetGridType(8, 13, TAXES);
	SetGridType(7, 13, BONUS_REPUTATION);
	SetGridType(6, 13, MALUS_VOTERS);
	SetGridType(5, 13, REPUTATION_VOTERS);
	SetGridType(4, 13, TAX_AUDIT);
	SetGridType(3, 13, CHANCE);

	//shortcut 1 
	SetGridType(3, 4, BONUS_MONEY_SHORTCUT);
	SetGridType(4, 4, ACTION);
	SetGridType(5, 4, MALUS_REPUTATION_SHORTCUT);
	SetGridType(6, 4, MALUS_MONEY_SHORTCUT);
	SetGridType(7, 4, REPUTATION_VOTERS_SHORTCUT);
	SetGridType(8, 4, MYSTERY);
	SetGridType(9, 4, CHANCE);
	SetGridType(10, 4, BONUS_VOTERS_SHORTCUT);
	SetGridType(11, 4, MALUS_MONEY_SHORTCUT);

	//shortcut 2
	SetGridType(5, 8, BONUS_MONEY_SHORTCUT);
	SetGridType(6, 8, BONUS_REPUTATION_SHORTCUT);
	SetGridType(7, 8, REPUTATION_VOTERS_SHORTCUT);
	SetGridType(8, 8, ACTION);
	SetGridType(9, 8, MYSTERY);
	SetGridType(10, 8, MALUS_REPUTATION_SHORTCUT);
	SetGridType(11, 8, REPUTATION_MONEY_SHORTCUT);

	tileSound.cashOnTile = AddSound("Assets/Sounds/CashOnTile.ogg");
	tileSound.cashNotOnTile = AddSound("Assets/Sounds/CashNotOnTile.ogg");
	tileSound.bonus = AddSound("Assets/Sounds/Bonus.ogg");
	tileSound.malus = AddSound("Assets/Sounds/Malus.ogg");
	tileSound.parliamentaryCouncil = AddSound("Assets/Sounds/ParliamentaryCouncil.ogg");
	tileSound.piecePlacement = AddSound("Assets/Sounds/PiecePlacement.ogg");
}

void UpdateTilesAction(sf::Vector2f _gridPos, int _playerIdx)
{
	unsigned char activePlayer = 0;
	switch (GetTileType((int)_gridPos.x, (int)_gridPos.y))
	{
	case START:
		if (GetPlayerNbTilesMoving(_playerIdx) > 0)
		{
			AddPlayerMoney(_playerIdx, 10000);
			PlaySoundFromList(tileSound.cashNotOnTile, 100);
		}
		else
		{
			AddPlayerMoney(_playerIdx, 20000);
			PlaySoundFromList(tileSound.cashOnTile, 100);
		}
		break;
	case BONUS_MONEY:
		AddPlayerMoney(_playerIdx, 10000);
		PlaySoundFromList(tileSound.bonus, 100);
		break;
	case BONUS_REPUTATION:
		AddPlayerReputation(_playerIdx, 1);
		PlaySoundFromList(tileSound.bonus, 100);
		break;
	case BONUS_VOTERS:
		AddPlayerVoters(_playerIdx, 100);
		PlaySoundFromList(tileSound.bonus, 100);
		break;
	case BONUS_MONEY_SHORTCUT:
		AddPlayerMoney(_playerIdx, 20000);
		PlaySoundFromList(tileSound.bonus, 100);
		break;
	case BONUS_REPUTATION_SHORTCUT:
		AddPlayerReputation(_playerIdx, 2);
		PlaySoundFromList(tileSound.bonus, 100);
		break;
	case BONUS_VOTERS_SHORTCUT:
		AddPlayerVoters(_playerIdx, 200);
		PlaySoundFromList(tileSound.bonus, 100);
		break;
	case REPUTATION_MONEY:
		AddPlayerMoney(_playerIdx, GetPlayersReputation(_playerIdx) * 3000);
		if (GetPlayersReputation(_playerIdx) > 0)
		{
			PlaySoundFromList(tileSound.bonus, 100);
		}
		else if (GetPlayersReputation(_playerIdx) < 0)
		{
			PlaySoundFromList(tileSound.malus, 100);
		}
		else
		{
			PlaySoundFromList(tileSound.piecePlacement, 100);
		}
		break;
	case REPUTATION_VOTERS:
		AddPlayerVoters(_playerIdx, GetPlayersReputation(_playerIdx) * 50);
		if (GetPlayersReputation(_playerIdx) > 0)
		{
			PlaySoundFromList(tileSound.bonus, 100);
		}
		else if (GetPlayersReputation(_playerIdx) < 0)
		{
			PlaySoundFromList(tileSound.malus, 100);
		}
		else
		{
			PlaySoundFromList(tileSound.piecePlacement, 100);
		}
		break;
	case REPUTATION_MONEY_SHORTCUT:
		AddPlayerMoney(_playerIdx, GetPlayersReputation(_playerIdx) * 6000);
		if (GetPlayersReputation(_playerIdx) > 0)
		{
			PlaySoundFromList(tileSound.bonus, 100);
		}
		else if (GetPlayersReputation(_playerIdx) < 0)
		{
			PlaySoundFromList(tileSound.malus, 100);
		}
		else
		{
			PlaySoundFromList(tileSound.piecePlacement, 100);
		}
		break;
	case REPUTATION_VOTERS_SHORTCUT:
		AddPlayerVoters(_playerIdx, GetPlayersReputation(_playerIdx) * 100);
		if (GetPlayersReputation(_playerIdx) > 0)
		{
			PlaySoundFromList(tileSound.bonus, 100);
		}
		else if (GetPlayersReputation(_playerIdx) < 0)
		{
			PlaySoundFromList(tileSound.malus, 100);
		}
		else
		{
			PlaySoundFromList(tileSound.piecePlacement, 100);
		}
		break;
	case MALUS_MONEY:
		AddPlayerMoney(_playerIdx, -10000);
		PlaySoundFromList(tileSound.malus, 100);
		break;
	case MALUS_REPUTATION:
		AddPlayerReputation(_playerIdx, -1);
		PlaySoundFromList(tileSound.malus, 100);
		break;
	case MALUS_VOTERS:
		AddPlayerVoters(_playerIdx, -100);
		PlaySoundFromList(tileSound.malus, 100);
		break;
	case MALUS_MONEY_SHORTCUT:
		AddPlayerMoney(_playerIdx, -20000);
		PlaySoundFromList(tileSound.malus, 50);
		break;
	case MALUS_REPUTATION_SHORTCUT:
		AddPlayerReputation(_playerIdx, -2);
		PlaySoundFromList(tileSound.malus, 100);
		break;
	case MALUS_VOTERS_SHORTCUT:
		AddPlayerVoters(_playerIdx, -200);
		PlaySoundFromList(tileSound.malus, 100);
		break;
	case ACTION:
		SetActionStackCanBeSelected();
		PlaySoundFromList(tileSound.piecePlacement, 100);
		break;
	case CHANCE:
		SetChanceStackCanBeSelected();
		PlaySoundFromList(tileSound.piecePlacement, 100);
		break;
	case MYSTERY:
		setDiceHasRolling(false);
		SetLaunchedDices(1);
		SetMysteryIsAppears(true);
		SetPlayerHasTookMysteryAction(_playerIdx, false);
		SetPlayerIsOnMysterytile(_playerIdx, true);
		PlaySoundFromList(tileSound.piecePlacement, 100);
		break;
	case TAX_AUDIT:
		AddPlayerMoney(_playerIdx, GetNbTaxes(_playerIdx) * -30000);
		AddPlayerReputation(_playerIdx, GetNbTaxes(_playerIdx) * -2);
		AddPlayerVoters(_playerIdx, GetNbTaxes(_playerIdx) * -200);
		AddTaxes(_playerIdx, -GetNbTaxes(_playerIdx));
		if (GetNbTaxes(_playerIdx) > 0)
		{
			PlaySoundFromList(tileSound.malus, 100);
		}
		else
		{
			PlaySoundFromList(tileSound.piecePlacement, 100);
		}
		break;
	case PARLIAMENTARY_COUNCIL:
		SetPlayerIsOnParliamentarytile(_playerIdx,true);
		setDiceHasRolling(false);
		SetLaunchedDices(1);
		SetActivePlayer(activePlayer);
		SetIsInParliamentaryCouncil(true);
		SetParliamentaryIsAppears(true);
		SetPseudoInInsert(activePlayer);
		SetLastPlayerPlayed(_playerIdx);		
		PlaySoundFromList(tileSound.parliamentaryCouncil, 50);
		break;
	case BREAK:
		PlaySoundFromList(tileSound.piecePlacement, 100);
		break;
	case EXAM:

		if (GetPlayersReputation(_playerIdx) > 0)
		{
			AddPlayerVoters(_playerIdx, GetPlayersReputation(_playerIdx) * 50);
			PlaySoundFromList(tileSound.bonus, 100);
		}
		else if (GetPlayersReputation(_playerIdx) < 0)
		{
			AddPlayerVoters(_playerIdx, GetPlayersReputation(_playerIdx) * 100);
			PlaySoundFromList(tileSound.malus, 100);
		}
		else
		{
			AddPlayerVoters(GetPlayersReputation(_playerIdx), 0);
			PlaySoundFromList(tileSound.piecePlacement, 100);
		}

		break;
	case SALARY:
		if (GetPlayerNbTilesMoving(_playerIdx) > 0)
		{
			AddPlayerMoney(_playerIdx, 10000);
			PlaySoundFromList(tileSound.cashNotOnTile, 100);
		}
		else
		{
			AddPlayerMoney(_playerIdx, 20000);
			PlaySoundFromList(tileSound.cashOnTile, 100);
		}
		break;
	case TAXES:
		SetPlayerIsOnTaxe(_playerIdx, true);
		SetPlayerHasChooseToPaidTaxesOrNot(_playerIdx, false);
		PlaySoundFromList(tileSound.piecePlacement, 100);
		SetTaxIsAppears(true);
		break;
	}
}

void InitRoads(void)
{
	vectorRoads.mainRoad1.push_back({ 2,3 });
	vectorRoads.mainRoad1.push_back({ 2,2 });
	vectorRoads.mainRoad1.push_back({ 3,2 });
	vectorRoads.mainRoad1.push_back({ 4,2 });
	vectorRoads.mainRoad1.push_back({ 5,2 });
	vectorRoads.mainRoad1.push_back({ 6,2 });
	vectorRoads.mainRoad1.push_back({ 6,1 });
	vectorRoads.mainRoad1.push_back({ 7,1 });
	vectorRoads.mainRoad1.push_back({ 8,1 });
	vectorRoads.mainRoad1.push_back({ 9,1 });
	vectorRoads.mainRoad1.push_back({ 10,1 });
	vectorRoads.mainRoad1.push_back({ 11,1 });

	vectorRoads.shortcutRoad1.push_back({ 3,4 });
	vectorRoads.shortcutRoad1.push_back({ 4,4 });
	vectorRoads.shortcutRoad1.push_back({ 5,4 });
	vectorRoads.shortcutRoad1.push_back({ 6,4 });
	vectorRoads.shortcutRoad1.push_back({ 7,4 });
	vectorRoads.shortcutRoad1.push_back({ 8,4 });
	vectorRoads.shortcutRoad1.push_back({ 9,4 });
	vectorRoads.shortcutRoad1.push_back({ 10,4 });
	vectorRoads.shortcutRoad1.push_back({ 11,4 });
	vectorRoads.shortcutRoad1.push_back({ 12,4 });
	vectorRoads.shortcutRoad1.push_back({ 12,5 });
	vectorRoads.shortcutRoad1.push_back({ 12,6 });

	vectorRoads.mainRoad2.push_back({ 4,9 });
	vectorRoads.mainRoad2.push_back({ 4,10 });
	vectorRoads.mainRoad2.push_back({ 4,11 });
	vectorRoads.mainRoad2.push_back({ 5,11 });
	vectorRoads.mainRoad2.push_back({ 6,11 });
	vectorRoads.mainRoad2.push_back({ 7,11 });
	vectorRoads.mainRoad2.push_back({ 8,11 });
	vectorRoads.mainRoad2.push_back({ 9,11 });
	vectorRoads.mainRoad2.push_back({ 10,11 });
	vectorRoads.mainRoad2.push_back({ 11,11 });
	vectorRoads.mainRoad2.push_back({ 12,11 });
	vectorRoads.mainRoad2.push_back({ 12,10 });

	vectorRoads.shortcutRoad2.push_back({ 5,8 });
	vectorRoads.shortcutRoad2.push_back({ 6,8 });
	vectorRoads.shortcutRoad2.push_back({ 7,8 });
	vectorRoads.shortcutRoad2.push_back({ 8,8 });
	vectorRoads.shortcutRoad2.push_back({ 9,8 });
	vectorRoads.shortcutRoad2.push_back({ 10,8 });
	vectorRoads.shortcutRoad2.push_back({ 11,8 });
	vectorRoads.shortcutRoad2.push_back({ 12,8 });
	vectorRoads.shortcutRoad2.push_back({ 13,8 });
	vectorRoads.shortcutRoad2.push_back({ 14,8 });
	vectorRoads.shortcutRoad2.push_back({ 14,9 });
	vectorRoads.shortcutRoad2.push_back({ 14,10 });
}

VectorRoads GetVectorRoad(void )
{
	return vectorRoads;
}