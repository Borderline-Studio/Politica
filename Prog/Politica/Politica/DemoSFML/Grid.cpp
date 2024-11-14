#include "Grid.h"

Block grid[LINE_GRID][COLUMN_GRID];
Objects decosGrid[LINE_GRID][COLUMN_GRID];
Objects decosGridRoadWay[LINE_GRID][COLUMN_GRID];
sf::Sprite tilesSpriteTab[NB_SPRITES_TILES];
sf::Sprite decoSpriteTab[NB_SPRITES_DECO];
sf::Sprite decoSpriteTabRoadWay[NB_SPRITES_DECO_ROADWAY];

void InitDecoSprites(void)
{

	std::string path = "Assets/Images/GridDecorations/";

	decoSpriteTab[BUILDING_LEFT] = LoadSprite(path + "BuildingLeftOriented.png");
	decoSpriteTab[BUILDING_RIGHT] = LoadSprite(path + "BuildingRightOriented.png");
	decoSpriteTab[SMALL_BUILDING] = LoadSprite(path + "SmallBuildingLeftOriented.png");
	decoSpriteTab[HOUSE] = LoadSprite(path + "House.png");
	decoSpriteTab[HOUSE2] = LoadSprite(path + "House2.png");
	decoSpriteTab[TOWER] = LoadSprite(path + "Tower.png");
	decoSpriteTab[STREET_LAMP_LEFT] = LoadSprite(path + "StreetLampLeft.png");
	decoSpriteTab[STREET_LAMP_RIGHT] = LoadSprite(path + "StreetLampRight.png");
	decoSpriteTab[SIGN_LEFT] = LoadSprite(path + "SignLeft.png");
	decoSpriteTab[SIGN_RIGHT] = LoadSprite(path + "SignRight.png");
	decoSpriteTab[SCHOOL] = LoadSprite(path + "School.png");
	decoSpriteTab[TREE1] = LoadSprite(path + "Tree/Tree1.png");
	decoSpriteTab[TREE2] = LoadSprite(path + "Tree/Tree2.png");
	decoSpriteTab[TREE3] = LoadSprite(path + "Tree/Tree3.png");
	decoSpriteTab[TREE4] = LoadSprite(path + "Tree/Tree4.png");
	decoSpriteTab[TREES1] = LoadSprite(path + "Trees/Trees1.png");
	decoSpriteTab[TREES2] = LoadSprite(path + "Trees/Trees2.png");
	decoSpriteTab[TREES3] = LoadSprite(path + "Trees/Trees3.png");
	decoSpriteTab[TREES4] = LoadSprite(path + "Trees/Trees4.png");

	decoSpriteTabRoadWay[TAR_BASE] = LoadSprite(path + "TarBase.png");
	decoSpriteTabRoadWay[SIDEWALK_BOTTOM] = LoadSprite(path + "SidewalkBottom.png");
	decoSpriteTabRoadWay[SIDEWALK_TOP] = LoadSprite(path + "SidewalkTop.png");
	decoSpriteTabRoadWay[SIDEWALK_LEFT] = LoadSprite(path + "SidewalkLeft.png");
	decoSpriteTabRoadWay[SIDEWALK_RIGHT] = LoadSprite(path + "SidewalkRight.png");
	decoSpriteTabRoadWay[SIDEWALK_RIGHT_LITTLE] = LoadSprite(path + "SidewalkRightLittle.png");
	decoSpriteTabRoadWay[SIDEWALK_LEFT_LITTLE] = LoadSprite(path + "SidewalkLeftLittle.png");
	decoSpriteTabRoadWay[SIDEWALK_TOP_LITTLE] = LoadSprite(path + "SidewalkTopLittle.png");
	decoSpriteTabRoadWay[SIDEWALK_BOTTOM_LITTLE] = LoadSprite(path + "SidewalkBottomLittle.png");
	decoSpriteTabRoadWay[SIDEWALK_CORNER_BOTTOM] = LoadSprite(path + "SidewalkCornerBottom.png");
	decoSpriteTabRoadWay[SIDEWALK_CORNER_TOP] = LoadSprite(path + "SidewalkCornerTop.png");
	decoSpriteTabRoadWay[SIDEWALK_CORNER_RIGHT] = LoadSprite(path + "SidewalkCornerRight.png");
	decoSpriteTabRoadWay[SIDEWALK_CORNER_LEFT] = LoadSprite(path + "SidewalkCornerLeft.png");
	decoSpriteTabRoadWay[SIDEWALK_CORNER_RIGHT_LITTLE] = LoadSprite(path + "SidewalkCornerRightLittle.png");
	decoSpriteTabRoadWay[SIDEWALK_CORNER_LEFT_LITTLE] = LoadSprite(path + "SidewalkCornerLeftLittle.png");
	decoSpriteTabRoadWay[SIDEWALK_CORNER_TOP_LITTLE] = LoadSprite(path + "SidewalkCornerTopLittle.png");
	decoSpriteTabRoadWay[SIDEWALK_CORNER_BOTTOM_LITTLE] = LoadSprite(path + "SidewalkCornerBottomLittle.png");
}

