/* Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
 Date: 3/2/2020
 Instructor: Joseph Helsing
 Description: Array. Find average of 10 students.
*/

#include <iostream>
using namespace std;

int main() {
const int SIZE=10;
	int height[SIZE] = {0};
	int above_average[SIZE] = {0};
	int below_average[SIZE] = {0};
	int sum = 0;
	int average = 0;
	for(int i = 0; i < SIZE; i++) {
		cout << "Enter height in inches of student #"<<i+1<<":";
		cin >> height[i];
		sum += height[i];
	}
	average = (sum / SIZE);
	cout << endl;
	cout << "You entered:"<<endl;
	for(int i = 0; i < SIZE; i++) {
		printf("%-3d|",height[i]);
		if(height[i] < average) {
			below_average[i] = height[i];
		} else if(height[i] > average){
			above_average[i] = height[i];
		}
	}
	cout << "\n\n";
	
	cout << "Average: " << average <<   "\n\n";
	cout << "Below average:" << endl;
	for(int i = 0; i < SIZE; i++) {
		if(below_average[i] != 0) {
			printf("%-3d|",below_average[i]);
		} else {
			cout << "   |";
		}
	}
	
	cout <<  "\n\n";
	cout << "Above average:" << endl;
	for(int i = 0; i < SIZE; i++) {
		if(above_average[i] != 0) {
			printf("%-3d|",above_average[i]);
		} else {
			cout << "   |";
		}
	}
	cout <<  "\n\n";

	return(0);
}