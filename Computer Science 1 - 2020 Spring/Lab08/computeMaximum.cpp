/* 	Author: Daniel Koelzer
	Date:3/26/20
	Instructor: Joseph Helsing
	Description: Compute maximum function wrapped in an individual file.
*/

#include "Lab08_Header.h"

void computeMaximum(float grades[][COLS],int rows, float maximum[]) {
	for (int i = 0; i < rows; i++) {
		int max = grades[i][0];
		for(int j = 0; j < COLS; j++) {
			if ( grades[i][j] > max) {
				max = grades[i][j];
			}
		}
		maximum[i] = max;
	}
}