#include <stdio.h>

void fmtstr();

int main()
{
	fmtstr();

	return 0;
}

void fmtstr()
{
	char input[100];
	int  var = 0x11223344;

	// print out information for experimental purposes
	printf("Target address: %x\n", (unsigned) &var);
	printf("Target address data: 0x%x\n", var);

	printf("Enter a string: ");
	fgets(input, sizeof(input) - 1, stdin);

	printf(input); // vulnerable place

	printf("Target address data: 0x%x\n", var);

	return;
}



