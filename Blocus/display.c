#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <string.h>
#include "display.h"

void InitDisplay() /* Permet d'initiliser le module graphique */
{
    InitialiserGraphique();
    CreerFenetre(10, 10, ECRWIDTH, ECRHEIGHT);
}

void CloseDisplay() /* Permet de fermer le module graphique */
{
    FermerGraphique();
}

void EcrireTexteCentre(int y, char *text, int taille)
{
    int x = ECRWIDTH / 2 - (TailleChaineEcran(text, taille) / 2); /* Calcul position X de debut de chaine */
    EcrireTexte(x, y, text, taille);
}

select ShowSelectDisplay() /* Affichage de l'ecran de selection */
{
    int size = 3; /* [0,9] */
    int mode = 0; /* 0 => 1J | 1=> 2J */
    char strSize[9];

    /* flag pour demander la mise a jour graphique */
    int updateSize = 0;

    /* flag pour continuer d'attendre le choix de l'utilisateur */
    int isUserSelecting = 1;

    /* On se place sur le bon écran et on l'efface */
    ChoisirEcran(ECRNO_SELECT);
    EffacerEcran(CouleurParNom("white"));

    /* Ecriture texte fixe */
    ChoisirCouleurDessin(CouleurParComposante(52, 204, 235));
    EcrireTexteCentre(100, "BLOCUS", 2);
    ChoisirCouleurDessin(CouleurParNom("black"));
    EcrireTexteCentre(ECRHEIGHT - 100, "Projet realise par Mathis Huriez & Guillaume Toutain", 1);

    EcrireTexteCentre(300, "Merci de choisir la taille de la grille : [3,9]", 1);
    ChoisirCouleurDessin(CouleurParNom("red"));
    EcrireTexte((ECRWIDTH/2)-40, 350, "-", 2);
    ChoisirCouleurDessin(CouleurParNom("green"));
    EcrireTexte((ECRWIDTH/2)+30, 350, "+", 2);
    ChoisirCouleurDessin(CouleurParNom("black"));
    EcrireTexteCentre(500, "Merci de choisir le mode de jeu :", 1);
    DessinerRectangle((ECRWIDTH/2)-40, 625, 80, 40);
    EcrireTexteCentre(650, "Jouer !", 1);

    /* Ecriture textes dynamiques */
    sprintf(strSize, "%d", size);
    EcrireTexteCentre(350, strSize, 2);
    DessinerRectangle((ECRWIDTH/2)-20, 320, 40, 40);
    DessinerRectangle((ECRWIDTH/2)-60, 525, 120, 40);
    EcrireTexteCentre(550, "1 joueur", 1);

    /* Ecriture images pour faire joli */
    ChargerImage(IMG_PLAYER_BLUE, (ECRWIDTH/2) - 150, 70, 0, 0, 100, 100);
    ChargerImage(IMG_PLAYER_ORANGE, (ECRWIDTH/2) + 100, 70, 0, 0, 100, 100);

    while (isUserSelecting)
    {
        if (SourisCliquee())
        {
            /* Partie pour la taille */

            if (_X >= (ECRWIDTH/2)-60 && _X <= (ECRWIDTH/2)-20 && _Y >= 320 && _Y <= 360) /* Appuis sur le bouton - */
            {
                size--;
                updateSize = 1;
            }

            if (_X >= (ECRWIDTH/2)+20 && _X <= (ECRWIDTH/2)+60 && _Y >= 320 && _Y <= 360) /* Appuis sur le bouton + */
            {
                size++;
                updateSize = 1;
            }

            if (size > 9)
            {
                size = 9;
            }

            if (size < 3)
            {
                size = 3;
            }

            if (updateSize)
            {
                /* Recriture de la taille */
                ChoisirCouleurDessin(CouleurParNom("white"));
                RemplirRectangle((ECRWIDTH/2)-20, 320, 40, 40);
                ChoisirCouleurDessin(CouleurParNom("black"));
                sprintf(strSize, "%d", size);
                EcrireTexteCentre(350, strSize, 2);
                DessinerRectangle((ECRWIDTH/2)-20, 320, 40, 40);

                updateSize = 0;
            }

            /* Partie pour le mode */

            if (_X >= (ECRWIDTH/2)-60 && _X <= (ECRWIDTH/2)+60 && _Y >= 525 && _Y <= 565) /* Appuis sur le bouton du mode */
            {
                mode = (mode + 1) % 2;

                ChoisirCouleurDessin(CouleurParNom("white"));
                RemplirRectangle((ECRWIDTH/2)-60, 525, 120, 40);
                ChoisirCouleurDessin(CouleurParNom("black"));
                DessinerRectangle((ECRWIDTH/2)-60, 525, 120, 40);

                if (mode == 0)
                {
                    EcrireTexteCentre(550, "1 joueur", 1);
                }
                else /* mode == 1 */
                {
                    EcrireTexteCentre(550, "2 joueurs", 1);
                }

            }


            /* Partie pour le bouton jouer */
            if (_X >= (ECRWIDTH/2)-40 && _X <= (ECRWIDTH/2)+40 && _Y >= 625 && _Y <= 665) /* Appuis sur le bouton jouer */
            {
                isUserSelecting = 0;
            }
        }
    }

    select choice = {size, mode};
    return choice;
}

