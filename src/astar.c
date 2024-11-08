#include "astar.h"
#include "tilemap.h"

#include <raylib.h>
#include <raymath.h>

#include <string.h>
#include <stdio.h>

Node* ListCreateNode(Vector2 data)
{
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) perror("Function 'ListCreateNode' could not allocate memory");
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void ListInsertFront(Node **head, Vector2 data)
{
    Node* newNode = ListCreateNode(data);
    newNode->next = *head;
    *head = newNode;
}

void ListInsertBack(Node **head, Vector2 data)
{
    Node *newNode = ListCreateNode(data);
    Node *currentNode = *head;

    if (*head == NULL) {
        ListInsertFront(head, data);
        return;
    }

    while (currentNode->next)
    {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;
}

Vector2 ListPopFront(Node **head)
{
    if (*head == NULL)
    {
        printf("List is empty \n");
        return (Vector2){0, 0};
    }

    Node *temp = *head;
    Vector2 data = temp->data;

    *head = temp->next;
    free(temp);
    temp = NULL;

    return data;
}

Vector2 ListPopBack(Node **head)
{
    if (*head == NULL) {
        printf("List is empty \n");
        return (Vector2){0, 0};
    }

    Node *currentNode = *head;
    while (currentNode->next->next)
    {
        currentNode = currentNode->next;
    }

    Vector2 data = currentNode->next->data;
    free(currentNode->next);

    currentNode->next = NULL;

    return data;
}

int ListLength(Node* head)
{
    int length = 0;
    Node *currentNode = head;
    
    while (currentNode)
    {
        length++;
        currentNode = currentNode->next;
    }
    
    return length;
}

void ListPrint(Node* head)
{
    printf("List: ");
    Node *currentNode = head;

    while (currentNode)
    {
        printf("[x: %d, y: %d] ", (int)currentNode->data.x, (int)currentNode->data.y);
        currentNode = currentNode->next;
    }
    printf("\n");
}

void ListFree(Node *head)
{
    while (head)
    {
        ListPopFront(&head);
    }
}

//PqData* PqGetData(Node *pqNode) { return (PqData*)(pqNode)->data; }

/* PqNode* PqCreateData(int priority, size_t size)
{
    PqData *temp = malloc(sizeof(PqData));
    if (temp == NULL) perror("Faield to allocate memory [Function: PqCreateData]");

    temp->priority = priority;
    temp->data = malloc(sizeof(size));

    return temp;
} */

PqNode *PqCreateNode(Vector2 data, int priority)
{
    PqNode *newNode = malloc(sizeof(PqNode));
    if (newNode == NULL) perror("Function 'ListCreateNode' could not allocate memory");
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;

    return newNode;
};

void PqPush(PqNode **head, Vector2 data, int priority)
{
    PqNode* newNode = PqCreateNode(data, priority);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    if ((*head)->priority > priority)
    {
        newNode->next = *head;
        (*head) = newNode;
        //ListInsertFront(head, newNode);
        return;
    }

    PqNode* currentNode = *head;

    while (currentNode->next && currentNode->next->priority < priority)
    {
        currentNode = currentNode->next;
    }

    newNode->next = currentNode->next;
    currentNode->next = newNode;
}

Vector2 PqPop(PqNode **head)
{
    if (*head == NULL)
    {
        printf("List is empty \n");
        return (Vector2){0, 0};
    }

    PqNode *temp = *head;
    Vector2 data = temp->data;
    *head = temp->next;

    free(temp);
    temp = NULL;

    return data;
}

void PqPrint(PqNode* head)
{
    printf("List: ");
    PqNode *currentNode = head;

    while (currentNode)
    {
        printf("[x: %f, y: %f] ", currentNode->data.x, currentNode->data.y);
        currentNode = currentNode->next;
    }
    printf("\n");
}

#include "raylib.h"
#include "raymath.h"

int ListHasVector(Node **head, Vector2 vector)
{
    if (head == NULL) return 0; // If list empty

    Node* currentNode = *head;
    while (currentNode->next)
    {
        if (Vector2Equals(currentNode->data, vector)) return 1;
        currentNode = currentNode->next;
    }
    
    return 0;
}

int PqHasVector(PqNode **head, Vector2 vector)
{
    if (*head == NULL) return 0;

    PqNode* currentNode = *head;

    while (currentNode->next)
    {
        if (Vector2Equals(currentNode->data, vector)) return 1;

        currentNode = currentNode->next;
    }
    return 0;
}

void PqFree(PqNode *head)
{
    while (head)
    {
        PqPop(&head);
    }
}

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
    int gCost = Vector2Distance(current, start)*10;
    int hCost = Vector2Distance(current, target)*10;

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

            int neighborFCost = GetFCost(current, target, neighbor)*10;

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

Node* GetReachableNodes(Vector2 start, int range)
{
    PqNode *open = NULL; // Priority queue
    PqPush(&open, start, 0);

    Node *closed = NULL; // Linked list

    Vector2 neighbors[4] = {(Vector2){1, 0}, (Vector2){-1, 0}, (Vector2){0, 1}, (Vector2){0, -1}};

    while (open)
    {
        if (open->priority > range*10) // If shortest distance is out of reach
        {
            ListInsertBack(&closed, PqPop(&open));
            break;
        }

        Vector2 current = PqPop(&open);
        ListInsertBack(&closed, current);

        for (int i=0; i<4; i++)
        {
            Vector2 neighbor = Vector2Add(current, neighbors[i]);
            neighbor.x = round(neighbor.x);
            neighbor.y = round(neighbor.y);

            if (!IsTraversible(neighbor) || ListHasVector(&closed, neighbor)) continue;

            int neighborCost = Vector2Distance(neighbor, start)*10;

            if (!PqHasVector(&open, neighbor))
            {   
                PqPush(&open, neighbor, neighborCost);
            }
        }
    }

    PqFree(open);
    open = NULL;

    return closed; // Failure
}