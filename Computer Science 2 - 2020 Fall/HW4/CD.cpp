/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW3
	Date: 10/30/20
*/
#include "CD.h"

CD::CD()
{
	artist = "NONE";
	title = "NONE";
	numTracks = 0;
	releaseDate = "NONE";
	genre = "NONE";
	id = -1;
	cost = -1;
	curStatus = IN;
	libraryItemType = COMPACTDISC;
}
CD::CD(string _art, string _title, int _numTracks, string _date, string _genre, int _id, double _cost, status _status)
{
	artist = _art;
	title = _title;
	numTracks = _numTracks;
	releaseDate = _date;
	genre = _genre;
	id = _id;
	cost = _cost;
	curStatus = _status;
	libraryItemType = COMPACTDISC;
}

bool CD::isEmpty() {
	return (artist == "NONE" && title == "NONE" && numTracks == 0 && releaseDate == "NONE" && genre == "NONE" && id == -1 && cost == -1 && curStatus == IN);
}

void CD::setArtist(string _artist){
	artist = _artist;
}
void CD::setTitle(string _title){
	title = _title;
}
void CD::setNumTracks(int _num){
	numTracks = _num;
}
void CD::setReleaseDate(string _date){
	releaseDate = _date;
}
void CD::setGenre(string _genre){
	genre = _genre;
}

string CD::getGenre(){
	return genre;
}
string CD::getArtist(){
	return artist;
}
string CD::getTitle(){
	return title;
}
int CD::getNumTracks(){
	return numTracks;
}
string CD::getReleaseDate(){
	return releaseDate;
}


ostream& CD::print(ostream& out)
{
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
	
	out << "|Artist: ";
	out << setw(55);
	out << getArtist();
	out << "|\n";

	out << "|Release Date: ";
	out << setw(49);
	out << getReleaseDate();
	out << "|\n";
	
	out << "|Genre: ";
	out << setw(56);
	out << getGenre();
	out << "|\n";
	
	out << "|# of Tracks: ";
	out << setw(50);
	out << getNumTracks();
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