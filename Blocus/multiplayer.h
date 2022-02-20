#ifndef MULTIPLAYER_H /* Protections inclusions multiples */
#define MULTIPLAYER_H

/* Declarations */

/* Structures */

typedef struct /* variable de position des deux joueurs */
{
	pos p1; /* position x et position y du joueur 1 */
	pos p2; 
} game_p;

struct elem /* structure d'un maillon pour la liste chaînée */
{
   pos coord;
   struct elem* next;
};
 
typedef struct elem element;

/* Fonctions */

game_p FirstsPlayersPositions(int g_size); /* Placement des deux pions de départ */

game_p MovementPlayer1(int g_size, game_p players, element* cross_list); /* Déplacement du joueur 1 */

element* CrossPlayer1(int g_size, game_p players, element* cross_list); /* Placement d'une croix du joueur 1 sur la carte */

game_p MovementPlayer2(int g_size, game_p players, element* cross_list); /* Déplacement du joueur 2 */

element* CrossPlayer2(int g_size, game_p players, element* cross_list); /* Placement d'une croix du joueur 2 sur la carte */

element* AddElement(element* previous, pos coord); /* Ajoute une coordonnée à la liste chaînée */

int BlockedCase(element* first, pos co_watched); /* Permet de tester si une case est occupé par une croix grâce à une liste chaînée */

void DeleteList(element* p); /* Supprime les éléments de la liste chaînée */

int EndOfGame(game_p players, pos coord_watched, element* cross_list, int g_size); /* Permet de tester si la partie prend fin */

#endif /* MULTIPLAYER_H */