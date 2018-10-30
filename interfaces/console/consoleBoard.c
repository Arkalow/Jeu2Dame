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
void showConsoleBoard(){
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