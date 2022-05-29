/* 	Author: Daniel Koelzer
	Collaborated with: Kevin Tran, Austin Carlin, and Seth Angelone.
	Date:3/25/20
	Instructor: Joseph Helsing
	Description: Find minimum of array.
*/

#include <iostream>
using namespace std;
const int SIZE = 7;
 
void get_min(double arr[SIZE], double& min);
 
int main()
{
	double my_array[SIZE]={3.2,4.5,-1.0,6.7,-4.5,1.2,3.3};
	double minimum = my_array[0];
 
	get_min(my_array,minimum);
	
	cout << "Smallest value:" << minimum << endl;
	return 0;
}
 
void get_min(double arr[SIZE], double& min) {
	for(int i = 1; i < SIZE; i++) {
		if (min > arr[i])
			min = arr[i];
	}
}