/*
Daniel Koelzer
dlk0138
11/16/2021
*/
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <bitset>
#include <time.h>

/*
struct timespec start,stop;
clock_gettime(CLOCK_REALTIME, &start);
clock_gettime(CLOCK_REALTIME, &stop);
std::cout << "TOOK " << (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) << std::endl;
*/

void countSort10(std::vector<int> *input, int size, int exp) {
	int temp[size];
	int i, count[10] = {0};
	for ( i = 0; i < size; i++) {
		count[(input->at(i) / exp) % 10]++;
	}

	for( i = 1; i < 10; i++) {
		count[i] += count[i-1];
	}
	
    for (i = size - 1; i >= 0; i--) {
        temp[count[(input->at(i) / exp) % 10] - 1] = input->at(i);
        count[(input->at(i) / exp) % 10]--;
    }
	
	for ( i = 0; i < size; i++) { 
		input->at(i) = temp[i];
	}
}

void countSortPow2(std::vector<std::string> *input, int size, int shift) {
	std::vector<long> binaryInput;
	
	for(int i = 0; i < size; i++) {
		std::bitset<14> binaryRep(std::stol(input->at(i)));
		binaryInput.push_back(std::stoll(binaryRep.to_string()));
	}
	
	int count[2] = {0};
    int temp[size];
    int i, last;
	for (i = 0; i < size; i++) {
        ++count[(binaryInput[i] >> shift) & 1];
    }
    for (i = last = 0; i < 2; i++) {
        last += count[i];
        count[i] = last - count[i];
    }
    for (i = 0; i < size; i++) {
        temp[count[(binaryInput[i] >> shift) & 1]++] = binaryInput[i];
    }
    for (i = 0; i < size; i++) {
        input->at(i) = std::to_string(temp[i]);
    }
}

void countSortPow8(std::vector<int> *input, int size, int shift) {
	int count[8] = {0};
    int temp[size];
    int i, last;
	for (i = 0; i < size; i++) {
        ++count[(input->at(i) >> shift) & (7)];
    }
    for (i = last = 0; i < 8; i++) {
        last += count[i];
        count[i] = last - count[i];
    }
    for (i = 0; i < size; i++) {
        temp[count[(input->at(i) >> shift) & (7)]++] = input->at(i);
    }
    for (i = 0; i < size; i++) {
        input->at(i) = temp[i];
    }
}

void countSortPow16(std::vector<int> *input, int size, int shift) {
	int count[16] = {0};
    int temp[size];
    int i, last;
	for (i = 0; i < size; i++) {
        ++count[(input->at(i) >> shift) & 15];
    }
    for (i = last = 0; i < 16; i++) {
        last += count[i];
        count[i] = last - count[i];
    }
    for (i = 0; i < size; i++) {
        temp[count[(input->at(i) >> shift) & 15]++] = input->at(i);
    }
    for (i = 0; i < size; i++) {
        input->at(i) = temp[i];
    }
}

void radixSort(int base,int size, std::vector<std::string> *inputString, std::vector<int> *inputInt){
	int maxVal;
	for(int i = 1; i < size; i++)
		maxVal = inputInt->at(i) > maxVal ? inputInt->at(i) : maxVal;
	
	switch(base){
		case(2):
			for(int shift = 0; (maxVal >> shift) > 0; shift += 1) {
				countSortPow2(inputString,size,shift);
			}
			break;
		case(8):
			for(int shift = 0; (maxVal >> shift) > 0; shift += 3) {
				countSortPow8(inputInt,size,shift);
			}
			break;
		case(10):
			for(int digit = 1; maxVal / digit > 0; digit *= 10) {
				countSort10(inputInt,size,digit);
			}
			break;
		case(16):
			for(int shift = 0; (maxVal >> shift) > 0; shift += 4) {
				countSortPow16(inputInt,size,shift);
			}
			break;
		default:
			break;
	}
}

int main(int argc, char**argv) {
	if(argc == 1) {
		std::cout << "No arguments provided. Please provide 1 argument specifying the desired radix (base).\n";
		return 1;
	}
	int base = std::stoi(argv[1]);
	srand(time(NULL));
	for(int len = 10; len <= 10000; len*=10) {
		int times[10] = {0};
		double average = 0;
		int passTime = 0;
		for(int j = 1; j < 11; j++) {
			std::vector<int> arr;
			for(int i = 0; i < len; i++){
				arr.push_back(rand()%10000);
			}	
			std::vector<std::string> arrString;
			for(int i = 0; i < len; i++){
				arrString.push_back(std::to_string(arr[i]));
			}
			
			if(j == 1) {
			printf("Radix Sort: base = %d size = %d\n",base,len);
			if(len == 10){
				printf("Unsorted:\t");
				for(int i = 0; i < 10; i++) {
					std::cout << arr[i] << " ";
				}
				std::cout << std::endl;
			}
			}
		
			struct timespec start,stop;
			clock_gettime(CLOCK_REALTIME, &start);
			radixSort(base,len,&arrString,&arr);
			clock_gettime(CLOCK_REALTIME, &stop);
		
			passTime = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec);
			if(len == 10 && j == 1) {
				printf("Sorted:\t\t");
				for(int i = 0; i < 10; i++) {
					std::cout << arr[i] << " ";
				}
				std::cout << std::endl;
			}
			printf("Pass %d: \t%d\tnanoseconds.\n",j,passTime);
			times[j-1] = passTime;
			average+=passTime;
		}
		average/=10;
		printf("Average: \t%f\tnanoseconds\n\n",average);
		
	}
	return 0;
}