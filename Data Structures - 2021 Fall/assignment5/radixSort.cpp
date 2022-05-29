/*
Daniel Koelzer
dlk0138
11/16/2021
*/
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*
struct timespec start,stop;
clock_gettime(CLOCK_REALTIME, &start);
clock_gettime(CLOCK_REALTIME, &stop);
std::cout << "TOOK " << (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) << std::endl;
*/

void radixSort(int base,int size, int input[]){
	if(base == 2 || base == 8 || base == 16) {					//Base 2^n calculation using counting sort w/ bit shifts / masking
		int max = 1;											//Max value
		int position = 0;										//Position for shifting / masking
		int output[size] = {0};									//Array for sorting
		int working = 0;										//Working digit
		while (max >> position > 0) {							//Check if there are remaining digits
			working = 0;										//Set working to 0
			int count[base] = {0};								//Initialize count array for # of occurances of each digit
			for(int i = 0; i < size; i++) {						
				if(position == 0 && input[i] > max)				//Check if this is the 1st digit and if current value > max
					max = input[i];								//If true, new max found
				count[(input[i] >> position) & (base-1)]++;		//Increment count of each digit found
			}
			for(int i = 1; i < base; i++) {						
				count[i] += count[i-1];							//Increment each sum by the sum of the previous
			}
			for(int i = size - 1; i >= 0; i--) {				
				working = (input[i] >> position) & (base-1);	//Extract working digit
				output[count[working]-1] = input[i];			//Find count of working digit, subtract one, assign current 
				count[working]--;								//Decrement count of working digit
			}
			for(int i = 0; i < size; i++) {
				input[i] = output[i];				//Pass sorted array to original array
			}
			position += int(log2(base));			//Increment shift amount by log_2 of base
		}
	} else {										//Base 10 calculation using counting sort
		int max = 0;								//Max value
		int digit = 1;								//Current digits place
		int output[size] = {0};						//Temp array for sorting
		int working = 0;							//Current working digit
		while(digit == 1 || (max / digit) > 0){		//Loop until last digit found
			working = 0;							//Reset working
			int count[10] = {0};					//Array to count # of occurances of each
			for(int i = 0; i < size; i++){			
				if(digit == 1 && input[i] > max)	
					max = input[i];					//Find max on first run
				count[(input[i]/digit)%10]++;		//Increment each occurance of a digit
			}
			for(int i = 1; i < 10; i++) {			
				count[i] += count[i-1];				//Increment each sum by the sum of the previous
			}
			for(int i = size - 1; i >= 0; i--) {	
				working = (input[i]/digit)%10;		//Working digit
				output[count[working]-1] = input[i];//Pick output based on the number of occurances of the working digit
				count[working]--;					//Decrement said digit
			}
			for(int i = 0; i < size; i++) {
				input[i] = output[i];				//Pass sorted array to original array
			}
			digit*=10;								//Move on to next digit
		}
	}
}

int main(int argc, char**argv) {
	if(argc == 1) { //Check for arguments passed
		std::cout << "No arguments provided. Please provide 1 argument specifying the desired radix (base).\n";
		return 1;
	}
	int base = std::stoi(argv[1]);					//Base (radix) passed as argument
	srand(time(NULL));								//Initialize srand
	for(int len = 10; len <= 10000; len*=10) {		//Iterate in multiples of 10
		int times[10] = {0};						//Times of 10 runs
		double average = 0;							//Average of 10 runs
		int passTime = 0;							//Time of current run
		for(int j = 1; j < 11; j++) {				//10 Runs, starting at 1 for output formatting
			int arr[len] = {0};						//Int array
			for(int i = 0; i < len; i++){			//Populate array with 10^n elements, depending on current run
				arr[i]=(rand()%10000);				//Random values 0-9999
			}	
			
			if(j == 1) {											//Only on 1st run of each size
			printf("Radix Sort: base = %d size = %d\n",base,len);	
			if(len == 10){											//Only on size 10
				printf("Unsorted:\t");								
				for(int i = 0; i < len; i++) {						
					std::cout << arr[i] << " ";						
				}
				std::cout << std::endl;								
			}
			}
		
			struct timespec start,stop;								//Timing
			clock_gettime(CLOCK_REALTIME, &start);					//Start time
				radixSort(base,len,arr);							//Sort
			clock_gettime(CLOCK_REALTIME, &stop);					//Stop time
		
			passTime = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec); //Calculate time elapsed
			if(len == 10 && j == 1) {								//If 1st run of size 10, print sorted array
				printf("Sorted:\t\t");
				for(int i = 0; i < len; i++) {
					std::cout << arr[i] << " ";
				}
				std::cout << std::endl;
			}
			printf("Pass %d: \t%d\tnanoseconds.\n",j,passTime);		//Print time for this pass
			times[j-1] = passTime;									//Add time to list
			average+=passTime;										//Add time to average
		}
		average/=10;												//Calculate average
		printf("Average: \t%f\tnanoseconds\n\n",average);			//Print average
		
	}
	return 0;
}