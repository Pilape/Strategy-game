#include "ecs.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

unsigned int ENTITIES = 1;

void components_init(struct ComponentList *components)
{
    components->total_collision_systems = 0;
    components->total_pos_systems = 0;
    components->total_movement_systems = 0;
    components->total_hp_systems = 0;
    components->total_draw_systems = 0;
    components->total_plr_ctrl_systems = 0;
}


void player_create(struct ComponentList *components)
{
    if (ENTITIES == max_entity_count)
    {
        printf("Entity limit reached \n");
        return;
    }
    int id = ENTITIES++;

    components->player_control_systems[id].entity_id = id;
    components->total_plr_ctrl_systems++;

    components->health_systems[id].entity_id = id;
    components->total_hp_systems++;

    components->position_systems[id].entity_id = id;
    components->position_systems[id].pos = (Vector2){64, 64};
    components->total_pos_systems++;

    components->movement_systems[id].entity_id = id;
    components->movement_systems[id].accel = 75;
    components->movement_systems[id].decel = 0.99;
    components->movement_systems[id].dist_max = 475.0f;
    components->total_movement_systems++;

    components->collision_systems[id].entity_id = id;
    components->collision_systems[id].size = 15.0f;
    components->collision_systems[id].pos = &components->position_systems[id].pos;
    components->total_collision_systems++;

    components->draw_systems[id].entity_id = id;
    components->draw_systems[id].color = RED;
    components->draw_systems[id].size = 15.0f;
    components->total_draw_systems++;
}


void obstacle_create(struct ComponentList *components, Vector2 pos)
{
    if (ENTITIES == max_entity_count)
    {
        printf("Entity limit reached \n");
        return;
    }
    int id = ENTITIES++;

    components->position_systems[id].entity_id = id;
    components->position_systems[id].pos = pos;
    components->total_pos_systems++;

    components->collision_systems[id].entity_id = id;
    components->collision_systems[id].size = 24.0f;
    components->collision_systems[id].pos = &components->position_systems[id].pos;
    components->total_collision_systems++;

    components->draw_systems[id].entity_id = id;
    components->draw_systems[id].color = BLACK;
    components->draw_systems[id].size = 24.0f;
    components->total_draw_systems++;
}


void update_player_control_system(struct ComponentList *components, struct PlayerController *component)
{
    if (components->movement_systems[component->entity_id].entity_id == 0)
        return;

    Vector2 dir = Vector2Zero();
    if (IsKeyDown(KEY_LEFT))
        dir.x--;
    if (IsKeyDown(KEY_RIGHT))
        dir.x++;
    if (IsKeyDown(KEY_UP))
        dir.y--;
    if (IsKeyDown(KEY_DOWN))
        dir.y++;
    dir = Vector2Normalize(dir);

    Vector2 new_vel = Vector2Scale(dir, components->movement_systems[component->entity_id].accel);
    components->movement_systems[component->entity_id].vel = Vector2Add(components->movement_systems[component->entity_id].vel, new_vel);
}


void update_movement_system(struct ComponentList *components, struct Movement *component)
{
    if (components->movement_systems[component->entity_id].entity_id == 0)
        return;

    component->vel = Vector2Scale(component->vel, GetFrameTime());

    component->dist_used += Vector2Length(component->vel);
    // if (component->dist_used >= component->dist_max) return;

    components->position_systems[component->entity_id].pos = Vector2Add(components->position_systems[component->entity_id].pos, component->vel);
    
    component->vel = Vector2Scale(component->vel, component->decel * GetFrameTime());
}


Vector2 closest_point_on_line(Vector2 line_start, Vector2 line_end, Vector2 target){ 

    Vector2 closest_point = Vector2Zero();

    float A = line_end.y - line_start.y;
    float B = line_start.x - line_end.x;

    double C1 = A*line_start.x + B*line_start.y;
    double C2 = -B*line_start.x + A*line_start.y;

    double det = A*A + B*B;

    if (det == 0) return target;

    closest_point.x = (A*C1 - B*C2)/det;
    closest_point.y = (A*C2 - -B*C1)/det;

    return closest_point;
}

void solve_collision(struct ComponentList *components, struct Collision *collider_a, struct Collision *collider_b)
{
    Vector2 *collider_a_vel = &components->movement_systems[collider_a->entity_id].vel;
    Vector2 futurepos_a = Vector2Add(*collider_a->pos, Vector2Scale(*collider_a_vel, GetFrameTime())); // scale with frame or the velocity will be BIG

    Vector2 d = closest_point_on_line(*collider_a->pos, futurepos_a, *collider_b->pos);

    double closestdist = Vector2Distance(*collider_b->pos, d); 
    if(closestdist >= collider_a->size + collider_b->size){ 
        // No collision has occurred
        return;
    }

    //*collider_a_vel = Vector2Zero();
    double backdist = sqrt(pow(collider_a->size + collider_b->size, 2) - pow(closestdist, 2));
    Vector2 collision_point = Vector2Subtract(d, Vector2Scale(Vector2Normalize(*collider_a_vel), backdist));
    
    Vector2 dir_from_collision = Vector2Subtract(collision_point, *collider_b->pos);

    *collider_a_vel = Vector2Scale(Vector2Normalize(dir_from_collision), Vector2Length(*collider_a_vel));
}

void update_collision_system(struct ComponentList *components, struct Collision *component)
{
    if (components->movement_systems[component->entity_id].entity_id == 0)
        return;

    for (int i = 1; i <= components->total_collision_systems; i++)
    {
        if (components->collision_systems[i].entity_id == component->entity_id)
            continue;

        solve_collision(components, component, &components->collision_systems[i]);
    }
}


void draw_circle_system(struct ComponentList components, struct Circle *component)
{
    if (components.movement_systems[component->entity_id].entity_id == 0)
        return;

    DrawCircleV(components.position_systems[component->entity_id].pos, component->size, component->color);
}
