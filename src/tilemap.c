#include "tilemap.h"
#include <raylib.h>
#include <raymath.h>
#include "globals.h"

const Vector2 TILE_SIZE = {16, 8};

int Map[WORLD_WIDTH][WORLD_LENGTH];

void MapInit()
{
    for (int x=1; x<WORLD_WIDTH; x++)
    {
        for (int z=1; z<WORLD_LENGTH; z++)
        {
            if ((x+z) % 2 == 0) Map[x][z] = FLOOR_WHITE;
            else Map[x][z] = FLOOR_BLACK;
        }
    }

    Map[11][12] = PIT; Map[12][12] = PIT;
    Map[11][11] = PIT; Map[12][11] = PIT;

}

Vector2 TileToScreenPos(Vector2 pos)
{
    Matrix TransfromMatrix = { 0 };
    TransfromMatrix.m0 = 0.5f * TILE_SIZE.x; TransfromMatrix.m4 = -0.5f * TILE_SIZE.x;
    TransfromMatrix.m1 = 0.5f * TILE_SIZE.y; TransfromMatrix.m5 = 0.5f * TILE_SIZE.y;

    return Vector2Transform(pos, TransfromMatrix);
}

struct Matrix2x2 {
    float a;
    float b;
    float c;
    float d;
};

struct Matrix2x2 InvertMatrix(struct Matrix2x2 matrix)
{
    const float det = (1 / (matrix.a * matrix.d - matrix.b * matrix.c));

    struct Matrix2x2 invMatrix = { 0 };
    invMatrix.a = det * matrix.d;
    invMatrix.b = det * -matrix.b;
    invMatrix.c = det * -matrix.c;
    invMatrix.d = det * matrix.a;

    return invMatrix;
}

Vector2 ScreenToTilePos(Vector2 pos, bool asInt)
{
    struct Matrix2x2 matrix = { 0 };
    matrix.a = 0.5f * TILE_SIZE.x;
    matrix.b = -0.5f * TILE_SIZE.x;
    matrix.c = 0.5f * TILE_SIZE.y;
    matrix.d = 0.5f * TILE_SIZE.y;

    const struct Matrix2x2 inv = InvertMatrix(matrix);

    Vector2 tilePos;
    tilePos.x = pos.x * inv.a + pos.y * inv.b;
    tilePos.y = pos.x * inv.c + pos.y * inv.d;

    if (asInt) {
        tilePos.x = round(tilePos.x);
        tilePos.y = round(tilePos.y);
    }

    return tilePos;
}

int IsInBounds(Vector2 pos)
{
    if (Vector2Equals(Vector2Clamp(pos, Vector2One(), (Vector2){WORLD_WIDTH-1, WORLD_LENGTH-1}), pos)) return true;

    return false;
}

int IsTraversible(Vector2 pos)
{
    return IsInBounds(pos) && Map[(int)pos.x][(int)pos.y] != PIT;
}

void DrawTiles()
{
    Vector2 floorTileTextureSize = {16, 16};

    for (int x=1; x<WORLD_WIDTH; x++)
    {
        for (int y=1; y<WORLD_LENGTH; y++)
        {
            Vector2 screenPos = TileToScreenPos((Vector2){x, y});
            
            Rectangle tileTextureSource = {0, 0, floorTileTextureSize.x, floorTileTextureSize.y};

            switch (Map[x][y])
            {
            case FLOOR_BLACK:
                tileTextureSource.x = 0;
                break;
            case FLOOR_WHITE:
                tileTextureSource.x = floorTileTextureSize.x;
                break;
            case PIT:
                tileTextureSource.x = floorTileTextureSize.x*3;
                break;
            default:
                tileTextureSource.x = 0;
            }

            DrawTexturePro(atlasTexture, tileTextureSource,
                (Rectangle){screenPos.x, screenPos.y, floorTileTextureSize.x, floorTileTextureSize.y},
                Vector2Scale(TILE_SIZE, 0.5f), 0, WHITE);
        }
    }
}