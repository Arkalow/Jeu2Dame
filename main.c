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
Les déplacements d'un pion sont représenté par un tableau de vecteur déplacement. Pour tester la validité
d'un déplacement on vérifie si le déplacement est inférieur à l'un des déplacement de la liste



LES PRISES
-----------------------------------------------------------------------------







*/



#define WIDTH 10 // Le plateau est carré, WIDTH représente la taille du côté

/**
 * Représente un vecteur
 * Pour un déplacement par exemple
 */
struct Vector
{
	int x;
	int y;
};

/**
 *	Représente un pion
 */
struct Pion
{
	struct Vector position;

    int team; // La team du pion
	int nbMove; // Nombre de déplacement possible
	struct Vector moveList[8]; // Les déplacements possible du pion
};

struct Pion * board[WIDTH][WIDTH]; // Plateau de jeu

/**
 * Créer un vecteur à partir de deux points
 * Peut représenter un vecteur déplacement par exemple
 */ 
struct Vector createVector(int startX, int startY, int endX, int endY){
	struct Vector vector;
	
	vector.x = endX - startX;
	vector.y = endY - startY;
	
	return vector;
}

/**
 * Affiche un vecteur
 * Pour le debug
 */
void showVector(struct Vector vector){
	printf("(%d, %d)", vector.x, vector.y);
}

/**
 * Test le vecteur move est compris dans le vecteur reference
 * C'est le cas dans un déplacement valide
 */
int testMove(struct Vector move, struct Vector reference){
	if(reference.x > 0){ // Le vecteur référence est positif sur x
		if(!(move.x > 0 && move.x < reference.x)){ // ! 0 < move.x < ref.x
			return 0; // False;
		}
	}else{
		printf("test");
		if(!(move.x < 0 && move.x > reference.x)){ //  ! ref.x < move.x < 0
			return 0; // False;
		}
	}

	if(reference.y > 0){ // Le vecteur référence est positif sur y
		if(!(move.y > 0 && move.y < reference.y)){ //  ! 0 < move.y < ref.y
			return 0; // False;
		}
	}else{
		if(!(move.y < 0 && move.y > reference.y)){ //  ! ref.y < move.y < 0
			return 0; // False;
		}
	}

	return 1; // True;
}

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
	board[x][y]->position.x = x;
	board[x][y]->position.y = y;
	board[x][y]->team = team;


	// Si le type est une dame
	// 	MAX 0 MAX
	// 	 0  P  0
	// 	MAX 0 MAX
	if(type == 1){

		board[x][y]->nbMove = 4; // Une dame a 4 déplacements possible
		board[x][y]->moveList[0] = createVector(0, 0, 10, 10); // Bas droite
		board[x][y]->moveList[1] = createVector(0, 0, -10, -10); // Haut gauche
		board[x][y]->moveList[2] = createVector(0, 0, -10, 10); // Bas gauche
		board[x][y]->moveList[3] = createVector(0, 0, 10, 10); // Haut droite

	}else{ // Le pion est un pion classique

		board[x][y]->nbMove = 4; // Un pion classique a 2 déplacements possible

		if(team == 1){
			// Si c'est un pion joueur 1
			// 	0 0 0
			// 	0 P 0
			// 	1 0 1
			board[x][y]->moveList[0] = createVector(0, 0, 10, 10); // Bas droite
			board[x][y]->moveList[2] = createVector(0, 0, -10, 10); // Bas gauche
		}else{
			// Si c'est un pion joueur 2
			// 	1 0 1
			// 	0 P 0
			// 	0 0 0
			board[x][y]->moveList[1] = createVector(0, 0, -10, -10); // Haut gauche
			board[x][y]->moveList[3] = createVector(0, 0, 10, 10); // Haut droite
		}
	}
}

/**
 * Affiche un rendu console du plateau
 */
void showBoard(){
	printf(" -----------------------------------------\n");
	printf(" |              JEU DE DAMES             |\n");
	printf(" -----------------------------------------\n");
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
 * Libère la mémoire allouée par le plateau
 */
void freeBoard(){
	for(int y = 0; y < WIDTH; y++){
		for(int x = 0; x < WIDTH; x++){
			free(board[x][y]);
		}
	}
}








// PROGRAMME PRINCIPALE
// -------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	setBoard();
	showBoard();


	if(testMove(createVector(0, 0, -1, -1), createVector(0, 0, 2, 2))){
		printf(" Deplacement possible\n");
	}else{
		printf(" Deplacement impossible\n");
	}

	board[1][1] = NULL;
	
	
	
	
	showBoard();

	freeBoard();
    return 0;
}