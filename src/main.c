#include "raylib.h"
#include "ecs.h"

int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib");

    struct ComponentList components;

    //for (int i=0; i<26; i++) player_create(&components);

    player_create(&components);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        for (int i=0; i<components.total_plr_ctrl_systems; i++) {
            update_player_control_system(&components, &components.player_control_systems[i]);
        }

        for (int i=0; i<components.total_movement_systems; i++)
        {
            update_movement_system(&components, &components.movement_systems[i]);
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);

            for (int i=0; i<components.total_draw_systems; i++)
            {
                draw_circle_system(components, &components.draw_systems[i]);
            }

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
