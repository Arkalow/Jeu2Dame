#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../define.h"
#include "../../mods/Vector.h"
#include "../../mods/Pion.h"
#include "../../mods/Player.h"
#include "sdlBoard.h"
#include "../../mods/network.h"
#include "../../mods/audio.h"
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

int str_contains(char * str1, char * str2)
{
    int index = 0;
    while(str2[index] != '\0')
    {
        if(str1[0] == '\0') return -1;
        if(str2[index] == str1[0])
        {
            index++;
        }
        str1++;
    }
    return 0;
}

/**
 * Retourne un nombre aleatoire avec pour max pour valeur maximum
 */
int randomValue(int max)
{
    return (int)(rand() / (double)RAND_MAX * (max - 1));
}

/**
 * Active le ronyMode
 */
void activeRonyMode(struct Menu * menu)
{
    initAudio();
    ronyMode = 1;

    SDL_SetWindowTitle(window, "RONY MODE !!!!");
    playMusic("sounds/oui.wav", SDL_MIX_MAXVOLUME);
    loadTextures("rony");
}

/**
 * Desactive le ronyMode
 */
void desactiveRonyMode()
{
    endAudio();
    initAudio();
    playSound("sounds/pet.wav", SDL_MIX_MAXVOLUME);
}

/**
 * Update le ronyMode
 */
void updateRonyMode(struct Menu menu)
{
    menu.backgroundColor.r = randomValue(255);
    menu.backgroundColor.g = randomValue(255);
    menu.backgroundColor.b = randomValue(255);

    showSdlBackground(menu.backgroundColor);

    SDL_Rect frame; 
    for(int i = 0; i < 50; i++)
    {
        frame.x = randomValue(caseWidth * 10);
        frame.y = randomValue(caseWidth * 12 + caseWidth * 3);
        frame.h = randomValue(100);
        frame.w = frame.h,
        SDL_RenderCopy(renderer, texturePion2, NULL, &frame);
    }

    for(int i = 0; i < menu.nbItem; i++){
        struct Item_menu item;
        item = menu.items[i];

        // BrainFuckColor
        item.backgroundColor.r = randomValue(255);
        item.backgroundColor.g = randomValue(255);
        item.backgroundColor.b = randomValue(255);

        // BrainFuck position
        item.position.x += randomValue(30) - 15;
        item.position.y += randomValue(30) - 15;
        item.textPosition.x += randomValue(30) - 15;
        item.textPosition.y += randomValue(30) - 15;
        showItem(item);        
    }

    menu.textPosition.x += randomValue(60) - 60;
    menu.textPosition.y += randomValue(60) - 15;
    sdlWrite("RONY MODE !!!", menu.surface, menu.textPosition, police, menu.fontColor);
    // Renderer Update
    SDL_RenderPresent(renderer);
}

/**
 * Affiche le menu
 */
int showMenu(struct Menu menu)
{
    char * inputText; // Text saisie par l'user
    inputText = (char *)malloc(sizeof(char) * 100);
    // Affichage du background
    showSdlBackground(menu.backgroundColor);
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
    if(ronyMode == 1) activeRonyMode(&menu);
    while(1)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    return 2;
                break;
                
                case SDL_MOUSEBUTTONUP:
                    // Detection left-click
                    if(event.button.button == SDL_BUTTON_LEFT)
                    {
                        SDL_Point mousePosition = { event.button.x, event.button.y };
                        for(int i = 0; i < menu.nbItem; i++){
                            if(SDL_PointInRect(&mousePosition, &(menu.items[i].position)) == SDL_TRUE){
                                //menu.items[i].click();
                                if(ronyMode == 1)
                                {
                                    desactiveRonyMode();
                                }
                                return i;
                            }
                        }
                    }
                break;

                case SDL_KEYDOWN:

                    if(event.key.keysym.sym == SDLK_r) inputText = strcat(inputText, "r");
                    else if(event.key.keysym.sym == SDLK_o) inputText = strcat(inputText, "o");
                    else if(event.key.keysym.sym == SDLK_n) inputText = strcat(inputText, "n");
                    else if(event.key.keysym.sym == SDLK_y) inputText = strcat(inputText, "y");
                    else inputText = strcpy(inputText, "");

                    if(str_contains(inputText, "rony") == 0) activeRonyMode(&menu); 
                    
                break;
            }
        }
        if(ronyMode == 1) updateRonyMode(menu);
        SDL_Delay(80);
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
    int nbItem = 3;
    struct Item_menu * items;
    items = malloc(sizeof(struct Item_menu) * nbItem);

    SDL_Rect rect = { 
        caseWidth, // Position x
        caseWidth * 4, // Position y
        caseWidth * WIDTH - 2, // largeur
        caseWidth * 2 // hauteur
    };
    SDL_Point textPosition;

    // Item 0
    textPosition.x = rect.x + caseWidth * 2.4; textPosition.y = rect.y + caseWidth * 0.2;
    items[0] = createItem("Partie locale", rect, textPosition, 0, white, black, NULL);

    // Item 1
    rect.y += caseWidth + rect.h;
    textPosition.x = rect.x + caseWidth * 2; textPosition.y = rect.y + caseWidth * 0.2;
    items[1] = createItem("Partie en reseau", rect, textPosition, 0, white, black, NULL);


    // Item 2
    rect.y += caseWidth + rect.h;
    textPosition.x = rect.x + caseWidth * 3.8; textPosition.y = rect.y + caseWidth * 0.2;
    items[2] = createItem("Quitter", rect, textPosition, 0, black, orange, NULL);


    SDL_Point textPositionMenu = { caseWidth * 4, caseWidth};
    SDL_Point point = { 0, 0 }; // Position du menu
    menu = createMenu("Jeu2Dame", textPositionMenu, items, nbItem, point, orange, black);

    return menu;
}