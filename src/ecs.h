#ifndef ECS_H_
#define ECS_H_

#include "raylib.h"

// Components //

struct Position {
    int entity_id;
    Vector2 pos;
};

struct Movement {
    int entity_id;
    Vector2 vel;
    float accel;
    float decel;
};

struct Health {
    int entity_id;
    int health;
    int max_health;
};

struct Circle {
    int entity_id;
    float size;
    Color color;
};

struct PlayerController {
    int entity_id;
};

/////////////////

#define max_entity_count 25

struct ComponentList {
    struct Position position_systems[max_entity_count];
    int total_pos_systems;

    struct Movement movement_systems[max_entity_count];
    int total_movement_systems;

    struct Health health_systems[max_entity_count];
    int total_hp_systems;

    struct Circle draw_systems[max_entity_count];
    int total_draw_systems;

    struct PlayerController player_control_systems[max_entity_count];
    int total_plr_ctrl_systems;
};

void player_create(struct ComponentList* components);

void update_player_control_system(struct ComponentList* components, struct PlayerController* component);
void update_movement_system(struct ComponentList* components, struct Movement* component);
void draw_circle_system(struct ComponentList components, struct Circle* component);

#endif