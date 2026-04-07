#include "../header/candy.h"
#include <stdlib.h>


Candy * create_Candy(int x, int y, int color,
     Candy * right, Candy * left, Candy * top, Candy * bot){
    
    Candy * self = malloc(sizeof(Candy));
    self->x = x;
    self->y = y;

    self->color = color;
    
    self->bot = bot;
    self->left = left;
    self->top= top;
    self->right = right;
    return self;
}

void free_Candy(Candy * candy){
    free(candy);
}