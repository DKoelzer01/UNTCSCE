/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW3
	Date: 10/30/20
*/

#ifndef PATRON_H
#define PATRON_H
#include <iostream>
#include <string>

using namespace std;
class Patron
{
private:
	string name;
	int id;
	double fineBalance;
	int numBooks;
public:
	Patron();
	Patron(string _name, int _id, double _bal, int _numBooks);
	string& getName();
	int& getId();
	double& getBalance();
	int& getNumBooks();

	void setName(string name);
	void setId(int id);
	void setBalance(double balance);
	void setNumBooks(int numBooks);

	void printPatron();
	bool isEmpty();
};
#endif