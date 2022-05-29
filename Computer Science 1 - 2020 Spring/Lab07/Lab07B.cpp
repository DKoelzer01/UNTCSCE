/* 	Author: Daniel Koelzer
	Collaborated with: Kevin Tran, Austin Carlin, and Seth Angelone.
	Date:3/25/20
	Instructor: Joseph Helsing
	Description: Find discriminant of quadratic function given A,B,C from user input.
*/

#include <iostream>

using namespace std;
double bb_4ac();
void get_coeff(double& coeff, int pos);

int main() {
	double d;
	d = bb_4ac();
	cout << "D = " << d << endl;
	return 0;
	}

double bb_4ac() {
	double a,b,c;
	get_coeff(a,2);
	get_coeff(b,1);
	get_coeff(c,0);
	return (b*b-4*a*c);
}

void get_coeff(double& coeff, int pos) {
	switch(pos) {
		case(2):
			cout << "A: ";
			cin >> coeff;
			break;
		case(1):
			cout << "B: ";
			cin >> coeff;
			break;
		case(0):
			cout << "C: ";
			cin >> coeff;
			break;
		default:
			break;
	}
}
