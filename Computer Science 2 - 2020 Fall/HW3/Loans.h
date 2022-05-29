/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW3
	Date: 10/30/20
*/

#ifndef LOANS_H
#define LOANS_H
#include <algorithm>
#include <vector>
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <string>
#include "Patron.h"
#include "Loan.h"
#include "Books.h"

class Patrons;

using namespace std;
using std::chrono::system_clock;
class Loans
{
private:
	vector<Loan> loanVector;
	Patrons* patronDatabase;
	Books* bookDatabase;
public:
	Loans();

	Loan emptyLoan;

	vector<Loan>* getLoanVector();

	void checkOutBook();
	void checkInBook(Loan* target, int id);
	void recheckBook(Loan* target);

	Loan* searchLoan(int id);
	void listOverdue();
	void listPatronBooks(Patron* target);

	void updateLoanStatus();

	void reportLost();

	void drawMenu();
	void menu(Patrons* patronDB,Books* bookDB);

	void setPatronDatabase(Patrons* patrons);
	void setBookDatabase(Books* books);
	Patrons* getPatronDatabase();
	Books* getBookDatabase();
};
#endif

