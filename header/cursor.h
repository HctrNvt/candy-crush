#ifndef CURSOR_H
#define CURSOR_H

struct cursor
{
    int i; int j;
    int max_i; int max_j;
};

typedef struct cursor Cursor;
Cursor * create_Cursor(int i, int j, int max_i, int max_j);
Cursor * free_Cursor(Cursor * c);
void move_Cursor(Cursor * cursor, int dx, int dy);
void show_Cursor(Cursor * c);

#endif