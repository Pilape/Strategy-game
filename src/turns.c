#include "entity.h"
#include "turns.h"

EntityNode *currentEntity;

void NextTurn()
{
    if (currentEntity == NULL) return;

    if (currentEntity->next == NULL) currentEntity = entities;
    else currentEntity = currentEntity->next;
}

void DoTurn()
{
    (*currentEntity->self->turnFunction)(currentEntity->self);
}