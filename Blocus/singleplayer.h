#ifndef SINGLEPLAYER_H /* Protections inclusions multiples */
#define SINGLEPLAYER_H

int IsCellFree(element* first, int x, int y, int grid_size, game_p players); /* Detecte si la case est libre */

game_p MovementRobot(int g_size, game_p players, element* cross_list); /* Déplacement du robot */

game_p SetupPositions(int g_size); /* Placement des deux pions de départ */

element* CrossRobot(int g_size, game_p players, element* cross_list); /* Placement d'une croix par le robot sur le plateau */

#endif /* SINGLEPLAYER_H */