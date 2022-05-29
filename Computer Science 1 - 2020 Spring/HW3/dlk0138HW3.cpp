/* 
Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
Date: March 27, 2020
Instructor: Joseph Helsing
Description: Homework 3. Lava Game.
*/

/* 	Function: printArray
	Parameters: 	2d char array
	Return:			none
	Description:	 outputs entire array with formatting.
*/

/* 	Function: runGame
	Parameters: 	int& tries, 2d char array, 2d char array, int& lava level
	Return:			none
	Description:	 Main wrapper for game functionality.
*/

/* 	Function: populate
	Parameters: 	2d character array, target char.
	Return:			none
	Description: 	Fills array with the desired character at a random position within bounds. Has error checking.
*/

/* 	Function: updateLava
	Parameters: 	2d char array, 2d char array, int& lavaLevel 
	Return:			none
	Description: 	Fills row with 'L' representing Lava, follows the current lava level.
					Does this for both arrays
*/

#include<iostream>
#include<string>
#include<ctype.h>
#include<ctime>

using namespace std;

const int WIDTH = 5; 
const int HEIGHT = 10;
//Size constants for the array dimensions.

void updateLava(char arr1[WIDTH][HEIGHT], char arr2[WIDTH][HEIGHT],int level); //Updates lava level.
void printArray(char arr[WIDTH][HEIGHT]); //Draws array to console.
void runGame(int& tries, char arr[WIDTH][HEIGHT], char viewArr[WIDTH][HEIGHT], int& lavaLevel); //Main wrapper for game.
void populate(char arr[WIDTH][HEIGHT],char target); //Fill array with target characters, with error checking as to avoid overwriting non-empty spaces.

int main() {
	bool debug = false; //Can be used to show hidden array. Value should be false during actual gameplay.
	
	cout << "+----------------------------------------------+" << endl;
	cout << "|       Computer Science and Engineering       |" << endl;
	cout << "|        CSCE 1030 - Computer Science I        |" << endl;
	cout << "| \033[1;34mDaniel Koelzer   dlk0138  dlk0138@my.unt.edu\033[0m |" << endl;
	cout << "+----------------------------------------------+" << endl;
	cout << endl << endl << endl;
	
	int tries = 10;
	int lavaLevel = 10;
	//start with 10 tries, and start the lava 1 level below the map.
	
	char hiddenArray[WIDTH][HEIGHT];
	char playField[WIDTH][HEIGHT];

	//fill arrays with X's
	for(int y = 0; y < HEIGHT; y++) {
		for(int x = 0; x < WIDTH; x++) {
			hiddenArray[x][y] = 'X';
			playField[x][y] = 'X';
		}
	}
	
	srand(time(NULL));
	
	for(int i = 0; i < 10; i++) {
		populate(hiddenArray,'R'); //Fill 10 slots with rocks.
	}
	
	for(int i = 0; i < 5; i++) {
		populate(hiddenArray,'E'); //Fill 5 slots with exits.
	}

	if(debug) {
		printArray(hiddenArray); //Show hidden array for debugging purposes.
	}

	
	do{
		runGame(tries, hiddenArray, playField, lavaLevel); //Starts game and runs until player uses all tries, or wins.
	} while (tries > 0);

	printArray(hiddenArray); //Output hidden array to show the player the solution.

	return 0;
}

void printArray(char arr[WIDTH][HEIGHT]) { //Draw arrays character by character, with color formatting and Row/Column headers.
	cout << "  0 1 2 3 4\n";
	for(int y = 0; y < HEIGHT; y++) {
		cout << y << " ";
		for(int x = 0; x < WIDTH; x++) {
			char temp = arr[x][y];
			switch(temp) { //Switch statement for character coloring in arrays.
				case('X'):
				printf("\033[1;0m%c\033[0m ",temp);
				break;
				case('L'):
				printf("\033[1;31m%c\033[0m ",temp);
				break;
				case('R'):
				printf("\033[1;33m%c\033[0m ",temp);
				break;
				case('E'):
				printf("\033[1;32m%c\033[0m ",temp);
				break;
				default:
				cout << temp << " ";
				break;
			}
		}
		cout << "\n";
	}
	cout << "\n";
}

void populate(char arr[WIDTH][HEIGHT],char target) { //Pick random positions for rocks or exits, with error checking.
	int randX = random()%WIDTH;
	int randY = random()%HEIGHT;
		do {
		if(arr[randX][randY] == 'X') {
			arr[randX][randY] = target;
		} else {
			randX = random()%WIDTH;
			randY = random()%HEIGHT;
		}
		} while (arr[randX][randY] != 'X');
}

void updateLava(char arr1[WIDTH][HEIGHT], char arr2[WIDTH][HEIGHT],int level) { //Fill row # level with lava.
		for(int i = 0; i < 5; i++) {
			arr1[i][level] = 'L';
			arr2[i][level] = 'L';
		}
	}

void runGame(int& tries, char arr[WIDTH][HEIGHT], char viewArr[WIDTH][HEIGHT], int& lavaLevel) {
	int x,y;
	printArray(viewArr); //Show viewable array, prompt for user input.
	
	cout << "\n" << tries << " Guesses left." << endl;
	
	
	cout << "Please enter an x and y coordinate:";
	
	cin >> x;
	cin >> y;
	
	tries--; //Decrement tries regardless of user input.
	if((x >= 0 && x <= 4) && (y >= 0 && y <= 9)) { //Bounds checking.
	switch(arr[x][y]) { //Switch statement for tile checks.
		case('X'):
			cout << "You found an empty tile! \033[1;31mThe lava rises!\033[0m" << endl;
			viewArr[x][y] = ' ';
			lavaLevel--;
			updateLava(arr, viewArr, lavaLevel);
		break;
		
		case('E'):
			cout << "\033[1;32mYou found the Exit! GOOD JOB! YOU WON!\033[0m" << endl;
			viewArr[x][y] = arr[x][y];
			tries = -69;
		break;
		
		case('L'):
			cout << "\033[1;31mYou found the LAVA! You lose an extra guess!\033[0m" << endl;
			viewArr[x][y] = arr[x][y];
			lavaLevel--;
			updateLava(arr, viewArr, lavaLevel);
			tries--;
		break;
		
		case('R'):
			cout << "You found a Rock, \033[1;31mouch!\033[0m Please try again." << endl;
			viewArr[x][y] = arr[x][y];
		break;
		
		default: //Default case for unexpected characters.
		cout << "Bad input" << endl;
		break;
	}
	} else {
		cout << "Your position is outside the bounds of the game!" << endl; //Bounds checking.
	}
	
	if(tries == 0 || tries == -1 || tries == -2 ) {
		cout << "You're out of lives. \033[1;31mYou lose!\033[1;0m" << endl;
	}
}

