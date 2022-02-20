#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "multiplayer.h"


/* Début de partie */


game_p FirstsPlayersPositions(int g_size) /* Placement des deux pions de départ */
{
   game_p players;

   SetGameStatus("Positionnement du joueur bleu :");
   do
   {
      players.p1 = GetClickPos(g_size);
   }
   while(players.p1.x == -1 || players.p1.y == -1); /* Un pion ne peut pas être en dehors du plateau */

   DisplayPlayer(players.p1.x, players.p1.y, g_size, 0);
   
   SetGameStatus("Positionnement du joueur orange :");
   do
   {
      players.p2 = GetClickPos(g_size);
   }
   while
   (
      players.p2.x == -1 || players.p2.y == -1 
      
      /* Un pion ne peut pas être sur une case déjà occupé par un pion */
      || (players.p2.x == players.p1.x && players.p2.y == players.p1.y)
   );

   DisplayPlayer(players.p2.x, players.p2.y, g_size, 1);

   return players;
}


/* Tour des joueurs */


game_p MovementPlayer1(int g_size, game_p players, element* cross_list) /* Déplacement du joueur 1 */
{
   game_p temp_pos;

   /* variable de position pour comparaison entre les anciennes et nouvelles coordonnées */
   temp_pos = players;
   
   SetGameStatus("Deplacement du joueur bleu :");

   do
   {
      players.p1 = GetClickPos(g_size);
   }
   while
   (
      /* Un pion ne peut pas se déplacer en dehors du plateau */
      players.p1.x == -1 || players.p1.y == -1 

      /* Un pion ne peut pas se déplacer sur une case déjà occupé par un pion */
      || (players.p1.x == players.p2.x && players.p1.y == players.p2.y)
      
      /* Un pion ne peut pas rester sur place */
      || (players.p1.x == temp_pos.p1.x && players.p1.y == temp_pos.p1.y)

      /* Un pion ne peut se déplacer que sur une case adjacente */
      || (
            (
               players.p1.x != temp_pos.p1.x+1 
               && players.p1.x != temp_pos.p1.x-1 
               && players.p1.x != temp_pos.p1.x
            ) 
         ||
            (
               players.p1.y != temp_pos.p1.y-1 
               && players.p1.y != temp_pos.p1.y+1 
               && players.p1.y != temp_pos.p1.y
            )
         )

      /* Un pion ne peut pas se déplacer sur une croix */
      || BlockedCase(cross_list, players.p1)
   );

   EraseCell(temp_pos.p1.x, temp_pos.p1.y, g_size);
   DisplayPlayer(players.p1.x, players.p1.y, g_size, 0);

   return players;
}

element* CrossPlayer1(int g_size, game_p players, element* cross_list) /* Placement d'une croix du joueur 1 sur la carte */
{
   game_p crosses;

   SetGameStatus("Positionnement d'une croix du joueur bleu :");

   do
   {
      crosses.p1 = GetClickPos(g_size);
   }
   while
   (
      /* Une croix ne peut pas être placer en dehors du plateau */
      crosses.p1.x == -1 || crosses.p1.y == -1 
      
      /* Une croix ne peut pas être placer sur un joueur */
      || (crosses.p1.x == players.p1.x && crosses.p1.y == players.p1.y)
      || (crosses.p1.x == players.p2.x && crosses.p1.y == players.p2.y)

      /* Une croix ne peut pas être placer sur une autre croix */
      || BlockedCase(cross_list, crosses.p1)
   );

   DisplayCross(crosses.p1.x, crosses.p1.y, g_size, 0);
   cross_list = AddElement(cross_list, crosses.p1);

   return cross_list;
}

game_p MovementPlayer2(int g_size, game_p players, element* cross_list) /* Déplacement du joueur 2 */
{
   game_p temp_pos;

   temp_pos = players;

   SetGameStatus("Deplacement du joueur orange :");

   do
   {
      players.p2 = GetClickPos(g_size);
   }
   while
   (
      players.p2.x == -1 || players.p2.y == -1 
      || (players.p2.x == players.p1.x && players.p2.y == players.p1.y)
      || (players.p2.x == temp_pos.p2.x && players.p2.y == temp_pos.p2.y)
      || (
            (
               players.p2.x != temp_pos.p2.x+1 
               && players.p2.x != temp_pos.p2.x-1 
               && players.p2.x != temp_pos.p2.x
            ) 
         ||
            (
               players.p2.y != temp_pos.p2.y-1 
               && players.p2.y != temp_pos.p2.y+1 
               && players.p2.y != temp_pos.p2.y
            )
         )
      || BlockedCase(cross_list, players.p2)
   );

   EraseCell(temp_pos.p2.x, temp_pos.p2.y, g_size);
   DisplayPlayer(players.p2.x, players.p2.y, g_size, 1);

   return players;
}

