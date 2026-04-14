#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

typedef struct level_h Level;

struct player_h
{
    int score;
    int move;
};
typedef struct player_h Player;

Player * create_Player(Level * l);
void free_Player(Player * p);
bool can_move(Player * p);

#endif