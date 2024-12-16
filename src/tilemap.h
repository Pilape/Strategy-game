#ifndef TILEMAP_H_
#define TILEMAP_H_

#include "raylib.h"

#define WORLD_WIDTH 16
#define WORLD_LENGTH 16

enum TILE_ID {
    FLOOR_BLACK,
    FLOOR_WHITE,
    PIT,
};

extern const Vector2 TILE_SIZE;

extern int Map[WORLD_WIDTH][WORLD_LENGTH];

void MapInit(void);

int IsInBounds(Vector2 pos);
int IsTraversible(Vector2 pos);

Vector2 TileToScreenPos(Vector2 pos);
Vector2 ScreenToTilePos(Vector2 pos, bool asInt);

void TexturesInit(void);
void DrawTiles(void);

#endif