void InitGridTilesSprite(void)
{
	std::string path = "Assets/Images/Grid/";


	tilesSpriteTab[GRASS_TILE] = LoadSprite(path + "Grass.png", false);
	tilesSpriteTab[TAR_TILE] = LoadSprite(path + "Tar.png", false);
	tilesSpriteTab[TAR_TILE_HALF] = LoadSprite(path + "HalfTar2.png", false);
	tilesSpriteTab[PATH_TILE] = LoadSprite(path + "Path.png", false);
	tilesSpriteTab[BONUS_TILE] = LoadSprite(path + "Bonus.png", false);
	tilesSpriteTab[CHANCE_TILE] = LoadSprite(path + "Chance.png", false);
	tilesSpriteTab[COUNCIL_TILE] = LoadSprite(path + "Council.png", false);
	tilesSpriteTab[EXAM_TILE] = LoadSprite(path + "Examen.png", false);
	tilesSpriteTab[TAXES_TILE] = LoadSprite(path + "Taxes.png", false);
	tilesSpriteTab[MALUS_TILE] = LoadSprite(path + "Malus.png", false);
	tilesSpriteTab[MYSTERY_TILE] = LoadSprite(path + "Mystery.png", false);
	tilesSpriteTab[ACTION_TILE] = LoadSprite(path + "Action.png", false);
	tilesSpriteTab[START_TILE] = LoadSprite(path + "Start.png", false);
	tilesSpriteTab[SALARY_TILE] = LoadSprite(path + "Salary.png", false);
	tilesSpriteTab[BREAK_TILE] = LoadSprite(path + "Break.png", false);
	tilesSpriteTab[TAXE_AUDIT_TILE] = LoadSprite(path + "TaxeAudit.png", false);
	tilesSpriteTab[BONUS_MONEY_TILE] = LoadSprite(path + "BonusMoney.png", false);
	tilesSpriteTab[BONUS_REP_TILE] = LoadSprite(path + "BonusReputation.png", false);
	tilesSpriteTab[BONUS_VOTERS_TILE] = LoadSprite(path + "BonusVoters.png", false);
	tilesSpriteTab[MALUS_MONEY_TILE] = LoadSprite(path + "MalusMoney.png", false);
	tilesSpriteTab[MALUS_REP_TILE] = LoadSprite(path + "MalusReputation.png", false);
	tilesSpriteTab[MALUS_VOTERS_TILE] = LoadSprite(path + "MalusVoters.png", false);
	tilesSpriteTab[REP_X_MONEY_TILE] = LoadSprite(path + "RepXMoney.png", false);
	tilesSpriteTab[REP_X_VOTERS_TILE] = LoadSprite(path + "RepXVoters.png", false);

	grid[0][0].width = (int)tilesSpriteTab[GRASS_TILE].getGlobalBounds().width;
}

