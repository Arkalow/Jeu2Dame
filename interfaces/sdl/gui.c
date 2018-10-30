#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../define.h"
#include "../../mods/Vector.h"
#include "../../mods/Pion.h"
#include "../../mods/Player.h"
#include "sdlBoard.h"
#include "gui.h"

/**
 * Creer une fenetre et renvoie le renderer
 * On recupere aussi l'adresse du pointeur de la fenetre
 */
SDL_Renderer * createWindow(int height, int width)
{
    /* Initialisation, création de la fenêtre et du renderer. */
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
        return NULL;
    }
    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              height, width, SDL_WINDOW_SHOWN);
    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s\n", SDL_GetError());
        return NULL;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s\n", SDL_GetError());
        return NULL;
    }

    return renderer;
}

/**
 * Load a picture and return the Texture
 */
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL; 
    SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP(path);
    if(NULL == tmp)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s\n", SDL_GetError());
        return NULL;
    }

    // Surface
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    // Libere l'espace aloué par la surface
    SDL_FreeSurface(tmp);

    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
        return NULL;
    }

    // On recupere les dimensions de l'image
    // A terme on rajoutera la taille en parametre et on redimensionnera en fonction
    //SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    
    return texture;
}

/**
 * 1. Fonction qui detecte les evenements
 * 2. Agit en fonction 
 * 3. Et retourne
 *      - Si evenement : Retourne le code de l'evenement SQL
 *      - Si pas d'evenement : Retourne 0
 *      - Erreur : -1
 */
int input(SDL_Event event)
{
   switch(event.type){

        case SDL_MOUSEBUTTONUP:
            // Detection left-click
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                // mouse position => event.button.x & event.button.y
                //printf("Click !\n");
                //printf("x = : %d\ty : %d\n", event.button.x, event.button.y);

                SDL_Point mousePosition = {event.button.x, event.button.y };
                
                // Test si le click est dans le plateau
                if(SDL_PointInRect(&mousePosition, &SDLboard) == SDL_TRUE){
                    //printf("Click sur le plateau de jeu\n");
                    showVector(convertPosition(mousePosition));          
                }

            }

            return SDL_MOUSEBUTTONUP;

        break;

        case SDL_QUIT:

            printf("Close window\n");
            return SDL_QUIT;

        break;

   }
   // Nothing
   return 0;
}

int gui()
{
    positionBoard.x = caseWidth; positionBoard.y = caseWidth;
    SDLboard.x = 0; SDLboard.y = 0; 
    SDLboard.h = caseWidth + 9 * caseWidth; SDLboard.w = caseWidth + 9 * caseWidth;
    window = NULL;
    renderer = NULL;
    texturePionPlayer1 = NULL; // Texture des pions du joueur 1
    texturePionPlayer2 = NULL; // Texture des pions du joueur 2
    orange.r = 255; orange.g = 127; orange.b = 40; orange.a = 255;
    black.r = 0; black.g = 0; black.b = 0; black.a = 255;

    SDLboard.x = positionBoard.x; SDLboard.y = positionBoard.y; // On place le plateau au bonne coordonnées

    int statut = EXIT_FAILURE;

    // Creation de la fenetre
    window = NULL;
    renderer = NULL;
    renderer = createWindow(caseWidth * 12, caseWidth * 12);
    if(renderer == NULL)
    {
        goto Quit;
    }

    loadTextures();

    setBoard();
    if(EXIT_FAILURE == showSdlBoard()){
        printf("Erreur affichage\n");
        return EXIT_FAILURE;
    }

    SDL_Event event;
    SDL_bool quit = SDL_FALSE;

    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(input(event) == SDL_QUIT)
                quit = SDL_TRUE;
        }
        SDL_Delay(30);
    }

    statut = EXIT_SUCCESS;

Quit:

    if(NULL != renderer) SDL_DestroyRenderer(renderer);
    if(NULL != window) SDL_DestroyWindow(window);
    if(NULL != texturePionPlayer1) SDL_DestroyTexture(texturePionPlayer1);
    if(NULL != texturePionPlayer2) SDL_DestroyTexture(texturePionPlayer2);

    SDL_Quit();
    return statut;
}