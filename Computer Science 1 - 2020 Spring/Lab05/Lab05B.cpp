/* Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
 Date: 2/17/20
 Instructor: Joseph Helsing
 Description: 	Do-While. Compute average of grades inside a do-while loop.
				Check if the entered grade is within bounds.
				Loop after bounds check if user prompt evaluates.
*/

#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string>
using namespace std;

int main() {
	int validGradeCount;
	double averageGrade,inputGrade,gradeSum;
	bool cont;
	string strInput;
	char charInput;
	
	validGradeCount = 0;
	averageGrade = 0.0;
	gradeSum = 0.0;
	inputGrade = 0.0;
	cont = false;
	
	do {
	cout << "Enter a grade : ";
	cin >> inputGrade;
	
	if(inputGrade < 0 || inputGrade > 100) {
		cout << "Error, Grade out of bounds. Please enter a grade between 0 and 100." << endl;
		cont = false;
	} else {
		cout << "Grade added. Would you like to enter another grade? (Y/N)\n";

		gradeSum += inputGrade;
		inputGrade = 0.0;
		validGradeCount++;
		
		cin >> strInput;
		charInput = strInput[0];
		
		if(toupper(charInput) == 'Y') {
			cont = false;
		} else {
			cont = true;
		}
	}

	}while (!cont);

	averageGrade = gradeSum / validGradeCount;
	printf("The average grade is %1.1f .\n",averageGrade);
	return(0);
}