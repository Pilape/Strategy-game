#ifndef ENTITY_H_
#define ENTITY_H_

#include <raylib.h>
#include "astar.h"

typedef struct {

    Vector2 screenPos;
    Vector2 atlasPos;

} Sprite;

typedef struct Entity {

    Vector2 tilePos;
    int health;
    int range;
    Node *path;
    void (*turnFunction)();
    int distMoved;
    struct Entity *next;

    Sprite sprite;

} Entity;

extern Entity *entities;

Entity* EntitySpawn(Vector2 pos);
void EntityAnimate(Entity *self);
void EntitiesUpdate(Entity *entities);
void EntityDraw(Entity *self);
int GetEntityCount(Entity* entities);

void DrawQueueInit(Entity* entities, Sprite drawQueue[]);
void DrawQueueSort(Sprite drawQueue[], size_t queueLen);
void DrawQueuePrint(Sprite drawQueue[], size_t queueLen);
void DrawQueueDraw(Sprite drawQueue[], size_t queueLen);

#endif