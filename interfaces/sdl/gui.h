/**
 * Gere la partie rendu sur l'interface graphique en SDL
 */
#define caseWidth 32

/**
 * Creer une fenetre et renvoie le renderer
 * On recupere aussi l'adresse du pointeur de la fenetre
 */
SDL_Renderer * createWindow(int height, int width, SDL_Window **window);

/**
 * Load a picture and return the Texture
 */
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer, SDL_Rect frame);

/**
 * 1. Fonction qui detecte les evenements
 * 2. Agit en fonction 
 * 3. Et retourne
 *      - Si evenement : Retourne le code de l'evenement SQL
 *      - Si pas d'evenement : Retourne 0
 *      - Erreur : -1
 */
int input(SDL_Event event);

int gui();