//Daniel Koelzer
//dlk0138
//CSCE3600.001 Group 7
//10/14/2021

#include "major1.h"

void parity(unsigned int x)
{
	unsigned int par = 0;
	//Bitwise parity calculation

	par = x ^ (x >> 16); //Divide the 32 bit integer in half repeatedly, using a bitwise XOR to nullify any pairs of matching digits.
	par = par ^ (par >> 8);
	par = par ^ (par >> 4);
	par = par ^ (par >> 2);
	par = par ^ (par >> 1); //Final bit represents parity. If even parity, all 1's should have a pair and cancel out. if odd parity, there will be a remaining 1.
	printf("Parity of %u is %u\n", x, par & 1);
}