element* CrossPlayer2(int g_size, game_p players, element* cross_list) /* Placement d'une croix du joueur 2 sur la carte */
{
   game_p crosses;

   SetGameStatus("Positionnement d'une croix du joueur orange :");

   do
   {
      crosses.p2 = GetClickPos(g_size);
   }
   while
   (
      crosses.p2.x == -1 || crosses.p2.y == -1 
      || (crosses.p2.x == players.p2.x && crosses.p2.y == players.p2.y)
      || (crosses.p2.x == players.p1.x && crosses.p2.y == players.p1.y)
      || BlockedCase(cross_list, crosses.p2)
   );

   DisplayCross(crosses.p2.x, crosses.p2.y, g_size, 1);
   cross_list = AddElement(cross_list, crosses.p2);

   return cross_list;
}


/* Fonctions de la liste chaînée */


element* AddElement(element* previous, pos coord)
{
   element* p = (element*) malloc(sizeof(element));

   if (p)
   {
      p->next = previous;
      p->coord = coord;
   }
   return p;
}

int BlockedCase(element* first, pos co_watched)
{
   element* p = (element*) malloc(sizeof(element));
   int blocked=0;
   for (p = first; p != NULL; p = p->next)
   {
      if(co_watched.x == p->coord.x && co_watched.y == p->coord.y)
      {
         blocked=1;
      }
   }         
   return blocked;
}

void DeleteList(element* p)
{
   element* next;

   while (p != NULL)
   {
      next = p->next;
      free(p);
      p = next;
   }
}

int EndOfGame(game_p players, pos coord_watched, element* cross_list, int g_size)
{
   int i, countBC = 0; /* Compteur des cases inaccessibles */
   pos tabcoord[8]; /* Tableau répertoriant les coordonnées des cases adjacentes au pion */

   /* Affectation des valeurs des cases adjacentes au tableau */
   coord_watched.x -= 1;
   coord_watched.y -= 1;
   tabcoord[0] = coord_watched;
   /* x=-1 y=-1 -> haut gauche */

   coord_watched.x++;
   tabcoord[1] = coord_watched;
   /* x=0 y=-1 -> haut milieu */
   
   coord_watched.x++;
   tabcoord[2] = coord_watched;
   /* x=+1 y=-1 -> haut droite */
   
   coord_watched.y++;
   tabcoord[3] = coord_watched;
   /* x=+1 y=0 -> milieu droite */
   
   coord_watched.y++;
   tabcoord[4] = coord_watched;
   /* x=+1 y=+1 -> bas droite */
   
   coord_watched.x--;
   tabcoord[5] = coord_watched;
   /* x=0 y=+1 -> bas milieu */
   
   coord_watched.x--;
   tabcoord[6] = coord_watched;
   /* x=-1 y=+1 -> bas gauche */
   
   coord_watched.y--;
   tabcoord[7] = coord_watched;
   /* x=-1 y=0 -> milieu gauche */

   for (i = 0; i < 8; i++)
   {  
      /* Test pour savoir si la case désignée est inaccessible */
      if
      (
         BlockedCase(cross_list, tabcoord[i])
         
         || (tabcoord[i].x == -1 || tabcoord[i].y == -1)
         || (tabcoord[i].x == g_size || tabcoord[i].y == g_size)

         || (tabcoord[i].x == players.p1.x && tabcoord[i].y == players.p1.y)
         || (tabcoord[i].x == players.p2.x && tabcoord[i].y == players.p2.y)
      )
      {
         countBC++;
      }

   }

   /* Test permettant de savoir si toute les cases adjacentes sont bloqué */
   if (countBC == 8)
   {
      return 1;
   }
   else
   {
      return 0;
   }
   
}