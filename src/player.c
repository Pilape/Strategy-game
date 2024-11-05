#include <raylib.h>
#include <raymath.h>

#include "tilemap.h"
#include "player.h"
#include "globals.h"
#include "astar.h"

struct Player player = { 0 };

Node* path;

void PlayerInit()
{
    player.tilePos = (Vector2){round(WORLD_WIDTH/2), round(WORLD_LENGTH/2)};
    player.pos = TileToScreenPos(player.tilePos);
    player.health = 20;
}

int Vector2AlmostEquals(Vector2 a, Vector2 b)
{
    Vector2 approxA = {round(a.x), round(a.y)};
    Vector2 approxB = {round(b.x), round(b.y)};

    return Vector2Equals(approxA, approxB);
}

void PlayerUpdate()
{
    player.pos = Vector2Lerp(player.pos, TileToScreenPos(player.tilePos), 50 * GetFrameTime());

    Vector2 mouseTilePos = ScreenToTilePos(GetScreenToWorld2D(GetMousePosition(), mainCamera), true);
    
    if (IsTraversible(mouseTilePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ListLength(path) == 0)
    {
        path = AStar(player.tilePos, mouseTilePos);
        //ListPrint(path);
    }

    if (ListLength(path) > 0 && Vector2AlmostEquals(player.pos, TileToScreenPos(player.tilePos)))
    {
        player.tilePos = ListPopFront(&path);
    }

}

void PlayerDraw()
{
    DrawTexturePro(Textures.player, (Rectangle){0, 0, 64, 64},
        (Rectangle){player.pos.x, player.pos.y, 64, 64},
        (Vector2){32, 48}, 0, WHITE);
/*     DrawCircleV(player.pos, 18.0f, BLACK);
    DrawCircleV(player.pos, 15.0f, WHITE); */
}