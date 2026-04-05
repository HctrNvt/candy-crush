#ifndef LEVEL_H
#define LEVEL_H

#include <stdbool.h>

typedef struct player_h Player;
typedef struct candy_h Candy;

struct level_h
{
    Candy candies[30][30];
    int max_move;
};
typedef struct level_h Level;

Level create_level(char * str);
void show_level();
void start_level(Player player); 
// On donne le nombre de coup qu'il faut au joueur.
bool should_end(Player player); // Si le niveau est terminé ou pas (objectifs complétés/ plus de coup)
void end_level(Player player);


#endif