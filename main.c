#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
 
#include "header/cursor.h"
#include "header/level.h"
#include "header/candy_manager.h"

int main(int argc, char const *argv[])
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(1);

    bool running = true;
    CandyManager * m = create_CandyManager();
    Level * l = create_level("###################\n###################\n###################\n###################\n###################\n###################");
    Cursor * c = create_Cursor(2,3,l->max_length,l->max_height);
    fill_level(m,l);

    while (running)
    {
        clear();
        show_level(l, m, c);
        refresh();
    
        int ch = getch(); // Attendre input
        switch (ch)
        {
            case 'a':
                running = false;
                break;
            case 's':
                move_Cursor(c,0,1);
                break;
            case 'z':
                move_Cursor(c,0,-1);
                break;
            case 'd':
                move_Cursor(c,1,0);
                break;
            case 'q':
                move_Cursor(c,-1,0);
                break;
            default:
                break;
        }
    }
    
    getch();
    
    endwin();
    free_CandyManager(m);
    free_Level(l);
    free_Cursor(c);
    return 0;
}
