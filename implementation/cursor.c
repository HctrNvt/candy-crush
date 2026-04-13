#include "../header/cursor.h"
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
    cursor->i += dx;
    cursor->j += dy;
}

void show_Cursor(Cursor * c){

}