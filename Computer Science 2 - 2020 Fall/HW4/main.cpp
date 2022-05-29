/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW4
	Date: 11/24/20
*/

#include <string>
#include <iostream>
#include <algorithm>

#include "Patron.h"
#include "Book.h"
#include "Loan.h"
#include "Patrons.h"
#include "LibraryItems.h"
#include "Loans.h"


using namespace std;

using std::chrono::system_clock;

enum prog_state
{
	RUN,
	QUIT
};

enum menu_state
{
	MENU,
	PATRONS,
	LOANS,
	ITEMS,
	EXIT
};

void clearTerminal()
{
	cout << "\033[2J\033[1;1H"; //Clears screen and positions cursor at 1,1. Does not re-initialize the terminal.
}

void drawMenu()
{
	cout << "O";
	for(int i = 0; i < 63; i++)
		{
			cout << '-';
		}
	cout << "O" << endl;

	printf("|%-63s|\n","                             MENU");
	printf("|%63s|\n"," ");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"P\" to make changes to the patron database");
	printf("|%-63s|\n"," ");
	printf("|%-63s|\n","\"L\" to make changes to the loan database");
	printf("|%-63s|\n"," ");
	printf("|%-63s|\n","\"I\" to make changes to the item database");
	printf("|%-63s|\n"," ");
	printf("|%-63s|\n"," ");
	printf("|%-63s|\n","\"Q\" To Quit");
	printf("|%-63s|\n"," ");


	cout << "O";
	for(int i = 0; i < 63; i++)
		{
			cout << '-';
		}
	cout << "O" << endl << endl;
}

int main()
{
	prog_state programState = RUN;
	menu_state menuState = MENU;

	Patrons patronDatabase;
	LibraryItems itemDatabase;
	Loans loanDatabase;

	char tempChar;
	string tempString;

	while(programState == RUN)
		{
			clearTerminal();
			menuState = MENU;
			drawMenu();
			while(menuState == MENU)
				{
					tempChar = '\0';
					tempString = "";

					getline(cin,tempString);
					cin.clear();
					tempChar = toupper(tempString[0]);

					switch(tempChar)
						{
						case('P'):
							menuState = PATRONS;
							break;
						case('L'):
							menuState = LOANS;
							break;
						case('I'):
							menuState = ITEMS;
							break;
						case('Q'):
							menuState = EXIT;
							break;
						default:
							menuState = MENU;
							break;
						}
				}
			switch(menuState)
				{
				case(PATRONS):
					clearTerminal();
					patronDatabase.menu(&loanDatabase,&itemDatabase);
					menuState = MENU;
					break;
				case(LOANS):
					clearTerminal();
					loanDatabase.menu(&patronDatabase,&itemDatabase);
					menuState = MENU;
					break;
				case(ITEMS):
					clearTerminal();
					itemDatabase.menu(&patronDatabase,&loanDatabase);
					menuState = MENU;
					break;
				case(EXIT):
					programState = QUIT;
					break;
				default:
					cout << "?????" << endl;
					programState = RUN;
					menuState = MENU;
					break;
				}
		}
	return 0;
}