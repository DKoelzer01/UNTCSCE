    .text                 // program section
	.global main
	.global pow
	.global fact
	.arch armv8-a+fp+simd // processor type
	.type main, %function
	.type pow, %function
	.type fact, %function

	//Calculate cos x = SUM (n=0, a) ((-1)^n*x^(2n))/(2n)!)
	//Input X is in D20, a in X20
	//Result in D21
	//x is double between 0.0 and 5.0
	//a is 64-bit non-zero positive int less than 10
	//Compute using double
	//Using pow function from PA5_b
main:
	FMOV D20, 1.0		//TESTER VALUE
	MOV X20, #5			//TESTER VALUE

	MOV X27, SP
	MOV X9, #0			//Set n = 0
	FMOV D21, XZR		//Clear result
loop:
	CMP X9, X20
	BGT exit			//If n > a, break loop
	FMOV D1, -1.0
	MOV X1, X9
	BL pow				//-1^n
	FMOV D9, D0			//Move result to D9
	LSL X10, X9, #1		//2n
	FMOV D1, D20
	MOV X1, X10
	BL pow				//x^(2n)
	FMOV D10, D0		//Move result to D10
	FMUL D9, D10, D9	//(-1)^n * x^(2n)
	MOV X1, X10			//Use previously stored 2n
	BL fact				//(2n)!
	MOV X10, X0			//Move result
	UCVTF D11, X10		//Convert result to double
	FDIV D10, D9, D11	//Compute
	FADD D21, D21, D10	//Add to total sum
	ADD X9, X9, #1		//Increment n by 1
	B loop
pow:					//u and v in D1 and X1, return using S0
	ADD X27, X27, #16	//Move stack pointer
	STUR X9, [X27, #0]	//Store current values
	STUR D9, [X27, #8]
	MOV X9, #0			//Initialize i = 0
	FMOV D9, 1.0		//Default of u^0 = 1
powloop:
	CMP X9, X1			//Compare i to v
	BEQ breakpowloop	//=, break loop
	FMUL D9, D9, D1		//Otherwise, mul u * S9
	ADD X9, X9, #1		//Increment i
	B powloop			//Loop
breakpowloop:
	FMOV D0, D9			//Move value to S0
	LDUR X9, [X27, #0]	//Load previous values
	LDUR D9, [X27, #8]
	SUB X27, X27, #16	//Move stack pointer
	BR X30				//Return

fact:					//Factorial, input x in x1, output in x0
	ADD X27, X27, #16	//Move stack pointer
	STUR X9, [X27, #0]	//Store current values
	STUR X10, [X27, #8]
	MOV X9, X1			//Initialize i = x
	MOV X10, #1			//Initialize sum = 0
factloop:
	CMP X9, XZR			//Compare i to 0
	BEQ breakfactloop		//=, break loop
	MUL X10, X10, X9
	SUB X9, X9, #1
	B factloop			//Loop
breakfactloop:
	MOV X0, X10			//Move value to X0
	LDUR X9, [X27, #0]	//Load previous values
	LDUR X10, [X27, #8]
	SUB X27, X27, #16	//Move stack pointer
	BR X30				//Return

exit:
	NOP
