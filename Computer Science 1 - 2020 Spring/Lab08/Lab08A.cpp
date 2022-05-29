/* 	Author: Daniel Koelzer
	Collaborated with: Kevin Tran, Austin Carlin, and Seth Angelone, Gerald Hoard.
	Date:3/26/20
	Instructor: Joseph Helsing
	Description:
*/

/* 	Function: Swap
	Parameters: int a, int b
	Return:	none
	Description: Swaps A and B using pass by reference and a holding int.
*/

/* 	Function: sortArray
	Parameters: int array arr, int mySize, bool sortType
	Return:	none
	Description: Sorts the array.
*/

/* 	Function: getArray
	Parameters: int array arr, int size.
	Return: none
	Description: Prompts user for array length and values to populate the array. 
*/

/* 	Function: showArray
	Parameters: int array arr, int size
	Return: none
	Description: Prints the contents of the array.
*/

#include <iostream>
using namespace std;
const int SIZE = 20;

void swap(int& a, int& b);
void sortArray(int arr[], int size, bool sortType);
void getArray(int arr[], int& size);
void showArray(int arr[], int size);

int main() {
	int myArray[SIZE];
	int mySize;
	getArray(myArray,mySize);
	
	sortArray(myArray,mySize,true);
	cout << "In ascending order:" << endl;
	showArray(myArray,mySize);
	
	sortArray(myArray,mySize,false);
	cout << "In descending order:" << endl;
	showArray(myArray,mySize);
	return 0;
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void sortArray(int arr[], int size, bool sortType) {
	if(sortType) {
		for(int i = 0; i < size; i++) {
			for(int j = i; j < size; j++) {
				if(arr[j] < arr[i]) {
					swap(arr[j],arr[i]);
				}
			}
		}
	} else {
		for(int i = 0; i < size; i++) {
			for(int j = i; j < size; j++) {
				if(arr[j] > arr[i]) {
					swap(arr[j],arr[i]);
				}
			}
		}
	}
}

void sortArray(int arr[], int size) {
	for(int i = 0; i < size; i++) {
		if(arr[i] < arr[0]) {
			swap(arr[i],arr[0]);
			for(int j = 1; j < i; j++) {
				swap(arr[j],arr[i]);
			}
		}
	}
}


void getArray(int arr[], int& size) {
	cout << "Enter array length less than 21: ";
	cin >> size;
	for(int i = 0; i < size; i++) {
		cout << "Input a value for " << i << ": ";
		cin >> arr[i];
	}
}

void showArray(int arr[], int size) {
	for(int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}