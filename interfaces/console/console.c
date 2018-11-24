#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../../define.h"
#include "../../mods/Vector.h"
#include "../../mods/Pion.h"
#include "../../mods/Player.h"
#include "../../main.h"
#include "consoleBoard.h"
#include "console.h"

int console()
{
	setBoard();
	//setTestBoard();


	struct Player player1, player2;
	struct Player * currentPlayer;
	player1 = createPlayer(1, "Joueur 1");
	player2 = createPlayer(2, "Joueur 2");

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

		if(pionStart->team != currentPlayer->team){ // Le pion n'appartient pas au joueur
			printf(" Ce pion n'appartient pas au joueur\n");
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

			resultAction = action(pionStart, end, currentPlayer, NULL);

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