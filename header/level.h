#ifndef LEVEL_H
#define LEVEL_H

#include <stdbool.h>

typedef struct candy_h Candy;
typedef struct player_h Player;
typedef struct candy_manager_h CandyManager;

struct level_h
{
    char * * str; // Booléen à changer
    Candy * * candies;
    int max_height;
    int max_length;
    int max_move;
};
typedef struct level_h Level;

Level * create_level(char * str);
void free_Level(Level * l);
void update_adjacent(Level * level); // Met à jour les bonbons adjacents aux autres.
void show_level(Level * l, CandyManager * m);
void start_level(Level * l, Player * player); 
// On donne le nombre de coup qu'il faut au joueur.
bool should_end(Level * l, Player * player); // Si le niveau est terminé ou pas (objectifs complétés/ plus de coup)
void end_level(Level * l,Player * player);
// Retire le bonbon, ajoute les points au joueur, fais tomber les bonbons
void break_candy(Level * l, Player * p, int x, int y);

#endif