void InitGrid(void)
{
	InitDecoSprites();
	InitGridTilesSprite();
	InitTiles();
	InitRoads();
	SetTileSprite();
}

void SetTileSprite(void)
{
	for (unsigned char line = 0; line < LINE_GRID; line++)
	{
		for (unsigned char column = 0; column < COLUMN_GRID; column++)
		{
			decosGrid[line][column].type = 55; // valeur hors du tableau par défaut
			decosGridRoadWay[line][column].type = 55; // valeur hors du tableau par défaut

			switch (grid[line][column].type)
			{
			case START:
				grid[line][column].typeSprite = START_TILE;
				break;
			case BONUS_MONEY:
				grid[line][column].typeSprite = BONUS_MONEY_TILE;
				break;
			case BONUS_REPUTATION:
				grid[line][column].typeSprite = BONUS_REP_TILE;
				break;
			case BONUS_VOTERS:
				grid[line][column].typeSprite = BONUS_VOTERS_TILE;
				break;
			case BONUS_MONEY_SHORTCUT:
				grid[line][column].typeSprite = BONUS_MONEY_TILE;
				break;
			case BONUS_REPUTATION_SHORTCUT:
				grid[line][column].typeSprite = BONUS_REP_TILE;
				break;
			case BONUS_VOTERS_SHORTCUT:
				grid[line][column].typeSprite = BONUS_VOTERS_TILE;
				break;
			case REPUTATION_MONEY:
				grid[line][column].typeSprite = REP_X_MONEY_TILE;
				break;
			case REPUTATION_VOTERS:
				grid[line][column].typeSprite = REP_X_VOTERS_TILE;
				break;
			case REPUTATION_MONEY_SHORTCUT:
				grid[line][column].typeSprite = REP_X_MONEY_TILE;
				break;
			case REPUTATION_VOTERS_SHORTCUT:
				grid[line][column].typeSprite = REP_X_VOTERS_TILE;
				break;
			case MALUS_MONEY:
				grid[line][column].typeSprite = MALUS_MONEY_TILE;
				break;
			case MALUS_REPUTATION:
				grid[line][column].typeSprite = MALUS_REP_TILE;
				break;
			case MALUS_VOTERS:
				grid[line][column].typeSprite = MALUS_VOTERS_TILE;
				break;
			case MALUS_MONEY_SHORTCUT:
				grid[line][column].typeSprite = MALUS_MONEY_TILE;
				break;
			case MALUS_REPUTATION_SHORTCUT:
				grid[line][column].typeSprite = MALUS_REP_TILE;
				break;
			case MALUS_VOTERS_SHORTCUT:
				grid[line][column].typeSprite = MALUS_VOTERS_TILE;
				break;
			case ACTION:
				grid[line][column].typeSprite = ACTION_TILE;
				break;
			case CHANCE:
				grid[line][column].typeSprite = CHANCE_TILE;
				break;
			case MYSTERY:
				grid[line][column].typeSprite = MYSTERY_TILE;
				break;
			case TAX_AUDIT:
				grid[line][column].typeSprite = TAXE_AUDIT_TILE;
				break;
			case PARLIAMENTARY_COUNCIL:
				grid[line][column].typeSprite = COUNCIL_TILE;
				break;
			case BREAK:
				grid[line][column].typeSprite = BREAK_TILE;
				break;
			case EXAM:
				grid[line][column].typeSprite = EXAM_TILE;
				break;
			case SALARY:
				grid[line][column].typeSprite = SALARY_TILE;
				break;
			case TAXES:
				grid[line][column].typeSprite = TAXES_TILE;
				break;
			default:

				if (line == 6 && column == 16)
				{
					grid[line][column].typeSprite = TAR_TILE_HALF;
				}
				else if (line < 6 && column == 16 || column <= 9 && column >= 3 && line == 16)
				{
					grid[line][column].typeSprite = TAR_TILE;
				}
				else
				{
					grid[line][column].typeSprite = GRASS_TILE;
				}

				DecoPlacements(line, column);

				break;
			}
		}
	}
}


