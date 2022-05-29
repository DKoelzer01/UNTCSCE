/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW3
	Date: 10/30/20
*/

#ifndef LIBRARYITEMS_H
#define LIBRARYITEMS_H
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

#include "LibraryItem.h"
#include "Book.h"
#include "CD.h"
#include "DVD.h"

class Loans;
class Patrons;

using namespace std;
class LibraryItems
{
private:
	vector<LibraryItem*> LibraryItemVector;
public:
	LibraryItems();
	vector<LibraryItem*>* getLibraryItemVector();

	LibraryItem emptyItem;
	
	void addItem();
	void addBook();
	void addCD();
	void addDVD();
	
	void editItem(LibraryItem* target);
	void deleteItem(LibraryItem* target, int id, Loans* loanDB);
	LibraryItem* searchItem();
	LibraryItem* searchItem(int id);
	void printAllItems();

	void drawMenu();
	void menu(Patrons* patronDB, Loans* loanDB);
};
#endif

#include "Loans.h"
#include "Patrons.h"