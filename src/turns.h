#ifndef TURNS_H_
#define TURNS_H_

#include "entity.h"

extern Entity *activeEntity;

void NextTurn(void);
void DoTurn(void);

#endif