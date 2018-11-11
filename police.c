//
//* main.c
//* test4
//
//* Created by Benoit Castagnetto on 10/02/2016.
//* Copyright © 2016 Benoit Castagnetto. All rights reserved.
//
 
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

int main (int argc, char** argv)
{
 
    SDL_Window *ecran = NULL;
    SDL_Surface *texte = NULL; //*fond = NULL;
    SDL_Rect position;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    int continuer = 1;
 
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
 
    //*** ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    //*** SDL_WM_SetCaption("Gestion du texte avec SDL_ttf", NULL);
 
    ecran = SDL_CreateWindow("test", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Surface *pSurf = SDL_GetWindowSurface(ecran);
 
    //fond = IMG_Load("moraira.jpg");
 
    /* Chargement de la police */
    if((police = TTF_OpenFont("./police/game_over.ttf", 12)) == NULL){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        goto Quit;
    }
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    if((texte = TTF_RenderText_Blended(police, "Salut", couleurNoire)) == NULL){
        printf("Erreur ecriture\n");
        goto Quit;
    }
    
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
            break;
        }

        SDL_FillRect(pSurf, NULL, SDL_MapRGB(pSurf->format, 255, 255, 255));
        position.x = 0;
        position.y = 0;
        //SDL_BlitSurface(fond, NULL, pSurf, &position); /* Blit du fond */
        //position.x = 60;
        //position.y = 370;
        SDL_BlitSurface(texte, NULL, pSurf, &position); /* Blit du texte */
        SDL_UpdateWindowSurface(ecran);
    }
goto Quit;

Quit:
    TTF_CloseFont(police);
    TTF_Quit();
 
    SDL_FreeSurface(texte);
    SDL_Quit();
 
    return EXIT_SUCCESS;
}