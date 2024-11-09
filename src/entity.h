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

} Entity;

typedef struct EntityNode {

    Entity *self;
    struct EntityNode *next;
} EntityNode;

extern EntityNode *entities;

void EntityInsertFront(EntityNode **head, Entity *self);

void EntityInit(Entity *self, Vector2 pos);
void EntityAnimate(Entity *self);
void EntityMove(Entity *self, int distance);
void EntitiesUpdate(EntityNode *entities);
void EntityDraw(Entity *self);

#endif