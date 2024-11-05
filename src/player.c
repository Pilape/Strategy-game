#include <raylib.h>
#include <raymath.h>

#include "tilemap.h"
#include "player.h"
#include "globals.h"
#include "astar.h"

struct Player player = { 0 };
Node *nodesInRange;

void PlayerInit()
{
    player.tilePos = (Vector2){round(WORLD_WIDTH/2), round(WORLD_LENGTH/2)};
    player.pos = TileToScreenPos(player.tilePos);
    player.health = 20;
    player.range = 2;

    nodesInRange = GetReachableNodes(player.tilePos, player.range);
}

int Vector2AlmostEquals(Vector2 a, Vector2 b)
{
    Vector2 approxA = {round(a.x), round(a.y)};
    Vector2 approxB = {round(b.x), round(b.y)};

    return Vector2Equals(approxA, approxB);
}

Node *path;

void PlayerUpdate()
{
    player.pos = Vector2Lerp(player.pos, TileToScreenPos(player.tilePos), 50 * GetFrameTime());

    Vector2 mouseTilePos = ScreenToTilePos(GetScreenToWorld2D(GetMousePosition(), mainCamera), true);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ListLength(path) == 0)
    {
        if (Vector2AlmostEquals(mouseTilePos, player.tilePos)) return;

        nodesInRange = GetReachableNodes(player.tilePos, player.range);
        if (!ListHasVector(&nodesInRange, mouseTilePos)) return;

        ListFree(nodesInRange);
        nodesInRange = NULL;

        path = AStar(player.tilePos, mouseTilePos);
    }

    if (ListLength(path) > 0 && Vector2AlmostEquals(player.pos, TileToScreenPos(player.tilePos)))
    {
        player.tilePos = ListPopFront(&path);

        if (ListLength(path) == 0) nodesInRange = GetReachableNodes(player.tilePos, player.range);
    }

}

void PlayerDraw()
{
    Node *currentNode = nodesInRange;
    for(int i=0; i<ListLength(nodesInRange)-1; i++) // -1 Node because function adds 1 too many >:(
    {
        Vector2 screenPos = TileToScreenPos(currentNode->data);

        DrawTexturePro(Textures.floorTiles, (Rectangle){128, 0, 64, 64},
            (Rectangle){screenPos.x, screenPos.y, 64, 64},
            Vector2Scale(TILE_SIZE, 0.5f), 0, WHITE);
        
        currentNode = currentNode->next;
    }

    DrawTexturePro(Textures.player, (Rectangle){0, 0, 64, 64},
        (Rectangle){player.pos.x, player.pos.y, 64, 64},
        (Vector2){32, 48}, 0, WHITE);
}