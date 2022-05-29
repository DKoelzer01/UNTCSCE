/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW3
	Date: 10/30/20
*/

#include "Loan.h"

Loan::Loan()
{
	loanId = -1;
	bookId = -1;
	patronId = -1;
	hasBeenRechecked = false;
	dueDateAndTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
	isOverdue = false;
}

Loan::Loan(int _loanId, int _bookId, int _patronId, bool _recheckStatus, time_t _dueDate, bool _isOverdue)
{
	loanId = _loanId;
	bookId = _bookId;
	patronId = _patronId;
	hasBeenRechecked = _recheckStatus;
	dueDateAndTime = _dueDate;
	isOverdue = _isOverdue;
}

void Loan::setLoanId(int _loanId)
{
	loanId = _loanId;
}

void Loan::setBookId(int _bookId)
{
	bookId = _bookId;
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

int Loan::getBookId()
{
	return bookId;
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
	printf("|Book ID: %54d|\n", getBookId());
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