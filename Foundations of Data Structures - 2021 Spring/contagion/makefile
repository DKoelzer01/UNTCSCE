contagion: main.o region.o area.o
	g++ -g main.o region.o area.o -o contagion

main.o: main.cpp
	g++ -c -g main.cpp

region.o: region.cpp region.h area.o
	g++ -c -g region.cpp

area.o: area.cpp area.h
	g++ -c -g area.cpp


clean: 
	rm contagion *.o

run: 
	make
	./contagion