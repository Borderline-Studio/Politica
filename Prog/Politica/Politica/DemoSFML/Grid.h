#ifndef  GRID_H

#define GRID_H

#include "Common.h"
#include "TilesManager.h"


#define NB_SPRITES_TILES 24
#define NB_SPRITES_DECO 19
#define NB_SPRITES_DECO_ROADWAY 17

enum TileSpriteType
{
	GRASS_TILE,
	TAR_TILE,
	TAR_TILE_HALF,
	PATH_TILE,
	BONUS_TILE,
	BONUS_VOTERS_TILE,
	BONUS_MONEY_TILE,
	BONUS_REP_TILE,
	CHANCE_TILE,
	COUNCIL_TILE,
	EXAM_TILE,
	TAXES_TILE,
	MALUS_TILE,
	MALUS_VOTERS_TILE,
	MALUS_MONEY_TILE,
	MALUS_REP_TILE,
	MYSTERY_TILE,
	ACTION_TILE,
	START_TILE,
	BREAK_TILE,
	TAXE_AUDIT_TILE,
	SALARY_TILE,
	REP_X_MONEY_TILE,
	REP_X_VOTERS_TILE,
};

enum DecoSpritesType
{
	BUILDING_LEFT,
	BUILDING_RIGHT,
	TOWER,
	SMALL_BUILDING,
	HOUSE,
	HOUSE2,
	SCHOOL,
	TREE1,
	TREE2,
	TREE3,
	TREE4,
	TREES1,
	TREES2,
	TREES3,
	TREES4,
	SIGN_LEFT,
	SIGN_RIGHT,
	STREET_LAMP_LEFT,
	STREET_LAMP_RIGHT,
};

enum DecoSpritesTypeRoadWay
{
	TAR_BASE,
	SIDEWALK_TOP,
	SIDEWALK_BOTTOM,
	SIDEWALK_LEFT,
	SIDEWALK_RIGHT,
	SIDEWALK_RIGHT_LITTLE,
	SIDEWALK_LEFT_LITTLE,
	SIDEWALK_TOP_LITTLE,
	SIDEWALK_BOTTOM_LITTLE,
	SIDEWALK_CORNER_TOP,
	SIDEWALK_CORNER_BOTTOM,
	SIDEWALK_CORNER_LEFT,
	SIDEWALK_CORNER_RIGHT,
	SIDEWALK_CORNER_RIGHT_LITTLE,
	SIDEWALK_CORNER_LEFT_LITTLE,
	SIDEWALK_CORNER_TOP_LITTLE,
	SIDEWALK_CORNER_BOTTOM_LITTLE,
};

struct Block
{
	sf::Vector2f pos;
	sf::Vector2f posIso;
	int width = 0;
	int type = 0;
	int typeSprite = 0;
};

struct Objects
{
	sf::Vector2f pos;
	sf::Vector2f posIso;
	int type = 0;
	bool front = 0;
};

void InitDecoSprites(void);

void InitGridTilesSprite(void);

void InitGrid(void);

void SetTileSprite(void);

void DecoPlacements(int _line, int _column);

void DisplayGrid(sf::RenderWindow& _window);

void DisplayDecosBeforePlayer(sf::RenderWindow& _window);

void DisplayDecosAfterPlayer(sf::RenderWindow& _window);
#endif // ! GAMESTATE_H

