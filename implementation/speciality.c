#include "../header/speciality.h"
#include <stdlib.h>

Speciality * create_Speciality(char c,void (*effect)(Candy * bonbon, Level * cur_level )){
    Speciality * s = malloc(sizeof(Speciality));
    s->symbol = c;
    s->effect = effect;
}

void free_Speciality(Speciality * s){
    free(s->effect);
    free(s);
}