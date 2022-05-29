/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW3
	Date: 10/30/20
*/

#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <map>
#include <string>

enum status
{
	ERROR = -1,
	IN,
	OUT,
	REPAIR,
	LOST
};

using namespace std;

class Book
{
private:
	string author;
	string title;
	int isbn;
	int id;
	double cost;
	status curStatus;
public:
	Book();
	Book(string _auth, string _title, int _isbn, int _id, double _cost, status _status);

	bool isEmpty();

	ostream& operator<<(ostream& out);

	void setAuthor(string _author);
	void setTitle(string _title);
	void setISBN(int _isbn);
	void setId(int _id);
	void setCost(double _cost);
	void setStatus(status newStatus);

	string getAuthor();
	string getTitle();
	int getISBN();
	int getId();
	double getCost();
	status getStatus();

	void printBook();
};
#endif