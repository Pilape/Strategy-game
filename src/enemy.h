#ifndef ENEMY_H_
#define ENEMY_H_

#include "entity.h"

typedef struct {

    Entity base;

} Enemy;

void EnemyInit(Enemy *self);
void EnemyTurnStart(Enemy *self);
void EnemyUpdate(Enemy *self);
void EnemyDraw(Enemy *self);

#endif