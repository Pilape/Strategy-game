#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "raylib.h"

struct Textures{

    Texture2D floorTiles;
    Texture2D player;

};

extern struct Textures Textures;

void TexturesInit();

extern Camera2D mainCamera;
void TextureDraw(Texture2D texture, Vector2 AtlasPos, Vector2 pos, Vector2 size);

#endif