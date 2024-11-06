#include "enemy.h"
#include "player.h"

enum TURN
{
    PLAYER,
    ENEMY,
};
enum TURN CURRENT_TURN = PLAYER;

void EndTurn()
{
    switch (CURRENT_TURN)
    {
    case PLAYER:
        /* code */
        break;
    
    case ENEMY:

        break;
    }
}