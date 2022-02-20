#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include "display.h"
#include "multiplayer.h"
#include "singleplayer.h"

int main(int argc, char * argv[])
{
    int replay = 1, gagnant;
    game_p pos_p; /* Coordonnées des pions de la partie */
    
    InitDisplay();

    while (replay)
    {
        gagnant = 0;
        element* list = NULL; /* (Ré)Initialisation de la liste chaînée */
        /* Sélection du mode de jeu et de la taille de la grille */
        select choice = ShowSelectDisplay();
        ShowGameDisplay(choice.size);

        /* Redirection vers le mode correspondant, 0-> Singleplayer, 1-> Multiplayer */
        if (choice.mode==0)
        {
            /* Positionnement de départ des pions */
            pos_p = SetupPositions(choice.size);

            while(gagnant == 0)
            {
                /* Tour du joueur bleu */    
                pos_p = MovementPlayer1(choice.size, pos_p, list);
                list = CrossPlayer1(choice.size, pos_p, list);
                if (EndOfGame(pos_p, pos_p.p2, list, choice.size)) { gagnant = 1; } else
                if (EndOfGame(pos_p, pos_p.p1, list, choice.size)) { gagnant = 2; }
            
                if (gagnant == 0)
                {
                    /* Tour du robot */
                    pos_p = MovementRobot(choice.size, pos_p, list);
                    list = CrossRobot(choice.size, pos_p, list);
                    if (EndOfGame(pos_p, pos_p.p1, list, choice.size)) { gagnant = 2; } else
                    if (EndOfGame(pos_p, pos_p.p2, list, choice.size)) { gagnant = 1; }
                }
                
            }
        }
        else
        {
            
            /* Positionnement de départ des pions */
            pos_p = FirstsPlayersPositions(choice.size);

            while(gagnant == 0)
            {
                /* Tour du joueur bleu */    
                pos_p = MovementPlayer1(choice.size, pos_p, list);
                list = CrossPlayer1(choice.size, pos_p, list);
                if (EndOfGame(pos_p, pos_p.p2, list, choice.size)) { gagnant = 1; } else
                if (EndOfGame(pos_p, pos_p.p1, list, choice.size)) { gagnant = 2; }
            
                if (gagnant == 0)
                {
                    /* Tour du joueur orange */
                    pos_p = MovementPlayer2(choice.size, pos_p, list);
                    list = CrossPlayer2(choice.size, pos_p, list);
                    if (EndOfGame(pos_p, pos_p.p1, list, choice.size)) { gagnant = 2; } else
                    if (EndOfGame(pos_p, pos_p.p2, list, choice.size)) { gagnant = 1; }
                }
                
            }

        }

        SetGameStatus(">> Fin de partie (cliquez pour continuer) <<");
        while(SourisCliquee()==0){}

        replay = ShowResultDisplay(gagnant); /* Affichage du gagnant */

        DeleteList(list); /* Suppression de la liste chaînée */
    }
    
    CloseDisplay();

    return EXIT_SUCCESS;
}
