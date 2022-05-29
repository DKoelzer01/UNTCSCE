/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW4
	Date: 11/24/20
*/

#ifndef LOAN_H
#define LOAN_H
#include <iostream>
#include <cstring>
#include <string>
#include <chrono>
#include <ctime>
#include <ratio>

using namespace std;
class Loan
{
private:
	int loanId;
	int itemId;
	int patronId;
	bool hasBeenRechecked;
	time_t dueDateAndTime;
	bool isOverdue;
public:
	Loan();
	Loan(int _loanId, int _itemId, int _patronId, bool _recheckStatus, time_t _dueDate, bool _isOverdue);

	void setLoanId(int _loanId);
	void setItemId(int _itemId);
	void setPatronId(int _patronId);
	void setRecheckedStatus(bool state);
	void setDueDate(time_t newDateAndTime);
	void setOverdueStatus(bool status);

	int getLoanId();
	int getItemId();
	int getPatronId();
	bool getRecheckedStatus();
	time_t getDueDate();
	bool getOverdueStatus();

	void printLoan();
};
#endif