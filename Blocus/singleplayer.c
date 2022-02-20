#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "display.h"
#include "multiplayer.h"
#include "singleplayer.h"

int IsCellFree(element* first, int x, int y, int grid_size, game_p players) /* Detecte si la case est libre */
{
    /* Verification des cases qui ont une croix */
    element* p = (element*) malloc(sizeof(element));

    for (p = first; p != NULL; p = p->next)
    {
        if(x == p->coord.x && y == p->coord.y)
        {
            return 0; /* La case est occupé par une croix */
        }
    }      

    /* Verification bordures du plateau */
    if (x < 0 || x >= grid_size || y < 0 || y >= grid_size)
    {
        return 0; /* La case est en dehors du plateau */
    }

    /* Verification si un joueur est sur la case */
    if ((players.p1.x == x && players.p1.y == y) || (players.p2.x == x && players.p2.y == y))
    {
        return 0; /* la case est occupé par un joueur */
    }

    return 1; /* La case est libre */
}

game_p MovementRobot(int g_size, game_p players, element* cross_list) /* Déplacement du robot */
{
    srand(time(NULL)); /* RESET générateur aleatoire */

    int freeCells[8], nbFreeCells = 0, i, randomSelected, moveSelected, temp;

    /* Remplissage du tableau des cases vides autour du robot */
    freeCells[0] = IsCellFree(cross_list, players.p2.x - 1, players.p2.y - 1, g_size, players); /* En haut à gauche */
    freeCells[1] = IsCellFree(cross_list, players.p2.x, players.p2.y - 1, g_size, players);     /* En haut */
    freeCells[2] = IsCellFree(cross_list, players.p2.x + 1, players.p2.y - 1, g_size, players); /* En haut à droite */
    freeCells[3] = IsCellFree(cross_list, players.p2.x - 1, players.p2.y, g_size, players);     /* Gauche */
    freeCells[4] = IsCellFree(cross_list, players.p2.x + 1, players.p2.y, g_size, players);     /* Droite */
    freeCells[5] = IsCellFree(cross_list, players.p2.x - 1, players.p2.y + 1, g_size, players); /* En bas à gauche */
    freeCells[6] = IsCellFree(cross_list, players.p2.x, players.p2.y + 1, g_size, players);     /* En bas */
    freeCells[7] = IsCellFree(cross_list, players.p2.x + 1, players.p2.y + 1, g_size, players); /* En bas à droite */

    for (i = 0; i < 8; i++) /* Compte le nombre de cases libres */
    {
        if (freeCells[i])
        {
            nbFreeCells++;
        }
    }

    randomSelected = rand() % nbFreeCells; /* On choisis une des position aleatoires disponibles */

    temp = -1;

    for (i = 0; i < 8; i++) /* Determination du movement choisi parmis ceux disponibles en fonction de l'aleatoire */
    {
        if (freeCells[i])
        {
            temp++;

            if (temp == randomSelected)
            {
                moveSelected = i;
            }
        }
    }

    EraseCell(players.p2.x, players.p2.y, g_size); /* On efface le joueur */

    if (moveSelected == 0) /* haut gauche */
    {
        players.p2.x--;
        players.p2.y--;
    }
    else if (moveSelected == 1) /* haut */
    {
        players.p2.y--;
    }
    else if (moveSelected == 2) /* haut droite */
    {
        players.p2.x++;
        players.p2.y--;
    }
    else if (moveSelected == 3) /* gauche */
    {
        players.p2.x--;
    }
    else if (moveSelected == 4) /* droite */
    {
        players.p2.x++;
    }
    else if (moveSelected == 5) /* bas gauche */
    {
        players.p2.x--;
        players.p2.y++;
    }
    else if (moveSelected == 6) /* bas */
    {
        players.p2.y++;
    }
    else if (moveSelected == 7) /* bas droite */
    {
        players.p2.x++;
        players.p2.y++;
    }

    DisplayPlayer(players.p2.x, players.p2.y, g_size, 1); /* On affiche le joueur a sa nouvelle position */

    return players;
}

