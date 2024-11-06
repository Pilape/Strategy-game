#ifndef PLAYER_H_
#define PLAYER_H_

#include "entity.h"

struct Player
{
    Entity base;
    Node *reachableNodes;
};
extern struct Player player;

void PlayerInit(void);
void PlayerUpdate(void);
void PlayerDraw(void);

#endif