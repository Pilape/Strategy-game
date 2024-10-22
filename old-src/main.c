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
    components_init(&components);

    player_create(&components);
    chain_node_create(&components, &components.position_systems[1].pos);
    for (int i=3; i<12; i++)
    {
        chain_node_create(&components, &components.position_systems[i-1].pos);
    }

    obstacle_create(&components, (Vector2) {175, 50});
    obstacle_create(&components, (Vector2) {175, 150});
    obstacle_create(&components, (Vector2) {275, 250});
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        for (int i=1; i<=components.total_plr_ctrl_systems; i++)
        {
            update_player_control_system(&components, &components.player_control_systems[i]);
        }

        for (int i=1; i<=components.total_chain_node_systems; i++)
        {
            update_chain_node_systems(&components, &components.chain_node_systems[i]);
        }

        for (int i=1; i<=components.total_collision_systems; i++)
        {
            update_collision_system(&components, &components.collision_systems[i]);
        }

        for (int i=1; i<=components.total_movement_systems; i++)
        {
            update_movement_system(&components, &components.movement_systems[i]);
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);

            for (int i=1; i<=components.total_draw_systems; i++)
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
