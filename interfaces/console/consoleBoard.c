#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../../define.h"
#include "../../mods/Vector.h"
#include "../../mods/Pion.h"
#include "consoleBoard.h"

/**
 * Affiche un rendu console du plateau
 */
void showBoard(){
	printf("   -----------------------------------------\n");
	printf("   |              JEU DE DAMES             |\n");
	printf("   -----------------------------------------\n\n");
	printf("     0   1   2   3   4   5   6   7   8   9  \n");
	printf("   -----------------------------------------\n");
	for(int y = 0; y < WIDTH; y++){
		printf(" %d", y);
		for(int x = 0; x < WIDTH; x++){
			printf(" | ");
			if(board[x][y] != NULL){
				if(board[x][y]->team == 1){
					if(board[x][y]->type == 1){
						printf(RED"D"WHITE);
					}else{
						printf(RED"P"WHITE);
					}
				}else{
					if(board[x][y]->type == 1){
						printf(BLUE"D"WHITE);
					}else{
						printf(BLUE"P"WHITE);
					}
				}
			}else{
				printf(" ");
			}
		}
		printf(" |\n");
		printf("   -----------------------------------------");
		printf("\n");
	}
		printf("\n");
		printf("\n");
}

/**
 * Rempli le plateau
 */
void setBoard(){

	// Partie haute du plateau (Joueur 1)
	for(int y = 0; y < 4; y++){
		for(int x = 0; x < WIDTH; x++){
			if((x+y)%2 == 0){
				createPion(x, y, 1, 0);
			}else{
				board[x][y] = NULL;
			}
		}
	}

	// Bande vide du milieu de plateau
	for(int y = 4; y < 6; y++){
		for(int x = 0; x < WIDTH; x++){
			board[x][y] = NULL;
		}
	}

	// Partie basse du plateau (Joueur 2)
	for(int y = 6; y < WIDTH; y++){
		for(int x = 0; x < WIDTH; x++){
			if((x+y)%2 == 0){
				createPion(x, y, 2, 0);
			}else{
				board[x][y] = NULL;
			}
		}
	}
}

/**
 * Rempli le plateau pour les tests
 */
void setTestBoard(){

	for(int y = 0; y < WIDTH; y++){
		for(int x = 0; x < WIDTH; x++){
			board[x][y] = NULL;
		}
	}

	// Team 1
	createPion(0, 0, 1, 0);
	createPion(3, 0, 1, 0);

	// Team 2
	createPion(1, 1, 2, 0);
	createPion(3, 3, 2, 0);
}