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
    char * title,
    SDL_Point textPosition,
    struct Item_menu * items,
    int nbItem,
    SDL_Point positionStartItem, 
    SDL_Color backgroundColor,
    SDL_Color fontColor
){
    struct Menu menu;
    menu.title = title;
    menu.textPosition = textPosition;
    menu.surface = NULL;
    menu.items = items;
    menu.nbItem = nbItem;
    menu.positionStartItem = positionStartItem;
    menu.backgroundColor = backgroundColor;
    menu.fontColor = fontColor;
    return menu;
}

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
){
    struct Item_menu item;
    item.title = title;
    item.position = position;
    item.textPosition = textPosition;
    item.selected = selected;
    item.backgroundColor = backgroundColor;
    item.fontColor = fontColor;
    item.click = click;
    item.surface = NULL;
    return item;
}

/**
 * Affiche un item
 */
void showItem(struct Item_menu item){
    changeColor(item.backgroundColor);
    SDL_RenderFillRect(renderer, &(item.position));
    sdlWrite(item.title, item.surface, item.textPosition, police, item.fontColor);
}

/**
 * Affiche le menu
 */
int showMenu(struct Menu menu){

    // Affichage du background
    changeColor(menu.backgroundColor);
    if(0 != SDL_RenderClear(renderer))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s\n", SDL_GetError());
    }
    for(int i = 0; i < menu.nbItem; i++){
        showItem(menu.items[i]);        
    }
    
    changeColor(menu.backgroundColor);
    sdlWrite(menu.title, menu.surface, menu.textPosition, police, menu.fontColor);

    // Renderer Update
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while(1)
    {
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                return 1;
            break;
            
            case SDL_MOUSEBUTTONUP:
                // Detection left-click
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_Point mousePosition = {event.button.x, event.button.y };
                    for(int i = 0; i < menu.nbItem; i++){
                        if(SDL_PointInRect(&mousePosition, &(menu.items[i].position)) == SDL_TRUE){
                            //menu.items[i].click();
                            return i;
                        }
                    }
                }
            break;
        }

    }
}

/**
 * Charge le menu
 */
void freeMenu(struct Menu menu){
    free(menu.items);
}


/**
 * Charge le menu start
 */
struct Menu loadStartMenu(){
    // ***MENU***
    struct Menu menu;
    int nbItem = 2;
    struct Item_menu * items;
    items = malloc(sizeof(struct Item_menu) * nbItem);

    // Item 1
    SDL_Rect rect1 = { caseWidth, caseWidth * 4, caseWidth * WIDTH - 2, caseWidth * 4 };
    SDL_Point textPosition1 = { caseWidth * 4.5, caseWidth * 5};
    items[0] = createItem("Jouer", rect1, textPosition1, 0, white, black, NULL);

    // Item 2
    SDL_Rect rect2 = { caseWidth, caseWidth * 9, caseWidth * WIDTH - 2, caseWidth * 4};
    SDL_Point textPosition2 = { caseWidth * 4.5, caseWidth * 10};
    items[1] = createItem("Quitter", rect2, textPosition2, 0, black, orange, NULL);


    SDL_Point textPositionMenu = { caseWidth * 4, caseWidth};
    SDL_Point point = { 0, 0 }; // Position du menu
    menu = createMenu("Jeu2Dame", textPositionMenu, items, nbItem, point, orange, black);

    return menu;
}