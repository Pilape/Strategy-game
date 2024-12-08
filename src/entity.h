#ifndef ENTITY_H_
#define ENTITY_H_

#include <raylib.h>
#include "astar.h"

typedef struct Entity{

    Vector2 pos;
    Vector2 tilePos;
    int health;
    int range;
    Node *path;
    void (*turnFunction)();
    int distMoved;
    struct Entity *next;

} Entity;

extern Entity *entities;

typedef struct drawQueue
{
    Entity *data;

    int priority;
    struct drawQueue *next;

} DrawQueue;

extern DrawQueue *EntityDrawQueue;

Entity* EntitySpawn(Vector2 pos);
void EntityAnimate(Entity *self);
void EntitiesUpdate(Entity *entities);
void EntityDraw(Entity *self);
//void EntitiesDraw(DrawQueue *queue);
void DrawQueueInsert(DrawQueue **queue, Entity *data, int priority);

#endif