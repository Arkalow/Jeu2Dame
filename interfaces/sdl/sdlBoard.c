#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "../../define.h"
#include "../../mods/Vector.h"
#include "../../mods/Pion.h"
#include "gui.h"
#include "sdlBoard.h"

/**
 * Affiche un rendu console du plateau
 */
void showSdlBoard(){
	printf("Affichage en mode graphique !!!\n");
    SDL_Rect frame = { 100, 100, 32, 32 };
    
    // On affiche la texture sur le renderer
    SDL_RenderCopy(renderer, texturePionPlayer1, NULL, &frame);
    frame.x = 200; frame.y = 200;
    SDL_RenderCopy(renderer, texturePionPlayer2, NULL, &frame);
}

/**
 * Charge les textures du jeu
 * Renvoie EXIT_FAILURE en cas d'erreur et EXIT_SUCCESS en cas de succes
 */
int loadTextures(){
    
    // Ajout des textures des pions du joueur 1
    texturePionPlayer1 = NULL;
    texturePionPlayer1 = loadImage("images/circle-red.bmp", renderer);
    
    if(NULL == texturePionPlayer1)
    {
        printf("Impossible de charger la texture du joueur 1");
        return EXIT_FAILURE;
    }
    

    // Ajout des textures des pions du joueur 2
    texturePionPlayer2 = NULL;
    texturePionPlayer2 = loadImage("images/circle-blue.bmp", renderer);
    
    if(NULL == texturePionPlayer2)
    {
        printf("Impossible de charger la texture du joueur 1");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}