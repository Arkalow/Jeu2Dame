/**
 * Le module pion comprends toutes les fonctions pour le rendu du plateau sur 
 * l'interface graphique en SDL
 */

/**
 * Affiche un rendu console du plateau
 */
int showSdlBoard();

/**
 * Charge les textures du jeu
 * Renvoie EXIT_FAILURE en cas d'erreur et EXIT_SUCCESS en cas de succes
 */
int loadTextures();

/**
 * Change la couleur du cuseur
 */
int changeColor(SDL_Color color);

/**
 * Convertie les coordonnées graphique en positions sur la grille
 */
struct Vector convertPosition(SDL_Point point);