void DecoPlacements(int _line , int _column)
{
#pragma region leftDeco
	decosGrid[0][16].type = SMALL_BUILDING;
	decosGrid[2][16].type = BUILDING_LEFT;
	decosGrid[4][16].type = TOWER;

	if (_line < 5)
	{
		if (_column == 14)
		{
			decosGridRoadWay[_line][_column].type = SIDEWALK_TOP_LITTLE;
		}
		if (_column == 15)
		{
			decosGridRoadWay[_line][_column].type = SIDEWALK_BOTTOM;
		}
		if (_column == 16)
		{
			decosGridRoadWay[_line][_column].type = TAR_BASE;
			
		}
	}

	if (_line == 5)
	{
		if (_column == 14)
		{
			decosGridRoadWay[_line][_column].type = SIDEWALK_TOP_LITTLE;
		}
		if (_column == 15)
		{
			decosGridRoadWay[_line][_column].type = TAR_BASE;
		}
		if (_column == 16)
		{
			decosGridRoadWay[_line][_column].type = SIDEWALK_LEFT;
		}
	}

	if (_line == 6)
	{
		if (_column == 14)
		{
			decosGridRoadWay[_line][_column].type = SIDEWALK_CORNER_RIGHT_LITTLE;
		}
		if (_column == 15)
		{
			decosGridRoadWay[_line][_column].type = SIDEWALK_RIGHT_LITTLE;
		}
		if (_column == 16)
		{
			decosGridRoadWay[_line][_column].type = SIDEWALK_RIGHT_LITTLE;
		}
	}
#pragma endregion

#pragma region rightDeco
	/*decosGrid[16][0].type = SMALL_BUILDING;
	decosGrid[16][2].type = BUILDING_RIGHT;
	decosGrid[16][4].type = TOWER;
	if (_column < 5)
	{
		if (_line == 14)
		{
			decosGridRoadWay[_line][_column].type = SIDEWALK_LEFT_LITTLE;
		}

		if (_line == 15)
		{
			decosGridRoadWay[_line][_column].type = SIDEWALK_RIGHT;
		}
		if (_line == 16)
		{
			decosGridRoadWay[_line][_column].type = TAR_BASE;
		}
	}

	if (_column == 5 )
	{
		if (_line == 14)
		{
			decosGridRoadWay[_line][_column].type = SIDEWALK_LEFT_LITTLE;
		}

		if (_line == 15)
		{
			decosGridRoadWay[_line][_column].type = TAR_BASE;
		}
		if (_line == 16)
		{
			decosGridRoadWay[_line][_column].type = SIDEWALK_TOP;
		}
	}

	if (_column == 6)
	{
		if (_line == 14)
		{
			decosGridRoadWay[_line][_column].type = SIDEWALK_CORNER_LEFT_LITTLE;
		}

		if (_line == 15 || _line == 16)
		{
			decosGridRoadWay[_line][_column].type = SIDEWALK_BOTTOM_LITTLE;
		}
	}*/

	if (_column <= 9 && _column >= 3 && _line == 16)
	{
		decosGridRoadWay[_line][_column].type = TAR_BASE;
	}

	if (_column <= 6 && _column >= 3 && (_line == 15 || _line == 14))
	{
		decosGridRoadWay[_line][_column].type = TAR_BASE;
	}

	if (_column <= 5 && _column >= 3 && _line == 14)
	{
		decosGridRoadWay[_line][_column].type = SIDEWALK_LEFT;
	}
	decosGridRoadWay[14][6].type = SIDEWALK_CORNER_LEFT;
	decosGridRoadWay[15][6].type = SIDEWALK_BOTTOM;
	decosGridRoadWay[14][3].type = SIDEWALK_CORNER_TOP;
	decosGrid[14][3].type = SMALL_BUILDING;
	decosGrid[15][3].type = STREET_LAMP_LEFT;
	decosGrid[14][6].type = STREET_LAMP_RIGHT;
	decosGrid[16][5].type = SIGN_RIGHT;
	decosGrid[16][3].type = BUILDING_LEFT;
	decosGridRoadWay[15][3].type = SIDEWALK_TOP;
	decosGridRoadWay[16][3].type = SIDEWALK_TOP;
	decosGrid[16][7].type = BUILDING_RIGHT;
	decosGrid[14][5].type = BUILDING_RIGHT;
	decosGridRoadWay[16][9].type = SIDEWALK_CORNER_LEFT;
	decosGrid[16][9].type = TOWER;
	decosGrid[16][9].front = true;
	decosGridRoadWay[16][8].type = SIDEWALK_LEFT;
	decosGridRoadWay[16][7].type = SIDEWALK_LEFT;

#pragma endregion

	decosGrid[7][0].type = HOUSE;
	decosGrid[10][10].type = HOUSE2;

	decosGrid[8][3].type = HOUSE2;
	decosGrid[10][3].type = HOUSE;

	decosGrid[11][14].type = SCHOOL;
	decosGrid[6][10].type = SCHOOL;

	decosGridRoadWay[0][5].type = SIDEWALK_CORNER_LEFT_LITTLE;
	decosGridRoadWay[1][5].type = SIDEWALK_BOTTOM_LITTLE;
	decosGridRoadWay[0][4].type = SIDEWALK_LEFT_LITTLE;
	decosGridRoadWay[0][3].type = SIDEWALK_LEFT_LITTLE;
	decosGridRoadWay[0][2].type = SIDEWALK_LEFT_LITTLE;
	decosGridRoadWay[0][1].type = SIDEWALK_LEFT_LITTLE;
	decosGridRoadWay[0][0].type = SIDEWALK_CORNER_TOP_LITTLE;
	decosGridRoadWay[1][0].type = SIDEWALK_TOP_LITTLE;
	decosGrid[1][4].type = BUILDING_RIGHT;
	decosGrid[1][2].type = BUILDING_RIGHT;
	decosGridRoadWay[1][3].type = TAR_BASE;
	decosGridRoadWay[1][2].type = TAR_BASE;
	decosGridRoadWay[1][1].type = TAR_BASE;
	
	decosGrid[1][5].type = STREET_LAMP_RIGHT;
	decosGrid[3][1].type = STREET_LAMP_LEFT;
	decosGrid[11][10].type = SIGN_LEFT;

	decosGrid[1][9].type = BUILDING_RIGHT;
	decosGridRoadWay[1][8].type = SIDEWALK_TOP_LITTLE;
	decosGridRoadWay[0][9].type = SIDEWALK_LEFT_LITTLE;
	decosGridRoadWay[0][10].type = SIDEWALK_CORNER_LEFT_LITTLE;
	decosGridRoadWay[1][10].type = SIDEWALK_BOTTOM_LITTLE;

	decosGrid[0][9].type = TREE1;
	decosGrid[0][10].type = TREE2;

	decosGrid[0][5].type = TOWER;
	decosGridRoadWay[1][4].type = TAR_BASE;
	decosGridRoadWay[1][9].type = TAR_BASE;

	decosGrid[2][1].type = SMALL_BUILDING;

	//decosGrid[3][1].type = TREE3;
	decosGrid[3][0].type = TREE1;

	decosGrid[0][1].type = TREE2;
	decosGrid[0][2].type = TREE2;
	decosGrid[0][3].type = TREE2;
	decosGrid[0][4].type = TREE2;
	decosGrid[0][4].type = TREE2;

	decosGrid[1][0].type = TREE2;
	decosGrid[2][0].type = TREE2;
	decosGrid[3][0].type = TREE2;
	decosGrid[4][0].type = TREES2;

	decosGridRoadWay[2][1].type = TAR_BASE;
	decosGridRoadWay[3][1].type = SIDEWALK_RIGHT_LITTLE;
	decosGridRoadWay[3][0].type = SIDEWALK_CORNER_RIGHT_LITTLE;
	decosGridRoadWay[2][0].type = SIDEWALK_TOP_LITTLE;

	for (int i = 0; i < 4; i++)
	{
		if (i !=1 && i !=0)
		{
			decosGrid[0][i + 1 * 4].type = TREES2;
			decosGrid[0][i * 4].type = TREES1;
			decosGrid[i * 4][0].type = TREES1;
		}
	}

	decosGrid[8][0].type = TREES3;
	decosGrid[9][0].type = TREES2;
	decosGrid[10][0].type = TREE1;
	decosGrid[11][0].type = TREES4;
	decosGrid[13][0].type = TREE4;
	decosGrid[14][0].type = TREE2;
	decosGrid[15][0].type = TREES4;
	decosGrid[15][1].type = TREE3;
	decosGrid[16][0].type = TREES1;
	decosGrid[16][1].type = TREES2;
	decosGrid[16][2].type = TREE3;

	decosGrid[1][6].type = TREES4;
	decosGrid[1][10].type = TREES2;
	decosGrid[1][13].type = TREES1;
	decosGrid[0][13].type = TREES4;

	decosGrid[16][13].type = TREES2;
	decosGrid[16][14].type = TREES3;
	decosGrid[16][15].type = TREES4;

	decosGrid[8][16].type = TREES1;
	decosGrid[8][16].front = true;
	decosGrid[9][16].type = TREES4;
	decosGrid[9][16].front = true;
	decosGrid[10][16].type = TREES3;
	decosGrid[10][16].front = true;	
	decosGrid[13][16].type = TREES3;
	decosGrid[13][16].front = true;
	decosGrid[14][16].type = TREES4;
	decosGrid[14][16].front = true;
	decosGrid[16][16].type = TREES4;
	decosGrid[16][16].front = true;
	decosGrid[15][16].type = TREES3;
	decosGrid[15][16].front = true;

	decosGrid[4][1].type = TREES3;
	decosGrid[5][1].type = TREES2;

	decosGrid[14][7].type = TREE4;
	decosGrid[7][3].type = TREE2;
	decosGrid[11][3].type = TREE1;
	decosGrid[12][14].type = TREE2;
	decosGrid[11][13].type = TREE4;
	decosGrid[1][10].type = TREE1;

	
	decosGrid[7][9].type = TREES3;
	decosGrid[7][9].front = true;
	decosGrid[8][9].type = TREE2;
	decosGrid[8][9].front = true;
	decosGrid[9][9].type = TREE2;
	decosGrid[9][9].front = true;
	decosGridRoadWay[8][9].type = SIDEWALK_CORNER_TOP_LITTLE;
	decosGridRoadWay[8][10].type = SIDEWALK_LEFT_LITTLE;
	decosGrid[9][10].type = STREET_LAMP_LEFT;
	for (int i = 0; i < 2; i++)
	{
		decosGridRoadWay[9+ i][9].type = SIDEWALK_TOP_LITTLE;
		decosGridRoadWay[9+ i][10].type = TAR_BASE;
	}
	decosGridRoadWay[11][9].type = SIDEWALK_CORNER_RIGHT_LITTLE;
	decosGridRoadWay[11][10].type = SIDEWALK_RIGHT_LITTLE;
}


