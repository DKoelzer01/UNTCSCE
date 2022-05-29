/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW3
	Date: 10/30/20
*/

#include "Book.h"

Book::Book()
{
	author = "NONE";
	title = "NONE";
	category = "NONE";
	isbn = -1;
	id = -1;
	cost = -1;
	curStatus = IN;
	libraryItemType = BOOK;
}

Book::Book(string _auth, string _title,string _cat, int _isbn, int _id, double _cost, status _status)
{
	author = _auth;
	title = _title;
	category = _cat;
	isbn = _isbn;
	id = _id;
	cost = _cost;
	curStatus = _status;
	libraryItemType = BOOK;
}

bool Book::isEmpty()
{
	return((author == "NONE") && (title == "NONE")&& (category == "NONE") && (isbn == -1) && (id == -1) && (cost == -1) && (curStatus == IN));
}

void Book::setAuthor(string _author)
{
	author = _author;
}

void Book::setTitle(string _title)
{
	title = _title;
}

void Book::setISBN(int _isbn)
{
	isbn = _isbn;
}

void Book::setCategory(string _cat) {
	category = _cat;
}


string Book::getAuthor()
{
	return author;
}

string Book::getTitle()
{
	return title;
}

int Book::getISBN()
{
	return isbn;
}

string Book::getCategory() {
	return category;
}

ostream& Book::print(ostream& out){
	string status;
	int temp = getStatus();
	switch(temp)
		{
		case(IN):
			status = "IN";
			break;
		case(OUT):
			status = "OUT";
			break;
		case(LOST):
			status = "LOST";
			break;
		default:
			status = "ERROR";
			break;
		}

	out << "O";
	for(int i = 0; i < 63; i++)
		{
			out << '-';
		}
	out << "O" << endl;
	
	out << "|Title: ";
	out << setw(56);
	out << getTitle();
	out << "|\n";
	
	out << "|Author: ";
	out << setw(55);
	out << getAuthor();
	out << "|\n";

	out << "|Category: ";
	out << setw(53);
	out << getCategory();
	out << "|\n";
	
	out << "|ISBN: ";
	out << setw(57);
	out << getISBN();
	out << "|\n";

	out << "|ID: ";
	out << setw(59);
	out << getId();
	out << "|\n";
	
	out << "|Cost: ";
	out << setw(57);
	out << setprecision(2);
	out << getCost();
	out << "|\n";

	out << "|Status: ";
	out << setw(55);
	out << status;
	out << "|\n";
	
	out << "O";
	for(int i = 0; i < 63; i++)
		{
			out << '-';
		}
	out << "O" << endl;
}



	
	
