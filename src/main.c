#include <raylib.h>
#include <raymath.h>

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "tilemap.h"
#include "player.h"

Camera2D mainCamera = { 0 };

void doThing()
{
    Node *list = ListCreateNode(PqCreateData(20, sizeof(int)));
    *(int*)PqGetData(list)->data = 20;

    PqData *data = PqCreateData(25, sizeof(int));
    *(int*)data->data = 25;
    PqPush(&list, data);

    PqData *dataB = PqCreateData(15, sizeof(int));
    *(int*)dataB->data = 15;
    PqPush(&list, dataB);

    PqPrint(list);

    PqPop(&list);
    PqPrint(list);
}

int main()
{
    const Vector2 SCREEN_SIZE = {800, 450};
    InitWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "AAAAA game");

    TexturesInit();
    MapInit();
    PlayerInit();
    mainCamera.target = TileToScreenPos(player.tilePos);
    mainCamera.offset = Vector2Scale(SCREEN_SIZE, 0.5f);
    mainCamera.rotation = 0.0f;
    mainCamera.zoom = 1.0f;

    doThing();

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