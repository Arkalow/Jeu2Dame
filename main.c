/**
 * Programme principale
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>

#include "Vector.h"
#include "Pion.h"
#include "Player.h"

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
Si un pion arrive au bout de la map (chez l'adversaire) ce dernier se transforme en dame


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
 * Effectue une action 
 * move, move + prise...
 * La fonction retourne -1 en cas d'echec ex: saut au dessus de plusieurs prises
 * Sinon si le tour fait partie d'un combo on retourne 2
 * Sinon retourne 1 en cas de succès
 */
int action(struct Pion * pion, struct Vector point, struct Player * player){
	struct Vector prise;
	
	printf("Pion selectionne : \n");
	showPion(*pion);
	printf("Destination : ");
	showVector(point);

	struct Pion * end;
	
	// Test de la case destination
	int resultSearchBoard = searchBoard(point, &end);
	int resultTestPrise;
	if(resultSearchBoard == 1){ // Case déjà occupée 
		printf(" Impossible, la case de destination est deja occupee\n");
		return -1;
	}
	
	if(resultSearchBoard == -1){ // Case hors limite
		printf(" Case hors limite\n");
		return -1;
	}

	incrementMoveList(pion);

	// Test de la validite du deplacement par rapport au possibilite du pion
	if(testMove(*pion, point)){

		// S'il y une prise
		resultTestPrise = testPrise(*pion, point, &prise);

		// S'il y a une prise
		if(resultTestPrise == 1){

			printf(" Prise trouvee\n");
			board[prise.x][prise.y] = NULL;
			player->score++;
			printf(" Prise effectue\n");

			printf(" Deplacement\n");
			move(pion, point);

		}else if(resultTestPrise == -1){
			printf(" Erreur prise\n");
			return -1; // Action annulée
		}


	}else{

		decrementMoveList(pion);

		if(testMove(*pion, point)){

			printf(" Deplacement possible\n");
			move(pion, point);

		}else{
			printf(" Le pion ne permet pas ce type de deplacement\n");
			return -1;
		}
	}
	
	return 2;

}



// PROGRAMME PRINCIPALE
// -------------------------------------------------------------------------------------
int main()
{
	//setBoard();
	setTestBoard();


	struct Player player1, player2;
	struct Player * currentPlayer;
	player1 = createPlayer(1);
	player2 = createPlayer(2);

	currentPlayer = &player1;

	struct Vector start, end;
	struct Pion * pionStart;
	int resultAction;

	showBoard();
	// Boucle de jeu
	while(player1.score != NB_PION && player2.score != NB_PION){
		printf("Score : \n \tPlayer1 : %d\n\tPlayer2 : %d\n", player1.score, player2.score);
		printf("Joueur %d\n", currentPlayer->team);
		printf(" Start : \n");
		printf(" => x : ");
		scanf("%d", &start.x);
		printf(" => y : ");
		scanf("%d", &start.y);
		
		int resultSearchBoard = searchBoard(start, &pionStart);

		if(resultSearchBoard == 0){ // Case déjà occupée 
			printf("Aucune piece n'est selectionnee\n");
			continue;
		}

		if(resultSearchBoard == -1){ // Case hors limite
			printf(" Case hors limite\n");
			continue;
		}

		// Case contient un pion

		do{

			// A FAIRE : 
			// La fin du Do se fera quand il n'y a plus de prise pour continuer le combo
			// Ajouter un test de prise sur tous les possibilités de déplacement du pion selectionné


			printf(" End : \n");
			printf(" => x : ");
			scanf("%d", &end.x);
			printf(" => y : ");
			scanf("%d", &end.y);

			resultAction = action(pionStart, end, currentPlayer);

			if(resultAction == -1){
				printf(" Echec action\n");
				continue;
			}

			printf(" Action reussi\n");

			// Changement de joueur
			if(resultAction == 1){
				if(currentPlayer->team == player1.team){
					currentPlayer = &player2;
				}else{
					currentPlayer = &player1;
				}
			}

			// Transformation
			if(testTranfo(*pionStart) == 1){
				printf("Tranformation !!!!\n");
				tranfoDame(pionStart);
			}

			// Si le nombre de prise disponible autour du pion est 0
			// Alors ont sort de la boucle
			if(testAllPrise(*pionStart) == 0){
				break;
			}

			showBoard();
		}while(resultAction == 2);

	}


	
	showBoard();
	if(currentPlayer->team == player1.team){
		currentPlayer = &player2;
	}else{
		currentPlayer = &player1;
	}
	printf("Player %d a gagne !\n", currentPlayer->team);
	freeBoard();
	return 0;
}