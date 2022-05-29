/* Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
 Date: 2/17/20
 Instructor: Joseph Helsing
 Description: 	For Loop. Write a program to find the sum of all even numbers between any two randomly genereated integers. 
				Include the random numbers.
*/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>

using namespace std;

/*
First integer between 1 and 10 inclusive.
Second integer between 11 and 20 inlcusive.
Include random numbers in sum if even.
Display random numbers and sum on screen with suitable messages.
*/


void setcolor(unsigned short color)                 //The function that you'll use to
{                                                   //set the colour
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon,color);
}

int draw(int low, int high) {
	
	int start, end;

	if(low%2 == 0) start = low; else start = low + 1;
	if(high%2 == 0) end = high; else end = high - 1;
	
	string line0 = "0  1  2  3  4  5  6  7  8  9 ";
	string line1 = "10 11 12 13 14 15 16 17 18 19";
	string line2 = "20 21 22 23 24 25 26 27 28 29";
	string line3 = "30 31 32 33 34 35 36 37 38 39";
	string line4 = "40 41 42 43 44 45 46 47 48 49";
	string line5 = "50 51 52 53 54 55 56 57 58 59";
	string line6 = "60 61 62 63 64 65 66 67 68 69";
	string line7 = "70 71 72 73 74 75 76 77 78 79";
	string line8 = "80 81 82 83 84 85 86 87 88 89";
	string line9 = "90 91 92 93 94 95 96 97 98 99";
	
	cout << to_string(low) << endl;
	
	switch(low/10) {
		case(0):
		setcolor(5);
		line0.replace(line0.find(to_string(low)),2,(to_string(low)));
		break;
		case(1):
		setcolor(5);
		line1.replace(line1.find(to_string(low)),2,(to_string(low)));
		break;
		case(2):
		setcolor(5);
		line2.replace(line2.find(to_string(low)),2,(to_string(low)));
		break;
		case(3):
		setcolor(5);
		line3.replace(line3.find(to_string(low)),2,(to_string(low)));
		break;
		case(4):
		setcolor(5);
		line4.replace(line4.find(to_string(low)),2,(to_string(low)));
		break;
		case(5):
		setcolor(5);
		line5.replace(line5.find(to_string(low)),2,(to_string(low)));
		break;
		case(6):
		setcolor(5);
		line6.replace(line6.find(to_string(low)),2,(to_string(low)));
		break;
		case(7):
		setcolor(5);
		line7.replace(line7.find(to_string(low)),2,(to_string(low)));
		break;
		case(8):
		setcolor(5);
		line8.replace(line8.find(to_string(low)),2,(to_string(low)));
		break;
		case(9):
		setcolor(5);
		line9.replace(line9.find(to_string(low)),2,(to_string(low)));
		break;
	}
	setcolor(0);
	/*
	vals[low/10][low%10] = ("\033[22;31m%c",low);
	vals[high/10][high%10] = static_cast<char>("\033[22;31m%c",high);
	*/

	printf("/‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\\\n");
	cout << "|" << line0 << "|" << endl;
	cout << "|" << line1 << "|" << endl;
	cout << "|" << line2 << "|" << endl;
	cout << "|" << line3 << "|" << endl;
	cout << "|" << line4 << "|" << endl;
	cout << "|" << line5 << "|" << endl;
	cout << "|" << line6 << "|" << endl;
	cout << "|" << line7 << "|" << endl;
	cout << "|" << line8 << "|" << endl;
	cout << "|" << line9 << "|" << endl;
	printf("\\_____________________________/\n");
	
	return 0;
}

int main() {
	srand(time(NULL));
	int randValA = (rand()%50);
	int randValB = (rand()%50)+50;
	

	

	printf("%d - %d\n",randValA,randValB);

	draw(randValA,randValB);
	return(0);
}

