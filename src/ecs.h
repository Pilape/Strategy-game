#ifndef ECS_H_
#define ECS_H_

#include "raylib.h"

// Components //

struct Position {
    unsigned int entity_id;
    Vector2 pos;
};

struct Movement {
    unsigned int entity_id;
    Vector2 vel;

    float dist_used;
    float dist_max;

    float accel;
    float decel;
};

struct Health {
    unsigned int entity_id;
    int health;
    int max_health;
};

struct Circle {
    unsigned int entity_id;
    float size;
    Color color;
};

struct PlayerController {
    unsigned int entity_id;
};

/////////////////

#define max_entity_count 25

struct ComponentList {
    struct Position position_systems[max_entity_count];
    unsigned int total_pos_systems;

    struct Movement movement_systems[max_entity_count];
    unsigned int total_movement_systems;

    struct Health health_systems[max_entity_count];
    unsigned int total_hp_systems;

    struct Circle draw_systems[max_entity_count];
    unsigned int total_draw_systems;

    struct PlayerController player_control_systems[max_entity_count];
    unsigned int total_plr_ctrl_systems;
};

void components_init(struct ComponentList* components);
void player_create(struct ComponentList* components);

void update_player_control_system(struct ComponentList* components, struct PlayerController* component);
void update_movement_system(struct ComponentList* components, struct Movement* component);
void draw_circle_system(struct ComponentList components, struct Circle* component);

#endif