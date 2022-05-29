    .data
    .type	arr, %object
arr:
	.xword  1,2,1,4

    .text                 // program section
	.global	main          // main
	.global max_val
	.arch armv8-a+fp+simd // processor type
	.type main, %function // main function
	.type max_val, %function




main: //Addr in X1, Len in X2, Return in X0

	MOV X20, #4 //DEBUG: Set X20 to number for testing. Arr set to 1,2,1,4 as part of default testing.

	MOV X27, SP
	ADR X9, arr
	MOV X1, X9 //Copy address of Arr into X1
	MOV X2, X20 //Copy value of "n" into X2
	BL max_val //Branch to max_val function
	MOV X21, X0
	B exit

max_val:
	SUB X27, X27, #24 //allocate 3 spaces
	STUR X9, [X27, #0]
	STUR X10, [X27, #8]
	STUR X11, [X27, #16]
	MOV X9, #0 // X9 = i = 0
	MOV X10, #0 // X10 = Working maximum
	MOV X11, #0 // X11 = Temp working value
max_loop: CMP X9, X2 // Check i >= n
	BGE pop //End of array, pop function from stack and return.
	LSL X11, X9, #3 //n * 8 to find offset
	ADD X11, X11, X1 //Absolute address of arr[i]
	LDUR X11, [X11, #0] //Load Arr[i] into X11
	CMP X10, X11 //Check Current Max >= Arr[i]
	ADD X9, X9, #1
	BGE max_loop //If true, loop
	MOV X10, X11 //Otherwise, Max = Arr[i]
	B max_loop
pop:
	MOV X0, X10 //Push max value to X0 to return.
	LDUR X9, [X27, #0]	//Pull all values back from stack.
	LDUR X10, [X27, #8]
	LDUR X11, [X27, #16]
	ADD X27, X27, #24 //Move stack pointer back to original pos.
	BR X30 //Return to caller
exit: NOP
