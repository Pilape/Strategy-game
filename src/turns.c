#include "entity.h"
#include "turns.h"

Entity *activeEntity;

void NextTurn()
{
    if (activeEntity == NULL) return;

    if (activeEntity->next == NULL) activeEntity = entities;
    else activeEntity = activeEntity->next;
}

void DoTurn()
{
    if (activeEntity == NULL || activeEntity->turnFunction == NULL) return;
    (*activeEntity->turnFunction)(activeEntity);
}