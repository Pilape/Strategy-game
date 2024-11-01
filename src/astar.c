#include "astar.h"
#include "tilemap.h"
#include "list.h"

#include <raylib.h>
#include <raymath.h>

#include <string.h>

int GetFCost(Vector2 start, Vector2 target, Vector2 current)
{
    int gCost = Vector2Distance(current, start);
    int hCost = Vector2Distance(current, target);

    return gCost + hCost;
}

/* 
typedef struct _pathNode{
    Vector2 *pos;

    struct _pathNode *parent;

    struct _pathNode *Child1;
    struct _pathNode *Child2;
    struct _pathNode *Child3;
} PathNode; */

/* Node* ReconstructPath(PathNode *target)
{
    Node *path = NULL;

    PathNode *currentNode = target;
    while (target->parent)
    {
        ListInsertBack(&path, currentNode->pos);
        currentNode = currentNode->parent;
    }
    
    return path;
} */


Node* AStar(Vector2 start, Vector2 target)
{
    PqNode *open = NULL; // Priority queue

    PqPush(&open, start, 0);

    Node *closed = NULL; // Linked list

    Vector2 neighbors[4] = {(Vector2){1, 0}, (Vector2){-1, 0}, (Vector2){0, 1}, (Vector2){0, -1}};

    while (open)
    {
        Vector2 current = PqPop(&open);
        ListInsertBack(&closed, current);

        if (Vector2Equals(current, target)) // Success
        {
            PqFree(open);
            open = NULL;

            return closed;
        }

        for (int i=0; i<4; i++)
        {

            Vector2 neighbor = Vector2Add(current, neighbors[i]);
            neighbor.x = round(neighbor.x);
            neighbor.y = round(neighbor.y);

            if (!IsInBounds(neighbor) || ListHasVector(&closed, neighbor)) continue;

            int neighborFCost = GetFCost(current, target, neighbor);

            // Set parent here

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