#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>

#include "Vector.h"
#include "Pion.h"
#include "board.h"

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
Les déplacements d'un pion sont représenté par un tableau de vecteur déplacement. 
Pour tester la validité d'un déplacement on vérifie si le vecteur déplacement est compris à l'interieur de l'un des
vecteurs deplacements de la moveList attachée au pion.


LES PRISES
-----------------------------------------------------------------------------
Une prise s'efectue quand le pion se déplace au dessus d'un seul pion adverse. 
Les conditons sont : 
	- La prise doit être de seulement 1 piont
	- La prise doit se faire par une trajectoire lineaire
	- Un pion ne peut pas passer au dessus d'un autre pion (même dans le cas d'un déplacement)
	- Pendant une prise, le pion augmente sa porté de 1
	- La case destination doit être libre


LES ACTIONS
-----------------------------------------------------------------------------
Un action est l'enchainement d'un déplacement et ou une prise la fonction action va mettre en relation les tests
de déplacement ainsi que les tests de prises pour effectuer les déplacements et les prises
Une action de déroule en plusieurs étapes : 

	- On commence par parcourir la trajectoire demandé pour déterminer si les prises sont correctes.
	- Ensuite on augmente la porté du pion pour cela on augmente tout les vecteurs deplacement du pion de 
		1 unite vecteur. 
	- Ensuite on effectue un déplacement classique (avec la porté augmenter)

	- A la fin du tour, il ne faut pas oublier de remettre les vecteurs déplacement à leurs valeurs initiales.


TOURS DE JEU
-----------------------------------------------------------------------------
Le jeu se déroule en tour par tour, les deux joueurs jouent chaqu'un leur tour.
Quand un joueur effectue une prise, il peut rejouer pour faire des combos 





*/




/**
 * Test si un pion peut atteindre la case c d'après la liste de ses déplacements possible
 */
int testMove(struct Pion pion, struct Vector c){
	struct Vector move;
	move = subVector(c, pion.position);

	// On parcourt tous les déplacements possible du pion
	for(int i = 0; i < pion.nbMove; i++){
		if(testVector(move, pion.moveList[i])){
			return 1; // True 
		}
	}
	return 0;
}

/**
 * Déplace un pion sur le plateau
 */
void move(struct Pion pion, struct Vector end){
	struct Vector start; start = pion.position;

	board[end.x][end.y] = board[start.x][start.y];
	board[start.x][start.y] = NULL;
}


/**
 * Test si pendant avec le vecteur deplacement, le pion rencontrera une piece
 * La fonction retourne :
 * 		1 : Si une piece adverse est trouvée 
 * 		0 : Si aucune piece n'est trouvée
 * 		-1 : Si une piece de la même team est trouvée ou plus d'une piece est trouvé
 * 
 * Le principe est simple, on parcourt la trajectoire lineaire avec un pas de vecteur unité
 * 
 */
int testPrise(struct Pion pion, struct Vector end, struct Vector * prise){
	int nbPrise = 0; // Nombre de pion trouvé sur le trajet
	struct Vector unit = unitVector(subVector(end, pion.position)); // Vecteur unité
	struct Vector start; start = pion.position; // Position de départ (position du pion)
	
	// Parcourt de la trajectoire
	while(start.x != end.x || start.y != end.y){
		start.x += unit.x; start.y += unit.y; // On incrémente le vecteur d'une unite
		if(board[start.x][start.y] != NULL){ // Si on tombe sur un pion
			if(board[start.x][start.y]->team == pion.team) { return -1; } // On ne traverse pas un de ses pions
			nbPrise++;
			*prise = start; // Pion trouvé
		}
	}

	if(nbPrise == 1){ // Une prise trouvée
		return 1;
	}else if(nbPrise == 0){ // Aucune prise trouvé
		return 0;
	}else{ // Erreur plus d'une prise trouvées
		return -1;
	}
}



/**
 * Effectu une action 
 * move, move + prise...
 * La fonction retourne -1 en cas d'echec ex: saut au dessus de plusieurs prises
 * Sinon retourne 1 en cas de succès
 */
int action(struct Pion pion, struct Vector point){
	struct Vector prise;
	int flagPrise = 0;
	
	showPion(pion);
	showVector(point);

	// Test de la case destination
	if(board[point.x][point.y] == NULL){
		switch(testPrise(pion, point, &prise)){
			case 1 : 
				printf(" Prise trouvee\n");
				flagPrise = 1;

				// On parcourt tous les déplacements possible du pion
				for(int i = 0; i < pion.nbMove; i++){
					
					// On increment le vecteur de 1 unite
					pion.moveList[i] = addVector(pion.moveList[i], unitVector(pion.moveList[i])); 
					
				}

			break;

			case -1 : 

				printf(" Erreur prise\n");
				return -1; // Action annulée

			break;

		}

		// Test de la validite du deplacement par rapport au possibilite du pion
		if(testMove(pion, point)){
			printf(" Deplacement possible\n");
			move(pion, point);
		}else{
			printf(" Le pion ne permet pas ce type de deplacement\n");
		}

		if(flagPrise){

			// On parcourt tous les déplacements possible du pion
			for(int i = 0; i < pion.nbMove; i++){
				// On decrement le vecteur de 1 unite
				pion.moveList[i] = subVector(pion.moveList[i], unitVector(pion.moveList[i])); 
			}

			board[prise.x][prise.y] = NULL;
			printf(" Prise effectue\n");

		}

		return 1;

	}else{
		printf(" Impossible, la case de destination est deja occupee\n");
		return -1;
	}
}








// PROGRAMME PRINCIPALE
// -------------------------------------------------------------------------------------
int main()
{
	setBoard();


	

	struct Vector point; point = createPoint(2, 2); // Point de destination

	board[1][1]->team = 2; // On ajoute une prise
	board[point.x][point.y] = NULL; // On vide la case destination
	showBoard();

	if(action(*board[0][0], point)){
		printf(" Action reussi\n");
	}else{
		printf(" Echec action\n");
	}

	showBoard();

	freeBoard();
    return 0;
}