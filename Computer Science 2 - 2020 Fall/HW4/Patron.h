/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW4
	Date: 11/24/20
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
	int numItems;
public:
	Patron();
	Patron(string _name, int _id, double _bal, int _numItems);
	string& getName();
	int& getId();
	double& getBalance();
	int& getNumItems();

	void setName(string name);
	void setId(int id);
	void setBalance(double balance);
	void setNumItems(int _numItems);

	void printPatron();
	bool isEmpty();
};
#endif