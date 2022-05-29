/* 	Author: Daniel Koelzer
	Date:4/16/20
	Instructor: Joseph Helsing
	Description: Lab 10 C
*/
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
	int arrSize;
	cout << "Enter dynamic array size: ";
	cin >> arrSize;
	
	int* numlist = new int[arrSize];
	
	int min;
	for(int i = 0; i < arrSize; i++) {
		cout << "Enter a data point: ";
		cin >> *(numlist + i); 
		if(min > *(numlist + i)) {
			min = *(numlist + i);
		}
	}
	
	cout << "Minimum: " << min << endl;
	delete numlist;
	return 0;
}