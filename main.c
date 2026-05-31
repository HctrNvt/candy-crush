    #include <ncurses.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <stdio.h>

    #include "header/cursor.h"
    #include "header/level.h"
    #include "header/player.h"
    #include "header/candy_manager.h"

    void move_to_input(int mv, Level * level, Cursor * cursor, Player * player,bool * isMovingCandy, bool * isRUNNING){
        switch (mv)
        {
            case 'a':
                *isRUNNING = false;
                break;
            case 's':
                if (*isMovingCandy && can_move_candy(player)){
                    player->move -= 1;
                    *isMovingCandy = false;
                    move_candies(level,cursor->i,cursor->j,0,1);
                } else 
                    move_Cursor(cursor,0,1);
                break;
            case 'z':
                if (*isMovingCandy && can_move_candy(player)){
                    player->move -= 1;
                    *isMovingCandy = false;
                    move_candies(level,cursor->i,cursor->j,0,-1);
                } else
                    move_Cursor(cursor,0,-1);
                break;
            case 'd':
                if (*isMovingCandy && can_move_candy(player)){
                    player->move -= 1;
                    *isMovingCandy = false;
                    move_candies(level,cursor->i,cursor->j,1,0);
                } else 
                    move_Cursor(cursor,1,0);
                break;
            case 'q':
                if (*isMovingCandy && can_move_candy(player)){
                    player->move -= 1;
                    *isMovingCandy = false;
                    move_candies(level,cursor->i,cursor->j,-1,0);
                } else 
                    move_Cursor(cursor,-1,0);
                break;
            case ' ':
                *isMovingCandy = true;
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
        bool isMovingCandy = false;
        CandyManager * manager = create_CandyManager();
        char * level_str = "###################\n###################\n###################\n###################\n###################\n###################";

        Level * level = create_level(level_str,34);
        Cursor * cursor = create_Cursor(0,0,level->max_length,level->max_height);
        Player * player = create_Player(level);

        fill_level(manager,level);

        start_color(); // Active les couleurs
        for (int i = 0; i < 4; i++)
            init_pair(i+1,COLOR_BLACK,manager->colors[i]); // Ne pas utiliser i = 0 : réserver pour le terminal...

        while (running)
        {
            clear();
            show_level(level, manager, cursor);
            refresh();
        
            int ch = getch(); // Attendre mv
            move_to_input(ch,level,cursor,player,
                &isMovingCandy,
                &running);
        }
        
        endwin();
        free_CandyManager(manager);
        free_Level(level);
        free_Cursor(cursor);
        free_Player(player);
        return 0;
    }
