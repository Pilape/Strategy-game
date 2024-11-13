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
    (*activeEntity->turnFunction)(activeEntity);
}