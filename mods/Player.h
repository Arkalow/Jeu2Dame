/**
 * Le module Player contient la structure d'un joueur ainsi que toutes les fonctions
 * que bénéficie un joueur
 */

/**
 * Représente un joueur
 */
struct Player{
    int team;
    int score; // Nombre de pion adverse attrapé
    char * name;
};

/**
 * Créer un pion
 */
struct Player createPlayer(int team, char * name);

/**
 * Test si le pion appartient au joueur
 */
int testPion(struct Pion pion, struct Player player);