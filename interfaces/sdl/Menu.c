#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../define.h"
#include "../../mods/Vector.h"
#include "../../mods/Pion.h"
#include "../../mods/Player.h"
#include "sdlBoard.h"
#include "gui.h"
#include "Menu.h"

/**
 * Créer un menu
 */
struct Menu createMenu(
    struct Item_menu * items,
    SDL_Point positionStartItem, 
    SDL_Color backgroundColor,
    SDL_Color fontColor
){
    struct Menu menu;
    menu.items = items;
    menu.positionStartItem = positionStartItem;
    menu.backgroundColor = backgroundColor;
    menu.fontColor = fontColor;
    menu.show = showMenu;
    return menu;
}

/**
 * Créer un item
 */
struct Item_menu createItem(
    SDL_Rect position,
	int selected,
    SDL_Color backgroundColor,
    SDL_Color fontColor,
    void (*click)(void)
){
    struct Item_menu item;
    item.position = position;
    item.selected = selected;
    item.backgroundColor = backgroundColor;
    item.fontColor = fontColor;
    item.click = click;
    return item;
}


void showMenu(){
    printf("showMenu !!!");
}