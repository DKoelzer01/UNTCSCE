//Austin Leath
//azl0007
//CSCE3600.001 Group 7
//10/14/2021

/*
	Instructions:
	This code will contain a single function (and the include directive to your headerfile) to count the number of leading zeros
	in the 32-bit input argument passed tothe  function  (leading  zeroes  are  the  zeroes  that occur  in the  most significant
	bit positions of the number until a bit value of ‘1’ is found).
*/
#include "major1.h"

void countLeadingZeros(int input /* 32-bit integer */)
{

	int initialInput;	   // initialize a variable that will store the initial input into. This is used later at the end of the function when calling printf()
	int leadingZerosCount; // initialize leading zeros count as an integer. This will be used when iterating through the do while loop

	initialInput = input;  // set initialInput to input for later
	leadingZerosCount = 0; // set leadingZerosCount to initial count of 0

	do
	{
		leadingZerosCount++;
		input <<= 1;				 //bitwise shift left
	} while (!(input & (~INT_MAX))); // while the input is not valuated as bitwise AND of INT_MAX

	printf("The number of leading zeroes in %d is %d\n", initialInput, leadingZerosCount); // output results for user to read
}
