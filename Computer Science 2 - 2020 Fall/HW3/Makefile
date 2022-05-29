#Author: Daniel Koelzer
#Course:	CSCE 1040
#Assignment: HW3
#Date: 10/30/20

CC = g++

output: Patron.o Book.o Loan.o Patrons.o Books.o Loans.o main.o 
	$(CC) -o output main.o Patron.o Book.o Loan.o Patrons.o Books.o Loans.o
	
main.o: main.cpp Patron.h Book.h Loan.h Patrons.h Books.h Loans.h
	$(CC) -c main.cpp
	
Patron.o: Patron.cpp Patron.h
	$(CC) -c Patron.cpp

Book.o: Book.cpp Book.h
	$(CC) -c Book.cpp

Loan.o: Loan.cpp Loan.h
	$(CC) -c Loan.cpp
	
Patrons.o: Patrons.cpp Patrons.h Patron.h Book.h Books.h Loan.h Loans.h
	$(CC) -c Patrons.cpp
	
Books.o: Books.cpp Books.h Book.h Patron.h Patrons.h Loan.h Loans.h
	$(CC) -c Books.cpp
	
Loans.o: Loans.cpp Loans.h Loan.h Patron.h Patrons.h  Book.h Books.h
	$(CC) -c Loans.cpp
	
clean:
	-rm output *.o