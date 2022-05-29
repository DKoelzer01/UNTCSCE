    .text                 // program section
	.global main
	.global pow
	.arch armv8-a+fp+simd // processor type
	.type main, %function
	.type pow, %function

	//Summation of series
	//y = SUM(n=0, a) ((n+b^n)/2)
	//a and b in X20 and S20 respectively
	//Store y in S21
	//write function (pow) to compute u^v

main:
	MOV X20, #5		//TESTER VALUE
	FMOV S20, 2.0	//TESTER VALUE

	MOV X27, SP		//Set X27 to Stack poitner
	MOV X9, #0		//n=0
	FMOV S21, WZR
loop:
	CMP X9, X20				//Compare n to a
	BGT exit				//>, break
	FMOV S1, S20			//Move parameters
	MOV X1, X9
	BL pow					//b^n
	FMOV S9, S0				//Move return value of pow function
	UCVTF S11, X9			//Convert X9 to float
	FADD S9, S9, S11		//n + b^n
	FMOV S11, 2.0			//Move 2.0 to S11 for FDIV
	FDIV S9, S9, S11		//result / 2
	FADD S21, S21, S9		//Add result to total sum
	ADD X9, X9, #1			//Increment n
	B loop
pow:	//u and v in S1 and X1, return using S0
	ADD X27, X27, #16	//Move stack pointer
	STUR X9, [X27, #0]	//Store current values
	STUR S9, [X27, #8]
	MOV X9, #0			//Initialize i = 0
	FMOV S9, 1.0		//Default of u^0 = 1
mulloop:
	CMP X9, X1			//Compare i to v
	BEQ breakloop		//=, break loop
	FMUL S9, S9, S1		//Otherwise, mul u * S9
	ADD X9, X9, #1		//Increment i
	B mulloop			//Loop
breakloop:
	FMOV S0, S9			//Move value to S0
	LDUR X9, [X27, #0]	//Load previous values
	LDUR S9, [X27, #8]
	SUB X27, X27, #16	//Move stack pointer
	BR X30				//Return
exit:
	NOP
