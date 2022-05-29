/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW4
	Date: 11/24/20
*/

#ifndef DVD_H
#define DVD_H
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include "LibraryItem.h"

using namespace std;

class DVD: public LibraryItem
{
private:
	string title;
	int runtime;
	string studio;
	string releaseDate;
	string category;
public:
	DVD();
	DVD(string _studio, string _title, int _runtime, string _date, string _category, int _id, double _cost, status _status);

	bool isEmpty();

	ostream& print(ostream& out);

	void setStudio(string _artist);
	void setTitle(string _title);
	void setRuntime(int _num);
	void setReleaseDate(string _date);
	void setCategory(string _genre);

	string getCategory();
	string getStudio();
	string getTitle();
	int getRuntime();
	string getReleaseDate();
	
};
#endif