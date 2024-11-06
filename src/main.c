#include <raylib.h>
#include <raymath.h>

#include <stdio.h>
#include <stdlib.h>

#include "tilemap.h"
#include "player.h"
#include "enemy.h"

Camera2D mainCamera = { 0 };

int main()
{
    const Vector2 SCREEN_SIZE = {800, 450};
    InitWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "AAAAA game");

    TexturesInit();
    MapInit();
    PlayerInit();
    mainCamera.target = TileToScreenPos(player.base.tilePos);
    mainCamera.offset = Vector2Scale(SCREEN_SIZE, 0.5f);
    mainCamera.rotation = 0.0f;
    mainCamera.zoom = 1.0f;

    Enemy enemy = { 0 };
    EnemyInit(&enemy);
    EnemyTurnStart(&enemy);

    while (!WindowShouldClose())
    {
        PlayerUpdate();

        EnemyUpdate(&enemy);

        BeginDrawing();
            ClearBackground(DARKGRAY);

            BeginMode2D(mainCamera);
                DrawTiles();

                EnemyDraw(&enemy);

                PlayerDraw();
            EndMode2D();

            DrawFPS(15, 15);
        EndDrawing();
    }

    return 0;
}