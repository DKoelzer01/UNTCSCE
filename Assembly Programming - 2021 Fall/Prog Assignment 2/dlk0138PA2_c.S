	.data
	.type	x,	%object
	.size	x,	64

x:
	.xword	1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,


	.text                 // program section
	.global	main          // main
	.arch armv8-a+fp+simd // processor type
	.type main, %function // main function

main:
	//A, B,C in X20,X21,X22 respectively. Values can be changed to test different cases.
	MOV X20, XZR
	MOV X21, XZR
	MOV X22, XZR

	ADD X20, X20, #2
	ADD X21, X21, #8
	ADD X22, X22, #4

	//X9 will always be the base address of x
	//X10 will be used as the first array value in calculations
	//X12 will be used as the second array value in calculations
	//X11 will be overwritten frequently as a temp variable
	//X13 will be the temporary base address for calculations

	ADR	X9, x

	LDUR X10, [X9, #16] 	//Load x[2] to X10
	ADD X10, X10, #5		//Add 5 to x[2]
	STUR X10, [X9, #24]		//Store x[2] + 5 to x[3]

	LSL X11, X21, #2 		// (b / 2) * 8 = b * 4
	ADD X13, X9, X11		// Calculate new offset base address
	LDUR X10, [X13, #0] 	// load x[b/2] into x10
	LSL X11, X22, #1 		// (c/4) * 8 = c * 2
	ADD X13, X9, X11		// Calculate new offset base address
	LDUR X12, [X13, #0] 	// load x[c/4] into x12
	LSL X11, X20, #4 		// 2 * a * 8 = a * 16
	ADD X10, X10, X12 		// x[b/2] + x[c/4]
	ADD X13, X9, X11		// Calculate new offset base address
	STUR X10, [X13, #0] 	// Store result in x[2*a]

							//2*a is still in X11, 4*a is needed shortly
	LSL X11, X11, #1
	ADD X13, X9, X11		// Calculate new offset base address
	LDUR X10, [X13, #0] 	// Load x[4*a] to X10
	LSR X11, X22, #4 		// c >> 4
	ADD X10, X10, X11		// x[4*a] + (c >> 4)
							//b / 8 * 8 = b, no operation needed to get offset of x[b/8]
	ADD X13, X9, X11		// Calculate new offset base address
	STUR X10, [X13, #0]
