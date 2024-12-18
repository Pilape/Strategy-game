#include <raylib.h>
#include <raymath.h>

#include <stdio.h>
#include <stdlib.h>

#include "tilemap.h"
#include "player.h"
#include "enemy.h"
#include "globals.h"
#include "turns.h"

#define MIN(a, b) ((a)<(b)? (a) : (b))

Camera2D mainCamera = { 0 };

Texture2D atlasTexture;

int main()
{
    // Init
    int scale = 1;
    const Vector2 SCREEN_SIZE = {800, 450};
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "AAAAA game");
    SetWindowMinSize(950, 500);

    atlasTexture = LoadTexture("resources/atlas.png");
    MapInit();
    PlayerInit();
    
    EnemySpawn(Vector2One());
    EnemySpawn((Vector2){WORLD_LENGTH-1, WORLD_WIDTH-1});
    EnemySpawn((Vector2){WORLD_LENGTH-1, 1});
    EnemySpawn((Vector2){1, WORLD_WIDTH-1});

    mainCamera.target = TileToScreenPos(player.base->tilePos);
    mainCamera.offset = Vector2Scale(SCREEN_SIZE, 0.5f);
    mainCamera.rotation = 0.0f;
    mainCamera.zoom = scale;

    activeEntity = entities;

    while (!WindowShouldClose())
    {
        // Update
        EntitiesUpdate(entities);
        DoTurn();

        if (IsWindowResized() && !IsWindowMaximized()) // Only maximize no manual rescaling
        {
            SetWindowSize(SCREEN_SIZE.x, SCREEN_SIZE.y);
        }

        scale = MIN(GetScreenWidth()/SCREEN_SIZE.x, GetScreenHeight()/SCREEN_SIZE.y);
        mainCamera.zoom = scale * 2;
        mainCamera.offset = Vector2Scale((Vector2){GetScreenWidth(), GetScreenHeight()}, 0.5f);

        const size_t drawQueueLen = GetEntityCount(entities);
        Sprite drawQueue[drawQueueLen];
        DrawQueueInit(entities, drawQueue);
        DrawQueueSort(drawQueue, drawQueueLen);

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode2D(mainCamera);
                DrawTiles();
                PlayerDraw();
                DrawQueueDraw(drawQueue, drawQueueLen);
            EndMode2D();

            DrawFPS(15, 15);
        EndDrawing();
    }

    return 0;
}