#Author: Daniel Koelzer
#Course:	CSCE 1040
#Assignment: HW3
#Date: 10/30/20

CC = g++

output: Patron.o LibraryItem.o Book.o CD.o DVD.o Loan.o Patrons.o LibraryItems.o Loans.o main.o 
	$(CC) -o output main.o Patron.o LibraryItem.o Book.o CD.o DVD.o Loan.o Patrons.o LibraryItems.o Loans.o
	
main.o: main.cpp Patron.h Book.h Loan.h Patrons.h LibraryItems.h Loans.h
	$(CC) -c main.cpp
	
LibraryItem.o: LibraryItem.cpp LibraryItem.h
	$(CC) -c LibraryItem.cpp
	
Patron.o: Patron.cpp Patron.h
	$(CC) -c Patron.cpp

Book.o: Book.cpp Book.h
	$(CC) -c Book.cpp
	
CD.o: CD.cpp CD.h
	$(CC) -c CD.cpp
	
DVD.o: DVD.cpp DVD.h
	$(CC) -c DVD.cpp

Loan.o: Loan.cpp Loan.h
	$(CC) -c Loan.cpp
	
Patrons.o: Patrons.cpp Patrons.h Patron.h Book.h LibraryItems.h Loan.h Loans.h
	$(CC) -c Patrons.cpp
	
LibraryItems.o: LibraryItems.cpp LibraryItems.h Book.h Patron.h Patrons.h Loan.h Loans.h
	$(CC) -c LibraryItems.cpp
	
Loans.o: Loans.cpp Loans.h Loan.h Patron.h Patrons.h  Book.h LibraryItems.h
	$(CC) -c Loans.cpp
	
clean:
	-rm output *.o