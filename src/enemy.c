#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#include "globals.h"
#include "astar.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"

void EnemyInit(Enemy *self)
{
    EntityInit(&self->base, Vector2One());
}

void EnemyTurnStart(Enemy *self)
{
    self->base.path = AStar(self->base.tilePos, player.base.tilePos);
}

void EnemyUpdate(Enemy *self)
{
    EntityAnimate(&self->base);
    EntityMove(&self->base, self->base.range);
}

void EnemyDraw(Enemy *self)
{
    EntityDraw(&self->base);
}