#include "astar.h"
#include "tilemap.h"
#include "list.h"

#include <raylib.h>
#include <raymath.h>

#include <string.h>
#include <stdio.h>

#define MAP_SIZE WORLD_WIDTH * WORLD_LENGTH

typedef struct {
    Vector2 keys[MAP_SIZE];
    Vector2 values[MAP_SIZE];
    int size;
} Dict;

int MapGetIndex(Dict *map, Vector2 key)
{
    for (int i=0; i<map->size; i++)
    {
        if (Vector2Equals(map->keys[i], key))
        {
            return i;
        }
    }
    return -1; // Failure :(
}

void MapInsert(Dict *map, Vector2 key, Vector2 value)
{
    int index = MapGetIndex(map, key);

    if (index != -1)
    {
        map->values[index] = value;
        return;
    }

    map->keys[map->size] = key;
    map->values[map->size] = value;
    map->size++;
}

Vector2 MapGet(Dict *map, Vector2 key)
{
    int index = MapGetIndex(map, key);

    if (index == -1) { // Failure :(
        //printf("Invalid key \n");
        return Vector2Zero(); 
    }

    return map->values[index];
}

Node* ReconstructPath(Dict *cameFrom, Vector2 end)
{
    Node *path = NULL;

    Vector2 current = end;
    for (int i=0; i<cameFrom->size; i++)
    {
        if (Vector2Equals(current, Vector2Zero())) continue;

        ListInsertFront(&path, current);
        current = MapGet(cameFrom, current);
    }

    return path;
}


int GetFCost(Vector2 start, Vector2 target, Vector2 current)
{
    int gCost = Vector2Distance(current, start);
    int hCost = Vector2Distance(current, target);

    return gCost + hCost;
}

Node* AStar(Vector2 start, Vector2 target)
{
    PqNode *open = NULL; // Priority queue

    PqPush(&open, start, 0);

    Node *closed = NULL; // Linked list

    Dict cameFrom = { 0 };

    Vector2 neighbors[4] = {(Vector2){1, 0}, (Vector2){-1, 0}, (Vector2){0, 1}, (Vector2){0, -1}};

    while (open)
    {
        Vector2 current = PqPop(&open);
        ListInsertBack(&closed, current);

        if (Vector2Equals(current, target)) // Success
        {
            PqFree(open);
            open = NULL;

            ListFree(closed);
            closed = NULL;

            return ReconstructPath(&cameFrom, current);
        }

        for (int i=0; i<4; i++)
        {

            Vector2 neighbor = Vector2Add(current, neighbors[i]);
            neighbor.x = round(neighbor.x);
            neighbor.y = round(neighbor.y);

            if (!IsTraversible(neighbor) || ListHasVector(&closed, neighbor)) continue;

            int neighborFCost = GetFCost(current, target, neighbor);

            // Set parent here
            MapInsert(&cameFrom, neighbor, current);

            if (!PqHasVector(&open, neighbor))
            {   
                PqPush(&open, neighbor, neighborFCost);
            }
        }
    }

    PqFree(open);
    open = NULL;

    ListFree(closed);
    closed = NULL;

    return NULL; // Failure
}