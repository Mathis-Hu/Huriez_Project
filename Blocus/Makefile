# PT1.1 APL 2020 MAKEFILE

# CHAPITRE 1 : BUT FINAL

but : pt11

# CHAPITRE 2 : VARIABLES

OFILES = display.o \
		 singleplayer.o \
		 multiplayer.o \
         main.o

CC = gcc

CFLAGS = -lgraph -Wall -ansi -g

# CHAPITRE 3 : DEPENDANCES (REGLES IMPLICITES)

multiplayer.o : display.h multiplayer.h

singleplayer.o : display.h multiplayer.h singleplayer.h

display.o : display.h

main.o : display.o multiplayer.o singleplayer.o

#CHAPITRE 4 : DEPENDANCES AVEC COMMANDES

pt11 : $(OFILES)
	$(CC) $(CFLAGS) -o pt11 $(OFILES)

#CHAPITRE 5 : AUTRES BUTS

clean :
	-rm -f $(OFILES) pt11

run : 
	./pt11

#CHAPITRE 6 : BUTS FACTICES

.PHONY : but clean run
