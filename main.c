#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
 
#include "header/cursor.h"
#include "header/level.h"
#include "header/candy_manager.h"

void level_init(){
    CandyManager * m = create_CandyManager();
    Level * l = create_level("#####\n#####\n#####");
    
    fill_level(m,l);
    
    show_level(l,m);
    
    free_CandyManager(m);
    free_Level(l);
}

int main(int argc, char const *argv[])
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(1);

    // bool running = true;
    level_init();
    getch();
    
    endwin();
    return 0;
}
