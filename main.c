#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

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
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    return texture;
}

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;
    SDL_Color orange = {255, 127, 40, 255};

    /* Initialisation, création de la fenêtre et du renderer. */
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
        goto Quit;
    }
    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              640, 480, SDL_WINDOW_SHOWN);
    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s\n", SDL_GetError());
        goto Quit;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s\n", SDL_GetError());
        goto Quit;
    }

    /* C’est à partir de maintenant que ça se passe. */
    if(0 != SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s\n", SDL_GetError());
        goto Quit;
    }

    if(0 != SDL_RenderClear(renderer))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s\n", SDL_GetError());
        goto Quit;
    }



    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //SDL_RenderDrawLine(renderer, 100, 100, 540, 380);



    // Ajout image
    SDL_Texture *texture = NULL;
    texture = loadImage("images/iop.bmp", renderer);
    if(NULL == texture)
    {
        goto Quit;
    }
    

    SDL_RenderCopy(renderer, texture, NULL, NULL); /* On copie tmp sur texture */
    SDL_DestroyTexture(texture);

    // Renderer Update
    SDL_RenderPresent(renderer);




    SDL_Delay(7000);

    statut = EXIT_SUCCESS;

Quit:
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}