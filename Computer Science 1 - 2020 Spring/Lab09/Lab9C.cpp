/* 	Author: Daniel Koelzer
	Date:4/10/2020
	Instructor: Joseph Helsing
	Description: Create a struct, populate with data, output to file
*/

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

struct paintings {
	string name;
	int canvas = 0;
    int paint_brush = 0;
    int cups = 0;
    float tubes = 0;
};

void get_stream(ofstream& o_s, string output_file);
void calcPaintings(paintings& paint, int count);

int main()
{
	ofstream out_stream;
	get_stream(out_stream,"painter.txt");
	
	paintings painter;
	int count;
	
    cout << "Enter the person's name: ";
    cin >> painter.name;
    
    cout << "Enter the number of paintings: ";
    cin >> count;
    
	calcPaintings(painter,count);
	
	out_stream << "Name: " << painter.name << endl;
    out_stream << "Number of Canvases: " << painter.canvas << endl;
    out_stream << "Number of Paint Brushes: " << painter.paint_brush << endl;
    out_stream << "Cups of Water: " << painter.cups << endl;
    out_stream << "Tubes of Paint: " << painter.tubes << endl;
	
    return 0;
}

void calcPaintings(paintings& paint, int count) {
	paint.canvas = count;
    paint.paint_brush = count * 5;
    paint.cups = count * 3;
    paint.tubes = count * 6.5;
}

void get_stream(ofstream& o_s, string output_file) {	
	o_s.open(output_file);
	if(o_s.fail()) {
		cout << "Unable to open output file " << output_file << endl;
		exit(EXIT_FAILURE);
	}
}