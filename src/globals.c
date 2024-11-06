#include "globals.h"
#include <raylib.h>
#include <raymath.h>

struct Textures Textures = { 0 };

int Vector2AlmostEquals(Vector2 a, Vector2 b)
{
    Vector2 approxA = {round(a.x), round(a.y)};
    Vector2 approxB = {round(b.x), round(b.y)};

    return Vector2Equals(approxA, approxB);
}

void TexturesInit()
{
    Textures.floorTiles = LoadTexture("resources/tileset.png");
    Textures.player = LoadTexture("resources/isometric-block-wizard.png");
}

void TextureDraw(Texture2D texture, Vector2 AtlasPos, Vector2 pos, Vector2 size)
{
    DrawTexturePro(texture, (Rectangle){AtlasPos.x, AtlasPos.y, size.x, size.y},
    (Rectangle){pos.x, pos.y, size.x, size.y}, Vector2Scale(pos, 0.5f), 0.0f, WHITE);
}