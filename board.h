
struct Pion * board[WIDTH][WIDTH]; // Plateau de jeu

/**
 * Affiche un rendu console du plateau
 */
void showBoard();

/**
 * Rempli le plateau
 */
void setBoard();

/**
 * Libère la mémoire allouée par le plateau
 */
void freeBoard();