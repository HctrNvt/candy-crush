#ifndef PLAYER_H
#define PLAYER_H

struct player_h
{
    int score;
    int coup;
};
typedef struct player_h Player;
bool can_move();

#endif