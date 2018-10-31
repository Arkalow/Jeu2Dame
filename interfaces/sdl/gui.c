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
 * Gere les actions du tour quand on click sur le plateau
 */
void clickOnBoard(struct Vector clickPosition){
    if(pionStart == NULL){
        // On selectionne un pion
        printf("On selectionne le pion de depart\n");
        int resultSearchBoard = searchBoard(clickPosition, &pionStart);

        if(resultSearchBoard == 0){ // Case déjà occupée 
            printf("Aucune piece n'est selectionnee\n");
            pionStart = NULL;
        }else if(resultSearchBoard == -1){ // Case hors limite
            printf(" Case hors limite\n");
            pionStart = NULL;
        }else if(pionStart->team != currentPlayer->team){ // Le pion n'appartient pas au joueur
            printf(" Ce pion n'appartient pas au joueur\n");
            pionStart = NULL;
        }else{
            printf("Pion selectionne\n");
            comboMode = 0; // Réinitialisation du mode Combo
            pionStart->selected = 1;
        }


    }else if(pionStart != NULL && equalVector(pionStart->position, clickPosition) && comboMode == 0){
        // L'user re-click sur le pion selectionne
        // On desactive alors le pion
        printf("Desactivation du pion selectionne\n");
        pionStart->selected = 0;
        pionStart = NULL;
        comboMode = 0;
    }else{
        printf("On selectionne la destination\n");
        int resultAction = action(pionStart, clickPosition, currentPlayer);

        // L'action n'a pas aboutie
        if(resultAction == -1){
            printf(" Echec action\n");

        // L'action est une prise
        }else if(resultAction == 2){
            comboMode = 1;
            printf(" Continue action\n");

        }else{
            printf(" Action reussi\n");

            // Changement de joueur
            if(currentPlayer->team == player1.team){
                currentPlayer = &player2;
            }else{
                currentPlayer = &player1;
            }
            // Transformation du pion en dame
            if(testTranfo(*pionStart) == 1){
                printf("Tranformation !!!!\n");
                tranfoDame(pionStart);
            }
            pionStart->selected = 0;
            pionStart = NULL;
        }

        // Si le nombre de prise disponible autour du pion est 0
        // Alors ont sort de la boucle marque la fin du tour
        if(comboMode == 1 && testAllPrise(*pionStart) == 0){
            printf(" Plus de prise disponible pour se tours\n");
            pionStart->selected = 0;
            pionStart = NULL;
            comboMode = 0;
            // Changement de joueur
            if(currentPlayer->team == player1.team){
                currentPlayer = &player2;
            }else{
                currentPlayer = &player1;
            }
            return;
        }

    }
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
                if(SDL_PointInRect(&mousePosition, &SDLboard) == SDL_TRUE && gameStarted == 1){
                    struct Vector clickPosition = convertPositionSdlToVector(mousePosition);
                    showVector(clickPosition);
                    clickOnBoard(clickPosition);   
                    showSdlBoard();
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

/**
 * Boucle de jeu
 */
int game(){
    gameStarted = 1; // Flag jeu lancé
    setTestBoard();

    if(EXIT_FAILURE == showSdlBoard()){
        printf("Erreur affichage\n");
        return EXIT_FAILURE;
    }


	player2 = createPlayer(2);
	player1 = createPlayer(1);
    currentPlayer = &player1;


    SDL_Event event;

    // Boucle de jeu
	while(player1.score != NB_PION && player2.score != NB_PION)
    {
        // Lecture d'un evenement
        while(SDL_PollEvent(&event))
        {
            if(input(event) == SDL_QUIT)
                return SDL_QUIT;
        }
        SDL_Delay(30);
    }
    // Changement de joueur
    if(currentPlayer->team == player1.team){
        currentPlayer = &player2;
    }else{
        currentPlayer = &player1;
    }
	printf("Player %d a gagne !\n", currentPlayer->team);
	freeBoard();

    gameStarted = 0;
    return 0;
}


int gui()
{
    positionBoard.x = caseWidth; positionBoard.y = caseWidth;
    SDLboard.x = 0; SDLboard.y = 0; 
    SDLboard.h = caseWidth + 9 * caseWidth; SDLboard.w = caseWidth + 9 * caseWidth;
    texturePionPlayer1 = NULL; // Texture des pions du joueur 1
    texturePionPlayer2 = NULL; // Texture des pions du joueur 2
    orange.r = 255; orange.g = 127; orange.b = 40; orange.a = 255;
    black.r = 0; black.g = 0; black.b = 0; black.a = 255;
    blue.r = 0; blue.g = 0; blue.b = 255; blue.a = 255;

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

    game();
    

    statut = EXIT_SUCCESS;

Quit:

    if(NULL != renderer) SDL_DestroyRenderer(renderer);
    if(NULL != window) SDL_DestroyWindow(window);
    if(NULL != texturePionPlayer1) SDL_DestroyTexture(texturePionPlayer1);
    if(NULL != texturePionPlayer2) SDL_DestroyTexture(texturePionPlayer2);

    SDL_Quit();
    return statut;
}