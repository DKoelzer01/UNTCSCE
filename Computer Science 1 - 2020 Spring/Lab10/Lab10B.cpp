/* 	Author: Daniel Koelzer
	Date:4/16/20
	Instructor: Joseph Helsing
	Description: Lab 10 B
*/

#include <iostream>
using namespace std;

struct House
{
	string address;
	int age;
	double area;
	double price;
};

int main() 
{
	House *housePtr;
	housePtr = new House;
	
	cout << "Enter Address: ";
	getline(cin,housePtr->address);
	
	cout << "Enter Age: ";
	cin >> housePtr->age;

	cout << "Enter Area: ";
	cin >> housePtr->area;
	cout << endl;
	
	if(housePtr->age < 15) {
		housePtr->price = housePtr->area * 150;
	} else {
		housePtr->price = housePtr->area * 100;
	}
	
	cout << housePtr->address << ", $" << housePtr->price << endl;
	delete housePtr;
	
	return 0;
}