/**
 * Programme principale
 */

/*

LE PLATEAU
-----------------------------------------------------------------------------
On modélise la map dans un tableau 2D. Chaque case du tableau est un pointeur 
de Pion. Si le pointeur est NULL il n'y a pas de pion sur cette case.

LES PIONS
-----------------------------------------------------------------------------
Les pions sont représentés par une structure du même nom. Il contiennent des
informations sur leurs positions, leurs types leurs teams leurs déplacements 
possibles.


LES DEPLACEMENTS
-----------------------------------------------------------------------------
Les déplacements d'un pion sont représenté par un tableau de vecteur 
déplacement. Pour tester la validité d'un déplacement on vérifie si le vecteur 
déplacement est compris à l'interieur de l'un des vecteurs deplacements de la 
moveList attachée au pion. Si un pion arrive au bout de la map (chez 
l'adversaire) ce dernier se transforme en dame


LES PRISES
-----------------------------------------------------------------------------
Une prise s'efectue quand le pion se déplace au dessus d'un seul pion adverse. 
Les conditons sont : 
	- La prise doit être de seulement 1 pion
	- La prise doit se faire par une trajectoire lineaire
	- Un pion ne peut pas passer au dessus d'un autre pion de sa team
	- Le pion doit passer au dessus d'un et unique pion
	- Pendant une prise, le pion augmente sa porté de 1
	- La case destination doit être libre


LES ACTIONS
-----------------------------------------------------------------------------
Une action est l'enchainement d'un déplacement et ou une prise. La fonction 
action va mettre en relation les tests de déplacement ainsi que les tests de 
prises pour effectuer les déplacements et les prises. 
Une action de déroule en plusieurs étapes : 
	- On commence par parcourir la trajectoire demandé pour déterminer si les 
	prises sont correctes.
	- Ensuite on augmente la porté du pion pour cela on augmente tout les 
	vecteurs deplacement du pion de 
		1 unite vecteur. 
	- Ensuite on effectue un déplacement classique (avec la porté augmenter)

	- A la fin du tour, il ne faut pas oublier de remettre les vecteurs 
	déplacement à leurs valeurs initiales.


TOURS DE JEU
-----------------------------------------------------------------------------
Le jeu se déroule en tour par tour, les deux joueurs jouent chaqu'un leurs 
tour.
Quand un joueur effectue une prise, il peut rejouer pour faire des combos 

MODE COMBO
-----------------------------------------------------------------------------
Si le joueur effectue une prise alors il passe en mode combo. Avec le pion 
selectionné, il peut effectuer autant de prise d'affiler. Ce mode combo est 
représenté ici par une variable flag qui prend la valeur 1 au moment où le 
joueur effectue une prise et reviens à 0 à la fin du tour.



=============================================================================
	MODE RESEAU
=============================================================================

CONNEXION RESEAUX
-----------------------------------------------------------------------------
Le mode multi joueur fonctionne grâce à un échange de socket. Dans un premier 
temps la personne lance le mode réseau et attend une personne qui se connecte, 
c'est à dire j'usqu'à ce qu'un client se connecte. Le joueur 1 sera le 
premier arrivé et le second se ra le joueur 2.

ECHANGE DE SOCKET (tour par tour)
-----------------------------------------------------------------------------
Après avoir jouer, le programme écoute sur son port source (dans un thread) 
et attend un réponse du joueur adverse. Pendant ce temps là le joueur 
récupère le données du joueur précédent en se connectant au joueur 1. Ensuite,
il joue et se met à son tour en mode serveur. L'autre joueur se connecte et 
ainsi de suite.

LES DONNEES ECHANGEES
-----------------------------------------------------------------------------
Les données du tour seront envoyées depuis le thread serveur. On enverra 
l'adresse de la structure dans le thread, il va encoder les données en chaine 
de caractère pour être envoyé dans une socket. Ensuite le joueur suivant se 
connecte au serveur récupère la chaine de caractère, la décode repoduit les 
actions sur son jeu.

DONNEES ENVOYEES
-----------------------------------------------------------------------------
Les données envoyé au thread est une structure contenant : 
		- La position de départ du pion joué
		- La position d'arrivée du pion joué
		- La liste des positions des prises capturées

Les position seront des structure Vector

ENCODAGE DONNEES
-----------------------------------------------------------------------------
L'objectif est d'encoder les données du tour en chaine de caractère. On va 
l'ecrire de cette manière :







*/

/**
 * Effectue une action 
 * move, move + prise...
 * On stocke l'adresse de la prise dans prise
 * La fonction retourne :
 * 		- 0 : succès
 * 		- 1 : combo
 * 		- -1 : pas de prise
 * 		- -2 : hors limite
 * 		- -3 : case de destination déjà occupée
 * 		- -4 : Erreur prise (plusieurs prises sur le chemin)
 * 		- -5 : Déplacement impossible
 */
int action(struct Pion * pion, struct Vector point, struct Player * player, struct Vector * posPrise);

int main();