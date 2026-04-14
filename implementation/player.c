#include "../header/player.h"
#include "../header/level.h"

#include <stdlib.h>

Player * create_Player(Level * l){
    Player * p = malloc(sizeof(Player));
    p->score = 0;
    p->move = l->max_move;
    return p;
}
void free_Player(Player * p){
    free(p);
}


bool can_move(Player * p){
    return p->move > 0;
}