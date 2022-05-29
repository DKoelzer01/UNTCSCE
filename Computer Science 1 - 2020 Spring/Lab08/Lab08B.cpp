/* 	Author: Daniel Koelzer
	Date:3/26/20
	Instructor: Joseph Helsing
	Description: Calculate max grade for students.
*/

#include "Lab08_Header.h"


int main() {
	float grades[ROWS][COLS];
	float maximum[ROWS];

	for(int row = 0; row < ROWS; row++) {
		for(int col = 0; col < COLS; col++) {
			cout << "Enter QUIZ #" << col+1 << " for STUDENT #" << row + 1 << ": ";
			cin >> grades[row][col];
		}
	}	
	
	computeMaximum(grades,ROWS,maximum);
	
	for(int row = 0; row < ROWS; row++) {
		for(int col = 0; col < COLS; col++) {
			cout << grades[row][col] << " ";
		}
		cout << endl;
	}	
	
	showArray(maximum,ROWS);
	
	return 0;
}