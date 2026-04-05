#include "../header/candy.h"
#include <stdlib.h>


Candy * create_Candy(int x, int y, int r, int g, int b,
     Candy * right, Candy * left, Candy * top, Candy * bot){
    
    Candy * self = malloc(sizeof(Candy));
    self->x = x;
    self->y = y;

    self->r = r;
    self->g = g;
    self->b = b;

    self->bot = bot;
    self->left = left;
    self->top= top;
    self->right = right;
    return self;
}

void free_Candy(Candy * candy){
    free(candy);
}