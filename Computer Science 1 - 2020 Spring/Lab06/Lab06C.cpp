/* Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
 Date: 3/2/2020
 Instructor: Joseph Helsing
 Description: 
*/

#include <iostream>
#include <cstring>
using namespace std;

int main() {
	char str1[30], str2[30];
	int len1, len2;
	
	strcpy(str1,"This is CSE1030");
	
	strcpy(str1,"....... my favorite class");

	strncpy(str1,"This is",7);
	
	cout << "Enter a word with 29 or fewer characters at the prompt: \n";
	cin.getline(str2,30);
	
	len1 = strlen(str1);
	len2 = strlen(str2);
	
	if(len1 != len2) {
		cout << "The C-strings are not the same length and must be different words." << endl;
		return 0;
	} else {
		cout << "The two C-strings are the same length." << endl;
	}
	
	if(strcmp(str1,str2) == 0) {
		cout << "The two C-strings are the same." << endl;
	} else {
		cout << "The two C-strings are NOT the same." << endl;
	}
	
	return(0);
}