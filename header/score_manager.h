
struct score_manager
{
    char *nomFichier;
    int nNomFichier;
};
typedef struct score_manager ScoreManager;

ScoreManager *createScoreManager(char *nomFichier, int nNomFichier);
void freeScoreManager(ScoreManager scoremanager);
void addScoreToFichier(ScoreManager scoreManager, int score);

void setBestScores(int *tab[], int n, char **scoreBuffer); // Le tableau à modifier et donner les n premiers scores

void setScores(int *tab[], int n, char **scoreBuffer); // Récupère les n premières lignes du fichier
