#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#define WIDTH 10
#define HEIGHT 10

/*

On modélise la map dans un tableau 2D.
Les cases sont codés de la manière suivante : 
	- 0 : Représente une case vide
	- 100 : Représente une case occupé par un pion
	- 10 : Représente une des pièces du joueur 1
	- 20 : Représente une des pièces du joueur 2
	- 1 : Représente un pion
	- 2 : Représente une dame

Ces états s'obtiennent avec des modulos.

*/



/**
 * Affiche un rendu console du plateau
 */
void showBoard(int board[WIDTH][HEIGHT]){
	for(int y = 0; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			printf("%d\t", board[x][y]);
		}
		printf("\n");
	}
}

/**
 * Rempli le plateau
 */
void setBoard(int board[WIDTH][HEIGHT]){

	// Partie haute du plateau (Joueur 1)
	for(int y = 0; y < 4; y++){
		for(int x = 0; x < WIDTH; x++){
			if((x+y)%2 == 0){
				board[x][y] = 111;
			}else{
				board[x][y] = 0;
			}
		}
	}

	// Bande vide du milieu de plateau
	for(int y = 4; y < 6; y++){
		for(int x = 0; x < WIDTH; x++){
			board[x][y] = 0;
		}
	}

	// Partie basse du plateau (Joueur 2)
	for(int y = 6; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			if((x+y)%2 == 0){
				board[x][y] = 121;
			}else{
				board[x][y] = 0;
			}
		}
	}
}


/**
 * Programme principale
 */
int main( int argc, char *argv[ ] )
{
    int board[WIDTH][HEIGHT];
    setBoard(board);
    showBoard(board);
    return 0;
}