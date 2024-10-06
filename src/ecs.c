#include "ecs.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

int PLAYER_COUNT;

void player_create(struct ComponentList* components)
{
    if (PLAYER_COUNT == max_entity_count) {
        printf("Entity limit reached \n");
        return;
    }
    int id = PLAYER_COUNT++;

    components->player_control_systems[id].entity_id = id;
    components->total_plr_ctrl_systems++;

    components->health_systems[id].entity_id = id;
    components->total_hp_systems++;

    components->position_systems[id].entity_id = id;
    components->position_systems[id].pos.y = id * 32;
    components->total_pos_systems++;

    components->movement_systems[id].entity_id = id;
    components->movement_systems[id].accel = 75;
    components->movement_systems[id].decel = 0.99;
    components->total_movement_systems++;

    components->draw_systems[id].entity_id = id;
    components->draw_systems[id].color = RED;
    components->draw_systems[id].size = 15.0f;
    components->total_draw_systems++;

}

void update_player_control_system(struct ComponentList* components, struct PlayerController* component)
{
    Vector2 dir = Vector2Zero();
    if (IsKeyDown(KEY_LEFT)) dir.x--;
    if (IsKeyDown(KEY_RIGHT)) dir.x++;
    if (IsKeyDown(KEY_UP)) dir.y--;
    if (IsKeyDown(KEY_DOWN)) dir.y++;
    dir = Vector2Normalize(dir);

    Vector2 new_vel = Vector2Scale(dir, components->movement_systems[component->entity_id].accel);
    components->movement_systems[component->entity_id].vel = Vector2Add(components->movement_systems[component->entity_id].vel, new_vel);

}

void update_movement_system(struct ComponentList* components, struct Movement* component)
{
    component->vel = Vector2Scale(component->vel, GetFrameTime());
    components->position_systems[component->entity_id].pos = Vector2Add(components->position_systems[component->entity_id].pos, component->vel);

    component->vel = Vector2Scale(component->vel, component->decel * GetFrameTime());
}

void draw_circle_system(struct ComponentList components, struct Circle* component)
{
    DrawCircleV(components.position_systems[component->entity_id].pos, component->size, component->color);
}