#include "major1.h"

int main()
{
	int userMenuInput = 0;		 //Function choice variable.
	unsigned int userDefInt = 0; //User defined 32 bit int, unsigned.

	int rotate_val;
	while (1) {
		userDefInt = 0;
		userMenuInput = 0;
		while (drawMenu(&userMenuInput, &userDefInt))
			; //Draw menu until valid choice.
		switch (userMenuInput)
		{ //Branch to user-selected function.
		case (1):
			countLeadingZeros(userDefInt); //Replace with leading zeros function.
			break;
		case (2):
			endian(userDefInt);
			// use endian2() for return value
			break;
		case (3):
			//rotate-right
			//if 'rotate right' is selected, prompt for second integer between 0 and 31 (inclusively
			printf("Enter the number of positions to rotate-right the input (between 0 and 31, inclusively): ");
			scanf("%d", &rotate_val);
			while (rotate_val < 0 || rotate_val > 31)
			{
				printf("Enter the number of positions to rotate-right the input (between 0 and 31, inclusively): ");
				scanf("%d", &rotate_val);
			}
			rotateRight(userDefInt, rotate_val);
			break;
		case (4):
			parity(userDefInt);
			break;
		case (5):
			printf("Program terminating. Goodbye...\n");
			return 0;
			break;
		default:
			break;
		}
	}
	return 0;
}

bool drawMenu(int *x, unsigned int *value)
{
	long long int userInput = 0; //32 bit unsigned value. Holding value until valid value is assigned.
	printf("Enter the menu option for the operation to perform:\n");
	printf("(1) Count Leading Zeroes\n");
	printf("(2) Endian Swap\n");
	printf("(3) Rotate-right\n");
	printf("(4) Parity\n");
	printf("(5) EXIT\n");
	printf("--> ");

	scanf("%lld", &userInput);

	if (userInput <= 0 || userInput >= 6)
	{ //Bounds checking
		printf("Error: Invalid option. Please try again.\n");
		return 1;
	}
	
	if (userInput == 5) {
		*x = userInput;
		return 0;
	}
	*x = userInput; //If valid, pass back to userMenuInput. Continue
	userInput = 0;	//Reset user input value.
	while (userInput <= 0 || userInput >= 4294967296)
	{				   //Bounds checking
		userInput = 0; //Reset user Input after evaluating bounds checking.
		printf("Enter a 32-bit number (>= 1 and <= 4294967295, inclusively): ");
		scanf("%lld", &userInput);
	}
	*value = userInput; //Pass value back to userDefInt now that it is valid.
	return 0;			//Break loop, continue program.
}