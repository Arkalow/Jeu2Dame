/**
 * Gere la partie rendu sur l'interface graphique en SDL
 */
#define caseWidth 32
SDL_Point positionBoard;
SDL_Rect SDLboard;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *rond_blue; // Texture pion 
SDL_Texture *rond_red; // Texture pion 
SDL_Texture *circle_blue; // Texture pion 
SDL_Texture *circle_red; // Texture pion 

struct Player player1;
struct Player player2;
int network; // Flag mode reseau
int gameStarted; // Flag jeu start 
struct Player * currentPlayer; // Joueur en cours
struct Pion * pionStart; // Pion selectionné
int comboMode; // Mode Combo

SDL_Color orange; // Couleur orange
SDL_Color black; // Couleur noire
SDL_Color blue; // Couleur bleu
SDL_Color white; // Couleur Blanc

TTF_Font *police;
SDL_Surface *text;
SDL_Surface *pSurf;
SDL_Point positionText;
char * infoMessage;

// Pour la partie network
struct Data thread_param;
int tour;
pthread_t thread;

/**
 * Creer une fenetre et renvoie le renderer
 * On recupere aussi l'adresse du pointeur de la fenetre
 */
SDL_Renderer * createWindow(int height, int width);

/**
 * Load a picture and return the Texture
 */
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer);

/**
 * Charge les textures du jeu
 * Renvoie EXIT_FAILURE en cas d'erreur et EXIT_SUCCESS en cas de succes
 */
int loadTextures();

/**
 * Charge les polices du jeu
 * Renvoie EXIT_FAILURE en cas d'erreur et EXIT_SUCCESS en cas de succes
 */
int loadPolices();

/**
 * Change la couleur du cuseur
 */
int changeColor(SDL_Color color);

/**
 * Fonction qui ecrit un texte a l'ecran
 * string est la valeur à afficher
 * font est la police du texte (à importer au prealable)
 * color du texte
 * position du texte
 */
SDL_Surface * sdlWrite(char * string, SDL_Surface * text,  SDL_Point position, TTF_Font * font, SDL_Color color);

/**
 * Affiche le font d'ecran
 */
int showSdlBackground();

/**
 * Affiche le joueur en cours
 */
void showSdlPlayer();

/**
 * Gere les actions du tour quand on click sur le plateau
 * La fonction renvoie :
 *      - -1 : erreur
 *      - 0 : fin combo
 *      - 1 : selection d'un pion
 *      - 2 : combo en cours
 *      - 3 : fin deplacement
 *      - 4 : Deselection pion
 */
int clickOnBoard(struct Vector clickPosition);

/**
 * 1. Fonction qui detecte les evenements
 * 2. Agit en fonction 
 * 3. Et retourne
 *      - Si evenement : Retourne le code de l'evenement SQL
 *      - Si pas d'evenement : Retourne 0
 *      - Erreur : -1
 */
int input(SDL_Event event);

/**
 * Boucle de jeu
 */
int game();

int gui();
