#include <raylib.h>
#include <raymath.h>

#include "astar.h"
#include "tilemap.h"
#include "globals.h"
#include "entity.h"

void EntityInit(Entity *self, Vector2 pos)
{
    self->tilePos = pos;
    self->pos = TileToScreenPos(self->tilePos);
    self->health = 20;
    self->range = 2;
}

void EntityAnimate(Entity *self)
{
    self->pos = Vector2Lerp(self->pos, TileToScreenPos(self->tilePos), 50 * GetFrameTime());
}

void EntityMove(Entity *self, int distance)
{
    static int distanceMoved = 0;
    if (distanceMoved >= distance && distance != -1) return;

    if (ListLength(self->path) > 0 && Vector2AlmostEquals(self->pos, TileToScreenPos(self->tilePos)))
    {
        self->tilePos = ListPopFront(&self->path);
        distanceMoved++;
    }
}

void EntityDraw(Entity *self)
{
    DrawTexturePro(Textures.player, (Rectangle){0, 0, 64, 64},
        (Rectangle){self->pos.x, self->pos.y, 64, 64},
        (Vector2){32, 48}, 0, WHITE);
}