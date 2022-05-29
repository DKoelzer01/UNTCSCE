/* 	Author: Daniel Koelzer
	Date:4/16/20
	Instructor: Joseph Helsing
	Description: Lab 10 A
*/

#include <stdio.h>
#include <iostream>
#include <new>

using namespace std;

int main() {
	int my_int = 21;
	int* my_iptr1 = &my_int;
	int* my_iptr2;
	
	cout << "my_int Value:\t\t" << my_int << endl;
	cout << "my_int Address:\t\t" << &my_int << endl;
	cout << "my_iptr1 Address:\t" << my_iptr1 << endl;
	cout << "my_iptr1 Value:\t\t" << *my_iptr1 << endl << endl;
	
	*my_iptr1 = 13;
	cout << "my_int Value:\t\t" << my_int << endl << endl;
	//my_iptr1 is a pointer tied to my_int, so my_int changed with my_iptr1 dereferenced.
	
	my_iptr1 = new int;
	*my_iptr1 = 9;
	cout << "my_int Value:\t\t" << my_int << endl << endl;
	//my_iptr1 is a NEW pointer pointing to a single new int. Changing my_iptr1 while dereferenced does not effect my_int.
	
	my_iptr2 = new int;
	my_iptr2 = my_iptr1;
	cout << "my_iptr2 Value:\t\t" << *my_iptr2 << endl << endl;
	delete my_iptr1;
	//my_iptr2 is a pointer that points to my_iptr1, dereferencing my_iptr2 gives the value of my_iptr1.
	return 0;
}
