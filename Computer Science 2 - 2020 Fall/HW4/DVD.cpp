/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW3
	Date: 10/30/20
*/
#include "DVD.h"

DVD::DVD()
{
	studio = "NONE";
	title = "NONE";
	runtime = 0;
	releaseDate = "NONE";
	category = "NONE";
	id = -1;
	cost = -1;
	curStatus = IN;
	libraryItemType = DIGITALVERSATILEDISC;
}
DVD::DVD(string _studio, string _title, int _runtime, string _date, string _category, int _id, double _cost, status _status)
{
	studio = _studio;
	title = _title;
	runtime = _runtime;
	releaseDate = _date;
	category = _category;
	id = _id;
	cost = _cost;
	curStatus = _status;
	libraryItemType = DIGITALVERSATILEDISC;
}

bool DVD::isEmpty(){
		return (studio == "NONE" && title == "NONE" && runtime == 0 && releaseDate == "NONE" && category == "NONE" && id == -1 && cost == -1 && curStatus == IN);
}

void DVD::setStudio(string _studio){
	studio = _studio;
}
void DVD::setTitle(string _title){
	title = _title;
}
void DVD::setRuntime(int _num){
	runtime = _num;
}
void DVD::setReleaseDate(string _date){
	releaseDate = _date;
}
void DVD::setCategory(string _category){
	category = _category;
}

string DVD::getCategory(){
	return category;
}
string DVD::getStudio(){
	return studio;
}
string DVD::getTitle(){
	return title;
}
int DVD::getRuntime(){
	return runtime;
}
string DVD::getReleaseDate(){
	return releaseDate;
}

ostream& DVD::print(ostream& out){
	string status;
	int temp = getStatus();
	switch(temp)
		{
		case(IN):
			status = "IN";
			break;
		case(OUT):
			status = "OUT";
			break;
		case(LOST):
			status = "LOST";
			break;
		default:
			status = "ERROR";
			break;
		}

	out << "O";
	for(int i = 0; i < 63; i++)
		{
			out << '-';
		}
	out << "O" << endl;
	
	out << "|Title: ";
	out << setw(56);
	out << getTitle();
	out << "|\n";
	
	out << "|Studio: ";
	out << setw(55);
	out << getStudio();
	out << "|\n";

	out << "|Release Date: ";
	out << setw(49);
	out << getReleaseDate();
	out << "|\n";
	
	out << "|Category: ";
	out << setw(53);
	out << getCategory();
	out << "|\n";
	
	out << "|Runtime: ";
	out << setw(54);
	out << getRuntime();
	out << "|\n";

	out << "|ID: ";
	out << setw(59);
	out << getId();
	out << "|\n";
	
	out << "|Cost: ";
	out << setw(57);
	out << setprecision(2);
	out << getCost();
	out << "|\n";

	out << "|Status: ";
	out << setw(55);
	out << status;
	out << "|\n";
	
	out << "O";
	for(int i = 0; i < 63; i++)
		{
			out << '-';
		}
	out << "O" << endl;
}
