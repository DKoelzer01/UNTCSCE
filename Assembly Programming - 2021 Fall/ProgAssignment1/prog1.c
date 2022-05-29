/*
	Daniel Koelzer  -  dlk0138
	CSCE2610.002
	9/16/2021
*/

#include <stdio.h>
#include <stdlib.h>

int userDefPow(int base, int exponent);

int main() {
	int a = 0;
	int b = 0;
	
	printf("Input a positive integer less than 8: ");
	scanf("%d",&a);
	
	printf("Input a second positive integer less than 8: ");
	scanf("%d",&b);
	
	printf("a: %d, b: %d\n",a,b);
	int sum = 0;
	for(int i = 0; i <= a; i++) {
		sum += i;
		sum += userDefPow(b,i);
	}
	
	printf("The summation of the series is : %d\n",sum);
	
	return 0;
}

int userDefPow(int base, int exponent) { // User defined power function.
	int pow = 1; //Initialize pow to 1 to account for x^0 = 1 case and allow for multiplication.
	for(int i = 1; i <= exponent; i++) { // Iterate n times where n is the exponent desired.
			pow *= base; //Multiply the base by the working product n times, where n is the exponent. This results in x * x * x ... * x = x^n
	}
	return pow;
}