/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW4
	Date: 11/24/20
*/

#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include "LibraryItem.h"

using namespace std;

class Book: public LibraryItem
{
private:
	string author;
	string title;
	int isbn;
	string category;
public:
	Book();
	Book(string _auth, string _title, string _cat, int _isbn, int _id, double _cost, status _status);

	bool isEmpty();

	ostream& print(ostream& out) override;

	void setAuthor(string _author);
	void setTitle(string _title);
	void setISBN(int _isbn);
	void setCategory(string _cat);

	string getCategory();
	string getAuthor();
	string getTitle();
	int getISBN();
};
#endif