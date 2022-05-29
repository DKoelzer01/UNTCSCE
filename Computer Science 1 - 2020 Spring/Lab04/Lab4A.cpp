/* Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
 Date: 2/10/20
 Instructor: Joseph Helsing
 Description: Flow of Control. Read user input for value within range. Check if within range, then compare to random value within same range.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int val,randVal;

int main() {
	printf("Enter a value for x between 10 and 100 inclusive: ");
	scanf("%d",&val);
	if(val < 10 || val > 100){ printf("Your value %i was out of the specified range. \n",val); return(1);}
	//Check if the value is outside of given range. If it is, exit with code "1".
	srand(time(NULL));
	randVal = (rand()%91)+10;
	printf("The random number generated was %d. \n",randVal);
	if(val < randVal) {
		printf("The random number, %d, was greater than your number, %d. \n",randVal,val);
	} else {
		if (val == randVal) {
		printf("The random number, %d, is equal to your number, %d. \n",randVal,val);
		} else if (val > randVal){
		printf("The random number, %d, was less than your number, %d. \n",randVal,val);
		} else {
			printf("Error.");
		}
	}	
	return(0);
}