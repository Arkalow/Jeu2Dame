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
    //SDL_RenderCopy(renderer, texturePionPlayer1, NULL, &frame);
}