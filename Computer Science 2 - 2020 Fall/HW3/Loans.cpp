/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW3
	Date: 10/30/20
*/

#include "Loans.h"
#include "Patrons.h"

chrono::duration<int,std::ratio<60*60*24> > one_day (1);

Loans::Loans()
{
	vector<Loan> loanVector;
}

vector<Loan>* Loans::getLoanVector()
{
	return &loanVector;
}

void Loans::setPatronDatabase(Patrons* patrons)
{
	patronDatabase = patrons;
}

void Loans::setBookDatabase(Books* books)
{
	bookDatabase = books;
}

Patrons* Loans::getPatronDatabase()
{
	return patronDatabase;
}

Books* Loans::getBookDatabase()
{
	return bookDatabase;
}

void Loans::checkOutBook()
{
	time_t newDate = system_clock::to_time_t(system_clock::now() + (one_day * 10));
	string::size_type sz;
	Patrons* patronDB = getPatronDatabase();
	Books* bookDB = getBookDatabase();
	Patron* patron;
	Book* book;
	int tempInt;
	int patronId;
	int bookId;
	string tempString;
	cin.clear();
	tempString = "";
	tempInt = 0;
	cout << "Enter a Patron ID, or press Q to quit\n";
	getline(cin,tempString);
	if(tempString[0] == 'Q' || tempString[0] == 'q')
		{
			cout << "Aborted.\n";
			return;
		}
	tempInt = stoi(tempString,&sz);
	cin.clear();

	if(patronDB->findId(tempInt))
		{
			patron = patronDB->searchPatron(tempInt);
			patronId = tempInt;
		}
	else
		{
			cout << "No matches found.\n";
			return;
		}

	if(patron->getNumBooks() >= 5)
		{
			cout << "This patron is at the maximum of 5 loaned books.\n";
			return;
		}

	cout << "Enter a book Title/Author/ID: \n";
	getline(cin,tempString);
	if(isalpha(tempString[0]))
		{
			book = bookDB->searchBook(tempString);
		}
	else
		{
			book = bookDB->searchBook(stoi(tempString,&sz));
		}

	if(book->isEmpty())
		{
			cout << "Null book.\n";
			return;
		}
	if(book->getStatus() != IN)
		{
			cout << "Book is currently unavailable.\n";
			return;
		}
	Loan tempLoan;
	unsigned i = 0;
	while(true)
		{
			for(unsigned j = 0; j < loanVector.size(); j++)
				{
					if(loanVector.at(j).getLoanId() == i)
						{
							i++;
							j=0;
						}
				}
			tempLoan.setLoanId(i);
			break;
		}
	tempLoan.setBookId(book->getId());
	tempLoan.setPatronId(patronId);
	tempLoan.setDueDate(newDate);
	tempLoan.setOverdueStatus(false);
	tempLoan.setRecheckedStatus(false);

	patron->setNumBooks(patron->getNumBooks() + 1);

	loanVector.push_back(tempLoan);

	cout << "Successfully added Loan to database." << endl;
	cin.ignore(1);
}

void Loans::checkInBook(Loan* target, int id)
{
	Patrons* patronDB = getPatronDatabase();
	Books* bookDB = getBookDatabase();
	bookDB->searchBook(target->getBookId())->setStatus(IN);
	patronDB->searchPatron(target->getPatronId())->setNumBooks(patronDB->searchPatron(target->getPatronId())->getNumBooks() -1);
	for(unsigned i = 0; i < loanVector.size(); i++)
		{
			if(loanVector.at(i).getLoanId() == id)
				{
					loanVector.erase(loanVector.begin() + i);
				}
		}
}
void Loans::recheckBook(Loan* target)
{
	time_t newDate = system_clock::to_time_t(system_clock::now() + (one_day * 10));
	if(!target->getRecheckedStatus())
		{
			target->setRecheckedStatus(true);
			target->setDueDate(newDate);
			cout << "Book rechecked." << endl;
		}
	else
		{
			cout << "This book has already been rechecked.\n";
		}
}

Loan* Loans::searchLoan(int id)
{
	if(loanVector.size() == 0)
		{
			cout << "Error, no patrons in database." << endl;
			return &emptyLoan;
		}
	for(unsigned i = 0; i < loanVector.size(); i++)
		{
			if(loanVector.at(i).getLoanId() == id)
				{
					return &loanVector.at(i);
				}
		}
	return &emptyLoan;
}
void Loans::listOverdue()
{
	if(loanVector.size() == 0)
		{
			cout << "Error, no loans in database." << endl;
			return;
		}
	vector<Loan*> overdue;
	int j = 0;
	for(unsigned i = 0; i < loanVector.size(); i++)
		{
			if(loanVector.at(i).getOverdueStatus())
				{
					overdue.push_back(&loanVector.at(i));
					j++;
				}
		}
	cout << j << " Overdue books found." << endl;
	for(unsigned i = 0; i < overdue.size(); i++)
		{
			overdue.at(i)->printLoan();
		}
}
void Loans::listPatronBooks(Patron* target)
{
	vector<Loan> matches;
	for(unsigned i = 0; i < loanVector.size(); i++)
		{
			if(loanVector.at(i).getPatronId() == target->getId())
				{
					matches.push_back(loanVector.at(i));
				}
		}

	for(Loan l : matches)
		{
			l.printLoan();
		}
}

