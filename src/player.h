#ifndef PLAYER_H_
#define PLAYER_H_

struct Player
{
    Vector2 pos;
    Vector2 tilePos;
    int health;
};
extern struct Player player;

void PlayerInit(void);
void PlayerUpdate(void);
void PlayerDraw(void);

#endif