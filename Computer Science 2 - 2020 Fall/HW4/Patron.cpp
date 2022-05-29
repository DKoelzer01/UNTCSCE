/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW4
	Date: 11/24/20
*/

#include "Patron.h"

Patron::Patron()
{
	name = "NONE";
	id = -1;
	fineBalance = 0;
	numItems = 0;
}

Patron::Patron(string _name, int _id, double _bal, int _numItems)
{
	name = _name;
	id = _id;
	fineBalance = _bal;
	numItems = _numItems;
}

bool Patron::isEmpty()
{
	return((name == "NONE") && (id == -1) && (fineBalance == 0) && (numItems == 0));
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

int& Patron::getNumItems()
{
	return numItems;
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

void Patron::setNumItems(int _numItems)
{
	numItems = _numItems;
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
	printf("|Items Out: %52d|\n", getNumItems());

	cout << "O";
	for(int i = 0; i < 63; i++)
		{
			cout << '-';
		}
	cout << "O" << endl << endl;
}