void Loans::updateLoanStatus()
{
	int j = 0;
	Patrons* patronDB = getPatronDatabase();
	Books* bookDB = getBookDatabase();
	for(unsigned i = 0; i < loanVector.size(); i++)
		{
			if(loanVector.at(i).getDueDate() <= system_clock::to_time_t(system_clock::now()))
				{
					loanVector.at(i).setOverdueStatus(true);
					int patronId = loanVector.at(i).getPatronId();
					Patron* patron = patronDB->searchPatron(patronId);
					patron->setBalance(patron->getBalance()-0.25);
					j++;
				}
		}
	cout << "Updated " << j << " loans.\n";
}

void Loans::reportLost()
{
	string::size_type sz;
	Patrons* patronDB = getPatronDatabase();
	Books* bookDB = getBookDatabase();
	Loan* target;
	string tempString;
	cout << "Enter a Loan ID, or press Q to exit.\n";
	cout << "Enter the loan's ID, or press Q to exit." << endl;
	getline(cin,tempString);
	cin.clear();
	if(tempString[0] == 'Q' || tempString[0] == 'q')
		{
			cout << "Aborted.\n";
			return;
		}
	target = searchLoan(stoi(tempString,&sz));
	patronDB->searchPatron(target->getPatronId())->setBalance(patronDB->searchPatron(target->getPatronId())->getBalance() - bookDB->searchBook(target->getBookId())->getCost());
	bookDB->searchBook(target->getBookId())->setStatus(LOST);
	for(unsigned i = 0; i < loanVector.size(); i++)
		{
			if(loanVector.at(i).getLoanId() == stoi(tempString,&sz))
				{
					loanVector.erase(loanVector.begin() + i);
				}
		}
}

void Loans::drawMenu()
{
	cout << "O";
	for(int i = 0; i < 63; i++)
		{
			cout << '-';
		}
	cout << "O" << endl;

	printf("|%-63s|\n","                            LOANS");
	printf("|%63s|\n"," ");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"A\" to add (Check out) a new loan to the database");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"E\" to edit (Re-Check) an existing loan");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"D\" to delete (Check in) an existing loan from the database");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"P\" to print ALL loans in the database for an individual patron");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"I\" to print an individual loan's data");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"U\" to update loan status from system clock");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"R\" to report a book as lost");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"T\" to print all loans past their due date");
	printf("|%63s|\n"," ");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"Q\" To return to main menu");
	printf("|%-63s|\n"," ");

	cout << "O";
	for(int i = 0; i < 63; i++)
		{
			cout << '-';
		}
	cout << "O" << endl << endl;
}

void Loans::menu(Patrons* patronDB, Books* bookDB)
{
	setPatronDatabase(patronDB);
	setBookDatabase(bookDB);

	string::size_type sz;
	while(true)
		{
			drawMenu();
			Loan* target;

			string tempString;
			int tempInt;

			string input = "";
			char charinput = '\0';
			bool inputLoop = true;
			while(inputLoop)
				{
					input = "";
					charinput = '\0';
					getline(cin,input);
					charinput = input[0];
					cin.clear();
					charinput = toupper(charinput);

					switch(charinput)
						{
						case('A'):
							checkOutBook();
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('E'):
							if(loanVector.size() == 0)
								{
									cout << "Error, no loans in database." << endl;
								}
							else
								{
									cout << "Enter the loan's ID, or press Q to exit." << endl;
									getline(cin,tempString);
									cin.clear();
									if(tempString[0] == 'Q' || tempString[0] == 'q')
										{
											cout << "Aborted.\n";
											continue;
										}
									target = searchLoan(stoi(tempString,&sz));
									recheckBook(target);
								}
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('D'):
							if(loanVector.size() == 0)
								{
									cout << "Error, no loans in database." << endl;
								}
							else
								{
									cout << "Enter the loan's ID, or press Q to quit." << endl;
									getline(cin,tempString);
									cin.clear();
									if(toupper(tempString[0] == 'Q'))
										{
											cout << "Aborted.\n";
											continue;
										}
									target = searchLoan(stoi(tempString,&sz));
									checkInBook(target, stoi(tempString,&sz));
								}
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('P'):
							if(loanVector.size() == 0)
								{
									cout << "Error, no loans in database." << endl;
								}
							else
								{
									Patrons* patronDB = getPatronDatabase();
									cout << "Enter the ID or Name of a patron, or hit Q to exit.\n";
									getline(cin,tempString);
									cin.clear();
									Patron* p;
									if(isalpha(tempString[0]))
										{
											p = patronDB->searchPatron(tempString);
										}
									else
										{
											p = patronDB->searchPatron(stoi(tempString,&sz));
										}
									listPatronBooks(p);
								}
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('I'):
							if(loanVector.size() == 0)
								{
									cout << "Error, no loans in database." << endl;
								}
							else
								{
									cout << "Enter the loan's ID, or press Q to quit." << endl;
									getline(cin,tempString);
									cin.clear();
									if(toupper(tempString[0] == 'Q'))
										{
											cout << "Aborted.\n";
											continue;
										}
									target = searchLoan(stoi(tempString,&sz));
									target->printLoan();
								}
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('U'):
							if(loanVector.size() == 0)
								{
									cout << "Error, no loans in database." << endl;

								}
							else
								{
									updateLoanStatus();
								}
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('R'):
							reportLost();
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('T'):
							listOverdue();
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('Q'):
							return;
						default:
							break;
						}
				}
			cout << "\033[2J\033[1;1H";
		}
}