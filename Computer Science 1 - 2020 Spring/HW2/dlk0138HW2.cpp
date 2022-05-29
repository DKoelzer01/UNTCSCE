/* 
Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
Date: February 23, 2020
Instructor: Joseph Helsing
Description: Homework 2. Paintball game.
*/

#include<iostream>
#include<string>
#include<ctype.h>
#include<ctime>

using namespace std;

int main() {
	bool debug = false; //Can be used to show partner and enemy positions. Value should be false during actual gameplay.
	
	cout << "+----------------------------------------------+" << endl;
	cout << "|       Computer Science and Engineering       |" << endl;
	cout << "|        CSCE 1030 - Computer Science I        |" << endl;
	cout << "| \033[1;34mDaniel Koelzer   dlk0138  dlk0138@my.unt.edu\033[0m |" << endl;
	cout << "+----------------------------------------------+" << endl;
	cout << endl << endl << endl;
	
	srand(time(NULL));
	const int size = 10;
	int tries = 3;
	int friendXPos,friendYPos,enemyXPos,enemyYPos;
	
	enemyXPos = rand()%size;
	enemyYPos = rand()%size;
	do{
		friendXPos = rand()%size;
		friendYPos = rand()%size;
	} while (friendXPos == enemyXPos && friendYPos == enemyYPos);
	
	if(debug) {
		cout << enemyXPos << ", " << enemyYPos << endl;
		cout << friendXPos << ", " << friendYPos << endl;
	}
	
	string rawUserInput;
	bool keepPlaying = true;
	bool cont = false;
	bool partnerFound = false;
	int userXPos,userYPos;
	enum OpponentOrPartner{NIL = 0,OPPONENT = 'O',PARTNER = 'P'}; //Declare enum for choice values. NIL serves as default.
	do {
		rawUserInput = "";
		printf("Enter your guess:");
		getline(cin,rawUserInput);
		if(rawUserInput.length() == 3) { //Check for valid input length.
			if(isdigit(rawUserInput.at(0))) {
				userXPos = rawUserInput.at(0) - 48;
			}
		
			if(isdigit(rawUserInput.at(2))) {
				userYPos = rawUserInput.at(2) - 48;
			}
			
			OpponentOrPartner choice;
			do{
				cont = false; // Reset all values to defaults for each iteration to avoid unwanted outcomes.
				choice = NIL;
				cout << "Do you want to attack your " << "\033[1;31m[O]\033[0m" << "pponent or find your " << "\033[1;32m[P]\033[0m" << "artner: "; 
				//Highlight choices for better readability.
				choice = static_cast<OpponentOrPartner>(toupper(getchar())); //normalize input to uppercase, cast to enum.
				cin.ignore(); // ignore the "\n" left at the end of cin from using getchar().
				switch(choice){
					case(OPPONENT):
						cout<<"\033[1;31mOPPONENT\033[0m"<<endl;
						if(userXPos == enemyXPos && userYPos == enemyYPos) { //Case for user attacking and hitting enemy.
							cout << "You shot your opponent. \033[1;32mYou won.\033[0m"<< endl;
							keepPlaying = false;
						} else if(userXPos == friendXPos && userYPos == friendYPos) { //Case for user attacking and hitting friendly.
							cout << "Oops, you shot your partner. \033[1;31mGame over!!!\033[0m"<< endl;
							keepPlaying = false;
						} else {
							cout << "You missed your opponent." << endl; // Case for user attacking and missing enemy and friendly.
							tries--;
						}
						
						cont = true;
						break;
					case(PARTNER):
						cout<<"\033[1;32mPARTNER\033[0m"<<endl;
						if(userXPos == friendXPos && userYPos == friendYPos) { //Case for user searching for partner and finding partner.
							if(!partnerFound){
							cout << "You found your partner."<< endl;
							tries *= 2;
							cout << "\033[1;33mTries Doubled!\033[0m" << endl;
							partnerFound = true;
							} else {
								cout << "You've already found your partner, don't cheat. You lose a try." << endl; // Cheat prevention.
								tries--;
							}
						} else if(userXPos == enemyXPos && userYPos == enemyYPos) { //Case for user searching for partner and hitting enemy.
							cout << "Oops, you alerted your opponent. You lose. \033[1;31mGame over!!!\033[0m"<< endl;
							keepPlaying = false;
						} else {
							cout << "You missed your partner." << endl; // Case for user searching for partner and finding nothing.
							tries--;
						}
						
						cont = true;
						break;
					default:
						cout<<"\033[1;31mINVALID INPUT\033[0m"<<endl; // catch invalid O / P choice.
						cont = false;
						break;
				}
			}
			while(!cont);
			
			cout << endl; //insert new line for readability.
	
		} 
		else {
			printf("Invalid input. Please input an x value and y value 0 - 9 in the format \"X Y\"\n");
			continue; //catch invalid x,y input.
		}
		
		if(keepPlaying) cout << "You have " << tries << " tries remaining." << endl;
				
	} while (tries > 0 && keepPlaying); // Check if user is out of tries or has beat/lost the game.
	if(tries == 0) {
		cout << "You've finished all tries. \033[1;31mGame over.\033[0m" << endl; 
	}
	return(0);
}