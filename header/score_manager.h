
struct score_manager
{
    char *nomFichier;
    int nNomFichier;
};
typedef struct score_manager ScoreManager;

ScoreManager *createScoreManager(char *nomFichier, int nNomFichier);
void freeScoreManager(ScoreManager scoremanager);
void addScoreToFichier(ScoreManager scoreManager, int score);

void getBestScores(int tab[], int n); // Le tableau à modifier et donner les n premiers scores

void getScores(int tab[], int n); // Récupère les n premières lignes du fichier
