#ifndef CANDY_H
#define CANDY_H

typedef struct candy_h Candy;
struct candy_h
{
    int x; int y;
    int color;
    Candy * right;
    Candy * left;
    Candy * top;
    Candy * bot;
};

Candy * create_Candy(int x, int y, int color,
     Candy * right, Candy * left, Candy * top, Candy * bot);

void free_Candy(Candy * candy);


#endif