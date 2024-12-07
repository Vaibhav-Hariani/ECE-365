merge.out: merge.o load.o
	g++ -o merge.out merge.o load.o

merge.o: merge.cpp
	g++ -c merge.cpp

load.o: load.cpp
	g++ -c load.cpp

debug:
	g++ -g -o mergeDebug.out merge.cpp load.cpp

clean:
	rm -f *.o *.stackdump *~ *.out