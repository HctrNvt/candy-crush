#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

struct player_h
{
    int score;
    int move;
};
typedef struct player_h Player;
bool can_move(Player * p);

#endif