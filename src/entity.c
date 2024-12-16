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
    newEntity->range = 1;
    newEntity->path = NULL;
    newEntity->next = NULL;

    newEntity->sprite.screenPos = TileToScreenPos(pos);
    newEntity->sprite.atlasPos = Vector2Zero();

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
    self->sprite.screenPos = Vector2Lerp(self->sprite.screenPos, TileToScreenPos(self->tilePos), 25 * GetFrameTime());
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

    if (self->path != NULL && Vector2AlmostEquals(self->sprite.screenPos, TileToScreenPos(self->tilePos)))
    {
        self->tilePos = ListPopFront(&self->path);
        self->distMoved++;
    }
}

void EntityDraw(Entity *self)
{
    DrawTexturePro(Textures.player, (Rectangle){0, 0, 64, 64},
        (Rectangle){self->sprite.screenPos.x, self->sprite.screenPos.y, 64, 64},
        (Vector2){32, 48}, 0, WHITE);
}

int GetEntityCount(Entity* entities)
{
    int count = 0;

    Entity* temp = entities;
    while (temp)
    {
        count++;
        temp = temp->next;
    }
    
    return count;
}

void DrawQueueInit(Entity* entities, Sprite drawQueue[])
{
    int index = 0;
    Entity* currentEntity = entities;
    while (currentEntity)
    {
        drawQueue[index] = currentEntity->sprite;

        currentEntity = currentEntity->next;
        index++;
    }
}

void DrawQueueSwap(Sprite* xp, Sprite* yp){
    Sprite temp = *xp;
    *xp = *yp;
    *yp = temp;
}


void DrawQueueSort(Sprite drawQueue[], size_t queueLen)
{
    // Bubble sort (stolen from web)
    int i, j;
    bool swapped;
    for (i = 0; i < queueLen - 1; i++) {
        swapped = false;
        for (j = 0; j < queueLen - i - 1; j++) {
            if (drawQueue[j].screenPos.y > drawQueue[j + 1].screenPos.y) {
                DrawQueueSwap(&drawQueue[j], &drawQueue[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }
}

void DrawQueueDraw(Sprite drawQueue[], size_t queueLen)
{
    for (int i=0; i<queueLen; i++)
    {
        Sprite self = drawQueue[i];

        DrawTexturePro(Textures.player, (Rectangle){0, 0, 64, 64},
            (Rectangle){self.screenPos.x, self.screenPos.y, 64, 64},
            (Vector2){32, 48}, 0, WHITE);
    }
}

void DrawQueuePrint(Sprite drawQueue[], size_t queueLen)
{
    for (int i=0; i<queueLen; i++)
    {
        Sprite self = drawQueue[i];
        printf("Sprite: {ScreenPos: [x: %f, y: %f], AtlasPos: [x: %d, y: %d]} \n", self.screenPos.x, self.screenPos.y, (int)self.atlasPos.x, (int)self.atlasPos.y);
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