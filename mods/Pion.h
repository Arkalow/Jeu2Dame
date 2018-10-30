/**
 * Le module pion comprends la structure pion ainsi que toutes les fonctions qui agissent 
 * sur un pion.
 */ 

/**
 *	Représente un pion
 */
struct Pion
{
	struct Vector position;

    int team; // La team du pion
	int nbMove; // Nombre de déplacement possible
	int type; // type de pion
	struct Vector moveList[8]; // Les déplacements possible du pion

	int selected; // Indique si le pion est selectionné
};

#define NB_PION 2 // Nombre de pion par joueur 

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
 * Test si le pion est à la bonne position pour se transformer en dame
 * Renvoi 1 si Oui sinon renvoi 0;
 */
int testTranfo(struct Pion pion);

/**
 * Transforme un pion en dame
 * On change tout simplement son type et sa moveList
 */
void tranfoDame(struct Pion * pion);

/**
 * Affiche un pion dans la console
 * Pour les debug
 */
void showPion(struct Pion pion);

/**
 * Libère la mémoire allouée par le plateau
 */
void freeBoard();

/**
 * Test si un pion peut atteindre la case c d'après la liste de ses déplacements possible
 */
int testMove(struct Pion pion, struct Vector c);

/**
 * Déplace un pion sur le plateau
 */
void move(struct Pion * pion, struct Vector end);

/**
 * Test si pendant avec le vecteur deplacement, le pion rencontrera une piece
 * La fonction retourne :
 * 		1 : Si une piece adverse est trouvée 
 * 		0 : Si aucune piece n'est trouvée
 * 		-1 : Si une piece de la même team est trouvée ou plus d'une piece est trouvé
 * 
 * Le principe est simple, on parcourt la trajectoire lineaire avec un pas de vecteur unité
 * 
 */
int testPrise(struct Pion pion, struct Vector end, struct Vector * prise);

/**
 * Test pour tous les déplacement possible du pion si il existe au moins 1 prise
 */ 
int testAllPrise(struct Pion pion);

/**
 * Récupère l'adresse d'un pion dans le plateau
 * Si les coordonées sont valide => retourne 1 et met l'adresse du pion dans pion
 * Sinon => retourne -1
 */
int searchBoard(struct Vector point, struct Pion ** pion);

/**
 * Incremente la liste des deplacement du pion de une unite vecteur
 */
void incrementMoveList(struct Pion * pion);

/**
 * Decrement la liste des deplacement du pion de une unite vecteur
 */
void decrementMoveList(struct Pion * pion);


/**
 * Rempli le plateau
 */
void setBoard();

/**
 * Rempli le plateau pour les tests
 */
void setTestBoard();