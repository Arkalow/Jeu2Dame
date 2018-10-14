
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
 * Créer un vecteur à partir de coordonées
 * Peut représenter un point par exemple
 */ 
struct Vector createPoint(int x, int y);

/**
 * Effectue une soustraction de deux vecteurs
 */ 
struct Vector subVector(struct Vector v1, struct Vector v2);

/**
 * Effectue une addidtion de deux vecteurs
 */ 
struct Vector addVector(struct Vector v1, struct Vector v2);

/**
 * Créer un vecteur à partir de deux points
 * Peut représenter un vecteur déplacement par exemple
 */ 
struct Vector createVector(int startX, int startY, int endX, int endY);

/**
 * Calcule le vecteur unite
 */
struct Vector unitVector(struct Vector v);

/**
 * Affiche un vecteur
 * Pour le debug
 */
void showVector(struct Vector vector);