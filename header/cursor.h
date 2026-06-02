#ifndef CURSOR_H
#define CURSOR_H

struct cursor_h
{
    int i;
    int j;
    int max_i; // ce i ne peut pas être atteint
    int max_j; // ce j ne peut pas être atteint
};
typedef struct cursor_h Cursor;

Cursor *create_Cursor(int i, int j, int max_i, int max_j);
void free_Cursor(Cursor *c);
void move_Cursor(Cursor *cursor, int dx, int dy);

#endif