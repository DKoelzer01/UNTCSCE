/*
	Daniel Koelzer  -  dlk0138
	CSCE2610.002
	9/16/2021
*/

#include <stdio.h>
#include <stdlib.h>

unsigned long long int userDefFactorial(int number);

int main() {
	int a = 0;
	int b = 0;
	
	printf("Input a positive integer less than 8: "); // Prompt user for input values.
	scanf("%d",&a);
	
	printf("Input a second positive integer less than 8: ");
	scanf("%d",&b);
	
	printf("a: %d, b: %d\n",a,b);
	unsigned long long int cumulative_sum = 0;
	unsigned long long int partial_sum = 0;
	for(int i = 0; i <= a; i++) {
		partial_sum = 0; 
		partial_sum += i; // partial sum of i + b 
		partial_sum += b;
		cumulative_sum += userDefFactorial(partial_sum); //Find factorial of i+b, add to cumulative sum
		
	}
	printf("The summation of the series is : %llu\n",cumulative_sum);
	
	return 0;
}

unsigned long long int userDefFactorial(int number) { // User defined factorial function.
	unsigned long long int product = 1; // Maximum length integer to store factorial result.
	for(int i = number; i > 0; i--) { // Decrement from target number to 1
		product *= i; // Multiply the working product by i, resulting in N * N-1 * N-2 * ... * N-(N-1) = N!
	}
	return product;
}