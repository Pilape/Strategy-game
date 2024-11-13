#include <raylib.h>
#include <raymath.h>

#include "astar.h"
#include "tilemap.h"
#include "globals.h"
#include "entity.h"
#include "turns.h"
/* 
EntityNode* EntityNodeCreate(Entity *self)
{
    EntityNode *newNode = malloc(sizeof(EntityNode));
    if (newNode == NULL) perror("Function 'EntityCreate' could not allocate memory");
    newNode->self = self;
    newNode->next = NULL;

    return newNode;
}

void EntityInsertFront(EntityNode **head, Entity *self)
{
    EntityNode* newNode = EntityNodeCreate(self);
    newNode->next = *head;
    *head = newNode;
}

EntityNode *entities = NULL;

void EntityInit(Entity *self, Vector2 pos)
{
    self->tilePos = pos;
    self->pos = TileToScreenPos(self->tilePos);
    self->health = 20;
    self->range = 1;
    self->distMoved = 0;

    EntityInsertFront(&entities, self);
}
 */

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

void EntitiesUpdate(Entity *entities)
{
    Entity *currentEntity = entities;

    while (currentEntity)
    {
        EntityAnimate(currentEntity);
        EntityMove(currentEntity, currentEntity->range);

        currentEntity = currentEntity->next;
    }
    
}

void EntityDraw(Entity *self)
{
    DrawTexturePro(Textures.player, (Rectangle){0, 0, 64, 64},
        (Rectangle){self->pos.x, self->pos.y, 64, 64},
        (Vector2){32, 48}, 0, WHITE);
}

void EntitiesDraw(Entity *entities)
{
    Entity *currentEntity = entities;

    while (currentEntity)
    {
        EntityDraw(currentEntity);

        currentEntity = currentEntity->next;
    }
    
}