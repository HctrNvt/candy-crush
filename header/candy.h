#ifndef CANDY_H
#define CANDY_H

typedef struct candy_h Candy;
typedef struct speciality_h Speciality;
struct candy_h
{
    int x; int y;
    int color;
    Candy * right;
    Candy * left;
    Candy * top;
    Candy * bot;
    Speciality * s;
};

Candy * create_Candy(int x, int y, int color,
     Candy * right, Candy * left, Candy * top, Candy * bot,
    Speciality s);

void free_Candy(Candy * candy);


#endif