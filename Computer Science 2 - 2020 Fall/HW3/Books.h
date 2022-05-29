/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW3
	Date: 10/30/20
*/

#ifndef BOOKS_H
#define BOOKS_H
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include "Book.h"

class Loans;
class Patrons;

using namespace std;
class Books
{
private:
	vector<Book> bookVector;
public:
	Books();
	vector<Book>* getBookVector();

	Book emptyBook;

	void addBook();
	void editBook(Book* target);
	void deleteBook(Book* target, int id, Loans* loanDB);
	Book* searchBook(string input);
	Book* searchBook(int id);
	void printAllBooks();

	void drawMenu();
	void menu(Patrons* patronDB, Loans* loanDB);
};
#endif

#include "Loans.h"
#include "Patrons.h"