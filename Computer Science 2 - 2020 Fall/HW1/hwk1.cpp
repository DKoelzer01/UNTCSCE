/* 
Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
Date: 9/9/2020
Instructor: David M. Keathly
Description: Homework 1. Grades
*/

/*
The program starts by initializing an int called "numStudents". 
This is used shortly to find the total number of lines with text on them, minus the first line. 
This goes on the assumption that any data files loaded will be properly formatted. 
A line with a single alpha character and nothing else would result in the program attempting to pull data from an empty string.

Next, an instance of the "classStats" struct is initialized and all of its' values are populated.
An input file-stream is opened called "fileRead". This is used to load the grades file twice, with load error checking for the first time.
The first time is used to count the number of lines with an alpha character at the beginning, minus the first line, and store this value in "numStudents".
The second time populates the course name and student array with the values found in the file.

The min and max values of the class averages are calculated while pulling individual's data.
The sum is held in the classA.mean value to later be used to calcluate the mean.
The median will be calculated after the array is sorted.

Once the array is sorted using the bubble() function provided in "bubble.h", the median can be calculated.
If the class has an ODD number of students, simply take the middle student in the list (numStudents/2)
If the class has an EVEN number of students, take the two middle students (numStudents/2 and numStudents/2 - 1), and find the average of their averages.

Finally, the data is formatted and output to the terminal student by student.
As each student's data is printed to the terminal, the associated memory is deallocated to avoid memory leaks.
*/

#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "bubble.h"
#include <iostream>
#include <fstream>
#include <sstream>

struct classStats {
	char * courseName;
	float mean;
	float min;
	float max;
	float median;
};

int main()
{
	int numStudents = 0; //Counting variable to count the number of students found in the data sheet. Calculated prior to writing data to the array.
	
	classStats classA;
	classA.courseName = new char[8]; //8 Chars allocated for the name, plus null (assuming all courses will follow the ABCD1234 naming format of UNT courses.)
	classA.mean = 0;
	classA.min = 0;
	classA.max = 0;
	classA.median = 0;
	
	std::ifstream fileRead;

	
	//Opening the file once to count the number of students ahead of time to allocate the correct sized Student array.
	fileRead.open("grades");
	if(!fileRead.is_open()) { std::cout << "File could not be opened.\n"; return 1; } //check if file loads properly.
	while(!fileRead.eof()) {
		std::string temp = ""; //clear temp string for holding each individual line.
		std::getline(fileRead,temp); //hold each line of text in the temp string
		if(temp != "") { //skip empty lines.
			if(isalpha(temp[0])) { numStudents++; }
		} else {
			continue;
		}
	}
	fileRead.close();
	numStudents--; //subtract first line.
	
	student * studentArray[numStudents]; // initialize the student array.
	
	fileRead.open("grades"); //Open file to pull data.
	
	std::string temp = ""; //clear temp string for holding each individual line.
	std::getline(fileRead,temp); //hold each line of text in the temp string
	std::stringstream(temp) >> classA.courseName; //push the string to the course name. any left-over text/whitespace is ignored and erased later.
	
	int index = 0;
	while(!fileRead.eof()) {
		std::string temp = ""; //clear temp string, discarding any leftover text from previous iterations.
		std::getline(fileRead,temp); //hold each line of text in the temp string
		if(temp != "") { //skip empty lines.
		studentArray[index] = (student *) malloc(sizeof(student)); //allocate space for the student data
		studentArray[index]->first = new char[12]; //12 character first name
		studentArray[index]->last = new char[12]; //12 character last name
		std::stringstream(temp) >> studentArray[index]->first >> studentArray[index]->last >> studentArray[index]->exam1 >> studentArray[index]->exam2 >> studentArray[index]->exam3; //read student data from 
		studentArray[index]->mean = (studentArray[index]->exam1 + studentArray[index]->exam2 + studentArray[index]->exam3)/3.0;
		
		//calculate min/max/mean values for class.
		float studentMean = studentArray[index]->mean;
		if(index==0) { classA.min = studentMean;}
		classA.min = (studentMean < classA.min) ? studentMean : classA.min;
		classA.max = (studentMean > classA.max) ? studentMean : classA.max;
		classA.mean += studentMean;
		
		index++;
		} else {
			continue;
		}
	}
	fileRead.close();
	//Sort the array using bubble sort.
	bubble(studentArray,numStudents);
	
	//calculate class median/mean.
	classA.mean /= numStudents;
	
	if(numStudents%2 == 1) {
	classA.median = studentArray[(numStudents/2)]->mean;
	} else {
		classA.median = ( studentArray[(numStudents/2)]->mean + studentArray[(numStudents/2)-1]->mean)/2;
	}
	
	printf("123456789012345678901234567890123456789012345678901234567890\n");
	printf("%s MEAN:  %5.2f MIN:  %5.2f MAX:  %5.2f MEDIAN:  %5.2f\n",classA.courseName,classA.mean,classA.min,classA.max,classA.median);
	for(int i = 0; i < numStudents; i++) {
		printf("%12s%12s  %5.2f\n",studentArray[i]->first,studentArray[i]->last,studentArray[i]->mean);
		delete studentArray[i]->first;
		delete studentArray[i]->last;
		free(studentArray[i]);
	}
	
	delete classA.courseName;
	
	return 0;
}
