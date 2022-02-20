#ifndef DISPLAY_H /* Protections inclusions multiples */
#define DISPLAY_H

/* Declarations */

/* Structures et define */


/* resolution de l'ecran */
#define ECRWIDTH 1000
#define ECRHEIGHT 800

#define ECRNO_SELECT 0 /* Numero de l'ecran de selection */
#define ECRNO_GAME 1 /* Numero de l'ecran de jeu */
#define ECRNO_RESULT 3 /* Numero de l'ecran de jeu */

#define CELL_SIZE 60 /* Taille en pixel d'une case */

#define IMG_PLAYER_ORANGE "Images/bonhomme_orange.png"
#define IMG_PLAYER_BLUE "Images/bonhomme_bleu.png"
#define IMG_CROSS_ORANGE "Images/croix_orange.png"
#define IMG_CROSS_BLUE "Images/croix_bleue.png"

struct select_s
{
    int size; /* [3,9] */
    int mode; /* 0 => single | 1 => multiplayer */
};

typedef struct select_s select;

struct pos_s
{
    int x; /* Si -1 en dehors du jeu */
    int y; /* Si -1 en dehors du jeu */
};

typedef struct pos_s pos;

/* Fonctions */

void InitDisplay(); /* Initilisation du module graphique */

void CloseDisplay(); /* Permet de fermer le module graphique */

void EcrireTexteCentre(int y, char *text, int taille); /* Affiche du texte au centre */

select ShowSelectDisplay(); /* Affichage de l'ecran de selection et retourne le choix de l'utilisateur */

void ShowGameDisplay(int size); /* Affiche l'ecran de jeu */

int ShowResultDisplay(int winner); /* Affiche l'ecran de resultat | Retourne le choix pour continuer ou non 0 = Quitter / 1 = Rejouer | winner = numero du joueur qui gagne */

void DisplayCross(int x, int y, int size, int color); /* Affiche une croix | 0 => Bleu / 1 => Orange */

void DisplayPlayer(int x, int y, int size, int color); /* Affiche un joueur | 0 => Bleu / 1 => Orange */

void EraseCell(int x, int y, int size); /* Efface une case */

pos GetClickPos(int size); /* Recupère la case ou à cliqué le joueur ATTENTION -1 veut dire que l'utilisateur a cliqué en dehors de la zone de jeu */

void SetGameStatus(char text[]); /* Affiche le statut de la partie, et quelle est la prochaine action */

#endif /* DISPLAY_H */