void ShowGameDisplay(int size) /* Affiche l'ecran de jeu */
{
    int i;
    int sideLength = size * CELL_SIZE;
    int startx = (ECRWIDTH/2) - (sideLength/2);
    int starty = 100;

    /* On se place sur le bon écran et on l'efface */
    ChoisirEcran(ECRNO_SELECT);
    EffacerEcran(CouleurParNom("white"));

    DessinerRectangle(startx, starty, sideLength, sideLength); /* Dessin rectangle principal */

    for (i = 1; i < size; i++)
    {
        DessinerSegment((startx + i * CELL_SIZE), starty, (startx + i * CELL_SIZE), starty + sideLength);
        DessinerSegment(startx, (starty + i * CELL_SIZE), startx + sideLength, (starty + i * CELL_SIZE));
    }
}

int ShowResultDisplay(int winner) /* Affiche l'ecran de resultat | Retour => 0 = Quitter / 1 = Rejouer */
{
    char winnerStr[9];
    char textWinner[256] = "Le gagnant est le joueur ";
    int choice = 0;

    /* flag pour continuer d'attendre le choix de l'utilisateur */
    int isUserSelecting = 1;

    /* On se place sur le bon écran et on l'efface */
    EffacerEcran(CouleurParNom("white"));

    /* Ecriture texte fixe */
    ChoisirCouleurDessin(CouleurParComposante(52, 204, 235));
    EcrireTexteCentre(100, "BLOCUS", 2);
    ChoisirCouleurDessin(CouleurParNom("black"));
    EcrireTexteCentre(ECRHEIGHT - 100, "Projet realise par Mathis Huriez & Guillaume Toutain", 1);

    sprintf(winnerStr, "%d", winner);
    EcrireTexteCentre(300, "Partie terminee !", 1);
    EcrireTexteCentre(350, strcat(textWinner, winnerStr), 2);

    DessinerRectangle((ECRWIDTH/2)-60, 525, 120, 40);
    EcrireTexteCentre(550, "Rejouer", 1);

    DessinerRectangle((ECRWIDTH/2)-60, 580, 120, 40);
    EcrireTexteCentre(605, "Quitter", 1);

    /* Ecriture images pour faire joli */
    ChargerImage(IMG_PLAYER_BLUE, (ECRWIDTH/2) - 150, 70, 0, 0, 100, 100);
    ChargerImage(IMG_PLAYER_ORANGE, (ECRWIDTH/2) + 100, 70, 0, 0, 100, 100);


    while (isUserSelecting)
    {
        if (SourisCliquee())
        {
            if (_X >= (ECRWIDTH/2)-60 && _X <= (ECRWIDTH/2)+60 && _Y >= 525 && _Y <= 565)
            {
                isUserSelecting = 0;
                choice = 1;
            }

            if (_X >= (ECRWIDTH/2)-60 && _X <= (ECRWIDTH/2)+60 && _Y >= 580 && _Y <= 620)
            {
                isUserSelecting = 0;
                choice = 0;
            }
        }
    }

    return choice;
}

