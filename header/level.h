#ifndef LEVEL_H
#define LEVEL_H

#include <stdbool.h>

typedef struct candy_h Candy;
typedef struct player_h Player;

struct level_h
{
    char * * str;
    Candy * * candies;
    int max_height;
    int max_length;
    int max_move;
};
typedef struct level_h Level;

Level * create_level(char * str);
void free_Level(Level * l);
void update_adjacent(Level * level); // Met à jour les bonbons adjacents aux autres.
void show_level();
void start_level(Level * l, Player * player); 
// On donne le nombre de coup qu'il faut au joueur.
bool should_end(Player * player); // Si le niveau est terminé ou pas (objectifs complétés/ plus de coup)
void end_level(Player * player);

#endif