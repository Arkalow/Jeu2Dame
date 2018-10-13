#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

/*

LE PLATEAU
-----------------------------------------------------------------------------
On modélise la map dans un tableau 2D. Chaque case du tableau est un pointeur de Pion
Si le pointeur est NULL il n'y a pas de pion sur cette case.

LES PIONS
-----------------------------------------------------------------------------
Les pions sont des structures représentant un pion en générale. On différenti les pions en
de leurs tableau de déplacement, leurs team (numéro du joueur) et leur coordonnées sur le plateau. 
Le tableau de déplacement est le nombre de déplacement possible 
pour un pion dans toutes les directions.



LES DEPLACEMENTS
-----------------------------------------------------------------------------




LES PRISES
-----------------------------------------------------------------------------







*/



#define WIDTH 10 // Le plateau est carré, WIDTH représente la taille du côté

/**
 *	Représente un pion
 */
struct Pion
{
	int x; // Position sur x
	int y; // Position sur y

    int team; // La team du pion
	int moveList[8]; // Les déplacement possible du pion
};

struct Pion * board[WIDTH][WIDTH]; // Plateau de jeu

/**
 * Créer un pion sur le plateau au coordonnées (x, y)
 * Le nom de la team est le numéro du joueur
 * Le paramètre type est le type de pion :
 * 		- Pion classique : 0
 * 		- Dame : 1
 * Ces deux types pions ont des déplacements différents
 */
void createPion(int x, int y, int team, int type){
	board[x][y] = malloc(sizeof(struct Pion));
	board[x][y]->x = x;
	board[x][y]->y = y;
	board[x][y]->team = team;

	// Si le type est une dame
	// 	MAX  MAX MAX
	// 	MAX   P  MAX
	// 	MAX  MAX MAX
	if(type == 1){

		board[x][y]->moveList[0] = WIDTH;
		board[x][y]->moveList[1] = WIDTH;
		board[x][y]->moveList[2] = WIDTH;
		board[x][y]->moveList[3] = WIDTH;
		board[x][y]->moveList[4] = WIDTH;
		board[x][y]->moveList[5] = WIDTH;
		board[x][y]->moveList[6] = WIDTH;
		board[x][y]->moveList[7] = WIDTH;

	}else{ // Le pion est un pion classique

		if(team == 1){
			// Si c'est un pion joueur 1
			// 	0 0 0
			// 	0 P 0
			// 	1 0 1
			board[x][y]->moveList[0] = 0;
			board[x][y]->moveList[1] = 0;
			board[x][y]->moveList[2] = 0;
			board[x][y]->moveList[3] = 0;
			board[x][y]->moveList[4] = 0;
			board[x][y]->moveList[5] = 1;
			board[x][y]->moveList[6] = 0;
			board[x][y]->moveList[7] = 1;
		}else{
			// Si c'est un pion joueur 2
			// 	1 0 1
			// 	0 P 0
			// 	0 0 0
			board[x][y]->moveList[0] = 1;
			board[x][y]->moveList[1] = 0;
			board[x][y]->moveList[2] = 1;
			board[x][y]->moveList[3] = 0;
			board[x][y]->moveList[4] = 0;
			board[x][y]->moveList[5] = 0;
			board[x][y]->moveList[6] = 0;
			board[x][y]->moveList[7] = 0;
		}
	}
}

/**
 * Affiche un rendu console du plateau
 */
void showBoard(){
	printf(" -----------------------------------------");
	printf("\n");
	for(int y = 0; y < WIDTH; y++){
		for(int x = 0; x < WIDTH; x++){
			printf(" | ");
			if(board[x][y] != NULL){
				printf("%d", board[x][y]->team);
			}else{
				printf(" ");
			}
		}
		printf(" |\n");
		printf(" -----------------------------------------");
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








// PROGRAMME PRINCIPALE
// -------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	setBoard();
	showBoard();

    return 0;
}