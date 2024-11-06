#ifndef ENTITY_H_
#define ENTITY_H_

#include <raylib.h>
#include "astar.h"

typedef struct {

    Vector2 pos;
    Vector2 tilePos;
    int health;
    int range;
    Node *path;

} Entity;

void EntityInit(Entity *self, Vector2 pos);
void EntityAnimate(Entity *self);
void EntityMove(Entity *self, int distance);
void EntityDraw(Entity *self);

#endif