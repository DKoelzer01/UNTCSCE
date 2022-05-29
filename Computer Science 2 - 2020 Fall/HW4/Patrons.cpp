/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW4
	Date: 11/24/20
*/

#include "Patrons.h"

Patrons::Patrons()
{
	vector<Patron> patronVector;
}

bool Patrons::findId(int id)
{
	for(unsigned i = 0; i < patronVector.size(); i++)
		{
			if(patronVector.at(i).getId() == id)
				{
					return true;
				}
		}
	return false;
}

void Patrons::addPatron()
{
	string name;
	int id;

	cout << "Enter the patron's Name, or press Q to exit: " << endl;
	getline(cin, name);
	cin.clear();
	if(name[0] == 'Q' || name[0] == 'q')
		{
			cout << "Aborted.\n";
			return;
		}
	cout << "Enter the patron's ID: " << endl;
	cin >> id;
	cin.clear();
	if(!findId(id))
		{
			patronVector.push_back(Patron(name,id,0,0));
			cout << "Patron added to database.\n";
		}
}

void Patrons::editPatron(Patron* target)
{
	if(target->isEmpty())
		{
			cout << "Patron with this ID does not exist.\n";
			return;
		}
	string::size_type sz;
	string tempString = "";
	cin.clear();
	cout << "Enter a new value, leave blank to the keep current value, or press 'Q' to exit." << endl;
	cin.ignore(1);
	cout << "ID: " << target->getId() << endl;
	getline(cin,tempString);
	cin.clear();
	if(tempString[0] == 'Q' || tempString[0] == 'q')
		{
			cout << "Aborted.\n";
			return;
		}

	if(!(tempString == "" || tempString == "\n"))
		{
			if(!findId(stoi(tempString,&sz)))
				{
					target->setId(stoi(tempString,&sz));
				}
		}
	cout << "Name: " << target->getName() << endl;
	tempString = "";
	getline(cin,tempString);
	cin.clear();
	if(tempString[0] == 'Q' || tempString[0] == 'q')
		{
			cout << "Aborted.\n";
			return;
		}

	if(!(tempString == "" || tempString == "\n"))
		{
			target->setName(tempString);
		}
		
	cout << "Balance: " << target->getBalance() << endl;
	tempString = "";
	getline(cin,tempString);
	cin.clear();
	
	if(tempString[0] == 'Q' || tempString[0] == 'q')
		{
			cout << "Aborted.\n";
			return;
		}
		
	if(!tempString.empty())
		{
			target->setBalance(stoi(tempString,&sz));
		}
		
	cout << "Items out: " << target->getNumItems() << endl;
	tempString = "";
	getline(cin,tempString);
	cin.clear();
	if(tempString[0] == 'Q' || tempString[0] == 'q')
		{
			cout << "Aborted.\n";
			return;
		}

	if(!(tempString == "" || tempString == "\n"))
		{
			target->setNumItems(stoi(tempString,&sz));
		}
}

void Patrons::deletePatron(Patron* target, int id, Loans* loanDB, LibraryItems* itemDB)
{
	if(!target->isEmpty())
		{
			if(findId(id))
				{
					cout << "Are you sure you want to delete this patron? (Y/N)\n";
					string tempString;
					getline(cin,tempString);
					if(toupper(tempString[0]) != 'Y')
						{
							cout << "Exiting.\n";
							return;
						}
					else
						{
							if(target->getBalance() != 0)
								{
									cout << "This patron has a non-zero balance. Are you sure you want to delete this patron? (Y/N)\n";
									getline(cin,tempString);
									cin.clear();
									if(toupper(tempString[0]) != 'Y')
										{
											return;
										}
								}
							for(unsigned i = 0; i < loanDB->getLoanVector()->size(); i++)
								{
									if(target->getId() == loanDB->getLoanVector()->at(i).getLoanId())
										{
											loanDB->checkIn(loanDB->searchLoan(loanDB->getLoanVector()->at(i).getLoanId()),loanDB->getLoanVector()->at(i).getLoanId());
										}
								}
							for(unsigned i = 0; i < patronVector.size(); i++)
								{
									if(patronVector.at(i).getId() == target->getId())
										{
											patronVector.erase(patronVector.begin()+i);
										}
								}

						}
				}
			else
				{
					cout << "ID does not exist." << endl;
				}
		}
	else
		{
			cout << "ID does not exist." << endl;
		}

}

