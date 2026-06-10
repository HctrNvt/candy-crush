#include "../header/speciality.h"
#include <stdlib.h>

Speciality *create_Speciality(char c, void (*effect)(Candy *bonbon, Level *cur_level, Player *player, int i, int j), int points)
{
    Speciality *s = malloc(sizeof(Speciality));
    s->symbol = c;
    s->effect = effect;
    s->points = points;
    return s;
}

void free_Speciality(Speciality *s)
{
    free(s->effect);
    free(s);
}