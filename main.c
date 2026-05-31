    #include <ncurses.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <stdio.h>

    #include "header/cursor.h"
    #include "header/level.h"
    #include "header/player.h"
    #include "header/candy_manager.h"

    void move_to_input(int mv, Level * l, Cursor * c, Player * p,bool * isMovingCandy, bool * isRUNNING){
        switch (mv)
        {
            case 'a':
                *isRUNNING = false;
                break;
            case 's':
                if (*isMovingCandy && can_move(p)){
                    p->move -= 1;
                    *isMovingCandy = false;
                    move_candies(l,c->i,c->j,0,1);
                } else 
                    move_Cursor(c,0,1);
                break;
            case 'z':
                if (*isMovingCandy && can_move(p)){
                    p->move -= 1;
                    *isMovingCandy = false;
                    move_candies(l,c->i,c->j,0,-1);
                } else
                    move_Cursor(c,0,-1);
                break;
            case 'd':
                if (*isMovingCandy && can_move(p)){
                    p->move -= 1;
                    *isMovingCandy = false;
                    move_candies(l,c->i,c->j,1,0);
                } else 
                    move_Cursor(c,1,0);
                break;
            case 'q':
                if (*isMovingCandy && can_move(p)){
                    p->move -= 1;
                    *isMovingCandy = false;
                    move_candies(l,c->i,c->j,-1,0);
                } else 
                    move_Cursor(c,-1,0);
                break;
            case ' ':
                *isMovingCandy = true;
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
        bool isMovingCandy = false;
        CandyManager * m = create_CandyManager();
        char * l_str = "###################\n###################\n###################\n###################\n###################\n###################";
        Level * l = create_level(l_str,30);
        Cursor * c = create_Cursor(0,0,l->max_length,l->max_height);
        Player * p = create_Player(l);
        fill_level(m,l);

        while (running)
        {
            clear();
            show_level(l, m, c);
            refresh();
        
            int ch = getch(); // Attendre mv
            move_to_input(ch,l,c,p,
                &isMovingCandy,
                &running);
        }
        
        endwin();
        free_CandyManager(m);
        free_Level(l);
        free_Cursor(c);
        free_Player(p);
        return 0;
    }
