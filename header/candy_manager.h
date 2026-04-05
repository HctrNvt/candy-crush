#ifndef CANDY_H
#define CANDY_H

#include "speciality.h"

typedef struct candy_h Candy;

struct candy_manager
{
    int colors[4][3]; // 4 couleurs en RGB
    Speciality * specialites;
};
typedef struct candy_manager CandyManager;

CandyManager * create_CandyManager();
void free_CandyManager(CandyManager * manager);
Candy * random_candy(int x, int y, CandyManager * manager);
void fill_level(CandyManager * manager, Level * level);
void make_candy_drop(CandyManager * manager, Level * level);
void move( Level * level, int x, int y, int dx, int dy); // dx et dy compris entre -1 et 1
void check_break(Level * level);

#endif