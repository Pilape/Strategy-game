#ifndef TILEMAP_H_
#define TILEMAP_H_

#include "raylib.h"

#define WORLD_WIDTH 16
#define WORLD_LENGTH 16

extern const Vector2 TILE_SIZE;

Vector2 TileToScreenPos(Vector2 pos);
Vector2 ScreenToTilePos(Vector2 pos, bool asInt);

void TexturesInit();
void DrawTiles();

#endif