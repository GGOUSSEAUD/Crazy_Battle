CC=gcc
SRC=affiche.c initialisation.c deroulement.c main.c
OBJ=$(SRC:.c=.o)
FLAGS=-Wall -g 
LIBS=header.h

bataille:  $(OBJ) $(LIBS)
	$(CC) -o $@ $^

%.o:	%.c
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o *~ core

