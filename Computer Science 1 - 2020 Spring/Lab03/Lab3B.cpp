/* Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
 Date: January 27, 2020
 Instructor: Joseph Helsing
 Description: Calculate sales tax given user prompted purchase value.
*/

#include <iostream>
using namespace std;

int main() {

	double value, salesTax;
	const double taxRate = 0.0825;

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	cout << "Enter purchase value:";
	cin >> value;

	salesTax = value * taxRate;
	value += salesTax;

	cout << "The final amount is $" << value << endl;

	return(0);
}