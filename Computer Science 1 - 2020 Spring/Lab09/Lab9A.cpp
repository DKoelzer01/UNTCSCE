/* 	Author: Daniel Koelzer
	Date:4/10/2020
	Instructor: Joseph Helsing
	Description: Reads strings from file, finds maximum integer value of each string. outputs max.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main() {
	int max[5];
	int index;
	
	ifstream in_stream;
	in_stream.open("act9A.txt");
	
	if (!in_stream.is_open()) {
      cout << "Could not open file." << endl;
      return 1;
	}

	for(int i = 0; i < 5; i++) {
		string str;
		in_stream >> str;
		max[i] = 0;
		index = -1;
		do {
			index++;
			int val = static_cast<int>(str[index]);
			if (val > max[i]){max[i] = val;}
		} while (str[index] != '\0');
	}
	
	for(int i = 0; i<5;i++) {
		cout << max[i] << " ";
	}
	cout << endl;
	return(0);
}