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
    struct Item_menu * items,
    int nbItem,
    SDL_Point positionStartItem, 
    SDL_Color backgroundColor,
    SDL_Color fontColor
){
    struct Menu menu;
    menu.title = title;
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
	int selected,
    SDL_Color backgroundColor,
    SDL_Color fontColor,
    void (*click)(void)
){
    struct Item_menu item;
    item.title = title;
    item.position = position;
    item.selected = selected;
    item.backgroundColor = backgroundColor;
    item.fontColor = fontColor;
    item.click = click;
    return item;
}

/**
 * Affiche le menu
 */
int showMenu(struct Menu menu){
    printf("showMenu !!!\n");
    // Affichage du background
    changeColor(orange);
    if(0 != SDL_RenderClear(renderer))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s\n", SDL_GetError());
    }
    for(int i = 0; i < menu.nbItem; i++){
        struct Item_menu item = menu.items[i];
        printf("%d %d %d %d\n", item.position.x, item.position.y, item.position.h, item.position.w);
        changeColor(item.backgroundColor);
        SDL_RenderFillRect(renderer, &(item.position));
    }
    
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
                            menu.items[i].click();
                            return i;
                        }
                    }
                }
            break;
        }

    }
}