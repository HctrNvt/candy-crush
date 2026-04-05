#include "../header/candy_manager.h"
#include <stdlib.h>
#include "candy.c"

int SPECIALITY_N = 3;

CandyManager * create_CandyManager(){
    CandyManager * manager = malloc(sizeof(CandyManager));    
    manager->colors[0][0] = 0;
    manager->colors[0][1] = 0;
    manager->colors[0][2] = 255;

    manager->colors[1][0] = 0;
    manager->colors[1][1] = 255;
    manager->colors[1][2] = 255;

    manager->colors[2][0] = 255;
    manager->colors[2][1] = 0;
    manager->colors[2][2] = 0;

    manager->colors[3][0] = 0;
    manager->colors[3][1] = 255;
    manager->colors[3][2] = 0;

    
    manager->specialites = malloc(sizeof(Speciality)*SPECIALITY_N);
    manager->specialites[0] = * create_Speciality('0',normal_effect);
    manager->specialites[1] = * create_Speciality('╬',zebra_effect);
    manager->specialites[2] = * create_Speciality('╬',zebra_effect); // A terminer
    manager->specialites[3] = * create_Speciality('╬',zebra_effect); // A terminer

    return manager;
}

void free_CandyManager(CandyManager * manager){
    if (manager == NULL) return;
    
    for (int i = 0; i < SPECIALITY_N; i++) // Est ce que c'est nécessaire ?
    {
        free_Speciality(&(manager->specialites[i]));
    }
    
    free(manager->specialites);
    free(manager);
}

Candy * random_candy(CandyManager manager){
    return create_Candy();
}
void fill_level(CandyManager * manager, Level * level);
void make_candy_drop(CandyManager * manager, Level * level);
void move( Level * level, int x, int y, int dx, int dy); // dx et dy compris entre -1 et 1
void check_break(Level * level);

void zebra_effect(Candy * candy, Level * level){
    // TODO
}

void disco_effect(Candy * candy, Level * level){
    // TODO
}

void carre_effect(Candy * candy, Level * level){
    // TODO
}

void normal_effect(Candy * candy, Level * level){
    // A laisser vide ou pas ?
}