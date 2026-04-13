#ifndef SPECIALITY_H
#define SPECIALITY_H

typedef struct candy_h Candy;
typedef struct level_h Level;

struct speciality_h
{
    char symbol;
    int points;
    void (*effect)(Candy * bonbon, Level * cur_level );
};
typedef struct speciality_h Speciality;

Speciality * create_Speciality(char c, void (* effect)(Candy * bonbon, Level * cur_level ),int points);
void free_Speciality(Speciality * s);

#endif