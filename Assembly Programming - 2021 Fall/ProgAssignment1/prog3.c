/*
	Daniel Koelzer  -  dlk0138
	CSCE2610.002
	9/16/2021
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
	char array[128] = "";
	char lowercase[128] = "";
	int len = 0;
	printf("Enter a valid word (No whitespace, alphabet only.)\n");
	scanf("%s",array); //User input
	
	char curChar = array[0]; //Initialize as the 1st character of the array.
	while(curChar != '\0') {
		if(curChar > 64 && curChar < 91) { //Check if current character is within bounds of uppercase chars.
			lowercase[len] = curChar + 32;  //convert uppercase to lower
		} else {
			lowercase[len] = curChar; //Preserve lowercase as lowercase
		}
		len++; 
		curChar = array[len];  // Set current character to next index of array.
	}
	
	printf("Word: \"%s\"\nLowercase: \"%s\"\nLength: %d\n",array,lowercase,len);
	return 0;
}