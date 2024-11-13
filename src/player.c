#include <raylib.h>
#include <raymath.h>

#include "tilemap.h"
#include "player.h"
#include "globals.h"
#include "astar.h"
#include "entity.h"
#include "turns.h"

struct Player player = { 0 };

void PlayerUpdatePath()
{
    if (player.base->path == NULL) player.reachableNodes = GetReachableNodes(player.base->tilePos, player.base->range);

    Vector2 mouseTilePos = ScreenToTilePos(GetScreenToWorld2D(GetMousePosition(), mainCamera), true);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ListLength(player.base->path) == 0)
    {
        if (Vector2AlmostEquals(mouseTilePos, player.base->tilePos)) return;

        if (!ListHasVector(&player.reachableNodes, mouseTilePos)) return;

        ListFree(player.reachableNodes);
        player.reachableNodes = NULL;

        player.base->path = AStar(player.base->tilePos, mouseTilePos);
        NextTurn();
    }
}

void PlayerInit()
{
    player.base = EntitySpawn((Vector2){round(WORLD_WIDTH/2), round(WORLD_LENGTH/2)});
    player.base->range = 2;
    player.base->turnFunction = &PlayerUpdatePath;
}

void DrawReachableNodes()
{
    Node *currentNode = player.reachableNodes;
    for(int i=0; i<ListLength(player.reachableNodes)-1; i++) // -1 Node because function adds 1 too many >:(
    {
        Vector2 screenPos = TileToScreenPos(currentNode->data);

        DrawTexturePro(Textures.floorTiles, (Rectangle){128, 0, 64, 64},
            (Rectangle){screenPos.x, screenPos.y, 64, 64},
            Vector2Scale(TILE_SIZE, 0.5f), 0, WHITE);
        
        currentNode = currentNode->next;
    }
}

void PlayerDraw()
{
    DrawReachableNodes();
    EntityDraw(player.base);
}