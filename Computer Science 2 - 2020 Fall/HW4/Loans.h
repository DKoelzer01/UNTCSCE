/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW4
	Date: 11/24/20
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
#include "LibraryItems.h"

class Patrons;

using namespace std;
using std::chrono::system_clock;
class Loans
{
private:
	vector<Loan> loanVector;
	Patrons* patronDatabase;
	LibraryItems* itemDatabase;
public:
	Loans();

	Loan emptyLoan;
	LibraryItem emptyItem;

	vector<Loan>* getLoanVector();

	void checkOut();
	void checkIn(Loan* target, int id);
	void recheck(Loan* target);

	Loan* searchLoan(int id);
	void listOverdue();
	void listPatronItems(Patron* target);

	void updateLoanStatus();

	void reportLost();

	void drawMenu();
	void menu(Patrons* patronDB,LibraryItems* itemDB);

	void setPatronDatabase(Patrons* patrons);
	void setItemDatabase(LibraryItems* items);
	Patrons* getPatronDatabase();
	LibraryItems* getItemDatabase();
};
#endif

