#include <stdio.h>
#include <stdlib.h>

#include "../header/score_manager.h"

typedef struct
{
    int nb_lignes;
    int max_caractere_par_ligne;
} DimensionsFichier;

DimensionsFichier mesurer_fichier(const char *nom_fichier)
{
    DimensionsFichier dim = {0, 0};

    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL)
    {
        perror("Erreur d'ouverture du fichier pour mesure");
        return dim;
    }

    int c;
    int longueur_courante = 0;
    int a_des_caracteres = 0;

    while ((c = fgetc(fichier)) != EOF)
    {
        a_des_caracteres = 1;

        if (c == '\n')
        {
            dim.nb_lignes++;
            if (longueur_courante > dim.max_caractere_par_ligne)
            {
                dim.max_caractere_par_ligne = longueur_courante;
            }
            longueur_courante = 0; // Reset pour la ligne suivante
        }
        else
            longueur_courante++;
    }

    if (longueur_courante > 0)
    {
        dim.nb_lignes++;
        if (longueur_courante > dim.max_caractere_par_ligne)
            dim.max_caractere_par_ligne = longueur_courante;
    }
    else if (dim.nb_lignes == 0 && a_des_caracteres)
        dim.nb_lignes = 1;

    fclose(fichier);
    return dim;
}

char **createScoreBuffer(DimensionsFichier dim)
{
    char **tab = malloc(sizeof(char *) * dim.nb_lignes);
    for (int i = 0; i < dim.nb_lignes; i++)
    {
        tab[i] = malloc(sizeof(char) * (dim.max_caractere_par_ligne + 1)); // +1 : pour le caractère sentinel
    }
    return tab;
}

void freeScoreBuffer(char **tab, DimensionsFichier dim)
{
    for (int i = 0; i < dim.nb_lignes; i++)
    {
        free(tab[i]);
    }
    free(tab);
}

char **getFileContent(ScoreManager score_manager)
{
    FILE *file = fopen(score_manager.nomFichier, "r");

    DimensionsFichier dim = mesurer_fichier(score_manager.nomFichier);
    // Chaque ligne est associé à un joueur : nomJoueur,score
    char **tab = createScoreBuffer(dim);
    char ch;
    int i = 0;
    int y = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            tab[i][y] = '\0';
            y = 0;
            i++;
        }
        else
        {
            tab[i][y] = ch;
            y++;
        }
    }
    return tab;
}

void addScoreToFichier(ScoreManager scoreManager, int score)
{
}

// Le tableau à modifier et donner les n premiers scores
void setBestScores(int *tab[], int n, char **scoreBuffer)
{
}

int getScoreFromLine(char *line)
{
    // La fonction n'est pas terminé.
    return atoi(line);
}

// Récupère les n premières lignes du fichier
void setScores(int *tab[], int n, char **scoreBuffer)
{
    for (int i = 0; i < n; i++)
    {
    }
}
