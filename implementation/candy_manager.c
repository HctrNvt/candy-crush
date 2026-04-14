#include <stdlib.h>

#include "../header/candy_manager.h"
#include "../header/speciality.h"
#include "../header/candy.h"
#include "../header/level.h"

#include <ncurses.h>

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
    // A laisser vide
}

CandyManager * create_CandyManager(){
    CandyManager * manager = malloc(sizeof(CandyManager));    
    manager->colors[0] = COLOR_GREEN;  
    manager->colors[1] = COLOR_YELLOW; 
    manager->colors[2] = COLOR_BLUE;   
    manager->colors[3] = COLOR_MAGENTA;

    
    manager->specialites = malloc(sizeof(Speciality)*SPECIALITY_N);
    manager->specialites[0] = * create_Speciality('0',normal_effect,100);
    manager->specialites[1] = * create_Speciality('=',zebra_effect,300); // A terminer
    manager->specialites[2] = * create_Speciality('#',carre_effect,300); // A terminer
    manager->specialites[3] = * create_Speciality('@',disco_effect,1000); // A terminer

    return manager;
}

void free_CandyManager(CandyManager * manager){
    if (manager == NULL) return;

    free(manager->specialites);
    free(manager);
}

Candy * random_candy(int x, int y, CandyManager * manager){
    int color = rand() % 4; // l'index couleur dans le manager
    Speciality * s = &(manager->specialites[0]);

    return create_Candy(x,y,
        color,
        NULL,NULL,NULL,NULL,
        s);
}

// Remplace si bonbon existe déjà
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
// On descends les bonbecs(#sable) et on génère des bonbons aléatoire (voir foncion random candy))
void make_candy_drop(CandyManager * manager, Level * level){
    while (!is_filled(level))
    {
        // On parcourt la matrice de bonbons et dès qu'on trouve un trou on fait descendre d'un étage le bonbon au dessus s'il existe sinon on prend celui encore plus haut.
        // UTILISER : move pour déplacer les bonbons, permettra de check moins de possibilités.
        
        // On fait apparaitre les bonbons en haut
        for (int i = 0; i < level->max_length; i++)
            if (level->can_be_placed[i][0] && level->candies[i][0] == NULL)
                    level->candies[i][0] = random_candy(i,0,manager);
    }
    
}; 

void move_candies(Level *level, int x, int y, int dx, int dy) {
    // Vérification des limites et des pointeurs nuls
    if (x+dx < 0 || y+dy < 0 || x+dx >= level->max_length || y+dy >= level->max_height)
        return;

    Candy *origin = level->candies[x][y];
    Candy *target = level->candies[x+dx][y+dy];

    level->candies[x][y] = target;
    level->candies[x+dx][y+dy] = origin;

    if (target != NULL){
        target->x = x;
        target->y = y;
    }
    if (origin != NULL) {
        origin->x = x+dx;
        origin->y = y+dy;
    }
}

// A modifier prendre en compte le mouvement qui a été fait (x,y) des deux bonbons échangés 
// Faire la vérification uniquement à partir de cet endroit la car ça réduit toute les possibilités.
void check_break(Level * level){

}

