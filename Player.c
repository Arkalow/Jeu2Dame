#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Vector.h"
#include "Pion.h"
#include "Player.h"

/**
 * Créer un joueur
 */
struct Player createPlayer(int team){
    struct Player player;
    player.team = team;
    player.nbCatchedPion = 0;
    return player;
}

/**
 * Si le pion appartient au joueur retourne 1
 * Sinon retourne 0
 */
int testPion(struct Pion pion, struct Player player){
    if(player.team == pion.team) return 1;
    else return 0; 
}