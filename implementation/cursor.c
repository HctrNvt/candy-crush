#include "../header/cursor.h"
#include "../header/level.h"
#include <stdlib.h>

Cursor *create_Cursor(int i, int j, int max_i, int max_j)
{
    Cursor *cursor = malloc(sizeof(Cursor));
    cursor->i = i;
    cursor->j = j;
    cursor->max_i = max_i;
    cursor->max_j = max_j;
    return cursor;
}

void free_Cursor(Cursor *c)
{
    free(c);
}

bool est_entre(int x, int a, int b)
{
    return x >= a && x <= b;
}

void move_Cursor(Cursor *cursor, int dx, int dy)
{
    if (est_entre(cursor->i + dy, 0, cursor->max_i - 1))
        cursor->i += dy;
    if (est_entre(cursor->j + dx, 0, cursor->max_j - 1))
        cursor->j += dx;
}