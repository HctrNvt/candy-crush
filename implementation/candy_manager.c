#include <stdlib.h>

#include "../header/candy_manager.h"
#include "../header/speciality.h"
#include "../header/candy.h"
#include "../header/level.h"

#include <ncurses.h>

int SPECIALITY_N = 4;

void zebra_effect(Candy *candy, Level *level, Player *player, int i, int j)
{
    for (int n = 0; n < level->max_length; n++)
    {
        break_candy(level, player, i, n);
    }
}

void disco_effect(Candy *candy, Level *level, Player *player, int i, int j)
{
    int color = candy->color;
    for (int x = 0; x < level->max_height; x++)
    {
        for (int y = 0; y < level->max_length; y++)
        {
            if (level->candies[x][y] != NULL &&
                level->candies[x][y]->color == color)
                break_candy(level, player, x, y);
        }
    }
}

void carre_effect(Candy *candy, Level *level, Player *player, int i, int j)
{
    // TODO
}

void normal_effect(Candy *candy, Level *level, Player *player, int i, int j)
{
    // A laisser vide
}

CandyManager *create_CandyManager()
{
    CandyManager *manager = malloc(sizeof(CandyManager));
    manager->colors[0] = COLOR_GREEN;
    manager->colors[1] = COLOR_YELLOW;
    manager->colors[2] = COLOR_BLUE;
    manager->colors[3] = COLOR_MAGENTA;

    manager->specialites = malloc(sizeof(Speciality) * SPECIALITY_N);
    manager->specialites[0] = *create_Speciality('0', normal_effect, 100);
    manager->specialites[1] = *create_Speciality('=', zebra_effect, 400);
    manager->specialites[2] = *create_Speciality('#', carre_effect, 800); // A terminer
    manager->specialites[3] = *create_Speciality('@', disco_effect, 600);

    return manager;
}

void free_CandyManager(CandyManager *manager)
{
    if (manager == NULL)
        return;

    free(manager->specialites);
    free(manager);
}

Candy *random_candy(int i, int j, CandyManager *manager)
{
    int color = rand() % 4; // l'index couleur dans le manager
    Speciality *s = &(manager->specialites[0]);

    return create_Candy(color, s);
}

// Remplace si bonbon existe déjà
void fill_level(CandyManager *manager, Level *l)
{
    for (int i = 0; i < l->max_height; i++)
    {
        for (int j = 0; j < l->max_length; j++)
        {
            l->candies[i][j] = random_candy(i, j, manager);
        }
    }
}

bool is_filled(Level *l)
{
    for (int i = 0; i < l->max_height; i++)
    {
        for (int j = 0; j < l->max_length; j++)
        {
            if (l->can_be_placed[i][j] && l->candies[i][j] == NULL)
                return false;
        }
    }
    return true;
}

void remplis_colonne(int debut_ligne, int colonne, Level *l, CandyManager *manager)
{
    for (int k = debut_ligne; k >= 0; k--) // En remontant
    {
        l->candies[k][colonne] = random_candy(k, colonne, manager);
    }
}

// On parcourt la matrice de bonbons et dès qu'on trouve un trou on fait descendre d'un étage le bonbon au dessus s'il existe sinon on prend celui encore plus haut.
// UTILISER : move pour déplacer les bonbons, permettra de check moins de possibilités.

void make_candy_drop(CandyManager *manager, Level *level, Cursor *cursor, Player *player)
{
    for (int i = level->max_height - 1; i >= 0; i--)
    {
        for (int j = level->max_length - 1; j >= 0; j--)
        {
            if (level->candies[i][j] == NULL)
            {
                int k = i - 1;
                while (k >= 0 && level->candies[k][j] == NULL)
                {
                    k--;
                }
                if (k < 0)
                    remplis_colonne(i, j, level, manager);
                else
                    move_candies(level, k, j, i - k, 0, manager, cursor, player);
            }
        }
    }
    show_level(level, manager, cursor, player);
}

void move_candies(Level *level, int i, int j, int di, int dj, CandyManager *manager, Cursor *cursor, Player *player)
{
    // Vérification des limites et des pointeurs nuls
    if (i + di < 0 || j + dj < 0 ||
        i + di >= level->max_height || j + dj >= level->max_length)
        return;

    Candy *origin = level->candies[i][j];
    Candy *target = level->candies[i + di][j + dj];

    level->candies[i][j] = target;
    level->candies[i + di][j + dj] = origin;

    show_level(level, manager, cursor, player);
}

void break_line_from(int start_i, int start_j, int n, Level *level, CandyManager *manager, Player *player)
{
    for (int j = 0; j < n; j++)
        if (level->candies[start_i][start_j + j] != NULL)
            break_candy(level, player, start_i, start_j + j);
}

void break_col_from(int start_i, int start_j, int n, Level *level, CandyManager *manager, Player *player)
{
    for (int i = 0; i < n; i++)
        if (level->candies[start_i + i][start_j] != NULL)
            break_candy(level, player, start_i + i, start_j);
}

void set_candy(int i, int j, Speciality *s, CandyManager *manager, Level *level, int color)
{
    Candy *bonbon = create_Candy(color, s);
    level->candies[i][j] = bonbon;
}

void check_break(Level *level, CandyManager *manager, Player *player)
{
    int motif_vert;
    int motif_horiz;
    for (int i = 0; i < level->max_height; i++)
    {
        for (int j = 0; j < level->max_length; j++)
        {
            Candy *candy_ij = level->candies[i][j];
            if (candy_ij == NULL)
                break;

            motif_vert = 0;
            motif_horiz = 0;

            int a = 0;
            while (j + a < level->max_length &&
                   level->candies[i][j + a] != NULL &&
                   candy_ij != NULL &&
                   candy_ij->color == level->candies[i][j + a]->color)
            {
                motif_horiz++;
                a++;
            }

            a = 0;
            while (i + a < level->max_height &&
                   level->candies[i + a][j] != NULL &&
                   candy_ij != NULL &&
                   candy_ij->color == level->candies[i + a][j]->color)
            {
                motif_vert++;
                a++;
            }
            int color = candy_ij->color;
            if (motif_vert >= 5)
            {
                break_col_from(i, j, motif_vert, level, manager, player);
                set_candy(i, j, &manager->specialites[3], manager, level, color);
            }
            else if (motif_horiz >= 5)
            {
                break_line_from(i, j, motif_horiz, level, manager, player);
                set_candy(i, j, &manager->specialites[3], manager, level, color);
            }
            else if (motif_vert >= 4)
            {
                break_col_from(i, j, motif_vert, level, manager, player);
                set_candy(i, j, &manager->specialites[1], manager, level, color);
            }
            else if (motif_horiz >= 4)
            {
                break_line_from(i, j, motif_horiz, level, manager, player);
                set_candy(i, j, &manager->specialites[1], manager, level, color);
            }
            else if ((motif_vert == 3) && (motif_horiz == 3))
            {
                break_line_from(i, j, 3, level, manager, player);
                break_col_from(i, j, 3, level, manager, player);
                set_candy(i, j, &manager->specialites[2], manager, level, color);
            }
            else if (motif_vert == 3)
            {
                break_col_from(i, j, 3, level, manager, player);
            }
            else if (motif_horiz == 3)
            {
                break_line_from(i, j, 3, level, manager, player);
            }
        }
    }
}
