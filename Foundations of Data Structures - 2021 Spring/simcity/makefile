sim: main.o region.o residential.o industrial.o commercial.o utility.o cell.o
	g++ -g main.o region.o residential.o industrial.o commercial.o utility.o cell.o -o sim

main.o: main.cpp
	g++ -c -g main.cpp

region.o: region.cpp region.h cell.o
	g++ -c -g region.cpp

residential.o: residential.cpp residential.h cell.o
	g++ -c -g residential.cpp

industrial.o: industrial.cpp industrial.h cell.o
	g++ -c -g industrial.cpp

commercial.o: commercial.cpp commercial.h cell.o
	g++ -c -g commercial.cpp

utility.o: utility.cpp utility.h cell.o
	g++ -c -g utility.cpp

cell.o: cell.cpp cell.h
	g++ -c -g cell.cpp

clean: 
	rm sim *.o

run: 
	make
	./sim