/* Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
 Date:	2/10/20
 Instructor: Joseph Helsing
 Description: String Manipulation - Palindrome Tester
*/

#include <iostream>
#include <ctype.h>
using namespace std;
bool palindrome = false;
int inputLength;
string input = "";
int main() {
	printf("Input a word with 3, 4, or 5 letters.\n");
	cin >> input;
	inputLength = input.length();

	//Normalize case
	string inputTemp = input;
	for(int i = 0; i < inputLength; i++) 
		input[i]=toupper(input[i]);

	//check if in bounds.
	if(inputLength < 3 || inputLength > 5); 
	else{
		if(inputLength == 3) {
			if(input[0] == input[2])
				palindrome = true;
		}else if(inputLength == 4) {
			if(input[0] == input[3])
				if(input[1] == input[2])
					palindrome = true;
		}else {
			if(input[0] == input[4])
				if(input[1]==input[3])
					palindrome = true;
		}
	}
	
	if(palindrome) {
		cout << inputTemp << " is a palindrome." << endl;
	} else {
		cout << inputTemp << " is not a palindrome or is the wrong size." << endl;
	}
	return(0);
}