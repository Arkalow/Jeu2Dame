#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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



#define WIDTH 10 // Le plateau est carré, WIDTH représente la taille du côté du plateau

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
 * Créer un vecteur à partir de coordonées
 * Peut représenter un point par exemple
 */ 
struct Vector createPoint(int x, int y){
	struct Vector vector;
	
	vector.x = x;
	vector.y = y;
	
	return vector;
}

/**
 * Effectue une soustraction de deux vecteurs
 */ 
struct Vector subVector(struct Vector v1, struct Vector v2){
	struct Vector vector;
	
	vector.x = v1.x - v2.x;
	vector.y = v1.y - v2.y;
	
	return vector;
}

/**
 * Effectue une addidtion de deux vecteurs
 */ 
struct Vector addVector(struct Vector v1, struct Vector v2){
	struct Vector vector;
	
	vector.x = v1.x + v2.x;
	vector.y = v1.y + v2.y;
	
	return vector;
}

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
 * Calcule le vecteur unite
 */
struct Vector unitVector(struct Vector v){
	if(v.x != 0){ v.x = v.x / abs(v.x); }
	if(v.y != 0){ v.y = v.y / abs(v.y); }
	return v;
}

/**
 * Affiche un vecteur
 * Pour le debug
 */
void showVector(struct Vector vector){
	printf("Vector (%d, %d)\n", vector.x, vector.y);
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
 * Affiche un pion dans la console
 * Pour les debug
 */
void showPion(struct Pion pion){
	printf("Pion (%d, %d) %d\n", pion.position.x, pion.position.y, pion.team);
}

/**
 * Test si le vecteur test est compris dans le vecteur reference
 * C'est le cas d'un déplacement valide par exemple
 */
int testVector(struct Vector test, struct Vector reference){
	if(reference.x > 0){ // Le vecteur référence est positif sur x
		if(!(test.x > 0 && test.x < reference.x)){ // ! 0 < test.x < ref.x
			return 0; // False;
		}
	}else{
		if(!(test.x < 0 && test.x > reference.x)){ //  ! ref.x < test.x < 0
			return 0; // False;
		}
	}

	if(reference.y > 0){ // Le vecteur référence est positif sur y
		if(!(test.y > 0 && test.y < reference.y)){ //  ! 0 < test.y < ref.y
			return 0; // False;
		}
	}else{
		if(!(test.y < 0 && test.y > reference.y)){ //  ! ref.y < test.y < 0
			return 0; // False;
		}
	}

	return 1; // True;
}

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