void DisplayCross(int x, int y, int size, int color) /* Affiche une croix */
{
    int sideLength = size * CELL_SIZE;
    int startx = (ECRWIDTH/2) - (sideLength/2);
    int starty = 100;

    int deltax = 10; /* delta ajustable pour regler l'alignement de l'image */
    int deltay = 15; /* delta ajustable pour regler l'alignement de l'image */

    if (color == 0) /* Bleu */
    {
        ChargerImage(IMG_CROSS_BLUE, deltax + startx + CELL_SIZE * x, deltay + starty + CELL_SIZE * y, 0, 0, 100, 100);
    }
    else /* Orange */
    {
        ChargerImage(IMG_CROSS_ORANGE, deltax + startx + CELL_SIZE * x, deltay + starty + CELL_SIZE * y, 0, 0, 100, 100);
    }
}

void DisplayPlayer(int x, int y, int size, int color) /* Affiche un joueur */
{
    int sideLength = size * CELL_SIZE;
    int startx = (ECRWIDTH/2) - (sideLength/2);
    int starty = 100;

    int deltax = 5; /* delta ajustable pour regler l'alignement de l'image */
    int deltay = 5; /* delta ajustable pour regler l'alignement de l'image */

    if (color == 0) /* Bleu */
    {
        ChargerImage(IMG_PLAYER_BLUE, deltax + startx + CELL_SIZE * x, deltay + starty + CELL_SIZE * y, 0, 0, 100, 100);
    }
    else /* Orange */
    {
        ChargerImage(IMG_PLAYER_ORANGE, deltax + startx + CELL_SIZE * x, deltay + starty + CELL_SIZE * y, 0, 0, 100, 100);
    }
}

void EraseCell(int x, int y, int size) /* Efface une case */
{
    int sideLength = size * CELL_SIZE;
    int startx = (ECRWIDTH/2) - (sideLength/2);
    int starty = 100;

    ChoisirCouleurDessin(CouleurParNom("white"));
    RemplirRectangle(1 +startx + x * CELL_SIZE, 1 + starty + y * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE -1);
    ChoisirCouleurDessin(CouleurParNom("black"));
}

pos GetClickPos(int size)
{
    int waiting = 1;

    int sideLength = size * CELL_SIZE;
    int startx = (ECRWIDTH/2) - (sideLength/2);
    int starty = 100;

    int x = -1;
    int y = -1;

    while (waiting)
    {
        if (SourisCliquee())
        {
            waiting = 0;

            if (_X > startx && _X < (startx + sideLength)) /* Verification si la souris est dans la zone de jeu en x */
            {
                x = (_X - startx) / CELL_SIZE; /* Calcul de la case en x */
            }

            if (_Y > starty && _Y < (starty + sideLength)) /* Verification si la souris est dans la zone de jeu en y */
            {
                y = (_Y - starty) / CELL_SIZE; /* Calcul de la case en x */
            }
        }
    }

    pos result = {x, y};
    return result;
}

void SetGameStatus(char text[]) /* Permet d'afficher du texte en haut de l'ecran A UTILISER SEULEMENT SUR L'ECRAN JEU */
{
    ChoisirCouleurDessin(CouleurParNom("white"));
    RemplirRectangle(0, 0, ECRWIDTH, 60);
    ChoisirCouleurDessin(CouleurParNom("black"));
    EcrireTexteCentre(50, text, 1);
}
