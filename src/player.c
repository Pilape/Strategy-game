#include "raylib.h"
#include "raymath.h"
#include "tilemap.h"
#include "player.h"
#include "globals.h"

struct Player player = { 0 };

void PlayerInit()
{
    player.tilePos = Vector2Zero();
    player.pos = Vector2Zero();
    player.health = 20;
}

void PlayerUpdate()
{
    player.pos = Vector2Lerp(player.pos, TileToScreenPos(player.tilePos), 50 * GetFrameTime());

    Vector2 mouseTilePos = ScreenToTilePos(GetScreenToWorld2D(GetMousePosition(), mainCamera), true);
    
    if (Vector2Equals(Vector2Clamp(mouseTilePos, Vector2Zero(), (Vector2){WORLD_WIDTH, WORLD_LENGTH}), mouseTilePos))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) player.tilePos = mouseTilePos;
    }

}

void PlayerDraw()
{
    DrawCircleV(player.pos, 18.0f, BLACK);
    DrawCircleV(player.pos, 15.0f, WHITE);
}