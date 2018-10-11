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
int board[WIDTH][HEIGHT]; // Plateau

/**
 *	Représente une case du plateau
 */
struct Case
{
    int x;
    int y;
    int value;
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
void showCase(struct Case c){
	printf("Case[%d][%d] => %d\n", c.x, c.y, c.value);
}

/**
 * Rempli le plateau
 */
void setBoard(int board[WIDTH][HEIGHT]){

	// Partie haute du plateau (Joueur 1)
	for(int y = 0; y < 4; y++){
		for(int x = 0; x < WIDTH; x++){
			if((x+y)%2 == 0){
				board[x][y] = 11;
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
				board[x][y] = 21;
			}else{
				board[x][y] = 0;
			}
		}
	}
}

/**
 * Retourne une case contenant les coordonnées ainsi que la valeur du tableau
 */
struct Case searchCase(int x, int y){
	struct Case c;
	c.x = x;
	c.y = y;
	c.value = board[x][y];
	return c;
}

/**
 * Retourne le numero de la team de la case
 * Joueur 1 : 1
 * Joueur 2 : 2
 * Case vide : 0
 */
int whatTheTeam(struct Case c){
	return c.value % 10;
}

/**
 * Test la validité du déplacement
 */
short testMove(struct Case start, struct Case end){
	int sens; // sens de calcul par rapport au joueur

	if(whatTheTeam(start) == 1)
		sens = -1;
	else
		sens = 1;

	if((end.x - start.x == -1) || (end.x - start.x == 1) && (end.y - start.y == sens))
		return 1;
	else
		return 0;
}

/**
 * Déplace un pion
 */
short move(struct Case start, struct Case end){
	board[end.x][end.y] = start.value;
	board[start.x][start.y] = 0;
}








// PROGRAMME PRINCIPALE
// -------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    setBoard(board);
    board[2][8] = 0;
    showBoard(board);
    struct Case start, end;
    start = searchCase(1, 9);
    end = searchCase(2, 8);
    if(testMove(start, end)){
		if(whatTheTeam(end) == 0){
			printf("Deplacement OK\n");
			move(start, end);
		}else{
			printf("Impossibe de se deplacer sur une case non vide\n");
		}
	}else{
		printf("Erreur\n");
	}
	printf("\n");
	showBoard(board);

    return 0;
}