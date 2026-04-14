#include "../header/cursor.h"
#include "../header/level.h"
#include <stdlib.h>


Cursor * create_Cursor(int i, int j, int max_i, int max_j){
    Cursor * c = malloc(sizeof(Cursor));
    c->i = i;
    c->j = j;
    c->max_i = max_i;
    c->max_j = max_j;
    return c;
}

void free_Cursor(Cursor * c){
    free(c);
}

void move_Cursor(Cursor * cursor, int dx, int dy){
    if (cursor->i + dx >= 0 && cursor->i + dx < cursor->max_i)
        cursor->i += dx;

    if (cursor->j + dy >= 0 && cursor->j + dy < cursor->max_j)
        cursor->j += dy;
}