/**
 *	Représente un pion
 */
struct Pion
{
	struct Vector position;

    int team; // La team du pion
	int nbMove; // Nombre de déplacement possible
	struct Vector moveList[8]; // Les déplacements possible du pion
};
#define WIDTH 10 // Le plateau est carré, WIDTH représente la taille du côté du plateau
struct Pion * board[WIDTH][WIDTH]; // Plateau de jeu

/**
 * Créer un pion sur le plateau au coordonnées (x, y)
 * Le nom de la team est le numéro du joueur
 * Le paramètre type est le type de pion :
 * 		- Pion classique : 0
 * 		- Dame : 1
 * Ces deux types pions ont des déplacements différents
 */
void createPion(int x, int y, int team, int type);

/**
 * Affiche un pion dans la console
 * Pour les debug
 */
void showPion(struct Pion pion);