#ifndef CANDY_H
#define CANDY_H

struct candy_h
{
    int x; int y;
    int r; int g; int b;
    candy_h * right;
    candy_h * left;
    candy_h * top;
    candy_h * bot;
};
typedef struct candy_h Candy;

Candy * create_Candy(int x, int y, int r, int g, int b,
     Candy * right, Candy * left, Candy * top, Candy * bot);

void free_Candy(Candy * candy);


#endif