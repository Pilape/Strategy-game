#include "ecs.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

unsigned int ENTITIES = 1;

void components_init(struct ComponentList* components)
{
    components->total_plr_ctrl_systems = 0;
    components->total_hp_systems = 0;
    components->total_movement_systems = 0;
    components->total_pos_systems = 0;
    components->total_draw_systems = 0;
    components->total_collision_systems = 0;
}

void player_create(struct ComponentList* components)
{
    if (ENTITIES == max_entity_count) {
        printf("Entity limit reached \n");
        return;
    }
    int id = ENTITIES++;
    
    components->player_control_systems[id].entity_id = id;
    components->total_plr_ctrl_systems++;

    components->health_systems[id].entity_id = id;
    components->total_hp_systems++;

    components->position_systems[id].entity_id = id;
    components->position_systems[id].pos = (Vector2) {64, 64};
    components->total_pos_systems++;

    components->movement_systems[id].entity_id = id;
    components->movement_systems[id].accel = 75;
    components->movement_systems[id].decel = 0.99;
    components->movement_systems[id].dist_max = 475.0f;
    components->total_movement_systems++;

    components->collision_systems[id].entity_id = id;
    components->collision_systems[id].size = 15.0f;
    components->total_collision_systems++;

    components->draw_systems[id].entity_id = id;
    components->draw_systems[id].color = RED;
    components->draw_systems[id].size = 15.0f;
    components->total_draw_systems++;
}

void obstacle_create(struct ComponentList* components, Vector2 pos)
{
    if (ENTITIES == max_entity_count) {
        printf("Entity limit reached \n");
        return;
    }
    int id = ENTITIES++;

    components->position_systems[id].entity_id = id;
    components->position_systems[id].pos = pos;
    components->total_pos_systems++;

    components->collision_systems[id].entity_id = id;
    components->collision_systems[id].size = 24.0f;
    components->total_collision_systems++;

    components->draw_systems[id].entity_id = id;
    components->draw_systems[id].color = BLACK;
    components->draw_systems[id].size = 24.0f;
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

    component->dist_used += Vector2Length(component->vel);
    if (component->dist_used >= component->dist_max) return;

    components->position_systems[component->entity_id].pos = Vector2Add(components->position_systems[component->entity_id].pos, component->vel);

    component->vel = Vector2Scale(component->vel, component->decel * GetFrameTime());
}

enum COLLISION_TYPE {
    NONE,
    VERTICAL,
    HORISONTAL,
    BOTH,
};

enum COLLISION_TYPE get_collision(Vector2 pos1, Vector2 newpos1, float size1, Vector2 pos2, float size2)
{
    bool colliding_h = false;
    bool colliding_v = false;

    if (Vector2Distance((Vector2){newpos1.x, pos1.y}, pos2) < size1 + size2) colliding_h = true;
    if (Vector2Distance((Vector2){pos1.x, newpos1.y}, pos2) < size1 + size2) colliding_v = true;

    if (colliding_h && colliding_v) return BOTH;

    if (colliding_h) return HORISONTAL;
    if (colliding_v) return VERTICAL;

    return NONE;
}

void update_collision_system(struct ComponentList* components, struct Collision* component)
{
    if (components->movement_systems[component->entity_id].entity_id == 0) return;

    Vector2 future_pos = components->position_systems[component->entity_id].pos;
    future_pos = Vector2Add(future_pos, Vector2Scale(components->movement_systems[component->entity_id].vel, GetFrameTime()));

    for (int i=1; i<=components->total_collision_systems; i++)
    {
        if (i == component->entity_id) continue;

        struct Collision collision_object = components->collision_systems[i];
        Vector2 collision_object_pos = components->position_systems[i].pos;

        enum COLLISION_TYPE collision = get_collision(
        components->position_systems[component->entity_id].pos, future_pos, component->size, 
        collision_object_pos, collision_object.size);

        printf("%d \n", collision);
        if (collision == BOTH) components->movement_systems[component->entity_id].vel = Vector2Zero();
        if (collision == HORISONTAL) components->movement_systems[component->entity_id].vel.x = 0;
        if (collision == VERTICAL) components->movement_systems[component->entity_id].vel.y = 0;
    }
}

void draw_circle_system(struct ComponentList components, struct Circle* component)
{
    DrawCircleV(components.position_systems[component->entity_id].pos, component->size, component->color);
    DrawCircleLinesV(components.position_systems[component->entity_id].pos, components.collision_systems[component->entity_id].size, BLUE);
}
