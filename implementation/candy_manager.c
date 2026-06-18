#include <stdlib.h>

#include "../header/candy_manager.h"
#include "../header/speciality.h"
#include "../header/candy.h"
#include "../header/level.h"
#include "../header/player.h"

#include <ncurses.h>

int SPECIALITY_N = 4;

// Fait par Julien
// Différents effets des bonbons spéciaux
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
    player->move += 3;
    for (int x = -1; x < 2; x++)
    {
        for (int y = -1; y < 2; y++)
        {
            if (i + x >= 0 && i + x < level->max_height &&
                j + y >= 0 && j + y < level->max_length)
            {
                break_candy(level, player, i + x, j + y);
            }
        }
    }
}

void normal_effect(Candy *candy, Level *level, Player *player, int i, int j)
{
    // A laisser vide
}

// ---

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
    manager->specialites[2] = *create_Speciality('#', carre_effect, 800);
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
//Fait par Hector et Mahaut
void remplis_colonne(int debut_ligne, int colonne, Level *l, CandyManager *manager)
{
    for (int k = debut_ligne; k >= 0; k--) // En remontant
    {
        l->candies[k][colonne] = random_candy(k, colonne, manager);
    }
}
//Fait par Hector et Mahaut
void make_candy_drop(CandyManager *manager, Level *level, Cursor *cursor, Player *player)
{
    for (int i = level->max_height - 1; i >= 0; i--)
    {
        for (int j = level->max_length - 1; j >= 0; j--)
        {
            if (level->candies[i][j] == NULL) // On fait tomber les bonbons
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
    // On vérifie si le déplacement n'est pas hors-map
    if (i + di < 0 || j + dj < 0 ||
        i + di >= level->max_height || j + dj >= level->max_length)
        return;
    
    // Echange du bonbon sélectionné avec le bonbon dans la direction souhaité
    Candy *origin = level->candies[i][j]; 
    Candy *target = level->candies[i + di][j + dj];

    level->candies[i][j] = target;
    level->candies[i + di][j + dj] = origin;

    show_level(level, manager, cursor, player);
}
// Hector et Mahaut
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

// Compte le nombre de couleur consécutive avec di,dj le déplacement fais à chaque itération
int compte_consecutive(Level *level, int i, int j, int di, int dj, int color)
{
    int count = 0;

    while (i + di * count < level->max_height &&
           j + dj * count < level->max_length &&
           level->candies[i + di * count][j + dj * count] != NULL &&
           level->candies[i + di * count][j + dj * count]->color == color)
        count++;
    return count;
}

// Hector et Mahaut
// On suppose que les deux matrices sont de même taille 
bool est_pareil(Candy ***candies1, Candy ***candies2, int maxi, int maxj)
{
    for (int i = 0; i < maxi; i++)
    {
        for (int j = 0; j < maxj; j++)
        {
            Candy *a = candies1[i][j];
            Candy *b = candies2[i][j];
            if (a->color != b->color)
                return false;
        }
    }
    return true;
}

// Nouvelle matrice qui n'a plus de lien avec l'anciene (Hector)
Candy ***copie(Candy ***candies, int maxi, int maxj)
{
    Candy ***candie_copie = malloc(sizeof(Candy **) * maxi);
    for (int i = 0; i < maxi; i++)
    {
        candie_copie[i] = malloc(sizeof(Candy *) * maxj);
        for (int j = 0; j < maxj; j++)
        {
            if (candies[i][j] != NULL)
                candie_copie[i][j] = create_Candy(candies[i][j]->color,
                                                  candies[i][j]->s);
        }
    }
    return candie_copie;
}

void free_candies(Candy ***candies, int maxi, int maxj)
{
    for (int i = 0; i < maxi; i++)
    {
        for (int j = 0; j < maxj; j++)
        {
            if (candies[i][j] != NULL)
                free_Candy(candies[i][j]);
        }
        free(candies[i]);
    }
    free(candies);
}


// Mahaut & Hector (& Julien)
void check_break(Level *level, CandyManager *manager, Player *player, Cursor *cursor)
{
    int motif_vert;
    int motif_horiz;
    Candy ***candies1 = copie(level->candies, level->max_height, level->max_length);
    for (int i = 0; i < level->max_height; i++)
    {
        for (int j = 0; j < level->max_length; j++)
        {
            Candy *candy_ij = level->candies[i][j];
            if (candy_ij == NULL)
                break;
            int color = candy_ij->color;
            
            motif_horiz = compte_consecutive(level, i, j, 0, 1, color);
            motif_vert = compte_consecutive(level, i, j, 1, 0, color);

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
    make_candy_drop(manager, level, cursor, player);
    if (!est_pareil(candies1, level->candies,
                    level->max_height, level->max_length))
    {
        free_candies(candies1, level->max_height, level->max_length);
        check_break(level, manager, player, cursor);
    }
}
