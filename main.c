#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

/*

LE PLATEAU
-----------------------------------------------------------------------------
On modélise la map dans un tableau 2D.
Les cases sont codés de la manière suivante : 
	- 0 : Représente une case vide
	- 10 : Représente une des pièces du joueur 1
	- 20 : Représente une des pièces du joueur 2
	- 1 : Représente un pion
	- 2 : Représente une dame
Ces états s'obtiennent avec des modulos.




LES CASES
-----------------------------------------------------------------------------
La structure Case représente une case du plateau. Elle contient les coordonnées
x et y ainsi que la valueeur de la case






LES DEPLACEMENTS
-----------------------------------------------------------------------------
Un déplacement s'effectu de la manière suivante : 
	- On test si les cases départ et d'arrivé sont valueide
	- On test si le pion a le droit d'effectuer ce déplacement
	- On test si si la case d'arrivé est libre
Dans le cas contraire le déplacement est soit invalueide ou soit c'est une prise



LES PRISES
-----------------------------------------------------------------------------







*/



#define WIDTH 10 // Largeur du plateau
#define HEIGHT 10 // Hauteur du plateau

/**
 *	Représente un pion
 */
struct Pion
{
	int x; // Position sur x
	int y; // Position sur y

    int team; // La team du pion
	int moveList[]; // Les déplacement possible du pion
};

struct Pion * board[WIDTH][HEIGHT]; // Plateau

/**
 * Affiche un rendu console du plateau
 */
void showBoard(){
	for(int y = 0; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			if(board[x][y] != NULL){
				printf("%d\t", board[x][y]->team);
			}else{
				printf("\t");
			}
		}
		printf("\n");
	}
}

/**
 * Rempli le plateau
 */
void setBoard(){

	// Partie haute du plateau (Joueur 1)
	for(int y = 0; y < 4; y++){
		for(int x = 0; x < WIDTH; x++){
			if((x+y)%2 == 0){
				board[x][y]->x = x;
				board[x][y]->y = y;
				board[x][y]->team = 1;
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
	for(int y = 6; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			if((x+y)%2 == 0){
				board[x][y]->x = x;
				board[x][y]->y = y;
				board[x][y]->team = 2;
			}else{
				board[x][y] = NULL;
			}
		}
	}
}








// PROGRAMME PRINCIPALE
// -------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	setBoard();
	showBoard();

    return 0;
}