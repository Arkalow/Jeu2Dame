#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#define WIDTH 10
#define HEIGHT 10
int board[WIDTH][HEIGHT];
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
 *	Représente une case du plateau
 */
struct Case
{
    int x;
    int y;
    int val;
};

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
 * Affiche une case
 */
void showCase(Case c){
	printf("Case[%d][%d] => %d\n", c.x, c.y, c.val);
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
 * Retourne une case contenant les coordonnées ainsi que la valeur du tableau
 */
Case searchCase(int x, int y){
	Case c;
	c.x = x;
	c.y = y;
	c.val = board[x][y];
	return c;
}

/**
 * Retourne le numero de la team de la case
 * Joueur 1 : 1
 * Joueur 2 : 2
 * Case vide : 0
 */
int whatTheTeam(Case c){
	return c.val % 10;
}

/**
 * Test la validité du déplacement
 */
bool testMove(Case start, Case end){
	int sens; // sens de calcul par rapport au joueur

	if(whatTheTeam(start) == 1)
		sens = -1;
	else
		sens = 1;

	if((end.x - start.x == sens) && (end.y - start.y == sens))
		return true;
	else
		return false;
}

/**
 * Programme principale
 */
int main( int argc, char *argv[ ] )
{

    setBoard(board);
    showBoard(board);
    //showCase(searchCase(0, 6));

	if(testMove(searchCase(0, 0), searchCase(1, 1)))
		printf("Deplacement OK\n");
	else
		printf("Erreur\n");


    return 0;
}