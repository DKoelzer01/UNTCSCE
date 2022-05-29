/* Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
 Date: 3/2/2020
 Instructor: Joseph Helsing
 Description: Two dimensional arrays. Enter a 2d matrix and display it.
*/

#include <iostream>
using namespace std;

int main() {
	int rowMax = 0;
	int colMax = 0;
	const int ROW_SIZE=2;
	const int COLUMN_SIZE=5;
	int matrix[ROW_SIZE][COLUMN_SIZE];
	for(int i = 0; i < ROW_SIZE; i++) {
		for(int h = 0; h < COLUMN_SIZE;h++) {
			cout << "Enter data for row#"<<i+1<<" and column #"<<h+1<<":";
			cin>>matrix[i][h];
		}
	}
	
	cout << "You entered:" << endl;
	for(int i = 0; i < ROW_SIZE; i++) {
		for(int h = 0; h < COLUMN_SIZE;h++) {
			rowMax = (rowMax < matrix[i][h]) ?  matrix[i][h] : rowMax;
			printf("%-3d\t",matrix[i][h]);
		}
		printf("|Max:%-3d\n",rowMax);
		rowMax = 0;
	}
	
	for(int i = 0; i < COLUMN_SIZE; i++) {
		cout << "--------";
	}
	cout <<"┼\n";
	
	for(int i = 0; i < COLUMN_SIZE; i++) {
		for(int h = 0; h < ROW_SIZE; h++) {
			colMax = (colMax < matrix[h][i]) ? matrix[h][i] : colMax;
		}
		printf("Max:%-3d\t",colMax);
		colMax = 0;
	}
	
	cout << "\n";
	return(0);
}