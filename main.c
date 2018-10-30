/**
 * Programme principale
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "define.h"
#include "mods/Vector.h"
#include "mods/Pion.h"
#include "mods/Player.h"
#include "interfaces/sdl/gui.h"
#include "interfaces/console/console.h"

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
Si un pion arrive au bout de la map (chez l'adversaire) ce dernier se transforme en dame


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

MODE COMBO
-----------------------------------------------------------------------------
Si le joueur effectue une prise alors il passe en mode combo. Avec le pion selectionné, il 
peut effectuer autant de prise d'affiler.
Ce mode combo est représenté ici par une variable flag qui prend la valeur 1 au moment où
le joueur effectue une prise et reviens à 0 à la fin du tour

*/

// PROGRAMME PRINCIPALE
// -------------------------------------------------------------------------------------
int main(){
	gui(); // Lancement jeu en SDL2
	//console(); // Lancement du jeu en console (Operationnel)
}