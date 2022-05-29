// endian.c
// mal0420

/*
	Instructions:
	This code will contain a single function (and the include directive 
	to your header file) to perform the endian swap operation of the 
	32-bit input argument passed to this function. Endianness refers to 
	how the bytes are stored in memory. In a 32-bit word, there are 4 
	bytes – B0, B1, B2, and B3. Let us assume that B0 refers to the least 
	significant byte and B3 the most significant byte.
	The function will swap (exchange) bytes B0 and B3, as well as bytes 
	B1 and B2.
*/

#include "major1.h"

void endian(int input /* 32-bit integer */)
{
	printf("Your input:\t%#010x (%d)\n", input, input);
	// Initialize Variables
	int B0, B1, B2, B3, output;
	// Mask and select bytes
	//	 the hexidecimal value acts as a mask to select only the values
	//	 where there is "FF" since the '&' is comparing with `input`.
	//   instead of hexidecimal, i will simply us the decimal equivalent.
	B0 = (input & /*3*/ 0x000000FF) >> 0;	 // select 4th set of 2 bytes (8 bits) with a mask
	B1 = (input & /*12*/ 0x0000FF00) >> 8;	 // select 3rd set of 2 bytes (8 bits) with a mask
	B2 = (input & /*48*/ 0x00FF0000) >> 16;	 // select 2nd set of 2 bytes (8 bits) with a mask
	B3 = (input & /*128*/ 0xFF000000) >> 24; // select 1st set of 2 bytes (8 bits) with a mask
	// Swap (shift) bytes
	B0 <<= 24; // left-shift the selected bits by 24, 3/4 of the 32-bit total
	B1 <<= 16; // left-shift the selected bits by 16, 1/2 of the 32-bit total
	B2 <<= 8;  // left-shift the selected bits by 8, 1/4 of the 32-bit total
	B3 <<= 0;  // left-shift the selected bits by 0, 3/4 of the 32-bit total
	// Output
	output = (B0 | B1 | B2 | B3); // combine the values like pieces of a puzzle
	printf("Swapped output:\t%#010x (%d)\n", output, output);
}

int endian2(int input /* 32-bit integer */)
{
	// Initialize Variables
	int B0, B1, B2, B3, output;
	// Mask and select bytes
	//	 the hexidecimal value acts as a mask to select only the values
	//	 where there is "FF" since the '&' is comparing with `input`.
	//   instead of hexidecimal, i will simply us the decimal equivalent.
	B0 = (input & /*3*/ 0x000000FF) >> 0;	 // select 4th set of 2 bytes (8 bits) with a mask
	B1 = (input & /*12*/ 0x0000FF00) >> 8;	 // select 3rd set of 2 bytes (8 bits) with a mask
	B2 = (input & /*48*/ 0x00FF0000) >> 16;	 // select 2nd set of 2 bytes (8 bits) with a mask
	B3 = (input & /*128*/ 0xFF000000) >> 24; // select 1st set of 2 bytes (8 bits) with a mask
	// Swap (shift) bytes
	B0 <<= 24; // left-shift the selected bits by 24, 3/4 of the 32-bit total
	B1 <<= 16; // left-shift the selected bits by 16, 1/2 of the 32-bit total
	B2 <<= 8;  // left-shift the selected bits by 8, 1/4 of the 32-bit total
	B3 <<= 0;  // left-shift the selected bits by 0, 3/4 of the 32-bit total
	// Output
	output = (B0 | B1 | B2 | B3); // combine the values like pieces of a puzzle
	return output;
}