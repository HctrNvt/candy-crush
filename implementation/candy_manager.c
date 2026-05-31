#include <stdlib.h>

#include "../header/candy_manager.h"
#include "../header/speciality.h"
#include "../header/candy.h"
#include "../header/level.h"

#include <ncurses.h>

int SPECIALITY_N = 4;

void zebra_effect(Candy * candy, Level * level){
    // TODO Elimine une ligne horizontale
}

void disco_effect(Candy * candy, Level * level){
    // TODO Elimine tous les bonbons de la même couleur
}

void carre_effect(Candy * candy, Level * level){
    // TODO // Elimine tous les bonbons autour
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

    return create_Candy(x,y,color,s);
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

void remplis_colonne(int debut_ligne, int colonne , Level * l, CandyManager * manager){
    for (int k = debut_ligne; k < l->max_height; k++)
    {
        l->candies[colonne][k] = random_candy(colonne,k,manager);
    }
}

// A TERMINER
// On descends les bonbecs(#sable) et on génère des bonbons aléatoire (voir foncion random candy))
// Il faut commencer par le bas
void make_candy_drop(CandyManager * manager, Level * level) {
    // On parcourt la matrice de bonbons et dès qu'on trouve un trou on fait descendre d'un étage le bonbon au dessus s'il existe sinon on prend celui encore plus haut.
    // UTILISER : move pour déplacer les bonbons, permettra de check moins de possibilités.
    for (int i = level->max_height; i == 0; i--)
    {
        for (int j = level->max_height; j == 0; j--)
        {
            if (level->candies[i][j] == NULL){
                int y = i -1;
                while (y != 0 && level->candies[y][j] != NULL)
                {
                    y--;
                }
                if (y == 0 && level->candies[y][j] == NULL) remplis_colonne(i,j,level,manager);
                else {
                    move_candies(level,y,j,i-y,0);
                }
            }   
        }
    }
}

void move_candies(Level *level, int x, int y, int dx, int dy) {
    // Vérification des limites et des pointeurs nuls
    if (x+dx < 0 || y+dy < 0 || x+dx >= level->max_length || y+dy >= level->max_height)
        return;

    Candy *origin = level->candies[y][x];
    Candy *target = level->candies[y+dy][x+dx];

    level->candies[y][x] = target;
    level->candies[y+dy][x+dx] = origin;

    if (target != NULL){
        target->x = x;
        target->y = y;
    }
    if (origin != NULL) {
        origin->x = x+dx;
        origin->y = y+dy;
    }
}

// POUR MAHAUT

// Casse la ligne depuis start_i inclu et fais n destruction en allant à DROITE
void break_line_from(int start_i, int start_j, int n, Level *level, CandyManager *manager, Player *player) {
    for (int i = 0; i < n; i++)
        break_candy(level, player, start_i + i, start_j);
}
// Casse la colonne depuis start_j et fais n destruction en allant vers le BAS
void break_col_from(int start_i, int start_j, int n, Level *level, CandyManager *manager, Player *player) {
    for (int j = 0; j < n; j++)
        break_candy(level, player, start_i, start_j + j);
}

// ALLEZ MAHAUT !!!!!!!
void check_break(Level * level, CandyManager * manager, Player * player){

}