void DisplayGrid(sf::RenderWindow& _window)
{
	for (unsigned char line = 0; line < LINE_GRID; line++)
	{
		for (unsigned char column = 0; column < COLUMN_GRID; column++)
		{
			grid[line][column].posIso = CartesianToIsometric(line, column, 0, (float)GetTileWidth());
			BlitSprite(tilesSpriteTab[grid[line][column].typeSprite], sf::Vector2f(grid[line][column].posIso.x + GetGridOffset().x, grid[line][column].posIso.y + GetGridOffset().y), _window);
		}
	}
}


void DisplayDecosBeforePlayer(sf::RenderWindow& _window)
{
	for (unsigned char line = 0; line < LINE_GRID; line++)
	{
		for (unsigned char column = 0; column < COLUMN_GRID; column++)
		{
			if (decosGridRoadWay[line][column].type != 55)
			{
				decosGridRoadWay[line][column].posIso = CartesianToIsometric(line, column, 0, (float)GetTileWidth());
				BlitSprite(decoSpriteTabRoadWay[decosGridRoadWay[line][column].type], sf::Vector2f(decosGridRoadWay[line][column].posIso.x + GetGridOffset().x, decosGridRoadWay[line][column].posIso.y + GetGridOffset().y), _window);
			}

			if (decosGrid[line][column].type != 55 && !decosGrid[line][column].front)
			{
				decosGrid[line][column].posIso = CartesianToIsometric(line, column, 1, (float)GetTileWidth());

				if (decosGrid[line][column].type == TOWER)
				{
					BlitSprite(decoSpriteTab[decosGrid[line][column].type],
						sf::Vector2f(decosGrid[line][column].posIso.x + GetGridOffset().x - PosToScreenX(40), decosGrid[line][column].posIso.y + GetGridOffset().y - PosToScreenY(76)),
						_window
					);
				}
				else
				{
					BlitSprite(decoSpriteTab[decosGrid[line][column].type], sf::Vector2f(decosGrid[line][column].posIso.x + GetGridOffset().x, decosGrid[line][column].posIso.y + GetGridOffset().y), _window);
				}
			}
		}
	}
}

