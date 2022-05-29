/* Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
 Date: January 27, 2020
 Instructor: Joseph Helsing
 Description: Calculate volume of Cylinder given user prompted Radius and Height.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {

	const double pi = 3.14;
	int radius, height;
	double volume;

	cout << "Enter Radius of the cylinder :" << endl;
	cin >> radius;

	cout << "Enter Height of the cylinder :" << endl;
	cin >> height;

	volume = pi * pow(radius, 2) * height;
	cout << "The volume of the cylinder with radius " << radius << " and height " << height << " is " << volume << endl;

	return 0;
}