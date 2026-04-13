#include <stdlib.h>

#include "../header/candy_manager.h"
#include "../header/speciality.h"
#include "../header/candy.h"
#include "../header/level.h"

#include <ncurses.h>

// 

int SPECIALITY_N = 4;

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

CandyManager * create_CandyManager(){
    CandyManager * manager = malloc(sizeof(CandyManager));    
    manager->colors[0] = COLOR_GREEN;  
    manager->colors[1] = COLOR_YELLOW; 
    manager->colors[2] = COLOR_BLUE;   
    manager->colors[3] = COLOR_MAGENTA;

    
    manager->specialites = malloc(sizeof(Speciality)*SPECIALITY_N);
    manager->specialites[0] = * create_Speciality('0',normal_effect);
    manager->specialites[1] = * create_Speciality('=',zebra_effect);
    manager->specialites[2] = * create_Speciality('#',carre_effect); // A terminer
    manager->specialites[3] = * create_Speciality('@',disco_effect); // A terminer

    return manager;
}

void free_CandyManager(CandyManager * manager){
    if (manager == NULL) return;
    
    free(manager->specialites);
    free(manager);
}

Candy * random_candy(int x, int y, CandyManager * manager){
    int color = rand() % 4; // l'index de la couleur dans le manager
    Speciality * s = &(manager->specialites[0]);

    return create_Candy(x,y,
        color,
        NULL,NULL,NULL,NULL,
        s);
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

bool is_filled(Level * l){
    for (int i = 0; i < l->max_height; i++)
    {
        for (int j = 0; j < l->max_length; j++)
        {
            if(l->can_be_placed[i][j] && l->candies[i][j] == NULL)
                return false;
        }
    }
    return true;
}

// A TERMINER
void make_candy_drop(CandyManager * manager, Level * level){
    while (!is_filled(level))
    {
        
        // On fait apparaitre les bonbons en haut
        for (int i = 0; i < level->max_length; i++)
            if (level->can_be_placed[i][0] && level->candies[i][0] == NULL)
                    level->candies[i][0] = random_candy(i,0,manager);
        
    }
    
}; //on descends les bonbecs(#sable) et on génère des bonbons aléatoire (voir foncion random candy))

// On suppose que le mouvement est possible
void move_candies( Level * level, int x, int y, int dx, int dy){
    Candy * origin = level->candies[x][y];
    level->candies[x][y] = level->candies[x+dx][y+dy];
    level->candies[x+dx][y+dy] = origin;
}

void check_break(Level * level){
    // La complexité de zinzin qu'on va avoir sur ça.

}

