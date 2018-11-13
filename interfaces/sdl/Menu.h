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

    SDL_Point positionStartItem;

    SDL_Color backgroundColor;
    SDL_Color fontColor;

    void (*show)(void);
};

/**
 *	Représente un item de menu
 */
struct Item_menu
{
    SDL_Rect position;
	int selected; // Indique si le pion est selectionné

    SDL_Color backgroundColor;
    SDL_Color fontColor;

    void (*click)(void); // Fonction executé au click
    //void (*select)(void); // Fonction executé au survol
};

/**
 * Créer un menu
 */
struct Menu createMenu(
    struct Item_menu * items,
    SDL_Point positionStartItem, 
    SDL_Color backgroundColor,
    SDL_Color fontColor
);

/**
 * Créer un item
 */
struct Item_menu createItem(
    SDL_Rect position,
	int selected,
    SDL_Color backgroundColor,
    SDL_Color fontColor,
    void (*click)(void)
);

void showMenu();