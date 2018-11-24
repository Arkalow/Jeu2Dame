/**
 * Programme principale
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#include "define.h"
#include "mods/Vector.h"
#include "mods/Pion.h"
#include "mods/Player.h"
#include "mods/network.h"
#include "interfaces/sdl/gui.h"
#include "interfaces/console/console.h"
#include "main.h"


/**
 * Effectue une action 
 * move, move + prise...
 * La fonction retourne :
 * 		- 0 : succès
 * 		- 1 : combo
 * 		- -1 : pas de prise
 * 		- -2 : hors limite
 * 		- -3 : case de destination déjà occupée
 * 		- -4 : Erreur prise (plusieurs prises sur le chemin)
 * 		- -5 : Déplacement impossible
 */
int action(struct Pion * pion, struct Vector point, struct Player * player){
	struct Vector prise;
	
	//printf("Pion selectionne : \n");
	//showPion(*pion);
	//printf("Destination : ");
	//showVector(point);

	struct Pion * end;
	
	// Test de la case destination
	int resultSearchBoard = searchBoard(point, &end);
	int resultTestPrise;
	if(resultSearchBoard == 1){ // Case déjà occupée 
		printf(" Impossible, la case de destination est deja occupee\n");
		return -3;
	}
	
	if(resultSearchBoard == -1){ // Case hors limite
		printf(" Case hors limite\n");
		return -3;
	}


	// Test de la validite du deplacement par rapport au possibilite du pion
	if(testMove(*pion, point)){

		// Test les prises s'il existe des prises sur le chemin
		resultTestPrise = testPrise(*pion, point, &prise);

		// Erreur, il y a plusieurs prises
		if(resultTestPrise == -1){
			printf(" Erreur prise\n");
			
			return -4; // Plusieurs prises
		}

		// Déplacement du pion
		printf(" Deplacement\n");
		move(pion, point);

		// Pas de prise
		if(resultTestPrise == 0){
			return 0; // move sans prise
		}

		// On est dans le cas restant, une prise est trouvée
		printf(" Prise trouvee\n");
		board[prise.x][prise.y] = NULL;
		player->score++;
		printf(" Prise effectue\n");
		return 1; // combo

	}else{
		// Test de la validite du deplacement par rapport au possibilite du pion 
		// avec une augmentation de 1 unite vecteur

		// Incrementation des moveList du pion
		incrementMoveList(pion);

		// Test de la validité du déplacement
		if(testMove(*pion, point)){

			// On test la présence de prises
			resultTestPrise = testPrise(*pion, point, &prise);

			// Plusieurs prise sur le chemin
			if(resultTestPrise == -1){
				printf(" Erreur prise\n");
				decrementMoveList(pion);
				return -4; // Action annulée
			}

			// Aucune prise sur le chemin
			if(resultTestPrise == 0){
				printf(" Deplacement impossible\n");
				decrementMoveList(pion);
				return -5; // Action annulée
			}

			// Il y a une seule prise sur le chemin
			// On déplace le pion et on supprime la prise
			printf(" Deplacement\n");
			move(pion, point);
			printf(" Prise trouvee\n");
			board[prise.x][prise.y] = NULL;
			player->score++;
			printf(" Prise effectue\n");
			decrementMoveList(pion);
			return 1;

		}else{

			// Déplacement impossible
			printf(" Le pion ne permet pas ce type de deplacement\n");
			decrementMoveList(pion);
			return -5;
		}
	}
}

// PROGRAMME PRINCIPALE
// -------------------------------------------------------------------------------------
int main(){
	struct Vector vector;
	vector = createPoint(2, 34);
	showVector("test", vector);
	printf("Vector : %s\n", vectorToString(vector));
	showVector("retest", stringToVector(vectorToString(vector)));
	gui(); // Lancement jeu en SDL2
	//console(); // Lancement du jeu en console (Operationnel)
}