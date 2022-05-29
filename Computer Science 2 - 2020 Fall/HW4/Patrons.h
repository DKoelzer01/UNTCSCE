/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW4
	Date: 11/24/20
*/

#ifndef PATRONS_H
#define PATRONS_H
#include "Patron.h"
#include "LibraryItems.h"
#include "Loans.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
class Patrons
{
private:
	vector<Patron> patronVector;
public:
	Patron emptyPatron;
	Patrons();
	void addPatron();
	void editPatron(Patron* target);
	void deletePatron(Patron* target, int id, Loans* loanDB, LibraryItems* itemDB);

	bool findId(int id);

	Patron* searchPatron(string _name);
	Patron* searchPatron(int _id);

	void printAllPatrons();

	void payFines(Patron* target);

	void drawMenu();
	void menu(Loans* loanDatabase,LibraryItems* itemDatabase);
};
#endif