#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#include "globals.h"
#include "astar.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "turns.h"

void EnemyUpdatePath(Entity *self)
{
    self->path = AStar(self->tilePos, player.base.tilePos);
    NextTurn();
}

void EnemyInit(Enemy *self)
{
    EntityInit(&self->base, Vector2One());
    self->base.turnFunction = &EnemyUpdatePath;
}

void EnemyDraw(Enemy *self)
{
    EntityDraw(&self->base);
}