/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW3
	Date: 10/30/20
*/

#include "Patron.h"

Patron::Patron()
{
	name = "NONE";
	id = -1;
	fineBalance = 0;
	numBooks = 0;
}

Patron::Patron(string _name, int _id, double _bal, int _numBooks)
{
	name = _name;
	id = _id;
	fineBalance = _bal;
	numBooks = _numBooks;
}

bool Patron::isEmpty()
{
	return((name == "NONE") && (id == -1) && (fineBalance == 0) && (numBooks == 0));
}

string& Patron::getName()
{
	return name;
}

int& Patron::getId()
{
	return id;
}

double& Patron::getBalance()
{
	return fineBalance;
}

int& Patron::getNumBooks()
{
	return numBooks;
}

void Patron::setName(string _name)
{
	name = _name;
}

void Patron::setId(int _id)
{
	id = _id;
}

void Patron::setBalance(double _balance)
{
	fineBalance = _balance;
}

void Patron::setNumBooks(int _numBooks)
{
	numBooks = _numBooks;
}

void Patron::printPatron()
{
	cout << "O";
	for(int i = 0; i < 63; i++)
		{
			cout << '-';
		}
	cout << "O" << endl;

	printf("|Name: %57s|\n", getName().c_str());
	printf("|ID: %59d|\n", getId());
	printf("|Balance: %54.2f|\n", getBalance());
	printf("|Books Out: %52d|\n", getNumBooks());

	cout << "O";
	for(int i = 0; i < 63; i++)
		{
			cout << '-';
		}
	cout << "O" << endl << endl;
}