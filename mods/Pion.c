#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../define.h"
#include "Vector.h"
#include "Pion.h"

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
	board[x][y]->type = type;
	board[x][y]->selected = 0; // Pion non selectionné
	board[x][y]->moveList = &(board[x][y]->normalMoveList);

	// Si le type est une dame
	// 	MAX 0 MAX
	// 	 0  P  0
	// 	MAX 0 MAX
	if(type == 1){

		board[x][y]->nbMove = 4; // Une dame a 4 déplacements possible
		board[x][y]->normalMoveList[0] = createVector(0, 0, 10, 10); // Bas droite
		board[x][y]->normalMoveList[1] = createVector(0, 0, -10, -10); // Haut gauche
		board[x][y]->normalMoveList[2] = createVector(0, 0, -10, 10); // Bas gauche
		board[x][y]->normalMoveList[3] = createVector(0, 0, 10, -10); // Haut droite

	}else{ // Le pion est un pion classique

		board[x][y]->nbMove = 2; // Un pion classique a 2 déplacements possible

		if(team == 1){
			// Si c'est un pion joueur 1
			// 	0 0 0
			// 	0 P 0
			// 	1 0 1
			board[x][y]->normalMoveList[0] = createVector(0, 0, 1, 1); // Bas droite
			board[x][y]->normalMoveList[1] = createVector(0, 0, -1, 1); // Bas gauche
			board[x][y]->nbNormalMove = 2;

			// Deplacement possible pendant une prise
			board[x][y]->specialMoveList[0] = createVector(0, 0, 2, 2); // Bas droite
			board[x][y]->specialMoveList[1] = createVector(0, 0, -2, 2); // Bas gauche
			board[x][y]->specialMoveList[2] = createVector(0, 0, -2, -2); // Haut gauche
			board[x][y]->specialMoveList[3] = createVector(0, 0, 2, -2); // Haut droite
			board[x][y]->nbSpecialMove = 4;
		}else{
			// Si c'est un pion joueur 2
			// 	1 0 1
			// 	0 P 0
			// 	0 0 0
			board[x][y]->normalMoveList[0] = createVector(0, 0, -1, -1); // Haut gauche
			board[x][y]->normalMoveList[1] = createVector(0, 0, 1, -1); // Haut droite
			board[x][y]->nbNormalMove = 2;

			// Deplacement possible pendant une prise
			board[x][y]->specialMoveList[0] = createVector(0, 0, -2, -2); // Haut gauche
			board[x][y]->specialMoveList[1] = createVector(0, 0, 2, -2); // Haut droite
			board[x][y]->specialMoveList[2] = createVector(0, 0, 2, 2); // Bas droite
			board[x][y]->specialMoveList[3] = createVector(0, 0, -2, 2); // Bas gauche
			board[x][y]->nbSpecialMove = 4;
		}
	}
}

/**
 * Test si le pion est à la bonne position pour se transformer en dame
 */
int testTranfo(struct Pion pion){
	if(pion.type != 0) return 0; // Ce n'est pas un pion 

	if(pion.team == 2 && pion.position.y == 0) return 1;
	else if(pion.team == 1 && pion.position.y == WIDTH - 1) return 1;
	
	return 0;
}

/**
 * Transforme un pion en dame
 * On change tout simplement son type et sa moveList
 */
void tranfoDame(struct Pion * pion){
	pion->type = 1;
	pion->nbMove = 4; // Une dame a 4 déplacements possible
	pion->normalMoveList[0] = createVector(0, 0, 10, 10); // Bas droite
	pion->normalMoveList[1] = createVector(0, 0, -10, -10); // Haut gauche
	pion->normalMoveList[2] = createVector(0, 0, -10, 10); // Bas gauche
	pion->normalMoveList[3] = createVector(0, 0, 10, -10); // Haut droite

	// Liste de deplacement pendant une prise
	pion->specialMoveList[0] = createVector(0, 0, 10, 10); // Bas droite
	pion->specialMoveList[1] = createVector(0, 0, -10, -10); // Haut gauche
	pion->specialMoveList[2] = createVector(0, 0, -10, 10); // Bas gauche
	pion->specialMoveList[3] = createVector(0, 0, 10, -10); // Haut droite
}

/**
 * Affiche un pion dans la console
 * Pour les debug
 */
