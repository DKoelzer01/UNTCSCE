/*
	Daniel Koelzer  -  dlk0138
	CSCE2610.002
	9/16/2021
*/

#include <stdio.h>
#include <stdlib.h>

double userDefPow(float base, int exponent);
unsigned long long int userDefFactorial(int number);

int main() {
	int a = 0;
	float x = 0.0f;
	
	//Prompt user for input values.
	
	printf("Input a positive integer \"a\": ");
	scanf("%d",&a);
	
	printf("Input a floating point value \"x\": ");
	scanf("%f",&x);
	
	double cumulative_sum = 0.0f;
	double numerator = 0.0f;
	unsigned long long int denominator = 0;
	
	//Begin summation. Iterate from 0 to a.
	for(int n = 0; n <= a; n++) {
		numerator = (userDefPow(-1,n) * userDefPow(x,2*n)); //Calculate numerator as (-1)^n * (x)^(2n)
		denominator = userDefFactorial(2*n); // Calculate Denominator as (2n)!. 
		if(n >= 10) { // Values of N greater than 10 are disregarded as (2*10)! is the largest denominator that can be held without overflow.
			printf("A has reached a sufficiently large value. Stopping calculations to avoid 64 bit overflow.\n");
			break;
		} else {
			cumulative_sum += (numerator / denominator); //Add the result of this iteration to the cumulative sum.
		}
	}
	
	printf("Cos(%f) with %d iterations is : %.10f\n",x,a,cumulative_sum); //Print final result.
	
	return 0;
}

double userDefPow(float base, int exponent) { // User defined power function.
	double pow = 1.0; //Initialize pow to 1 to account for x^0 = 1 case and allow for multiplication.
	for(int i = 1; i <= exponent; i++) { // Iterate n times where n is the exponent desired.
			pow *= base; //Multiply the base by the working product n times, where n is the exponent. This results in x * x * x ... * x = x^n
	}
	return pow;
}

unsigned long long int userDefFactorial(int number) { // User defined factorial function.
	unsigned long long int product = 1; // Maximum length integer to store factorial result.
	for(int i = number; i > 0; i--) { // Decrement from target number to 1
		product *= i; // Multiply the working product by i, resulting in N * N-1 * N-2 * ... * N-(N-1) = N!
	}
	return product;
}