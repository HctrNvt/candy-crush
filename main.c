#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

 
#include "header/cursor.h"
#include "header/level.h"

int taille_fichier(char * filename){
    FILE * f = fopen(filename,"r");
    char carac;
    int i = 0;
    while (fscanf(f,"%c",&carac) != EOF)
    {
        i++;
    }
    fclose(f);
    return i;
}

// On suppose que la taille de level est la bonne
void getFileContent(char * fileName, char * level){
    FILE * f = fopen(fileName,"r");
    if (f == NULL) printf("Le fichier n'a pas été correctement lu.");
    int i = 0;
    int c = fgetc(f);
    while (c != EOF) {
        level[i] = (char)c;
        i++;
        c = fgetc(f);
    }
    level[i] = '\0';
    
    fclose(f);
}

void print_level(Level lvl,Cursor crsr){
    
}

int main(int argc, char const *argv[])
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(1);

    char * fileName = "test.txt";
    char * level = malloc(taille_fichier(fileName)*sizeof(char));
    getFileContent(fileName,level);

    Cursor * cursor = CursorCreate(level);

    bool running = true;
    while (running)
    {
        clear();
        attron(A_REVERSE);
        mvprintw(0,0,"         Candy Crush         ");
        attroff(A_REVERSE);
        mvprintw(2,0,"%s",level);

        refresh();

        int ch = getch();
        switch (ch)
        {
        case 'q':
            running = false;
            break;
        case KEY_RIGHT:
            moveCursor(cursor,1,0);
            break;
        case KEY_LEFT:
            moveCursor(cursor,-1,0);
            break;
        case KEY_UP:
            moveCursor(cursor, 0, -1);
            break;
        case KEY_DOWN:
            moveCursor(cursor, 0, 1);
            break;
        default:
            break;
        }
        printw("%d",cursor->x);
        printw("%d",cursor->y);
    }
    
    endwin();
    
    free(level);
    free(cursor);
    return 0;
}
