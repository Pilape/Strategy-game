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
    self->path = AStar(self->tilePos, player.base->tilePos);
    NextTurn();
}

void EnemySpawn(Vector2 pos)
{
    Entity *newEnemy = EntitySpawn(pos);
    newEnemy->turnFunction = &EnemyUpdatePath;
}