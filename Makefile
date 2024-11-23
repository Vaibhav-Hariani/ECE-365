Djikstra.out: Djikstra.o heap.o hash.o graph.o
	g++ -o Djikstra.out Djikstra.o heap.o hash.o graph.o

Djikstra.o: Djikstra.cpp
	g++ -c Djikstra.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

debug:
	g++ -g -o DjikstraDebug.out Djikstra.cpp heap.cpp hash.cpp graph.cpp

clean:
	rm -f *.o *.stackdump *~ *.out

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
