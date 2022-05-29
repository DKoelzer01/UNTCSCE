/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW4
	Date: 11/24/20
*/

#include "LibraryItems.h"

LibraryItems::LibraryItems()
{
	vector<LibraryItem*> LibraryItemVector;
}

vector<LibraryItem*>* LibraryItems::getLibraryItemVector()
{
	return &LibraryItemVector;
}

void LibraryItems::addItem()
{
	string tempString = "";
	cout << "Add a new (B)ook, (D)VD, (C)D, or press \"Q\" to quit.\n";
	getline(cin,tempString);
	while(true)
		{
			switch(toupper(tempString[0]))
				{
				case('Q'):
					cout << "Aborted.\n";
					return;
				case('B'):
					addBook();
					return;
				case('D'):
					addDVD();
					return;
				case('C'):
					addCD();
					return;
				default:
					break;
				}
		}
}

void LibraryItems::addBook()
{
	while(true)
		{
			string title = "";
			string author = "";
			string isbn = "";
			string id = "";
			string cost = "";
			string category = "";

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

			cout << "Enter the Book's Category / Genre, or press Q to exit: " << endl;
			getline(cin, category);
			cin.clear();
			if(category[0] == 'Q' || category[0] == 'q')
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
			for(unsigned i = 0; i < LibraryItemVector.size(); i++)
				{
					if(LibraryItemVector.at(i)->getId() == stoi(id,&sz))
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

			LibraryItemVector.push_back(new Book(author,title,category,stoi(isbn,&sz),stoi(id,&sz),stod(cost,&sz),IN));
			cout << "Book added to database.\n";
			break;
		}

}

void LibraryItems::addDVD()
{
	while(true)
		{
			string title = "";
			string studio = "";
			string runtime = "";
			string category = "";
			string date = "";
			string id = "";
			string cost = "";

			cout << "Enter the Studio's Name, or press Q to exit: " << endl;
			getline(cin, studio);
			cin.clear();
			if(studio[0] == 'Q' || studio[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}
			cout << "Enter the DVD's Title, or press Q to exit: " << endl;
			getline(cin, title);
			cin.clear();
			if(title[0] == 'Q' || title[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			cout << "Enter the DVD's Category / Genre, or press Q to exit: " << endl;
			getline(cin, category);
			cin.clear();
			if(category[0] == 'Q' || category[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			cout << "Enter the DVD's Release Date, or press Q to exit: " << endl;
			getline(cin, date);
			cin.clear();
			if(date[0] == 'Q' || date[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			cout << "Enter the length of the DVD, or press Q to exit: " << endl;
			getline(cin, runtime);
			cin.clear();
			if(runtime[0] == 'Q' || runtime[0] == 'q')
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
			for(unsigned i = 0; i < LibraryItemVector.size(); i++)
				{
					if(LibraryItemVector.at(i)->getId() == stoi(id,&sz))
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

			LibraryItemVector.push_back(new DVD(studio,title,stoi(runtime,&sz),date,category,stoi(id,&sz),stod(cost,&sz),IN));
			cout << "DVD added to database.\n";
			break;
		}

}

void LibraryItems::addCD()
{
	while(true)
		{
			string title = "";
			string artist = "";
			string num = "";
			string date = "";
			string id = "";
			string cost = "";
			string category = "";

			cout << "Enter the Artist's Name, or press Q to exit: " << endl;
			getline(cin, artist);
			cin.clear();
			if(artist[0] == 'Q' || artist[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}
			cout << "Enter the CD's Title, or press Q to exit: " << endl;
			getline(cin, title);
			cin.clear();
			if(title[0] == 'Q' || title[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			cout << "Enter the CD's Category / Genre, or press Q to exit: " << endl;
			getline(cin, category);
			cin.clear();
			if(category[0] == 'Q' || category[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			cout << "Enter the Release date of the CD, or press Q to exit: " << endl;
			getline(cin, date);
			cin.clear();
			if(date[0] == 'Q' || date[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			cout << "Enter the Number of tracks on the disc, or press Q to exit: " << endl;
			getline(cin, num);
			cin.clear();
			if(num[0] == 'Q' || num[0] == 'q')
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
			for(unsigned i = 0; i < LibraryItemVector.size(); i++)
				{
					if(LibraryItemVector.at(i)->getId() == stoi(id,&sz))
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

			LibraryItemVector.push_back(new CD(artist,title,stoi(num,&sz),date,category,stoi(id,&sz),stod(cost,&sz),IN));
			cout << "CD added to database.\n";
			break;
		}

}

void LibraryItems::editItem(LibraryItem* target)
{
	if(target == &emptyItem)
		{
			cout << "Item with this ID does not exist.\n";
			return;
		}

	string::size_type sz;
	string tempString = "";
	cin.clear();
	cout << "Enter a new value, leave blank to the keep current value, or press 'Q' to exit." << endl;

	switch(target->getItemType())
		{
		case(BOOK):
			cout << "Author: " << (dynamic_cast <Book*> (target))->getAuthor() << endl;
			getline(cin,tempString);
			cin.clear();
			if(tempString[0] == 'Q' || tempString[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			if(tempString != "")
				{
					(dynamic_cast <Book*> (target))->setAuthor(tempString);
				}

			cout << "Title: " << (dynamic_cast <Book*> (target))->getTitle() << endl;
			getline(cin,tempString);
			cin.clear();
			if(tempString[0] == 'Q' || tempString[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			if(tempString != "")
				{
					(dynamic_cast <Book*> (target))->setTitle(tempString);
				}

			cout << "Category: " << (dynamic_cast <Book*> (target))->getCategory() << endl;
			getline(cin,tempString);
			cin.clear();
			if(tempString[0] == 'Q' || tempString[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			if(tempString != "")
				{
					(dynamic_cast <Book*> (target))->setCategory(tempString);
				}

			cout << "ISBN: " << (dynamic_cast <Book*> (target))->getISBN() << endl;
			getline(cin,tempString);
			cin.clear();
			if(tempString[0] == 'Q' || tempString[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			if(tempString != "")
				{
					(dynamic_cast <Book*> (target))->setISBN(stoi(tempString,&sz));
				}
			break;
		case(COMPACTDISC):
			cout << "Artist: " << (dynamic_cast <CD*> (target))->getArtist() << endl;
			getline(cin,tempString);
			cin.clear();
			if(tempString[0] == 'Q' || tempString[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			if(tempString != "")
				{
					(dynamic_cast <CD*> (target))->setArtist(tempString);
				}

			cout << "Title: " << (dynamic_cast <CD*> (target))->getTitle() << endl;
			getline(cin,tempString);
			cin.clear();
			if(tempString[0] == 'Q' || tempString[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			if(tempString != "")
				{
					(dynamic_cast <CD*> (target))->setTitle(tempString);
				}

			cout << "Genre: " << (dynamic_cast <CD*> (target))->getGenre() << endl;
			getline(cin,tempString);
			cin.clear();
			if(tempString[0] == 'Q' || tempString[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			if(tempString != "")
				{
					(dynamic_cast <CD*> (target))->setGenre(tempString);
				}

			cout << "Number of Tracks: " << (dynamic_cast <CD*> (target))->getNumTracks() << endl;
			getline(cin,tempString);
			cin.clear();
			if(tempString[0] == 'Q' || tempString[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			if(tempString != "")
				{
					(dynamic_cast <CD*> (target))->setNumTracks(stoi(tempString,&sz));
				}
			break;
		case(DIGITALVERSATILEDISC):
			cout << "Studio: " << (dynamic_cast <DVD*> (target))->getStudio() << endl;
			getline(cin,tempString);
			cin.clear();
			if(tempString[0] == 'Q' || tempString[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			if(tempString != "")
				{
					(dynamic_cast <DVD*> (target))->setStudio(tempString);
				}

			cout << "Title: " << (dynamic_cast <DVD*> (target))->getTitle() << endl;
			getline(cin,tempString);
			cin.clear();
			if(tempString[0] == 'Q' || tempString[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			if(tempString != "")
				{
					(dynamic_cast <DVD*> (target))->setTitle(tempString);
				}

			cout << "Genre: " << (dynamic_cast <DVD*> (target))->getCategory() << endl;
			getline(cin,tempString);
			cin.clear();
			if(tempString[0] == 'Q' || tempString[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			if(tempString != "")
				{
					(dynamic_cast <DVD*> (target))->setCategory(tempString);
				}

			cout << "Runtime: " << (dynamic_cast <DVD*> (target))->getRuntime() << endl;
			getline(cin,tempString);
			cin.clear();
			if(tempString[0] == 'Q' || tempString[0] == 'q')
				{
					cout << "Aborted.\n";
					return;
				}

			if(tempString != "")
				{
					(dynamic_cast <DVD*> (target))->setRuntime(stoi(tempString,&sz));
				}
			break;
		default:
			cout << "???????\n";
			return;
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
			for(unsigned i = 0; i < LibraryItemVector.size(); i++)
				{
					if(LibraryItemVector.at(i)->getId() == stoi(tempString,&sz))
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
			case(LOST):
				return "LOST";
			default:
				return "ERROR";
			}
	}
	(tempStatus);
	cout << "Status: " << statusOut << endl;
	cout << "Valid Statuses: IN, OUT, LOST\n";
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
			tempStatus = (tempString == "IN") ? IN : tempString == "OUT" ? OUT : tempString == "LOST" ? LOST : ERROR;
			target->setStatus(tempStatus);
		}
}

void LibraryItems::deleteItem(LibraryItem* target, int id, Loans* loanDB)
{
	if(target != &emptyItem)
		{
			for(unsigned i = 0; i < loanDB->getLoanVector()->size(); i++)
				{
					if(loanDB->getLoanVector()->at(i).getItemId() == id)
						{
							loanDB->checkIn(&loanDB->getLoanVector()->at(i),id);
						}
				}

			for(unsigned i = 0; i < LibraryItemVector.size(); i++)
				{
					if(LibraryItemVector.at(i)->getId() == id)
						{
							LibraryItemVector.erase(LibraryItemVector.begin()+i);
						}
				}

		}
	else
		{
			cout << "ID does not exist." << endl;
		}
}

LibraryItem* LibraryItems::searchItem()
{
	if(LibraryItemVector.size() == 0)
		{
			cout << "Error, no items in database." << endl;
			return &emptyItem;
		}

	vector<LibraryItem*> matches;
	int id;
	char ch;
	string input = "";

	bool loopinput = true;
	bool loopinputB = true;
	cout << "Select a (T)ype of item to search for, search (A)ll items, or press \"Q\" to quit.\n";
	while(loopinput)
		{
			ch = '\0';
			cin >> ch;
			ch = toupper(ch);
			if(ch == 'Q')
				{
					loopinput = false;
					cout << "Aborted.\n";
					return &emptyItem;
				}
			if(ch == 'T')
				{
					loopinput = false;
					cout << "(C)D, (D)VD, (B)ook, or \"Q\" to quit.\n";
					ch = '\0';
					cin >> ch;
					ch = toupper(ch);
					switch(ch)
						{
						case('C'):
							cout << "Search by (T)itle, (A)rtist, (D)ate, (G)enre,(P)rint all CD's,  or press \"Q\" to quit.\n";
							loopinputB = true;
							while(loopinputB)
								{
									loopinputB = false;
									ch = '\0';
									cin >> ch;
									ch = toupper(ch);
									switch(ch)
										{
										case('T'):
											input = "";
											cout << "Enter the Title: \n";
											getline(cin, input);
											for(unsigned i = 0; i < LibraryItemVector.size(); i++)
												{
													if((dynamic_cast <CD*> (LibraryItemVector.at(i)))->getTitle() == input)
														{
															matches.push_back(LibraryItemVector.at(i));
														}
												}
											break;
										case('A'):
											input = "";
											cout << "Enter the Artist: \n";
											getline(cin, input);
											for(unsigned i = 0; i < LibraryItemVector.size(); i++)
												{
													if((dynamic_cast <CD*> (LibraryItemVector.at(i)))->getArtist() == input)
														{
															matches.push_back(LibraryItemVector.at(i));
														}
												}
											break;
										case('D'):
											input = "";
											cout << "Enter the Date: \n";
											getline(cin, input);
											for(unsigned i = 0; i < LibraryItemVector.size(); i++)
												{
													if((dynamic_cast <CD*> (LibraryItemVector.at(i)))->getReleaseDate() == input)
														{
															matches.push_back(LibraryItemVector.at(i));
														}
												}
											break;
										case('G'):
											input = "";
											cout << "Enter the Genre: \n";
											getline(cin, input);
											for(unsigned i = 0; i < LibraryItemVector.size(); i++)
												{
													if((dynamic_cast <CD*> (LibraryItemVector.at(i)))->getGenre() == input)
														{
															matches.push_back(LibraryItemVector.at(i));
														}
												}
											break;
										case('P'):
											for(unsigned i = 0; i < LibraryItemVector.size(); i++)
												{
													if((dynamic_cast <CD*> (LibraryItemVector.at(i)))->getItemType() == COMPACTDISC)
														{
															matches.push_back(LibraryItemVector.at(i));
														}
												}
											break;
										case('Q'):
											cout << "Aborted.\n";
											return &emptyItem;
										default:
											loopinputB = true;
											break;
										}
								}
							break;
						case('D'):
							cout << "Search by (T)itle, (S)tudio, (D)ate, (G)enre,(P)rint all DVD's, or press \"Q\" to quit.\n";
							loopinputB = true;
							while(loopinputB)
								{
									loopinputB = false;
									ch = '\0';
									cin >> ch;
									ch = toupper(ch);
									switch(ch)
										{
										case('T'):
											input = "";
											cout << "Enter the Title: \n";
											getline(cin, input);
											for(unsigned i = 0; i < LibraryItemVector.size(); i++)
												{
													if((dynamic_cast <DVD*> (LibraryItemVector.at(i)))->getTitle() == input)
														{
															matches.push_back(LibraryItemVector.at(i));
														}
												}
											break;
										case('S'):
											input = "";
											cout << "Enter the Studio: \n";
											getline(cin, input);
											for(unsigned i = 0; i < LibraryItemVector.size(); i++)
												{
													if((dynamic_cast <DVD*> (LibraryItemVector.at(i)))->getStudio() == input)
														{
															matches.push_back(LibraryItemVector.at(i));
														}
												}
											break;
										case('D'):
											input = "";
											cout << "Enter the Date: \n";
											getline(cin, input);
											for(unsigned i = 0; i < LibraryItemVector.size(); i++)
												{
													if((dynamic_cast <DVD*> (LibraryItemVector.at(i)))->getReleaseDate() == input)
														{
															matches.push_back(LibraryItemVector.at(i));
														}
												}
											break;
										case('G'):
											input = "";
											cout << "Enter the Genre: \n";
											getline(cin, input);
											for(unsigned i = 0; i < LibraryItemVector.size(); i++)
												{
													if((dynamic_cast <DVD*> (LibraryItemVector.at(i)))->getCategory() == input)
														{
															matches.push_back(LibraryItemVector.at(i));
														}
												}
											break;
										case('P'):
											for(unsigned i = 0; i < LibraryItemVector.size(); i++)
												{
													if((dynamic_cast <DVD*> (LibraryItemVector.at(i)))->getItemType() == DIGITALVERSATILEDISC)
														{
															matches.push_back(LibraryItemVector.at(i));
														}
												}
											break;
										case('Q'):
											cout << "Aborted.\n";
											return &emptyItem;
										default:
											loopinputB = true;
											break;
										}
								}
							break;
						case('B'):
							cout << "Search by (T)itle, (A)uthor, (G)enre,(P)rint all Books, or press \"Q\" to quit.\n";
							loopinputB = true;
							while(loopinputB)
								{
									loopinputB = false;
									ch = '\0';
									cin >> ch;
									cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
									ch = toupper(ch);
									switch(ch)
										{
										case('T'):
											input = "";
											cout << "Enter the Title: \n";
											getline(cin, input);
											for(unsigned i = 0; i < LibraryItemVector.size(); i++)
												{
													if(LibraryItemVector.at(i)->getItemType() == BOOK)
														{
															if((dynamic_cast <Book*> (LibraryItemVector.at(i)))->getTitle() == input)
																{
																	matches.push_back(LibraryItemVector.at(i));
																}
														}
												}
											break;
										case('A'):
											input = "";
											cout << "Enter the Author: \n";
											getline(cin, input);
											for(unsigned i = 0; i < LibraryItemVector.size(); i++)
												{
													if(LibraryItemVector.at(i)->getItemType() == BOOK)
														{
															if((dynamic_cast <Book*> (LibraryItemVector.at(i)))->getAuthor() == input)
																{
																	matches.push_back(LibraryItemVector.at(i));
																}
														}
												}
											break;
										case('G'):
											input = "";
											cout << "Enter the Genre: \n";
											getline(cin, input);
											for(unsigned i = 0; i < LibraryItemVector.size(); i++)
												{
													if(LibraryItemVector.at(i)->getItemType() == BOOK)
														{
															if((dynamic_cast <Book*> (LibraryItemVector.at(i)))->getCategory() == input)
																{
																	matches.push_back(LibraryItemVector.at(i));
																}
														}
												}
											break;
										case('P'):
											for(unsigned i = 0; i < LibraryItemVector.size(); i++)
												{
													if(LibraryItemVector.at(i)->getItemType() == BOOK)
														{
															matches.push_back(LibraryItemVector.at(i));
														}
												}
											break;
										case('Q'):
											cout << "Aborted.\n";
											return &emptyItem;
										default:
											loopinputB = true;
											break;
										}
								}
							break;
						case('Q'):
							cout << "Aborted.\n";
							return &emptyItem;
						default:
							continue;
						}
				}
			if(ch == 'A')
				{
					loopinput = false;
					cout << "Search by (T)itle, or (I)d,or press \"Q\" to quit.\n";
					while(true)
						{
							ch = '\0';
							cin >> ch;
							cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
							ch = toupper(ch);
							if(ch == 'T')
								{
									input = "";
									cout << "Enter the Title: \n";
									getline(cin, input);
									cout << input << endl;
									for(unsigned i = 0; i < LibraryItemVector.size(); i++)
										{
											if(LibraryItemVector.at(i)->getTitle() == input)
												{
													matches.push_back(LibraryItemVector.at(i));
												}
										}
									break;
								}
							else if(ch == 'I')
								{
									input = "";
									cout << "Enter the ID: \n";
									cin.ignore();
									getline(cin, input);
									for(unsigned i = 0; i < LibraryItemVector.size(); i++)
										{
											if(LibraryItemVector.at(i)->getId() == stoi(input))
												{
													matches.push_back(LibraryItemVector.at(i));
												}
										}
									break;
								}

						}
				}
		}
	if(matches.size() > 1)
		{
			cout << "Multiple matches found. Please select the item from the list below via ID : " << endl;
			for(unsigned i = 0; i < matches.size(); i++)
				{
					switch(matches.at(i)->getItemType())
						{
						case(BOOK):
							cout << matches.at(i)->getId() << ": " << (dynamic_cast <Book*> (matches.at(i)))->getAuthor() << endl;
							cout << matches.at(i)->getTitle() << endl << endl;
							break;
						case(COMPACTDISC):
							cout << matches.at(i)->getId() << ": " << (dynamic_cast <CD*> (matches.at(i)))->getArtist() << endl;
							cout << matches.at(i)->getTitle() << endl << endl;
							break;
						case(DIGITALVERSATILEDISC):
							cout << matches.at(i)->getId() << ": " << (dynamic_cast <DVD*> (matches.at(i)))->getStudio() << endl;
							cout << matches.at(i)->getTitle() << endl << endl;
							break;
						default:
							break;
						}
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
			return &emptyItem;
		}
}


LibraryItem* LibraryItems::searchItem(int id)
{
	if(LibraryItemVector.size() == 0)
		{
			cout << "Error, no items in database." << endl;
			return &emptyItem;
		}
	for(unsigned i = 0; i < LibraryItemVector.size(); i++)
		{
			if(LibraryItemVector.at(i)->getId() == id)
				{
					return LibraryItemVector.at(i);
				}
		}
	return &emptyItem;
}

void LibraryItems::printAllItems()
{
	if(LibraryItemVector.size() == 0)
		{
			cout << "Error, no items in database." << endl;
		}
	else
		{
			for(unsigned i = 0; i < LibraryItemVector.size(); i++)
				{
					switch(LibraryItemVector.at(i)->getItemType())
						{
						case(BOOK):
							cout << *(dynamic_cast <Book*> (LibraryItemVector.at(i)));
							break;
						case(COMPACTDISC):
							cout << *(dynamic_cast <CD*> (LibraryItemVector.at(i)));
							break;
						case(DIGITALVERSATILEDISC):
							cout << *(dynamic_cast <DVD*> (LibraryItemVector.at(i)));
							break;
						default:
							break;
						}
				}
		}
}

void LibraryItems::drawMenu()
{
	cout << "O";
	for(int i = 0; i < 63; i++)
		{
			cout << '-';
		}
	cout << "O" << endl;

	printf("|%-63s|\n","                            ITEMS");
	printf("|%63s|\n"," ");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"A\" to add a new item to the database");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"E\" to edit an existing item's data");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"D\" to delete an existing item from the database");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"P\" to print ALL items in the database");
	printf("|%63s|\n"," ");
	printf("|%-63s|\n","\"I\" to search for an individual item");
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

void LibraryItems::menu(Patrons* patronDB, Loans* loanDB)
{
	string::size_type sz;
	while(true)
		{
			drawMenu();
			LibraryItem* target;

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
							addItem();
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('E'):
							if(LibraryItemVector.size() == 0)
								{
									cout << "Error, no items in database." << endl;
								}
							else
								{
									cout << "Enter the item's ID, or press Q to exit." << endl;
									getline(cin,tempString);
									cin.clear();
									if(tempString[0] == 'Q' || tempString[0] == 'q')
										{
											cout << "Aborted.\n";
											continue;
										}
									target = searchItem(stoi(tempString,&sz));
									editItem(target);
								}
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('D'):
							if(LibraryItemVector.size() == 0)
								{
									cout << "Error, no items in database." << endl;
								}
							else
								{
									cout << "Enter the item's ID, or press Q to quit." << endl;
									getline(cin,tempString);
									cin.clear();
									if(toupper(tempString[0] == 'Q'))
										{
											cout << "Aborted.\n";
											continue;
										}
									target = searchItem(stoi(tempString,&sz));
									deleteItem(target, stoi(tempString,&sz), loanDB);
								}
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('P'):
							printAllItems();
							cout << "Press enter to continue ..." << endl;
							cin.get();
							inputLoop = false;
							break;
						case('I'):
							if(LibraryItemVector.size() == 0)
								{
									cout << "Error, no items in database." << endl;
								}
							else
								{
									target = searchItem();
									switch(target->getItemType())
										{
										case(BOOK):
											cout << *(dynamic_cast <Book*> (target));
											break;
										case(COMPACTDISC):
											cout << *(dynamic_cast <CD*> (target));
											break;
										case(DIGITALVERSATILEDISC):
											cout << *(dynamic_cast <DVD*> (target));
											break;
										default:
											break;
										}
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