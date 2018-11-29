/**
 * Gere la les menus dans la SDL
 */

/**
 *	Représente un menu
 */
struct Menu
{
    struct Item_menu * items;
    int nbItem;
    char * title;
    SDL_Surface *surface; // Surface pour afficher le title
    SDL_Point textPosition; // Position du title sur le menu

    SDL_Point positionStartItem;

    SDL_Color backgroundColor;
    SDL_Color fontColor;
};

/**
 *	Représente un item de menu
 */
struct Item_menu
{
    SDL_Rect position;
	int selected; // Indique si le pion est selectionné
    char * title;
    SDL_Surface *surface; // Surface pour afficher le title
    SDL_Point textPosition;

    SDL_Color backgroundColor;
    SDL_Color fontColor;

    void (*click)(void); // Fonction executé au click
    //void (*select)(void); // Fonction executé au survol
};

/**
 * Créer un menu
 */
struct Menu createMenu(
    char * title,
    SDL_Point textPosition,
    struct Item_menu * items,
    int nbItem,
    SDL_Point positionStartItem, 
    SDL_Color backgroundColor,
    SDL_Color fontColor
);

/**
 * Créer un item
 */
struct Item_menu createItem(
    char * title,
    SDL_Rect position,
    SDL_Point textPosition,
	int selected,
    SDL_Color backgroundColor,
    SDL_Color fontColor,
    void (*click)(void)
);

/**
 * Affiche un item
 */
void showItem(struct Item_menu item);

/**
 * Retourne un nombre aleatoire avec pour max pour valeur maximum
 */
int randomValue(int max);

/**
 * Active le ronyMode
 */
void activeRonyMode(struct Menu * menu);

/**
 * Update le ronyMode
 */
void updateRonyMode(struct Menu menu);

/**
 * Desactive le ronyMode
 */
void desactiveRonyMode();

/**
 * Affiche le menu
 */
int showMenu(struct Menu menu);


/**
 * Charge le menu start
 */
struct Menu loadStartMenu();

/**
 * Charge le menu
 */
void freeMenu(struct Menu menu);
