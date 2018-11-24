#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
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
 * Test si deux vecteur sont egaux
 */
int equalVector(struct Vector v1, struct Vector v2){
	if(v1.x == v2.x && v1.y == v1.y) return 1;
	else return 0;
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

char * intToString(int nb)
{
	char* str;
	str = malloc(sizeof(char));
	sprintf(str, "%d", nb);
	return str;
}

/**
 * Concat 2 chaines de caractère
 */
char * str_concat(char * str1, char * str2)
{
	char* str;
	str = malloc(sizeof(char) * strlen(str1)); /* make space for the new string (should check the return value ...) */
	strcpy(str, str1); /* copy str1 into the new var */
	strcat(str, str2); /* add the str2 */
	return str;
}

/**
 * Affiche un vecteur
 * Pour le debug
 */
void showVector(char * title, struct Vector vector){
	printf("Vector : %s (%d, %d)\n", title, vector.x, vector.y);
}

/**
 * Convertie un vector en chaine de caractère
 * Format : (x,y)
 */
char * vectorToString(struct Vector vector)
{
	char * str = "(";
	str = str_concat(str, intToString(vector.x));
	str = str_concat(str, ",");
	str = str_concat(str, intToString(vector.y));
	str = str_concat(str, ")");
	return str;
}

/**
 * Convertie une chaine de caractère en Vector
 */
struct Vector stringToVector(char * str){
	struct Vector vector;
	int temp = 0;
	while(str++[0] != ')'){
		if(str[0] == ')') continue;
		if(str[0] == ','){
			vector.x = temp;
			temp = 0;
			continue;
		}
		temp = temp * 10 + str[0] - '0';
	}
	vector.y = temp;
	return vector;
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

	// Le problème est que sur l'axe des x le vecteur correspond.
	// Sur l'axe des y aussi mais les 2 en même temps non
	// La solution est de comparer les coeff directeur
	if(coeffDirector(createPoint(0, 0), test) != coeffDirector(createPoint(0, 0), reference)){
		return 0; // False;
	}



	return 1; // True;
}


/**
 * Calcul le coeff directeur de la droite passant par ces deux points
 */
int coeffDirector(struct Vector p1, struct Vector p2){
	return (p2.x - p1.x) / (p2.y - p1.y);
}