void showPion(struct Pion pion){
	printf("Pion (%d, %d) \n team %d\n", pion.position.x, pion.position.y, pion.team);
	printf("\tType %d\n", pion.type);
	printf("\tDeplacement : \n");
	for(int i = 0; i < pion.nbMove; i++){
		printf("\t\t");
		showVector("", pion.moveList[i]);
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

/**
 * Test si un pion peut atteindre la case c d'après la liste de ses déplacements possible
 * retourne 0 si pas possible
 * retourne 1 si deplacement
 * retourne 2 si deplacement speciale
 */
int testMove(struct Pion pion, struct Vector c){
	struct Vector move;
	move = subVector(c, pion.position);

	// On parcourt tous les déplacements possible du pion
	for(int i = 0; i < pion.nbMove; i++){
		if(testVector(move, pion.moveList[i]) == 1){
			return 1; // True 
		}
	}
	incrementMoveList(&pion);
	for(int i = 0; i < pion.nbMove; i++){
		if(testVector(move, pion.moveList[i]) == 1){
			return 2; // True 
		}
	}
	decrementMoveList(&pion);

	return 0;
}

/**
 * Déplace un pion sur le plateau
 */
void move(struct Pion * pion, struct Vector end){
	struct Vector start; start = pion->position;

	pion->position.x = end.x;
	pion->position.y = end.y;

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
	struct Vector start; start = pion.position; // Position de départ (position du pion)
	struct Vector unit = unitVector(subVector(end, pion.position)); // Vecteur unité

	// Gestion des déplacements hors plateau
	while(end.x >= WIDTH || end.y >= WIDTH){
		end = subVector(end, unit);
	}
	while(end.x < 0 || end.y < 0){
		end = subVector(end, unit);
	}
	// Parcourt de la trajectoire
	while(start.x != end.x || start.y != end.y){

		start = addVector(start, unit); // On incrémente le vecteur d'une unite

		// Si on tombe sur un pion
		if(board[start.x][start.y] != NULL){ 

			// On traverse un de ses pions
			if(board[start.x][start.y]->team == pion.team) { 
				return -1; 

			}else{ // On ne traverse pas un de ses pions mais un pion adverse
				nbPrise++;
				*prise = start; // Pion trouvé
			}
			
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
 * Test pour tous les déplacement possible du pion s'il existe au moins 1 prise et rien derriere
 */ 
int testAllPrise(struct Pion pion){
	struct Vector prise;
	struct Pion * p;
	for(int i = 0; i < pion.nbMove; i++){
		if(
			testPrise(pion, addVector(pion.position, (pion.moveList)[i]), &prise) == 1 && 
			searchBoard(addVector(pion.moveList[i], unitVector(pion.moveList[i])), &p) == 0
		){
			return 1;
		}
	}
	return 0;
}

/**
 * Récupère l'adresse d'un pion dans le plateau
 * Si les coordonées sont valide => retourne 1 et met l'adresse du pion dans pion
 * Sinon => retourne -1
 */
int searchBoard(struct Vector point, struct Pion ** pion){
	if(point.x < WIDTH && point.x >= 0 && point.y >= 0 && point.y < WIDTH){

		*pion = board[point.x][point.y];
		if(*pion != NULL){
			return 1; // Vrai
		}else{
			return 0; // Faux
		}

	}else{
		*pion = NULL;
		return -1; // Erreur
	}
}

/**
 * Incremente la liste des deplacement du pion de une unite vecteur
 */
void incrementMoveList(struct Pion * pion){
	pion->moveList = &(pion->specialMoveList);
	pion->nbMove = pion->nbSpecialMove;
}

/**
 * Decrement la liste des deplacement du pion de une unite vecteur
 */
void decrementMoveList(struct Pion * pion){
	pion->moveList = &(pion->normalMoveList);
	pion->nbMove = pion->nbNormalMove;
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
 * Rempli le plateau pour les tests
 */
void setTestBoard(){

	for(int y = 0; y < WIDTH; y++){
		for(int x = 0; x < WIDTH; x++){
			board[x][y] = NULL;
		}
	}

	// Team 1
	createPion(0, 0, 1, 0);
	createPion(2, 0, 1, 0);

	// Team 2
	createPion(1, 1, 2, 0);
	createPion(4, 4, 2, 0);
}