/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW4
	Date: 11/24/20
*/

#include "Loan.h"

Loan::Loan()
{
	loanId = -1;
	itemId = -1;
	patronId = -1;
	hasBeenRechecked = false;
	dueDateAndTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
	isOverdue = false;
}

Loan::Loan(int _loanId, int _itemId, int _patronId, bool _recheckStatus, time_t _dueDate, bool _isOverdue)
{
	loanId = _loanId;
	itemId = _itemId;
	patronId = _patronId;
	hasBeenRechecked = _recheckStatus;
	dueDateAndTime = _dueDate;
	isOverdue = _isOverdue;
}

void Loan::setLoanId(int _loanId)
{
	loanId = _loanId;
}

void Loan::setItemId(int _itemId)
{
	itemId = _itemId;
}

void Loan::setPatronId(int _patronId)
{
	patronId = _patronId;
}

void Loan::setRecheckedStatus(bool state)
{
	hasBeenRechecked = state;
}

void Loan::setDueDate(time_t newDateAndTime)
{
	dueDateAndTime = newDateAndTime;
}

void Loan::setOverdueStatus(bool status)
{
	isOverdue = status;
}

int Loan::getLoanId()
{
	return loanId;
}

int Loan::getItemId()
{
	return itemId;
}

int Loan::getPatronId()
{
	return patronId;
}

bool Loan::getRecheckedStatus()
{
	return hasBeenRechecked;
}

time_t Loan::getDueDate()
{
	return dueDateAndTime;
}

bool Loan::getOverdueStatus()
{
	return isOverdue;
}

void Loan::printLoan()
{
	cout << "O";
	for(int i = 0; i < 63; i++)
		{
			cout << '-';
		}
	cout << "O" << endl;
	time_t time = getDueDate();
	char* newDate = ctime(&time);
	newDate[strlen(newDate)-1] = '\0';

	std::boolalpha;
	printf("|Loan ID: %54d|\n", getLoanId());
	printf("|Item ID: %54d|\n", getItemId());
	printf("|Patron ID: %52d|\n", getPatronId());
	printf("|Due Date: %53s|\n", newDate);
	printf("|Rechecked: %52s|\n", getRecheckedStatus() ? "TRUE" : "FALSE");
	printf("|Overdue: %54s|\n", getOverdueStatus() ? "TRUE" : "FALSE");

	cout << "O";
	for(int i = 0; i < 63; i++)
		{
			cout << '-';
		}
	cout << "O" << endl << endl;
}