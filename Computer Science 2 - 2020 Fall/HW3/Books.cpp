/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW3
	Date: 10/30/20
*/

#include "Books.h"

Books::Books()
{
	vector<Book> bookVector;
}

vector<Book>* Books::getBookVector()
{
	return &bookVector;
}

void Books::addBook()
{
	while(true)
		{
			string title = "";
			string author = "";
			string isbn = "";
			string id = "";
			string cost = "";

			cout << "Enter the Author's Name, or press Q to exit: " << endl;
			getline(cin, author);
			cin.clear();
			if(author[0] == 'Q' || author[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}
			cout << "Enter the Book's Title, or press Q to exit: " << endl;
			getline(cin, title);
			cin.clear();
			if(title[0] == 'Q' || title[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			cout << "Enter the ISBN Number, or press Q to exit: " << endl;
			getline(cin, isbn);
			cin.clear();
			if(isbn[0] == 'Q' || isbn[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			cout << "Enter the Library ID, or press Q to exit: " << endl;
			getline(cin, id);
			cin.clear();
			if(id[0] == 'Q' || id[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			string::size_type sz;
			for(unsigned i = 0; i < bookVector.size(); i++)
				{
					if(bookVector.at(i).getId() == stoi(id,&sz))
						{
							cout << "This ID is already in use.\n";
							return;
						}
				}

			cout << "Enter the Cost, or press Q to exit: " << endl;
			getline(cin, cost);
			cin.clear();
			if(cost[0] == 'Q' || cost[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			bookVector.push_back(Book(author,title,stoi(isbn,&sz),stoi(id,&sz),stod(cost,&sz),IN));
			cout << "Book added to database.\n";
			break;
		}

}

void Books::editBook(Book* target)
{
	if(target->isEmpty())
		{
			cout << "Book with this ID does not exist.\n";
			return;
		}
	string::size_type sz;
	string tempString = "";
	cin.clear();
	cout << "Enter a new value, leave blank to the keep current value, or press 'Q' to exit." << endl;

	cout << "Author: " << target->getAuthor() << endl;
	getline(cin,tempString);
	cin.clear();
	if(tempString[0] == 'Q' || tempString[0] == 'q')
		{
			cout << "Aborted.\n";
			return;
		}

	if(tempString != "")
		{
			target->setAuthor(tempString);
		}

	cout << "Title: " << target->getTitle() << endl;
	getline(cin,tempString);
	cin.clear();
	if(tempString[0] == 'Q' || tempString[0] == 'q')
		{
			cout << "Aborted.\n";
			return;
		}

	if(tempString != "")
		{
			target->setTitle(tempString);
		}

	cout << "ISBN: " << target->getISBN() << endl;
	getline(cin,tempString);
	cin.clear();
	if(tempString[0] == 'Q' || tempString[0] == 'q')
		{
			cout << "Aborted.\n";
			return;
		}

	if(tempString != "")
		{
			target->setISBN(stoi(tempString,&sz));
		}

	cout << "ID: " <<  target->getId() << endl;
	getline(cin,tempString);
	cin.clear();
	if(tempString[0] == 'Q' || tempString[0] == 'q')
		{
			cout << "Aborted.\n";
			return;
		}

	if(tempString != "")
		{
			for(unsigned i = 0; i < bookVector.size(); i++)
				{
					if(bookVector.at(i).getId() == stoi(tempString,&sz))
						{
							cout << "This ID is already in use.\n";
							return;
						}
				}
			target->setId(stoi(tempString,&sz));
		}

	cout << "Cost: " << target->getCost() << endl;
	getline(cin,tempString);
	cin.clear();
	if(tempString[0] == 'Q' || tempString[0] == 'q')
		{
			cout << "Aborted.\n";
			return;
		}

	if(tempString != "")
		{
			target->setCost(stod(tempString,&sz));
		}
	status tempStatus = target->getStatus();
	string statusOut = [=](status stat)
	{
		switch(stat)
			{
			case(IN):
				return "IN";
			case(OUT):
				return "OUT";
			case(REPAIR):
				return "REPAIR";
			case(LOST):
				return "LOST";
			default:
				return "ERROR";
			}
	}
	(tempStatus);
	cout << "Status: " << statusOut << endl;
	cout << "Valid Statuses: IN, OUT, REPAIR, LOST\n";
	getline(cin,tempString);
	cin.clear();
	if(tempString[0] == 'Q' || tempString[0] == 'q')
		{
			cout << "Aborted.\n";
			return;
		}

	if(tempString != "")
		{
			transform(tempString.begin(), tempString.end(), tempString.begin(), ::toupper);
			tempStatus = (tempString == "IN") ? IN : tempString == "OUT" ? OUT : tempString == "REPAIR" ? REPAIR : tempString == "LOST" ? LOST : ERROR;
			target->setStatus(tempStatus);
		}
}

void Books::deleteBook(Book* target, int id, Loans* loanDB)
{
	if(!target->isEmpty())
		{
			for(unsigned i = 0; i < loanDB->getLoanVector()->size(); i++)
				{
					if(loanDB->getLoanVector()->at(i).getBookId() == id)
						{
							loanDB->checkInBook(&loanDB->getLoanVector()->at(i),id);
						}
				}

			for(unsigned i = 0; i < bookVector.size(); i++)
				{
					if(bookVector.at(i).getId() == id)
						{
							bookVector.erase(bookVector.begin()+i);
						}
				}

		}
	else
		{
			cout << "ID does not exist." << endl;
		}
}

Book* Books::searchBook(string input)
{
	if(bookVector.size() == 0)
		{
			cout << "Error, no patrons in database." << endl;
			return &emptyBook;
		}
	vector<Book*> matches;
	int id;

	char ch;
	cout << "Search by (T)itle or (A)uthor\n";
	while(true)
		{
			cin >> ch;
			if(toupper(ch) == 'T')
				{
					cout << "TITLE" << endl;
					for(unsigned i = 0; i < bookVector.size(); i++)
						{
							if(bookVector.at(i).getTitle() == input)
								{
									cout << "FOUND" << endl;
									matches.push_back(&bookVector.at(i));
								}
						}
					break;
				}
			else if (toupper(ch) == 'A')
				{
					cout << "AUTHOR" << endl;
					for(unsigned i = 0; i < bookVector.size(); i++)
						{
							if(bookVector.at(i).getAuthor() == input)
								{
									cout << "FOUND" << endl;
									matches.push_back(&bookVector.at(i));
								}
						}
					break;
				}
		}
	if(matches.size() > 1)
		{
			cout << "Multiple matches found. Please select the book from the list below via ID : " << endl;
			for(unsigned i = 0; i < matches.size(); i++)
				{
					printf("%d: %s, %s\n",matches.at(i)->getId(),matches.at(i)->getTitle().c_str(),matches.at(i)->getAuthor().c_str());
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
			return &emptyBook;
		}
}

Book* Books::searchBook(int id)
{
	if(bookVector.size() == 0)
		{
			cout << "Error, no books in database." << endl;
			return &emptyBook;
		}
	for(unsigned i = 0; i < bookVector.size(); i++)
		{
			if(bookVector.at(i).getId() == id)
				{
					return &bookVector.at(i);
				}
		}
	return &emptyBook;
}

void Books::printAllBooks()
{
	if(bookVector.size() == 0)
		{
			cout << "Error, no books in database." << endl;
		}
	else
		{
			for(unsigned i = 0; i < bookVector.size(); i++)
				{
					bookVector.at(i).printBook();
				}
		}
}

void Books::drawMenu()
{
	cout << "O";
	for(int i = 0; i < 63; i++)
		{
			cout << '-';
		}
	cout << "O" << endl;

	printf("|%-63s|\n","                            BOOKS");
	printf("|%63s|\n"," ");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"A\" to add a new book to the database");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"E\" to edit an existing book's data");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"D\" to delete an existing book from the database");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"P\" to print ALL books in the database");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"I\" to print an individual book's data");
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

void Books::menu(Patrons* patronDB, Loans* loanDB)
{
	string::size_type sz;
	while(true)
		{
			drawMenu();
			Book* target;

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
							addBook();
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('E'):
							if(bookVector.size() == 0)
								{
									cout << "Error, no books in database." << endl;
								}
							else
								{
									cout << "Enter the book's ID, or press Q to exit." << endl;
									getline(cin,tempString);
									cin.clear();
									if(tempString[0] == 'Q' || tempString[0] == 'q')
										{
											cout << "Aborted.\n";
											continue;
										}
									target = searchBook(stoi(tempString,&sz));
									editBook(target);
								}
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('D'):
							if(bookVector.size() == 0)
								{
									cout << "Error, no books in database." << endl;
								}
							else
								{
									cout << "Enter the book's ID, or press Q to quit." << endl;
									getline(cin,tempString);
									cin.clear();
									if(toupper(tempString[0] == 'Q'))
										{
											cout << "Aborted.\n";
											continue;
										}
									target = searchBook(stoi(tempString,&sz));
									deleteBook(target, stoi(tempString,&sz), loanDB);
								}
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('P'):
							printAllBooks();
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('I'):
							if(bookVector.size() == 0)
								{
									cout << "Error, no books in database." << endl;
								}
							else
								{
									cout << "Enter the book's ID, or press Q to quit." << endl;
									getline(cin,tempString);
									cin.clear();
									if(toupper(tempString[0] == 'Q'))
										{
											cout << "Aborted.\n";
											continue;
										}
									target = searchBook(stoi(tempString,&sz));
									target->printBook();
								}
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