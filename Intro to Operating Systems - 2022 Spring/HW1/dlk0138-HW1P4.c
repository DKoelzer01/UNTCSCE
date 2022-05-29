/*
Daniel Koelzer
dlk0138
2/22/2022
CSCE 4600 -- HW 1 Problem 4
Copy files Byte-by-Byte.
*/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <fcntl.h>

FILE * fileA;
FILE * fileB;

char * baseAddressA = "/tmp/dlk0138-4600TMP/fileA"; 		//Location of fileA(1-128). Ensure there are 8 files named fileA1, fileA2, fileA4, ... fileA128 at this directory
char * baseAddressB = "/tmp/dlk0138-4600TMP/fileB";			//Location of fileB. Preferrably located in the same directory as fileA.

char * buffer;

int main (int argc, char **argv) {
	if(argc != 2) {
		printf("Invalid number of arguments. Usage: ./p4 <number of bytes at a time>\n");
		return 0;
	}
	char addr[256];											//Address of file
	double times[8];										//Array of times elapsed
	int timecount = 0;										//Iterator to follow the current run #
	int numBytes = atoi(argv[1]);							//Number of bytes pulled from command line arguments
	for(int i = 1; i < 129; i*=2) {
		sprintf(addr,"%s%d",baseAddressA,i);				//Calculate address of next file
		fileA = fopen(addr,"r+");							//Open next fileA
		remove(baseAddressB); 								//Ensure file B is empty
		fileB = fopen(baseAddressB,"w");					//Open File B for writing.
		printf("Copying %d MB...",i);
		buffer = malloc(numBytes * sizeof(char));           //Allocate buffer size determined by num_bytes argument
		clock_t start = clock();							//Time starts at the beginning of copying
		// START TIME
		
		fseek(fileA,0,SEEK_SET);							//Ensure read/write starts at beginning of file.
		while(1) {
			for(int j = 0; j < numBytes; j++) {				//Read n bytes at a time, where n is the number of bytes specified at the beginning
				buffer[j] = fgetc(fileA);
				if(feof(fileA)) break;						//Exit loop on end of file.
			}
			for(int j = 0; j < numBytes; j++) {
				fputc(buffer[j],fileB);						//Write n bytes at a time.
			}
			if(feof(fileA)) break;							//Exit loop on end of file.
		}
		
		// STOP TIME
		clock_t end = clock();								//Time ends at the end of copying
		printf("Done.\n");
		double timeElapsed = (double)(end - start)/CLOCKS_PER_SEC;	//Calculate elapsed time
		times[timecount] = timeElapsed;						//Register elapsed time in array for display at end.
		fclose(fileA);										//Close files and reset for next iteration
		fclose(fileB);
		timecount++;
	}
	
	printf("Finished.\n");
	printf("================================\n");			//Formatted output
	printf("%d Byte(s) at a time\n",numBytes);
	timecount = 0;
	for(int i = 1; i < 129; i*=2) {
		printf("%3dMB: %.10f seconds.\n",i,times[timecount]);
		timecount++;
	}
}

