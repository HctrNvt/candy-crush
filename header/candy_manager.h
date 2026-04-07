#ifndef CANDY_MANAGER_H
#define CANDY_MANAGER_H

typedef struct speciality_h Speciality;
typedef struct candy_h Candy;
typedef struct level_h Level;

struct candy_manager_h
{
    int colors[4];
    Speciality * specialites;
};
typedef struct candy_manager_h CandyManager;

CandyManager * create_CandyManager();
void free_CandyManager(CandyManager * manager);
Candy * random_candy(int x, int y, CandyManager * manager);
void fill_level(CandyManager * manager, Level * level);
void make_candy_drop(CandyManager * manager, Level * level);
void move_candies( Level * level, int x, int y, int dx, int dy); // dx et dy compris entre -1 et 1
void check_break(Level * level);

#endif