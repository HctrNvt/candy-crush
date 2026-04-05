#include "../header/level.h"
#include "../header/player.h"

#include <string.h>
#include <stdlib.h>

Level * create_level(char * str){
    Level * l = malloc(sizeof(Level));
    l->max_length = get_max_length(str);
    l->max_height = get_height(str);

    l->candies = malloc(sizeof(Candy * *)*l->max_height);
    l->str = malloc(sizeof(char * *)*l->max_height);
    for (int i = 0; i < l->max_height; i++)
    {
        l->candies[i] = malloc(sizeof(Candy *)*l->max_length);
        l->str[i] = malloc(sizeof(char * )* l->max_length);
    }

    for (int i = 0; i < l->max_height; i++)
    {
        int y = 0;
        while (str[i] != '\n') // tant qu'on est pas sur une fin de ligne
        {
            if (str[i] == '#') { // La ou les bonbons peuvent être placé.
                l->str[i] = '#';
            } else{
                l->str[i] = NULL;
            }
            y++;
        }
        // On remplit le reste de vide.
        if (y < l->max_length){
            for (int j = 0; j < l->max_length-y; j++)
            {
                str[y+j] = NULL;
            }
        }
    }
    
    return l;
}

void free_Level(Level * l){
    for (int i = 0; i < l->max_height; i++)
    {
        free(l->candies[i]);
        free(l->str[i]);
    }
    free(l->candies);
    free(l->str);
    
    free(l);
}
// Récupère la ligne la plus longue
int get_max_length(char * str){
    int len = strlen(str);
    int curr_line_len = 0;
    int max_line_len = 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '\n'){
            max_line_len = max(max_line_len, curr_line_len);
            curr_line_len = 0;
        } else {
            curr_line_len +=1;
        }
    }
    return max_line_len;
}

// Récupère la hauteur du fichier (en nombre de ligne)
int get_height(char * str){
    int len = strlen(str);
    int max_height = 1;
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '\n') max_height += 1;
    }
    return max_height;
}

int max( int a, int b ){
    if (a >= b ) return a;
    return b;
}

void show_level(){
    for (int i = 0; i < 0; i++)
    {
        /* code */
    }
    
}
void update_adjacent(Level * level){
    
}
void show_level();
void start_level(Level * l, Player * player){
    player->move = l->max_move;
} 

bool should_end(Player * player); // Si le niveau est terminé ou pas (objectifs complétés/ plus de coup)

void end_level(Player * player);