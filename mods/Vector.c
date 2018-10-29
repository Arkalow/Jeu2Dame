#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Vector.h"

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
 * Test si le vecteur test est compris dans le vecteur reference
 * C'est le cas d'un déplacement valide par exemple
 */
int testVector(struct Vector test, struct Vector reference){

	if(reference.x > 0){ // Le vecteur référence est positif sur x
		if(test.x <= 0 || test.x > reference.x){ // ! 0 < test.x < ref.x
			return 0; // False;
		}
	}else if(reference.x < 0){
		if(test.x >= 0 || test.x < reference.x){ //  ! ref.x < test.x < 0
			return 0; // False;
		}
	}

	
	if(reference.y > 0){ // Le vecteur référence est positif sur y
		if(test.y <= 0 || test.y > reference.y){ //  ! 0 < test.y < ref.y
			return 0; // False;
		}
	}else if(reference.y < 0){
		if(test.y >= 0 || test.y < reference.y){ //  ! ref.y < test.y < 0
			return 0; // False;
		}
	}

	return 1; // True;
}