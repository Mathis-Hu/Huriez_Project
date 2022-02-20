#include "ihm.h"
#include<graph.h>


static couleur white,black;

void startIHM(int w,int h){
	InitialiserGraphique();
	CreerFenetre((Maxx()-w)/2,(Maxy()-h)/2,w,h);
	white = CouleurParNom("white");
	black = CouleurParNom("black");
}


void pointIHM(int x,int y,colorIHM c){
	couleur cc = (c == WHITE)?white:black;
	ChoisirCouleurDessin(cc);
	DessinerPixel(x,y);
}

void lineIHM(int x,int y,int xx,int yy,colorIHM c){
	couleur cc = (c == WHITE)?white:black;
	ChoisirCouleurDessin(cc);
	DessinerSegment(x,y,xx,yy);
}

void endIHM(){
	FermerGraphique();
}
unsigned long microsecondesIHM(){
	return Microsecondes();
}
