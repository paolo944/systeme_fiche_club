CC = gcc
FLAGS = -Wall -lm -g
PROG = main
OBJS = adherent.o

$(PROG): $(OBJS)
	$(CC) -o $@ main.c $^ $(FLAGS)

adherent.o: adherent.c adherent.h
	$(CC) -c adherent.c $(FLAGS)

clean:
	rm -f *.o $(PROG)

.PHONY: clean
