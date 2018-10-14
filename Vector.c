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