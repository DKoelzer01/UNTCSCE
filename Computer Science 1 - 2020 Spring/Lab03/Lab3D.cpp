/* Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
 Date: January 27, 2020
 Instructor: Joseph Helsing
 Description: Assign random labels to 4 test samples.*/

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

string charToString(char input) 
{
	return(string(1,input));
}


string sample(int offset, int range) 
{
	string sampleOut = "";
	char firstChar = (rand() % 26) + 65;
	int firstNum = (rand() % range) + offset;	
	int secondNum = (rand() % range) + offset;
	sampleOut = firstChar + to_string(firstNum) + "-" + to_string(secondNum);
	return sampleOut;
}


int main() 
{
	srand(time(0));
	cout << "There are four test samples:" << endl;
	cout << sample(11,14) << endl;
	cout << sample(25,14) << endl;
	cout << sample(50,14) << endl;
	cout << sample(75,14) << endl;

	return(0);
}

