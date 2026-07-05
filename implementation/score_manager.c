#include <stdio.h>
#include <stdlib.h>

#include "../header/score_manager.h"

struct str
{
    int len;
    unsigned char *data;
};
typedef struct str string;

string *createString(char tab[], int n)
{
    string *str = malloc(sizeof(string));
    str->len = n;
    for (int i = 0; i < n; i++)
    {
        str->data[i] = tab[i];
    }
    return str;
}

string *cat(string s, unsigned char c)
{
    // Concaténation d'un string avec un char
    string str;
    str.len = s.len + 1;
    str.data = malloc(str.len * sizeof(unsigned char));
    for (size_t i = 0; i < str.len - 2; i++)
    {
        str.data[i] = s.data[i];
    }
    str.data[s.len] = c;
    return &str;
}
string *cat(string s1, string s2)
{
    string str;
    str.len = s1.len + s2.len;
    str.data = malloc(str.len * sizeof(unsigned char));
    for (int i = 0; i < s1.len; i++)
    {
        str.data[i] = s1.data[i];
    }
    for (int i = 0; i < s2.len; i++)
    {
        str.data[i] = s2.data[i];
    }
    return &str;
}
char *getFileContent(ScoreManager score_manager)
{
    FILE *file = fopen(score_manager.nomFichier, "r");
    
}

void addScoreToFichier(ScoreManager scoreManager, int score)
{
}

void getBestScores(int tab[], int n)
{
}

void getScores(int tab[], int n)
{
}
