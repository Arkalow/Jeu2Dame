#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "../../define.h"
#include "../../mods/Vector.h"
#include "../../mods/Player.h"
#include "../../mods/Pion.h"
#include "../../mods/network.h"
#include "gui.h"
#include "sdlBoard.h"

/**
 * Met en lumière une case du plateau
 */
void highlight(struct Vector vector){
    SDL_Point point = convertPositionVectorToSdl(vector);
    SDL_Rect frame = { point.x, point.y, caseWidth, caseWidth };
    SDL_RenderFillRect(renderer, &frame); 
}

/**
 * Affiche un rendu console du plateau
 */
int showSdlBoard(){

    changeColor(black);

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
                        SDL_RenderCopy(renderer, rond_blue, NULL, &frame);
					}else{
						// Pion du joueur 1
                        SDL_RenderCopy(renderer, circle_blue, NULL, &frame);
					}
				}else{
                    // Joueur 2
					if(board[x][y]->type == 1){
						// Dame du joueur 2
                        SDL_RenderCopy(renderer, rond_red, NULL, &frame);
					}else{
						// Pion du joueur 2
                        SDL_RenderCopy(renderer, circle_red, NULL, &frame);
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