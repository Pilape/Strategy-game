#include <raylib.h>
#include <raymath.h>

#include "tilemap.h"
#include "player.h"
#include "globals.h"

struct Player player = { 0 };

void PlayerInit()
{
    player.tilePos = (Vector2){round(WORLD_WIDTH/2), round(WORLD_LENGTH/2)};
    player.pos = TileToScreenPos(player.tilePos);
    player.health = 20;
}

void PlayerUpdate()
{
    player.pos = Vector2Lerp(player.pos, TileToScreenPos(player.tilePos), 50 * GetFrameTime());

    Vector2 mouseTilePos = ScreenToTilePos(GetScreenToWorld2D(GetMousePosition(), mainCamera), true);
    
    if (IsInBounds(mouseTilePos))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) player.tilePos = mouseTilePos;
    }

}

void PlayerDraw()
{
    DrawCircleV(player.pos, 18.0f, BLACK);
    DrawCircleV(player.pos, 15.0f, WHITE);
}