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
	isbn = -1;
	id = -1;
	cost = -1;
	curStatus = ERROR;
}

Book::Book(string _auth, string _title, int _isbn, int _id, double _cost, status _status)
{
	author = _auth;
	title = _title;
	isbn = _isbn;
	id = _id;
	cost = _cost;
	curStatus = _status;
}

bool Book::isEmpty()
{
	return((author == "NONE") && (title == "NONE") && (isbn == -1) && (id == -1) && (cost == -1) && (curStatus == ERROR));
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

void Book::setId(int _id)
{
	id = _id;
}

void Book::setCost(double _cost)
{
	cost = _cost;
}

void Book::setStatus(status newStatus)
{
	curStatus = newStatus;
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

int Book::getId()
{
	return id;
}

double Book::getCost()
{
	return cost;
}

status Book::getStatus()
{
	return curStatus;
}

void Book::printBook()
{
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
		case(REPAIR):
			status = "REPAIR";
			break;
		case(LOST):
			status = "LOST";
			break;
		default:
			status = "ERROR";
			break;
		}

	cout << "O";
	for(int i = 0; i < 63; i++)
		{
			cout << '-';
		}
	cout << "O" << endl;

	printf("|Title: %56s|\n", getTitle().c_str());
	printf("|Author: %55s|\n", getAuthor().c_str());
	printf("|ISBN: %57d|\n", getISBN());
	printf("|ID: %59d|\n", getId());
	printf("|Cost: %57.2f|\n", getCost());
	printf("|Status: %55s|\n", status.c_str());

	cout << "O";
	for(int i = 0; i < 63; i++)
		{
			cout << '-';
		}
	cout << "O" << endl << endl;
}