#include "../header/candy.h"
#include "../header/speciality.h"
#include <stdlib.h>

Candy *create_Candy(int x, int y, int color, Speciality *s)
{
    Candy *self = malloc(sizeof(Candy));
    self->x = x;
    self->y = y;

    self->color = color;
    self->s = s;
    return self;
}

void free_Candy(Candy *candy)
{
    free(candy);
}