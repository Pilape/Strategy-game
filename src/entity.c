#include <raylib.h>
#include <raymath.h>

#include "astar.h"
#include "tilemap.h"
#include "globals.h"
#include "entity.h"
#include "turns.h"

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

void EntitiesUpdate(EntityNode *entities)
{
    EntityNode *currentEntity = entities;

    while (currentEntity)
    {
        EntityAnimate(currentEntity->self);
        EntityMove(currentEntity->self, currentEntity->self->range);

        currentEntity = currentEntity->next;
    }
    
}

void EntityAnimate(Entity *self)
{
    self->pos = Vector2Lerp(self->pos, TileToScreenPos(self->tilePos), 50 * GetFrameTime());
}

void EntityMove(Entity *self, int distance)
{
    if (self->distMoved > distance || self->path == NULL)
    {
        self->distMoved = 0;

        ListFree(self->path);
        self->path = NULL;
    }

    if (ListLength(self->path) > 0 && Vector2AlmostEquals(self->pos, TileToScreenPos(self->tilePos)))
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