void DisplayDecosAfterPlayer(sf::RenderWindow& _window)
{
	for (unsigned char line = OFFSET_GRID_LINE; line < LINE_GRID; line++)
	{
		for (unsigned char column = 0; column < COLUMN_GRID; column++)
		{
			if (decosGrid[line][column].type != 55 && decosGrid[line][column].front)
			{
				decosGrid[line][column].posIso = CartesianToIsometric(line, column, 1, (float)GetTileWidth());
				
				if (decosGrid[line][column].type == TOWER)
				{
					BlitSprite(decoSpriteTab[decosGrid[line][column].type],
						sf::Vector2f(decosGrid[line][column].posIso.x + GetGridOffset().x - PosToScreenX(40), decosGrid[line][column].posIso.y + GetGridOffset().y - PosToScreenY(76)),
						_window
					);
				}
				else
				{
					BlitSprite(decoSpriteTab[decosGrid[line][column].type], sf::Vector2f(decosGrid[line][column].posIso.x + GetGridOffset().x, decosGrid[line][column].posIso.y + GetGridOffset().y), _window);
				}
					
			}
		}

	}
}

int GetTileWidth(void)
{
	return grid[0][0].width;
}

void SetGridType(int _line, int _column, int _type)
{
	grid[_line][_column].type = _type;
}

int GetTileType(int _line, int _column)
{
	return grid[_line][_column].type;
}

sf::Vector2f GetGridOffset(void)
{
	return { PosToScreenX(912) , PosToScreenY(22) };
}

sf::Vector2f GetCell(int _line, int _column, int _z)
{
	sf::Vector2f pos;
	pos = CartesianToIsometric((float)_line, (float)_column, (float)_z, (float)GetTileWidth());
	return sf::Vector2f{ pos.x + GetGridOffset().x, pos.y + GetGridOffset().y };
}