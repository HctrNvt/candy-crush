#include "../header/level.h"
#include "../header/player.h"
#include "../header/candy_manager.h"
#include "../header/candy.h"
#include "../header/speciality.h"
#include "../header/cursor.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>

int max(int a, int b)
{
    if (a >= b)
        return a;
    return b;
}

// Hector
// La ligne la plus longue
int get_max_length(char *str)
{
    int len = strlen(str);
    int curr_line_len = 0;
    int max_line_len = 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '\n')
        {
            max_line_len = max(max_line_len, curr_line_len);
            curr_line_len = 0;
        }
        else
            curr_line_len += 1;
    }
    max_line_len = max(max_line_len, curr_line_len);
    return max_line_len;
}

// La colonne la plus longue
int get_max_height(char *str)
{
    int len = strlen(str);
    int height = 0;
    for (int i = 0; i < len; i++)
        if (str[i] == '\n')
            height += 1;

    if (len > 0 && str[len - 1] != '\n')
        height += 1;
    return height;
}

// ----

Level *create_level(char *str, int max_move)
{
    Level *l = malloc(sizeof(Level));
    l->max_move = max_move;
    l->max_length = get_max_length(str);
    l->max_height = get_max_height(str);

    l->candies = malloc(sizeof(Candy **) * l->max_height);
    if (l->candies == NULL)
    {
        free(l);
        return NULL;
    }

    l->can_be_placed = malloc(sizeof(bool *) * l->max_height);
    if (l->can_be_placed == NULL)
    {
        free(l->candies);
        free(l);
        return NULL;
    }

    for (int i = 0; i < l->max_height; i++)
    {
        l->candies[i] = malloc(sizeof(Candy *) * l->max_length);
        l->can_be_placed[i] = malloc(sizeof(bool) * l->max_length);

        for (int j = 0; j < l->max_length; j++)
        {
            l->candies[i][j] = NULL;
            l->can_be_placed[i][j] = false;
        }
    }

    int str_idx = 0;
    for (int i = 0; i < l->max_height; i++)
    {
        int j = 0;

        // Parcourir la ligne jusqu'à '\n' ou fin de string
        while (str[str_idx] != '\n' && str[str_idx] != '\0')
        {
            if (j < l->max_length)
            {
                l->can_be_placed[i][j] = (str[str_idx] == '#'); // Si != # On n'a pas le droit de placer de bonbons
            }
            j++;
            str_idx++;
        }

        // On remplit le reste de la ligne
        while (j < l->max_length)
        {
            l->can_be_placed[i][j] = false;
            j++;
        }

        if (str[str_idx] == '\n')
            str_idx++;
    }

    return l;
}

void free_Level(Level *l)
{
    for (int i = 0; i < l->max_height; i++)
    {
        for (int j = 0; j < l->max_length; j++)
        {
            free_Candy(l->candies[i][j]);
        }

        free(l->candies[i]);
        free(l->can_be_placed[i]);
    }

    free(l->candies);
    free(l->can_be_placed);

    free(l);
}

// Affichage d'une ligne de couleurs
void show_border(int largeur)
{
    for (int i = 0; i < largeur; i++)
    {
        attron(COLOR_PAIR((i % 4) + 1));
        printw("_");
        attroff(COLOR_PAIR((i % 4) + 1));
    }
    printw("\n");
}

// Interface au dessus du niveau
void show_interface(Level *l, Player *p)
{
    int largeur = l->max_length;
    char titre[] = "BONBONS ECRASES";
    int marge = (l->max_length - strlen(titre)) / 2;

    show_border(largeur);

    for (int i = 0; i < marge; i++)
        printw(" ");
    printw("%s", titre);
    printw("\n");

    printw(" %d/%d | %d¤", p->move, l->max_move, p->score);

    printw("\n");

    show_border(largeur);
}

// Affichage du niveau en entier (interface & bonbons)
void show_level(Level *l, CandyManager *m, Cursor *c, Player *p)
{
    clear();
    show_interface(l, p);

    for (int i = 0; i < l->max_height; i++)
    {
        for (int j = 0; j < l->max_length; j++)
        {
            bool is_cursor = (c->i == i && c->j == j);
            char symbol;
            int color_pair;

            if (l->candies[i][j] == NULL) // On affiche le symbole "vide"
            {
                color_pair = 0;
                symbol = '/';
            }
            else
            {
                color_pair = l->candies[i][j]->color + 1;
                symbol = l->candies[i][j]->s->symbol;
            }

            if (is_cursor)
                symbol = '+';

            attron(COLOR_PAIR(color_pair));
            printw("%c", symbol);
            attroff(COLOR_PAIR(color_pair));
        }
        printw("\n");
    }
    refresh();
}

void break_candy(Level *l, Player *p, int i, int j)
{
    if (l->candies[i][j] == NULL)
        return;
    Candy *candy = l->candies[i][j];
    l->candies[i][j] = NULL;

    p->score += candy->s->points;

    candy->s->effect(candy, l, p, i, j); // Applique l'effet du bonbon détruit.
    free_Candy(candy);
}

void start_level(Level *l, Player *player)
{
    player->move = l->max_move;
}

bool should_end(Level *l, Player *player)
{
    return player->move <= 0;
}

void show_end(Player *p)
{
    clear();
    show_border(35);

    printw("\n\n\n\n     Vous avez gagnez !\n     Vous avez : %d points !\n\n\n", p->score);

    show_border(35);
}

void end_level(Level *l, Player *player)
{
    show_end(player);
}