#ifndef SPECIALITY_H
#define SPECIALITY_H

typedef struct candy_h Candy;
typedef struct level_h Level;
typedef struct player_h Player;

struct speciality_h
{
    char symbol;
    int points;
    void (*effect)(Candy *bonbon, Level *cur_level, Player *player, int i, int j);
};
typedef struct speciality_h Speciality;

Speciality *create_Speciality(char c, void (*effect)(Candy *bonbon, Level *cur_level, Player *player, int i, int j), int points);
void free_Speciality(Speciality *s);

#endif