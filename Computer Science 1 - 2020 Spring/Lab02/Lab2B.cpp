#include <iostream>
using namespace std;

int main()
{
	double radius,height,area;
	const double pi = 3.1416;

	cout << "Enter the radius of the cylinder (in inches): ";
	cin >> radius;
	cout << "Enter the height of the cylinder (in inches): ";
	cin >> height;
	area = 2 * pi * radius * (radius + height);
	cout << "The surface area of the cylinder is:" << area << " square inches" << endl;
}
