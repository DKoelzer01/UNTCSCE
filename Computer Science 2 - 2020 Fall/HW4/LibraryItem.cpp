/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW4
	Date: 11/24/20
*/

#include "LibraryItem.h"

LibraryItem::LibraryItem()
{
id = -1;
cost = 0;
curStatus = ERROR;
loanPeriod = 0;
libraryItemType = NONE;
}
LibraryItem::LibraryItem(int _id, double _cost, status _stat, int _loan, itemType _type)
{
id = _id;
cost = _cost;
curStatus = _stat;
loanPeriod = _loan;
libraryItemType = _type;
}

int LibraryItem::getId()
{
	return id;
}
double LibraryItem::getCost()
{
	return cost;
}
status LibraryItem::getStatus()
{
	return curStatus;
}
int LibraryItem::getLoanPeriod()
{
	return loanPeriod;
}
itemType LibraryItem::getItemType() {
	return libraryItemType;
}

string LibraryItem::getTitle() {
	return "null";
}

void LibraryItem::setId(int _id)
{
	id = _id;
}
void LibraryItem::setCost(double _cost)
{
	cost = _cost;
}
void LibraryItem::setStatus(status _stat)
{
	curStatus = _stat;
}
void LibraryItem::setLoanPeriod(int _loan)
{
	loanPeriod = _loan;
}
void LibraryItem::setItemType(itemType _type) {
	libraryItemType = _type;
}

ostream& LibraryItem::print(ostream& out)
{
	out << "PARENT PRINT FUNCTION" << endl;
}