    .text                 // program section
	.global	main          // main
	.global power
	.arch armv8-a+fp+simd // processor type
	.type main, %function // main function
	.type power, %function // main function




main: //A and B are stored in X20 and X21, respectively. Store result, Y, in X22.

	MOV X20, #5 //TESTING: Set A to 5
	MOV X21, #3 //TESTING: Set B to 3

	MOV X27, SP
	MOV X9, #0 //i = 0
	MOV X22, #0 //Y = 0
loop:
	CMP X9, X20 //Compare i to a
	BGT exit
	ADD X22, X22, X9 //Add n to sum
	MOV X1, X21 //Move B to x for X^Y
	MOV X2, X9 //Move i (n) to y for X^Y
	BL power
	ADD X22, X22, X0 //Add result of power to sum.
	ADD X9, X9, #1 //i++
	B loop

power: //inputs x and y are in X1 and X2 respectively. Return using X0
	SUB X27, X27, #16
	STUR X9, [X27, #0]
	STUR X10, [X27, #8]
	MOV X9, #0 //Let X9 = i = 0
	MOV X10, #1 // Let X10 = working sum
pow_loop:
	CMP X9, X2 //Check i >= y
	BGE pow_exit
	MUL X10, X10, X1
	ADD X9, X9, #1
	B pow_loop
pow_exit:
	MOV X0, X10
	LDUR X9, [X27, #0]	//Pull all values back from stack.
	LDUR X10, [X27, #8]
	ADD X27, X27, #16 //Move stack pointer back to original pos.
	BR X30 //Return to caller
exit: NOP //NO-OP to allow breakpoint on line 48 for testing.
