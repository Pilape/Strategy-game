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


typedef struct _pathNode{
    Vector2 *pos;

    struct _pathNode *parent;

    struct _pathNode *Child1;
    struct _pathNode *Child2;
    struct _pathNode *Child3;
} PathNode;

Node* ReconstructPath(PathNode *target)
{
    Node *path = NULL;

    PathNode *currentNode = target;
    while (target->parent)
    {
        ListInsertBack(&path, currentNode->pos);
        currentNode = currentNode->parent;
    }
    
    return path;
}


Node* AStar(Vector2 start, Vector2 target)
{
    Node *open = NULL; // Priority queue
    PqData *startNode = PqCreateData(0, sizeof(Vector2));
    *(Vector2*)startNode->data = start;

    PqPush(&open, startNode);

    Node *closed = NULL; // Linked list

    Vector2 neighbors[4] = {(Vector2){1, 0}, (Vector2){-1, 0}, (Vector2){0, 1}, (Vector2){0, -1}};

    while (open)
    {
        PqData current = PqPop(&open);
        Vector2 *currentData = (Vector2*)current.data;
        ListInsertBack(&closed, currentData);

        if (Vector2Equals(*(Vector2*)current.data, target)) return closed;

        for (int i=0; i<4; i++)
        {

            Vector2 neighbor = Vector2Add(*(Vector2*)current.data, neighbors[i]);
            neighbor.x = round(neighbor.x);
            neighbor.y = round(neighbor.y);

            if (!IsInBounds(neighbor) || ListHasVector(&closed, neighbor)) continue;

            int neighborFCost = GetFCost(*currentData, target, neighbor);

            // Set parent here

            if (!PqHasVector(&open, neighbor))
            {
                PqData *neighborData = PqCreateData(neighborFCost, sizeof(Vector2));
                *(Vector2*)neighborData->data = neighbor;
                
                PqPush(&open, neighborData);
            
            }
        }
    }

    return closed;
}