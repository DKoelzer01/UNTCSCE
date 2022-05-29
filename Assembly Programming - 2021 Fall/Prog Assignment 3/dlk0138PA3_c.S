    .text                 // program section
	.global cube_sum
	.global main
	.arch armv8-a+fp+simd // processor type
	.type cube_sum, %function
	.type main, %function

main:
	MOV X1, #4 //Tester main
	MOV X27, SP
	BL cube_sum
	B exit

cube_sum: //N in X1.
	ADD X27, X27, #24
	STUR X9, [X27, #0]
	STUR X10, [X27, #8]
	STUR X30, [X27, #16]
	MOV X9, #0 //Let X9 be a temp working value, i = 0
	MOV X10, #0 //Let X10 be the working sum, sum = 0
	MOV X9, X1
	LSL X9, X9, #1 //N * 2
	SUB X9, X9, #1 //(N*2) - 1
	MUL X10, X9, X9 //X9 ^ 2
	MUL X10, X9, X10 //X9 ^ 3
	CMP X1, #1 //Check for end case to cascade back through stack
	BEQ cont
	SUB X1, X1, #1 //N--
	BL cube_sum
	ADD X10, X10, X0 //Add result from next recurrence

cont:
	MOV X0, X10 //Move X10 to X0 to return.
	LDUR X9, [X27, #0]
	LDUR X10, [X27, #8]
	LDUR X30, [X27, #16]
	SUB X27, X27, #24
	BR X30

exit: NOP //NO-OP to allow breakpoint on line 48 for testing.
