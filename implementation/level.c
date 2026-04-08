#include "../header/level.h"
#include "../header/player.h"
#include "../header/candy_manager.h"
#include "../header/candy.h"

#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

int max( int a, int b ){
    if (a >= b ) return a;
    return b;
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


// ----

Level * create_level(char * str){
    Level * l = malloc(sizeof(Level));
    l->max_length = get_max_length(str);
    l->max_height = get_height(str);
    l->candies = malloc(sizeof(Candy * *) * l->max_height);
    l->str = malloc(sizeof(char * ) * l->max_height);
    
    for (int i = 0; i < l->max_height; i++) {
        l->candies[i] = malloc(sizeof(Candy *) * l->max_length);
        l->str[i] = malloc(sizeof(char) * l->max_length);
    }
    
    int str_idx = 0;  // Index dans la string d'entrée
    
    for (int i = 0; i < l->max_height; i++) {
        int y = 0;
        
        // Parcourir la ligne jusqu'à '\n' ou fin de string
        while (str[str_idx] != '\n' && str[str_idx] != '\0') {
            if (str[str_idx] == '#') {
                l->str[i][y] = '#';
            } else {
                l->str[i][y] = ' ';  // Utilise ' ' au lieu de NULL
            }
            y++;
            str_idx++;
        }
        
        while (y < l->max_length) {
            l->str[i][y] = ' ';
            y++;
        }
        
        if (str[str_idx] == '\n') {
            str_idx++;
        }
    }
       
    return l;
}

void free_Level(Level * l){
    for (int i = 0; i < l->max_height; i++)
    {
        for (int y = 0; y < l->max_length; y++)
        {
            free_Candy(&l->candies[i][y]);
        }
        
        free(l->candies[i]);
        free(l->str[i]);
    }
    free(l->candies);
    free(l->str);
    
    free(l);
}

void show_level(Level * l,CandyManager * m){
    // Affichage avec ncurses.
    start_color();
    for (int i = 0; i < 4; i++)
        init_pair(i,COLOR_BLACK,m->colors[i]);
    
    attron(COLOR_PAIR(0));
    printw("Tout ça en vrai ?");

}
void update_adjacent(Level * level){
    
}

void break_candy(Level * l, Player * p, int x, int y){
    
}

void start_level(Level * l, Player * player){
    player->move = l->max_move;
} 

bool should_end(Level * l, Player * player){
    return player->move <= 0; // Check si les points sont passés aussi
}

void end_level(Level * l, Player * player){

    // Qu'est ce qu'on peut faire de plus ?

    free_Level(l);
}
