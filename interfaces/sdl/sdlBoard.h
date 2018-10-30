/**
 * Le module pion comprends toutes les fonctions pour le rendu du plateau sur 
 * l'interface graphique en SDL
 */

/**
 * Affiche un rendu console du plateau
 */
void showSdlBoard();

/**
 * Charge les textures du jeu
 * Renvoie EXIT_FAILURE en cas d'erreur et EXIT_SUCCESS en cas de succes
 */
int loadTextures();