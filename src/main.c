#include "raylib.h"
#include "raymath.h"

#include "stdio.h"
#include "stdlib.h"

#include "list.h"
#include "tilemap.h"
#include "player.h"

Camera2D mainCamera = { 0 };

int main()
{

    const Vector2 SCREEN_SIZE = {800, 450};
    InitWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "AAAAA game");

    TexturesInit();
    PlayerInit();
    mainCamera.target = TileToScreenPos(player.tilePos);
    mainCamera.offset = Vector2Scale(SCREEN_SIZE, 0.5f);
    mainCamera.rotation = 0.0f;
    mainCamera.zoom = 1.0f;

    while (!WindowShouldClose())
    {
        PlayerUpdate();
        mainCamera.target = Vector2Lerp(mainCamera.target, TileToScreenPos(player.tilePos), 5.0f * GetFrameTime());

        BeginDrawing();
            ClearBackground(DARKGRAY);

            BeginMode2D(mainCamera);
                DrawTiles();
                PlayerDraw();
            EndMode2D();

            DrawFPS(15, 15);
        EndDrawing();
    }

    return 0;
}