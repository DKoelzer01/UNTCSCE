/*
	Daniel Koelzer  -  dlk0138
	CSCE3600.002 / CSCE3600.202
	8/30/21
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
	unsigned char userChar;
	int userCharInt;
	char userCharBin[9] = {0};
	printf("Enter an ASCII character: ");
	scanf("%c",&userChar);
	userCharInt = (int)(userChar);

	

	userCharBin[8] = '\0';
	
	printf("The ASCII value of %c is:\n", userChar);
	printf("\t dec -- %i\n",userCharInt);
	printf("\t hex -- %x\n",userCharInt);
	printf("\t bin -- ");
	
	int temp = 0;
	for (int i = 7; i > -1; i--) { // from 7 to 0 inclusive
		temp = userCharInt >> i; //bitshift right by i
		if(temp & 1) { // bitwise AND with 1 to pass value
			printf("1");
		} else {
			printf("0");
		}
	}
	
	printf("\n");
	return 0;
}