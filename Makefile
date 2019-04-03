CC = gcc
CO = -Wall

EXEC = test_graphe

all: $(EXEC)

test_graphe: test_graphe.o graphe.o file.o
	$(CC) $(CO) -o $@ $^

graphe.o: graphe.c file.h graphe.h
	$(CC) $(CO) -std=gnu99 -c $<

test_graphe.o: test_graphe.c file.h
	$(CC) $(CO) -c $< -std=gnu99

file.o: file.c file.h graphe.h
	$(CC) $(CO) -c $< -std=gnu99


clean:
	rm -f *.o $(EXEC)  *~
