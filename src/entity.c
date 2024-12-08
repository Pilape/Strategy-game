#include <raylib.h>
#include <raymath.h>

#include <stdio.h>

#include "astar.h"
#include "tilemap.h"
#include "globals.h"
#include "entity.h"
#include "turns.h"



Entity *entities = NULL;

Entity* EntityInit(Vector2 pos)
{
    Entity *newEntity = malloc(sizeof(Entity));
    if (newEntity == NULL) perror("Could not allocate memory in function 'EntityInit()'");

    newEntity->distMoved = 0;
    newEntity->health = 20;
    newEntity->tilePos = pos;
    newEntity->pos = TileToScreenPos(pos);
    newEntity->range = 1;
    newEntity->path = NULL;
    newEntity->next = NULL;

    return newEntity;
}

void EntityInsert(Entity **entities, Entity *entity)
{
    Entity *currentEntity = *entities;

    if (*entities == NULL)
    {
        entity->next = *entities;
        *entities = entity;
        return;
    }

    while (currentEntity->next)
    {
        currentEntity = currentEntity->next;
    }
    currentEntity->next = entity;
}

Entity* EntitySpawn(Vector2 pos)
{
    Entity *newEntity = EntityInit(pos);
    
    EntityInsert(&entities, newEntity);

    return newEntity;
}

void EntityAnimate(Entity *self)
{
    self->pos = Vector2Lerp(self->pos, TileToScreenPos(self->tilePos), 25 * GetFrameTime());
}

void EntityMove(Entity *self, int distance)
{
    if (self->distMoved > distance || self->path == NULL)
    {
        self->distMoved = 0;

        ListFree(self->path);
        self->path = NULL;
        //NextTurn();
    }

    if (self->path != NULL && Vector2AlmostEquals(self->pos, TileToScreenPos(self->tilePos)))
    {
        self->tilePos = ListPopFront(&self->path);
        self->distMoved++;
    }
}

void EntityDraw(Entity *self)
{
    DrawTexturePro(Textures.player, (Rectangle){0, 0, 64, 64},
        (Rectangle){self->pos.x, self->pos.y, 64, 64},
        (Vector2){32, 48}, 0, WHITE);
}

DrawQueue *EntityDrawQueue = NULL;

void DrawQueueInsert(DrawQueue **head, Entity *data, int priority)
{
    DrawQueue *newNode = malloc(sizeof(DrawQueue));
    newNode->data = data;
    newNode->priority = priority;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    if ((*head)->priority > priority)
    {
        newNode->next = *head;
        (*head) = newNode;
        return;
    }
    DrawQueue* currentNode = *head;

    while (currentNode->next != NULL && currentNode->next->priority < priority)
    {
        currentNode = currentNode->next;
        // The problem
        printf("%p \n", currentNode);
    }

    newNode->next = currentNode->next;
    currentNode->next = newNode;
}

Entity* DrawQueuePop(DrawQueue **head)
{
    if (*head == NULL)
    {
        printf("List is empty \n");
        return NULL;
    }

    DrawQueue *temp = *head;
    Entity *data = temp->data;
    *head = temp->next;

    free(temp);
    temp = NULL;

    return data;
}

void EntitiesDraw(DrawQueue *queue)
{
    while (queue)
    {
        EntityDraw(DrawQueuePop(&queue));
    }
}

void EntitiesUpdate(Entity *entities)
{
    Entity *currentEntity = entities;

    while (currentEntity)
    {
        EntityAnimate(currentEntity);
        EntityMove(currentEntity, currentEntity->range);

        //DrawQueueInsert(&EntityDrawQueue, currentEntity, currentEntity->pos.y);
        currentEntity = currentEntity->next;
    }
}