#include "../header/candy.h"
#include "../header/speciality.h"
#include <stdlib.h>

Candy *create_Candy(int i, int j, int color, Speciality *s)
{
    Candy *self = malloc(sizeof(Candy));
    self->i = i;
    self->j = j;

    self->color = color;
    self->s = s;
    return self;
}

void free_Candy(Candy *candy)
{
    free(candy);
}