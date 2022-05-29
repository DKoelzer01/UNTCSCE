/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW4
	Date: 11/24/20
*/

#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H
#include <iostream>
#include <iomanip>
#include <string>

enum status
{
	ERROR = -1,
	IN,
	OUT,
	LOST,
};

enum itemType
{
	NONE = -1,
	BOOK,
	COMPACTDISC,
	DIGITALVERSATILEDISC
};

using namespace std;

class LibraryItem
{
private:
	virtual ostream& print(ostream&);
protected:
	int id;
	double cost;
	status curStatus;
	itemType libraryItemType;
	int loanPeriod;
public:
	LibraryItem();
	LibraryItem(int _id, double _cost, status _stat, int _loan, itemType _type);
	
	friend ostream& operator<<(ostream& out, LibraryItem& item){
		return item.print(out);
	}

	virtual string getTitle();
	
	int getId();
	double getCost();
	status getStatus();
	int getLoanPeriod();
	itemType getItemType();
	
	void setId(int _id);
	void setCost(double _cost);
	void setStatus(status _stat);
	void setLoanPeriod(int _loan);
	void setItemType(itemType _type);
};
#endif