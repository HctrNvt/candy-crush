#ifndef CANDY_H
#define CANDY_H

typedef struct speciality_h Speciality;
typedef struct candy_h Candy;
struct candy_h
{
    int color;
    Speciality *s;
};

Candy *create_Candy(int color, Speciality *s);

void free_Candy(Candy *candy);

#endif