#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "header/cursor.h"
#include "header/level.h"
#include "header/player.h"
#include "header/candy_manager.h"

void move_to_input(int mv, Level * l,Cursor * c,Player * p){
    switch (mv)
    {
        case 's':
            if (can_move(p)){
                p->move -= 1;
                move_candies(l,c->i,c->j,0,1);
            }
            break;
        case 'z':
            if (can_move(p)){
                p->move -= 1;
                move_candies(l,c->i,c->j,0,-1);
            }
            break;
        case 'd':
            if (can_move(p)){
                p->move -= 1;
                move_candies(l,c->i,c->j,1,0);
            }
            break;
        case 'q':
            if (can_move(p)){
                p->move -= 1;
                move_candies(l,c->i,c->j,-1,0);
            }
            break;
        default:
            break;
    }
}

int main(int argc, char const *argv[]) {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(1);

    bool running = true;
    CandyManager * m = create_CandyManager();
    char * l_str = "###################\n###################\n###################\n###################\n###################\n###################";
    Level * l = create_level(l_str,30);
    Cursor * c = create_Cursor(2,3,l->max_length,l->max_height);
    Player * p = create_Player(l);
    fill_level(m,l);

    while (running)
    {
        clear();
        show_level(l, m, c);
        refresh();
    
        int ch = getch(); // Attendre mv
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
            case ' ':
                int mv = getch();
                move_to_input(mv,l,c,p);
                break;
            default:
                break;
        }
    }
    
    endwin();
    free_CandyManager(m);
    free_Level(l);
    free_Cursor(c);
    free_Player(p);
    return 0;
}