game_p SetupPositions(int g_size) /* Placement des deux pions de départ */
{
    srand(time(NULL)); /* RESET générateur aleatoire */

    game_p players;

    SetGameStatus("Positionnement du joueur bleu :");

    do
    {
        players.p1 = GetClickPos(g_size);
    }
    while(players.p1.x == -1 || players.p1.y == -1); /* Un pion ne peut pas être en dehors du plateau */

    DisplayPlayer(players.p1.x, players.p1.y, g_size, 0);
   
    do
    {
        players.p2.x = rand() % g_size;
        players.p2.y = rand() % g_size;
    }
    while(players.p2.x == players.p1.x && players.p2.y == players.p1.y); /* Verification si on est sur l'autre pion */

    DisplayPlayer(players.p2.x, players.p2.y, g_size, 1);

    return players;
}

element* CrossRobot(int g_size, game_p players, element* cross_list) /* Placement d'une croix par le robot sur le plateau */
{
    srand(time(NULL)); /* RESET générateur aleatoire */

    int freeCells[8], nbFreeCells = 0, i, randomSelected, placeSelected, temp, x, y;
    pos crossPos;

    /* Remplissage du tableau des cases vides autour du joueur adverse */
    freeCells[0] = IsCellFree(cross_list, players.p1.x - 1, players.p1.y - 1, g_size, players); /* En haut à gauche */
    freeCells[1] = IsCellFree(cross_list, players.p1.x, players.p1.y - 1, g_size, players);     /* En haut */
    freeCells[2] = IsCellFree(cross_list, players.p1.x + 1, players.p1.y - 1, g_size, players); /* En haut à droite */
    freeCells[3] = IsCellFree(cross_list, players.p1.x - 1, players.p1.y, g_size, players);     /* Gauche */
    freeCells[4] = IsCellFree(cross_list, players.p1.x + 1, players.p1.y, g_size, players);     /* Droite */
    freeCells[5] = IsCellFree(cross_list, players.p1.x - 1, players.p1.y + 1, g_size, players); /* En bas à gauche */
    freeCells[6] = IsCellFree(cross_list, players.p1.x, players.p1.y + 1, g_size, players);     /* En bas */
    freeCells[7] = IsCellFree(cross_list, players.p1.x + 1, players.p1.y + 1, g_size, players); /* En bas à droite */

    for (i = 0; i < 8; i++) /* Compte le nombre de cases libres */
    {
        if (freeCells[i])
        {
            nbFreeCells++;
        }
    }

    randomSelected = rand() % nbFreeCells; /* On choisis une des cases aleatoires disponibles */

    temp = -1;

    for (i = 0; i < 8; i++) /* Determination de la case choisi parmis ceux disponibles en fonction de l'aleatoire */
    {
        if (freeCells[i])
        {
            temp++;

            if (temp == randomSelected)
            {
                placeSelected = i;
            }
        }
    }


    x = players.p1.x;
    y = players.p1.y;


    if (placeSelected == 0) /* haut gauche */
    {
        x--;
        y--;
    }
    else if (placeSelected == 1) /* haut */
    {
        y--;
    }
    else if (placeSelected == 2) /* haut droite */
    {
        x++;
        y--;
    }
    else if (placeSelected == 3) /* gauche */
    {
        x--;
    }
    else if (placeSelected == 4) /* droite */
    {
        x++;
    }
    else if (placeSelected == 5) /* bas gauche */
    {
        x--;
        y++;
    }
    else if (placeSelected == 6) /* bas */
    {
        y++;
    }
    else if (placeSelected == 7) /* bas droite */
    {
        x++;
        y++;
    }

    DisplayCross(x, y, g_size, 1);
    crossPos.x = x;
    crossPos.y = y;
    cross_list = AddElement(cross_list, crossPos);

    return cross_list;
}