/* 	Author: Daniel Koelzer
	Collaborated with: Kevin Tran, Austin Carlin, and Seth Angelone.
	Date:3/25/20
	Instructor: Joseph Helsing
	Description: Calculate surface area of a Right Cylinder.
*/

/* Function: calcBaseArea
Parameters: Float: Radius.
Return: Float: base area.
Description: Calculates the surface area of the base of the cylinder.
*/

/* Function: calcSideArea
Parameters: Float: Height. Float: Radius.
Return: Float: Side area.
Description: Calculates the surface area of the side of the cylinder.
*/

/* Function: calcBaseArea
Parameters: Float: base. Float: side.
Return: Void.
Description: Calculates the surface area and outputs the result to the console.
*/


#include <iostream>
#include <cmath>
using namespace std;

float calcBaseArea(float r);
float calcSideArea(float h, float r);
void prntSurfArea(float base, float side);

int main() {
	float h;
	float r;
	float base_area;
	float side_area;
	
	//Prompt user input for Radius and Height.
	cout << "Enter the length of the radius for the right cylinder in feet: ";
	cin >> r;
	
	cout << "Enter the height of the right cylinder in feet: ";
	cin >> h;
	
	//Call function to Calculate Base surface area.
	base_area = calcBaseArea(r);
	cout << "Base surface area of the right cylinder is " << base_area << " square feet." << endl;
	
	//Call function to Calculate Side surface area.
	side_area = calcSideArea(h,r);
	cout << "Side surface area of the right cylinder is " << side_area << " square feet." << endl;
	
	//Call function to output final surface area.
	prntSurfArea(base_area, side_area);
	
	return 0;
}

float calcBaseArea(float r) {
	return 3.14*pow(r,2);
}

float calcSideArea(float h, float r) {
	return h * 2 * 3.14 * r;
}

void prntSurfArea(float base, float side) {
	cout << "The total surface area is " << (2*base + side) << " square feet." << endl;
}