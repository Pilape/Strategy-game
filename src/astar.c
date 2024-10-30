#include "astar.h"
#include "tilemap.h"
#include "list.h"

#include <raylib.h>
#include <raymath.h>

#include <string.h>

Node* AStar(Vector2 start, Vector2 target)
{
    int open[WORLD_WIDTH][WORLD_LENGTH] = {0};
    open[(int)start.x][(int)start.y] = 1;

    int closed[WORLD_WIDTH][WORLD_LENGTH] = {0};


}