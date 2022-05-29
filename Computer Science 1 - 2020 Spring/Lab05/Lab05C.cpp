/* Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
 Date: 2/17/20
 Instructor: Joseph Helsing
 Description: 	For Loop. Write a program to find the sum of all even numbers between any two randomly genereated integers. 
				Include the random numbers.
*/

#include <iostream>
#include <ctime>
using namespace std;

/*
First integer between 1 and 10 inclusive.
Second integer between 11 and 20 inlcusive.
Include random numbers in sum if even.
Display random numbers and sum on screen with suitable messages.
*/

int main() {
	srand(time(NULL));
	int randValA = (rand()%10)+1;
	int randValB = (rand()%10)+11;
	int sum = 0;
	int start, end;
	
	if(randValA%2 == 0) start = randValA; else start = randValA + 1;
	if(randValB%2 == 0) end = randValB; else end = randValB - 1;

	for(int i = start; i <= end; i+=2) {
		sum += i;
	}
	printf("%d - %d , Sum : %d.\n",randValA,randValB,sum);

	return(0);
}