Patron* Patrons::searchPatron(string _name)
{
	if(patronVector.size() == 0)
		{
			cout << "Error, no patrons in database." << endl;
			return &emptyPatron;
		}
	vector<Patron*> matches;
	int id;
	for(unsigned i = 0; i < patronVector.size(); i++)
		{
			if(patronVector.at(i).getName() == _name)
				{
					matches.push_back(&patronVector.at(i));
				}
		}
	if(matches.size() > 1)
		{
			cout << "Multiple matches found. Please select the patron from the list below via ID : " << endl;
			for(unsigned i = 0; i < matches.size(); i++)
				{
					printf("%d: %s\n",matches.at(i)->getId(),matches.at(i)->getName().c_str());
				}
			while(true)
				{
					id = 0;
					cin >> id;
					cin.clear();

					for(unsigned i = 0; i < matches.size(); i++)
						{
							if(matches.at(i)->getId() == id)
								{
									return matches.at(i);
								}
						}
				}
		}
	else if (matches.size() == 1)
		{
			return matches.at(0);
		}
	else
		{
			cout << "No matches found." << endl;
			return &emptyPatron;
		}
}

Patron* Patrons::searchPatron(int id)
{
	if(patronVector.size() == 0)
		{
			cout << "Error, no patrons in database." << endl;
			return &emptyPatron;
		}
	for(unsigned i = 0; i < patronVector.size(); i++)
		{
			if(patronVector.at(i).getId() == id)
				{
					return &patronVector.at(i);
				}
		}
	return &emptyPatron;
}

void Patrons::printAllPatrons()
{
	if(patronVector.size() == 0)
		{
			cout << "Error, no patrons in database." << endl;
		}
	else
		{
			for(unsigned i = 0; i < patronVector.size(); i++)
				{
					patronVector.at(i).printPatron();
				}
		}
}

void Patrons::payFines(Patron* target)
{
	cout << target->getName() << endl;
	if(!target->isEmpty())
		{
			double amount = 0;
			cout << "Enter an amount you wish to change the balance by: " << endl;
			cin >> amount;
			cin.clear();
			target->setBalance(target->getBalance() + amount);
			cout << "New balance: " << target->getBalance() << endl;
		}
}

void Patrons::drawMenu()
{
	cout << "O";
	for(int i = 0; i < 63; i++)
		{
			cout << '-';
		}
	cout << "O" << endl;

	printf("|%-63s|\n","                          PATRONS");
	printf("|%63s|\n"," ");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"A\" to add a new patron to the database");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"E\" to edit an existing patron's data");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"D\" to delete an existing patron from the database");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"P\" to print ALL patrons in the database");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"I\" to print an individual patron's data");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"F\" to change a patron's outstanding balance");
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

void Patrons::menu(Loans* loanDatabase,LibraryItems* itemDatabase)
{
	while(true)
		{
			drawMenu();
			Patron* temp;
			string tempString;
			int tempInt;
			Patron* target;
			string input = "";
			char charinput = '\0';
			bool inputLoop = true;
			while(inputLoop)
				{
					getline(cin,input);
					charinput = input[0];
					cin.clear();
					charinput = toupper(charinput);

					switch(charinput)
						{
						case('A'):
							addPatron();
							cin.ignore(1);
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('E'):
							if(patronVector.size() == 0)
								{
									cout << "Error, no patrons in database." << endl;
								}
							else
								{
									cout << "Enter the patron's ID: " << endl;
									cin >> tempInt;
									temp = searchPatron(tempInt);
									editPatron(temp);
								}
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('D'):
							if(patronVector.size() == 0)
								{
									cout << "Error, no patrons in database." << endl;
								}
							else
								{
									cout << "Enter the patron's ID: " << endl;
									cin >> tempInt;
									temp = searchPatron(tempInt);
									deletePatron(temp,tempInt,loanDatabase,itemDatabase);
								}
							cout << "Press enter to continue ..." << endl;
							cin.ignore(1);
							cin.get();
							inputLoop = false;
							break;
						case('P'):
							printAllPatrons();
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('I'):
							if(patronVector.size() == 0)
								{
									cout << "Error, no patrons in database." << endl;
								}
							else
								{
									input = "";
									cout << "Enter a patron's ID or Name that you want to view, or press Q to exit." << endl;
									getline(cin, input);
									cin.clear();

									if(isalpha(input[0]))
										{
											if(toupper(input[0]) == 'Q')
												{
													break;
												}
											else
												{
													target = searchPatron(input);
												}
										}
									else
										{
											string::size_type sz;
											target = searchPatron(stoi(input,&sz));
										}
									target->printPatron();
								}
							cin.ignore(1);
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('Q'):
							return;
						case('F'):
							if(patronVector.size() == 0)
								{
									cout << "Error, no patrons in database." << endl;
								}
							else
								{
									input = "";
									cout << "Enter a patron's ID or Name that you want to change, or press Q to exit." << endl;
									getline(cin, input);
									cin.clear();

									if(isalpha(input[0]))
										{
											if(toupper(input[0]) == 'Q')
												{
													break;
												}
											else
												{
													target = searchPatron(input);
												}
										}
									else
										{
											string::size_type sz;
											target = searchPatron(stoi(input,&sz));
										}
									payFines(target);
								}
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						default:
							break;
						}
				}
			cout << "\033[2J\033[1;1H";
		}
}