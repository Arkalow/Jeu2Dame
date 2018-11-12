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

/**
 * Fonction qui ecrit un texte a l'ecran
 * string est la valeur à afficher
 * font est la police du texte (à importer au prealable)
 * color du texte
 * position du texte
 */
SDL_Surface * write(char * string, SDL_Surface * text, TTF_Font * font, SDL_Color color, SDL_Rect position, SDL_Surface *pSurf){
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    if((text = TTF_RenderText_Blended(font, string, color)) == NULL){
        printf("Erreur ecriture\n");
        return NULL;
    }
    SDL_BlitSurface(text, NULL, pSurf, &position); /* Blit du texte */
    return text;
}

int main (int argc, char** argv)
{
 
    SDL_Window *ecran = NULL;
    SDL_Surface *texte = NULL; //*fond = NULL;
    SDL_Rect position;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {255, 255, 255, 255};
    int continuer = 1;
 
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
 
    //*** ecran = ccSDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    //*** SDL_WM_SetCaption("Gestion du texte avec SDL_ttf", NULL);
 
    ecran = SDL_CreateWindow("test", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Surface *pSurf = SDL_GetWindowSurface(ecran);
 
    //fond = IMG_Load("moraira.jpg");
 
    /* Chargement de la police */
    if((police = TTF_OpenFont("./police/game_over.ttf", 62)) == NULL){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        goto Quit;
    }

    position.x = 0;
    position.y = 0;

    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    if((texte = write("Wait...", texte, police, couleurNoire, position, pSurf)) == NULL){
        printf("Erreur ecriture\n");
        goto Quit;
    }
    
    SDL_UpdateWindowSurface(ecran);
    SDL_Delay(3000);




    position.x = 100;
    position.y = 100;

    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    if((texte = write("Ok c'est bon", texte, police, couleurNoire, position, pSurf)) == NULL){
        printf("Erreur ecriture\n");
        goto Quit;
    }
    
    SDL_UpdateWindowSurface(ecran);
    SDL_Delay(3000);



goto Quit;

Quit:
    TTF_CloseFont(police);
    TTF_Quit();
 
    SDL_FreeSurface(texte);
    SDL_Quit();
 
    return EXIT_SUCCESS;
}