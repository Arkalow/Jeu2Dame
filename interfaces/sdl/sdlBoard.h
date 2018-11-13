/**
 * Le module pion comprends toutes les fonctions pour le rendu du plateau sur 
 * l'interface graphique en SDL
 */

/**
 * Met en lumière une case du plateau
 */
void highlight(struct Vector vector);

/**
 * Affiche un rendu console du plateau
 */
int showSdlBoard();

/**
 * Convertie les coordonnées graphique en positions sur la grille
 */
struct Vector convertPositionSdlToVector(SDL_Point point);

/**
 * Convertie les positions sur le plateau en coordonnees
 */
SDL_Point convertPositionVectorToSdl(struct Vector vector);