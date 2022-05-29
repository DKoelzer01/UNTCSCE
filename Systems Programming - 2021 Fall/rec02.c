/*
	Daniel Koelzer  -  dlk0138
	CSCE3600.002 / CSCE3600.202
	9/13/2021
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
	int *int_ptr;
	int_ptr = (int*) malloc(sizeof(int) * 2);
	if(int_ptr == NULL) {
		printf("Memory could not be allocated.\n");
		return 1;
	}
	printf("Enter first integer: ");
	scanf("%d",&int_ptr[0]);
	
	printf("Enter second integer: ");
	scanf("%d",&int_ptr[1]);
	
	printf("Original values: 1st = %16d 2nd = %16d\n",int_ptr[0],int_ptr[1]);
	
	//SWAP
	int_ptr[0] = int_ptr[0] ^ int_ptr[1]; 	
	int_ptr[1] = int_ptr[0] ^ int_ptr[1];	
	int_ptr[0] = int_ptr[0] ^ int_ptr[1];	
	
	printf("Swapped  values: 1st = %16d 2nd = %16d\n",int_ptr[0],int_ptr[1]);
	free(int_ptr);
	return 0;
}