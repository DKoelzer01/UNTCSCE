/* 	Author: Daniel Koelzer
	Date:3/26/20
	Instructor: Joseph Helsing
	Description: Display array.
*/

#include "Lab08_Header.h"

void showArray(float array[], int size) {
	for(int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}
