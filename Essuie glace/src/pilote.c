#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

// Valeur static du PID
static pid_t f_pid;

/* Variable global permettant de suivre le mode actuel des essuis glace :
*	0 = Arrêt
*	1 = Lent
*	2 = Rapide
*	3 = Impulsion
*/
static int MODE;

// Variable global définissant le nombre de secondes entre chaque impulsion
static int PULSE;

// Variable global définissant si les commentaires sont activés (=1) ou non (=0) pendant l'exécution
static int COMMENT;

// Gère l'envoi des impulsions, non accessible par l'utilisateur via commandes 
void SIGALRM_handler(){
	kill(f_pid, SIGUSR1);
	alarm(PULSE);
}

// Commande -
void SIGTSTP_handler(){
	
	// Passage du mode rapide au mode lent
	if (MODE == 2){
		kill(f_pid, SIGHUP);
		MODE = 1;
		if(COMMENT == 1) printf(" = ' - ' : Mode = Lent\n");

	// Passage du mode lent au mode impulsion
	}else if (MODE == 1){
		kill(f_pid, SIGUSR2);
		alarm(PULSE);
		MODE = 3;
		if(COMMENT == 1) printf(" = ' - ' : Mode = Impulsion | Intervalle = %d\n", PULSE);


	// Passage du mode impulsion à l'arrêt ou augmente le temps entre impulsions
	}else if (MODE == 3){
		if (PULSE == 10){
			kill(f_pid, SIGUSR2);
			MODE = 0;
			alarm(0);
			if(COMMENT == 1) printf(" = ' - ' : Mode = Arrêt\n");
			kill(f_pid, SIGUSR2);

		}else{
			PULSE++;
			if(COMMENT == 1) printf(" = ' - ' : Intervalle = %d\n", PULSE);
		}
	}
}

// Commande +
void SIGQUIT_handler(){
	
	// Passage du mode lent au mode rapide
	if (MODE == 1){
		kill(f_pid, SIGPIPE);
		MODE = 2;
		if(COMMENT == 1) printf(" = ' + ' : Mode = Rapide\n");

	// Passage du mode impulsion au mode lent ou diminue le temps entre impulsions
	}else if (MODE == 3){
		if (PULSE == 3){
			kill(f_pid, SIGHUP);
			MODE = 1;
			alarm(0);
			if(COMMENT == 1) printf(" = ' + ' : Mode = Lent\n");
		}else{
			PULSE--;
			if(COMMENT == 1) printf(" = ' + ' : Intervalle = %d\n", PULSE);
		}
	}
}

// Commande M/A
void SIGINT_handler(){
	
	kill(f_pid, SIGUSR2);
	// Passage du mode arrêt au mode lent
	if (MODE == 0){
		MODE = 1;
		// Reinitialise le nombre de secondes entre chaque impulsion à la mise en marche des essuies glaces
		PULSE = 3;
		// Reinitialise le signal d'alarme
		alarm(0);
		if(COMMENT == 1) printf(" = 'M/A' : Mode = Lent\n");

	// Passage au mode arrêt (peu importe le mode)
	}else{
		if (MODE == 3) kill(f_pid, SIGUSR2);
		alarm(0);
		MODE = 0;
		if(COMMENT == 1) printf(" = 'M/A' : Mode = Arrêt\n");

	}
}

int main(int argc, char *argv[]){
	printf("Commandes : | Ctrl+C = 'M/A' | Ctrl+Z = '-' | Ctrl+AltGr+\\ = '+' |\n");
	printf("(Activer les commentaires : './pilote -c')\n");
	
	char *c = argv[1];

	// Commentaires ou non
	COMMENT = 0;
	if (argc == 2){
		if (strcmp(argv[1], "-c") == 0){
			printf("~ Commentaires activés ~\n");
			COMMENT = 1;
		}
	}

	f_pid = fork();
	MODE = 0;
	int *ptr;
	if (f_pid == -1){
		printf("Erreur : fork()\n");
		exit(1);
	}else if (f_pid == 0) {
		execl("./simul", NULL);	
	}else{

		// Signal depuis Ctrl+C
		signal(SIGINT, SIGINT_handler);
		// Signal depuis Ctrl+X
		signal(SIGQUIT, SIGQUIT_handler);
		// Signal depuis Ctrl+Z
		signal(SIGTSTP, SIGTSTP_handler);
		// Signal depuis un appel alarm()
		signal(SIGALRM, SIGALRM_handler);

		wait(ptr);
	}
	return 0;
}