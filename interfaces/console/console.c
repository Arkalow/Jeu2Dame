#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../../define.h"
#include "../../mods/Vector.h"
#include "../../mods/Pion.h"
#include "../../mods/Player.h"
#include "consoleBoard.h"
#include "console.h"

/**
 * Effectue une action 
 * move, move + prise...
 * La fonction retourne -1 en cas d'echec ex: saut au dessus de plusieurs prises
 * Sinon si le tour fait partie d'un combo on retourne 2
 * Sinon retourne 1 en cas de succès
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
		return -1;
	}
	
	if(resultSearchBoard == -1){ // Case hors limite
		printf(" Case hors limite\n");
		return -1;
	}


	// Test de la validite du deplacement par rapport au possibilite du pion
	if(testMove(*pion, point)){

		// Test les prises s'il existe des prises sur le chemin
		resultTestPrise = testPrise(*pion, point, &prise);

		// Erreur, il y a plusieurs prises
		if(resultTestPrise == -1){
			printf(" Erreur prise\n");
			
			return -1; // Action annulée
		}

		// Déplacement du pion
		printf(" Deplacement\n");
		move(pion, point);

		// Pas de prise
		if(resultTestPrise == 0){
			return 1;
		}

		// On est dans le cas restant, un prise est trouvée
		printf(" Prise trouvee\n");
		board[prise.x][prise.y] = NULL;
		player->score++;
		printf(" Prise effectue\n");
		return 2;

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
				return -1; // Action annulée
			}

			// Aucune prise sur le chemin
			if(resultTestPrise == 0){
				printf(" Deplacement impossible\n");
				decrementMoveList(pion);
				return -1; // Action annulée
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
			return 2;

		}else{

			// Déplacement impossible
			printf(" Le pion ne permet pas ce type de deplacement\n");
			decrementMoveList(pion);
			return -1;
		}
	}
}

int console()
{
	setBoard();
	//setTestBoard();


	struct Player player1, player2;
	struct Player * currentPlayer;
	player1 = createPlayer(1);
	player2 = createPlayer(2);

	currentPlayer = &player1;

	struct Vector start, end;
	struct Pion * pionStart;
	int resultAction;
	int comboMode = 0; // Si le joueur effectue une prise, il rentre en mode combo

	// Boucle de jeu
	while(player1.score != NB_PION && player2.score != NB_PION){
		showConsoleBoard();
		printf("Score : \n  Player1 : %d\n  Player2 : %d\n", player1.score, player2.score);
		printf("Joueur %d\n", currentPlayer->team);
		printf(" Start : \n");
		printf(" => x : ");
		scanf("%d", &start.x);
		printf(" => y : ");
		scanf("%d", &start.y);

		comboMode = 0; // Réinitialisation du mode Combo

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
			// Si le nombre de prise disponible autour du pion est 0
			// Alors ont sort de la boucle marque la fin du tour
			if(comboMode == 1 && testAllPrise(*pionStart) == 0){
				printf(" Plus de prise disponible pour se tours\n");
				break;
			}

			showConsoleBoard();

			printf(" End : \n");
			printf(" => x : ");
			scanf("%d", &end.x);
			printf(" => y : ");
			scanf("%d", &end.y);

			resultAction = action(pionStart, end, currentPlayer);

			// L'action n'a pas aboutie
			if(resultAction == -1){
				printf(" Echec action\n");
				continue;
			// L'action est une prise
			}else if(resultAction == 2){
				comboMode = 1;
				printf(" Continue action\n");
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

			// Transformation du pion en dame
			if(testTranfo(*pionStart) == 1){
				printf("Tranformation !!!!\n");
				tranfoDame(pionStart);
			}

			
		}while(resultAction == 2);

	}


	
	showConsoleBoard();
	if(currentPlayer->team == player1.team){
		currentPlayer = &player2;
	}else{
		currentPlayer = &player1;
	}
	printf("Player %d a gagne !\n", currentPlayer->team);
	freeBoard();
	return 0;
}