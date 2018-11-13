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
    SDL_Surface *surface;
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
 * Affiche le menu
 */
int showMenu(struct Menu menu);