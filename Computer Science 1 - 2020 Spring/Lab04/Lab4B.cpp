/* Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
 Date: 2/10/20
 Instructor: Joseph Helsing
 Description: Switch-Case. Multiple choice question.
*/
#include <iostream>
#include <cstdlib>
#include <ctype.h>
using namespace std;
enum Choice {CHOICE1 = 1, CHOICE2, CHOICE3, CHOICE4, CHOICE5};
Choice userChoice;
char ch;
int main() {
	//compressed quiz question into 1 line string to reduce line count.
	printf("Welcome to the 1030 quiz. Please choose the correct answer to the following question:\nWhich planet in our solar system is on average farthest away from the sun?\nA. Mercury\nB. Jupiter\nC. Neptune\nD. Saturn\nE. Pluto\nPlease enter your choice (A, B, C, D, or E):");
	scanf("%c",&ch); 
	ch = toupper(ch);
	userChoice = Choice(ch-64); // Cast the character the user input into the range 
	switch(userChoice){
		case(CHOICE1):
		printf("That is incorrect! Mercury is the planet closest to the sun.\n");
		break;
		case(CHOICE2):
		printf("That is incorrect! Jupiter is the fifth planet from the sun.\n");
		break;
		case(CHOICE3):
		printf("That is correct! Neptune is the planet farthest away from the sun.\n");
		break;
		case(CHOICE4):
		printf("That is incorrect! Saturn is the sixth planet from the sun.\n");
		break;
		case(CHOICE5):
		printf("That is incorrect! Pluto is not a planet, but a dwarf planet.\n");
		break;
		default:
		printf("That is not a valid choice.\n");
		break;
	}
	return(0);
}