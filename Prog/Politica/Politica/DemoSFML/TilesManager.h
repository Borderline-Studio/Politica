#ifndef TILE_GESTION_H
#define TILE_GESTION_H

#include "Common.h"
#include "Audio.h"

struct TileSound
{
	unsigned char cashOnTile;
	unsigned char cashNotOnTile;
	unsigned char bonus;
	unsigned char malus;
	unsigned char parliamentaryCouncil;
	unsigned char piecePlacement;
};

void InitTiles(void);
void InitRoads(void);

#endif // !TILE_GESTION_H
