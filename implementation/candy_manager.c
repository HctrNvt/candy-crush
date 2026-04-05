#include <stdlib.h>

#include "../header/candy_manager.h"
#include "../header/speciality.h"
#include "../header/candy.h"
#include "../header/level.h"

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
    manager->specialites[2] = * create_Speciality('#',carre_effect); // A terminer
    manager->specialites[3] = * create_Speciality('@',disco_effect); // A terminer

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

Candy * random_candy(int x, int y, CandyManager * manager){
    int color_index = rand() % 4;
    int r = manager->colors[color_index][0];
    int g = manager->colors[color_index][1];
    int b = manager->colors[color_index][2];

    return create_Candy(x,y,r,g,b,NULL,NULL,NULL,NULL);
}

// Ne se soucie pas de si le niveau contient déjà des bonbons ou non.
void fill_level(CandyManager * manager, Level * l){
    for (int i = 0; i < l->max_height; i++)
    {
        for (int j = 0; j < l->max_length; j++)
        {
            l->candies[i][j] = random_candy(i,j,manager);
        }
    }
}
void make_candy_drop(CandyManager * manager, Level * level);

// On suppose que le mouvement est possible
void move( Level * level, int x, int y, int dx, int dy){
    Candy origin = level->candies[x][y];
    level->candies[x][y] = level->candies[x+dx][y+dy];
    level->candies[x+dx][y+dy] = origin;
}

void check_break(Level * level){
    // La complexité de zinzin qu'on va avoir sur ça.

}

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