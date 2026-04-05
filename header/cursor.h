#ifndef CURSOR_H
#define CURSOR_H

struct cursor
{
    int i; int j;
    int max_i; int max_j;
};

typedef struct cursor Cursor;
Cursor * cursorCreate(char * level);
void moveCursor(Cursor * cursor, int dx, int dy);

#endif