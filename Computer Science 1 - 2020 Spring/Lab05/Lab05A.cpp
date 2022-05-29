/* Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
 Date: 2/17/20
 Instructor: Joseph Helsing
 Description: 	While Loop. Count number of Alpha, Digit, Whitespace, and Special characters in a user entered string. 
				Any char that is not an alpha, digit, or whitespace is special.
*/

#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;

int main() {
/*
Prompt user for string.
Test each char within while loop.
Store counts in each unique variable.
Print counts at end.
*/
string userInput;
int alpha,dig,white,special;
alpha = 0;
dig = 0;
white = 0;
special = 0;

printf("Enter a String : ");
getline(cin,userInput);
while (userInput.size() > 0) {
	if(isalpha(userInput[0])){
		alpha++;
	} else if (isdigit(userInput[0])) {
		dig++;
	} else if (isspace(userInput[0])) {
		white++;
	} else {
		special++;
	}
	userInput.erase(0,1);
}

printf("The string contained %d Alphabet characters, %d Digits, %d Whitespace characters, and %d Special characters.\n",alpha,dig,white,special);

return(0);
}