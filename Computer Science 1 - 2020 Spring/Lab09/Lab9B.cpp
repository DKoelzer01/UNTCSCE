/* 	Author: Daniel Koelzer
	Date:4/10/2020
	Instructor: Joseph Helsing
	Description: copies data from one txt file to another.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void get_stream(ifstream& in_s,ofstream& o_s);
int main() {
	string str;
	ifstream in_stream;
	ofstream out_stream;
	
	get_stream(in_stream,out_stream);
	
	while (!in_stream.eof() && !in_stream.fail() && !in_stream.bad())
	{
		getline(in_stream,str);
		int iterator = 0;
		while (str[iterator] != '\0')
		{
			out_stream.put(str[iterator]);
			iterator++;
		} 
	}
		
	in_stream.close();
	out_stream.close();
	return(0);
}

void get_stream(ifstream& in_s,ofstream& o_s) {
	char input_file[15];
	cout << "Enter the name of the input file: ";
	cin >> input_file;
	
	in_s.open(input_file);
	if(in_s.fail()) {
		cout << "Unable to open input file " << input_file << endl;
		exit(EXIT_FAILURE);
	}
	
	char output_file[15];
	cout << "Enter the name of the output file: ";
	cin >> output_file;
	
	o_s.open(output_file);
	if(o_s.fail()) {
		cout << "Unable to open output file " << output_file << endl;
		exit(EXIT_FAILURE);
	}
}
