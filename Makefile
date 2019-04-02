all: test_graphe

test_graphe: test_graphe.o graphe.o
	gcc -o test_graphe test_graphe.o graphe.o

graphe.o: graphe.c graphe.h
	gcc -Wall -std=gnu99 -c graphe.c

test_graphe.o: test_graphe.c graphe.h
	gcc -Wall -c test_graphe.c -std=gnu99

clean:
	rm -f *.o test_graphe  *~
