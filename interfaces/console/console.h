
/**
 * Effectue une action 
 * move, move + prise...
 * La fonction retourne -1 en cas d'echec ex: saut au dessus de plusieurs prises
 * Sinon si le tour fait partie d'un combo on retourne 2
 * Sinon retourne 1 en cas de succès
 */
int action(struct Pion * pion, struct Vector point, struct Player * player);

int console();