/* Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
 Date: January 27, 2020
 Instructor: Joseph Helsing
 Description: Given 5 variables and 1 constant "OFFSET", use arithmetic functions to return a value of 0 using all 6 variables.
*/

#include <iostream>
using namespace std;

int main() 
{
	const float OFFSET = -0.5;

	int var1 = 30;
	int var2 = 60;
	int var3 = 2;
	char var4 = '0';
	double var5 = 48.5;

	int var6 = (var2 / var1 - var3)*(var5 - var4 + OFFSET);
	cout << var6 << endl;

	return(0);
}