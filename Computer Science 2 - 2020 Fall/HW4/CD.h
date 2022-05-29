/* 	Author: Daniel Koelzer
	Course:	CSCE 1040
	Assignment: HW4
	Date: 11/24/20
*/

#ifndef CD_H
#define CD_H
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include "LibraryItem.h"

using namespace std;

class CD: public LibraryItem
{
private:
	string artist;
	string title;
	int numTracks;
	string releaseDate;
	string genre;
public:
	CD();
	CD(string _art, string _title, int _numTracks, string _date, string _genre, int _id, double _cost, status _status);

	bool isEmpty();

	ostream& print(ostream& out);

	void setArtist(string _artist);
	void setTitle(string _title);
	void setNumTracks(int _num);
	void setReleaseDate(string _date);
	void setGenre(string _genre);

	string getGenre();
	string getArtist();
	string getTitle();
	int getNumTracks();
	string getReleaseDate();
	
};
#endif