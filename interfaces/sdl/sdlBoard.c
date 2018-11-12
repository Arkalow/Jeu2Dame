#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "../../define.h"
#include "../../mods/Vector.h"
#include "../../mods/Player.h"
#include "../../mods/Pion.h"
#include "gui.h"
#include "sdlBoard.h"

/**
 * Met en lumière une case du plateau
 */
void highlight(struct Vector vector){
    SDL_Point point = convertPositionVectorToSdl(vector);
    printf("x : %d, y : %d\n", point.x, point.y);
    SDL_Rect frame = { point.x, point.y, caseWidth, caseWidth };
    SDL_RenderFillRect(renderer, &frame); 
}

/**
 * Affiche un rendu console du plateau
 */
int showSdlBoard(){

    changeColor(black);

	printf("Affichage en mode graphique !!!\n");
    SDL_Rect frame = { positionBoard.x, positionBoard.y, caseWidth, caseWidth };
    
    for(int y = 0; y < WIDTH; y++){
		for(int x = 0; x < WIDTH; x++){

            SDL_RenderDrawRect(renderer, &frame);
			if(board[x][y] != NULL){
                if(board[x][y]->selected == 1) {
                    changeColor(blue);
                    highlight(board[x][y]->position);
                    changeColor(black);
                }
				if(board[x][y]->team == 1){
                    // Joueur 1
					if(board[x][y]->type == 1){
						// Dame du joueur 1
                        SDL_RenderCopy(renderer, texturePionPlayer1, NULL, &frame);
					}else{
						// Pion du joueur 1
                        SDL_RenderCopy(renderer, texturePionPlayer1, NULL, &frame);
					}
				}else{
                    // Joueur 2
					if(board[x][y]->type == 1){
						// Dame du joueur 2
                        SDL_RenderCopy(renderer, texturePionPlayer2, NULL, &frame);
					}else{
						// Pion du joueur 2
                        SDL_RenderCopy(renderer, texturePionPlayer2, NULL, &frame);
					}
				}
			}else{
                // Case vide
				
			}
                frame.x += caseWidth;
		}
        frame.y += caseWidth;
        frame.x = positionBoard.x;
	}

    return EXIT_SUCCESS;
}

/**
 * Charge les textures du jeu
 * Renvoie EXIT_FAILURE en cas d'erreur et EXIT_SUCCESS en cas de succes
 */
int loadTextures()
{
    
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

/**
 * Charge les polices du jeu
 * Renvoie EXIT_FAILURE en cas d'erreur et EXIT_SUCCESS en cas de succes
 */
int loadPolices()
{
    TTF_Init();
    police = NULL;
    text = NULL; //*fond = NULL;
    pSurf = SDL_GetWindowSurface(window);
    /* Chargement de la police */
    if((police = TTF_OpenFont("./police/game_over.ttf", 62)) == NULL){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * Change la couleur du cuseur
 */
int changeColor(SDL_Color color){

    if(0 != SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

/**
 * Convertie les coordonnées graphique en positions sur la grille
 */
struct Vector convertPositionSdlToVector(SDL_Point point){
    struct Vector vector;
    vector = createPoint(
        (point.x - positionBoard.x)/caseWidth,
        (point.y - positionBoard.y)/caseWidth
    );
    return vector;
}

/**
 * Convertie les positions sur le plateau en coordonnees
 */
SDL_Point convertPositionVectorToSdl(struct Vector vector){
    SDL_Point point;
    point.x = positionBoard.x + vector.x * caseWidth;
    point.y = positionBoard.y + vector.y * caseWidth;
    return point;
}